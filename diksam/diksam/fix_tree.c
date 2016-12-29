#include "stdafx.h"
//#include <math.h>
//#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "diksamc.h"

// 修复标识符表达式
static Expression* fix_identifier_expression(Block *current_block, Expression *expr,
											 Expression *parent){
    Declaration *decl;
    FunctionDefinition *fd;
	// 在当前的语句块内搜寻标识符声明
    decl = dkc_search_declaration(expr->u.identifier.name, current_block);
	// 如果成功找到标识符声明，则将其相关属性传递给expr，并返回expr的地址
    if (decl) {
        expr->type = decl->type;
        expr->u.identifier.is_function = DVM_FALSE;
        expr->u.identifier.u.declaration = decl;
        return expr;
    }
	// 如果没能找到声明的标识符，就在函数中寻找，找到后设定相关属性并返回expr地址
	// 否则编译时报错
    fd = dkc_search_function(expr->u.identifier.name);
    if (fd == NULL) {
        dkc_compile_error(expr->line_number,
                          IDENTIFIER_NOT_FOUND_ERR,
                          STRING_MESSAGE_ARGUMENT, "name",
                          expr->u.identifier.name,
                          MESSAGE_ARGUMENT_END);
    }
    expr->type = fd->type;
    expr->u.identifier.is_function = DVM_TRUE;
    expr->u.identifier.u.function = fd;

    return expr;
}
// 函数前向声明，修复表达式
static Expression *fix_expression(Block *current_block, Expression *expr,
                                  Expression *parent);
// 修复逗号表达式，分别对逗号的左表达式和右表达式进行修复
static Expression* fix_comma_expression(Block *current_block, Expression *expr){
    expr->u.comma.left
        = fix_expression(current_block, expr->u.comma.left, expr);
    expr->u.comma.right
        = fix_expression(current_block, expr->u.comma.right, expr);
	// 逗号表达式的类型为最右边的表达式类型
    expr->type = expr->u.comma.right->type;

    return expr;
}
// 显示类型转换匹配错误消息
static void cast_mismatch_error(int line_number, TypeSpecifier *src, TypeSpecifier *dest){
    char *tmp;
    char *src_name;
    char *dest_name;
	// 获得源类型名称和目的类型名称
    tmp = dkc_get_type_name(src);
    src_name = dkc_strdup(tmp);
    MEM_free(tmp);

    tmp = dkc_get_type_name(dest);
    dest_name = dkc_strdup(tmp);
    MEM_free(tmp);

    dkc_compile_error(line_number,
                      CAST_MISMATCH_ERR,
                      STRING_MESSAGE_ARGUMENT, "src", src_name,
                      STRING_MESSAGE_ARGUMENT, "dest", dest_name,
                      MESSAGE_ARGUMENT_END);
}
// 为类型转换表达式分配空间，并返回初始化后的类型转换表达式
static Expression* alloc_cast_expression(CastType cast_type, Expression *operand){
    Expression *cast_expr = dkc_alloc_expression(CAST_EXPRESSION);
    cast_expr->line_number = operand->line_number;
    cast_expr->u.cast.type = cast_type;
    cast_expr->u.cast.operand = operand;

    if (cast_type == INT_TO_DOUBLE_CAST) {
        cast_expr->type = dkc_alloc_type_specifier(DVM_DOUBLE_TYPE);
    } else if (cast_type == DOUBLE_TO_INT_CAST) {
        cast_expr->type = dkc_alloc_type_specifier(DVM_INT_TYPE);
    } else if (cast_type == BOOLEAN_TO_STRING_CAST
               || cast_type == INT_TO_STRING_CAST
               || cast_type == DOUBLE_TO_STRING_CAST) {
        cast_expr->type = dkc_alloc_type_specifier(DVM_STRING_TYPE);
    }

    return cast_expr;
}
// 创建赋值转换
static Expression* create_assign_cast(Expression *src, TypeSpecifier *dest){
	Expression *cast_expr;
	// 比较源与目的的类型，如果相同则直接返回src
	if (dkc_compare_type(src->type, dest)) {
		return src;
	}
	// 如果目的类型为object，并且源类型为null，则直接返回src
	if (dkc_is_object(dest) && src->type->basic_type == DVM_NULL_TYPE) {
		DBG_assert(src->type->derive == NULL, ("derive != NULL"));
		return src;
	}
	// int向double赋值，应将src转换为double
	if (src->type->basic_type == DVM_INT_TYPE && dest->basic_type == DVM_DOUBLE_TYPE) {
		cast_expr = alloc_cast_expression(INT_TO_DOUBLE_CAST, src);
		return cast_expr;
	}
	// double向int赋值，应将src转换为src
	else if (src->type->basic_type == DVM_DOUBLE_TYPE && dest->basic_type == DVM_INT_TYPE) {
		cast_expr = alloc_cast_expression(DOUBLE_TO_INT_CAST, src);
		return cast_expr;
	}
	else {
		// 否则类型转换出错
		cast_mismatch_error(src->line_number, src->type, dest);
	}
	return NULL; /* make compiler happy. */
}
// 修复赋值表达式
static Expression* fix_assign_expression(Block *current_block, Expression *expr){
    Expression *operand;
	// 必须确保赋值号的左部位左值（标识符表达式或者数组的索引表达式）
    if (expr->u.assign_expression.left->kind != IDENTIFIER_EXPRESSION
        && expr->u.assign_expression.left->kind != INDEX_EXPRESSION) {
        dkc_compile_error(expr->u.assign_expression.left->line_number,
                          NOT_LVALUE_ERR, MESSAGE_ARGUMENT_END);
    }
	// 分别对赋值表达式左部和右部进行修复
    expr->u.assign_expression.left
        = fix_expression(current_block, expr->u.assign_expression.left,
                         expr);
    operand = fix_expression(current_block, expr->u.assign_expression.operand,
                             expr);
	// 将赋值表达式的右端转换为左部的类型
    expr->u.assign_expression.operand
        = create_assign_cast(operand, expr->u.assign_expression.left->type);
    // 表达式的类型为左部的类型
	expr->type = expr->u.assign_expression.left->type;

    return expr;
}
// 评估int型的数学表达式，返回表示加法结果的表达式
static Expression* eval_math_expression_int(Expression *expr, int left, int right){
    // 加法
	if (expr->kind == ADD_EXPRESSION) {
        expr->u.int_value = left + right;
    } 
	// 减法
	else if (expr->kind == SUB_EXPRESSION) {
        expr->u.int_value = left - right;
    }
	// 乘法
	else if (expr->kind == MUL_EXPRESSION) {
        expr->u.int_value = left * right;
    }
	// 除法
	else if (expr->kind == DIV_EXPRESSION) {
        if (right == 0) {
            dkc_compile_error(expr->line_number,
                              DIVISION_BY_ZERO_IN_COMPILE_ERR,
                              MESSAGE_ARGUMENT_END);
        }
        expr->u.int_value = left / right;
    }
	// 取余
	else if (expr->kind == MOD_EXPRESSION) {
        expr->u.int_value = left % right;
    } else {
        DBG_assert(0, ("expr->kind..%d\n", expr->kind));
    }
    expr->kind = INT_EXPRESSION;
    expr->type = dkc_alloc_type_specifier(DVM_INT_TYPE);

    return expr;
}
// 评估double型的数学表达式，同int版本
static Expression* eval_math_expression_double(Expression *expr, double left, double right){
	if (expr->kind == ADD_EXPRESSION) {
        expr->u.double_value = left + right;
    } else if (expr->kind == SUB_EXPRESSION) {
        expr->u.double_value = left - right;
    } else if (expr->kind == MUL_EXPRESSION) {
        expr->u.double_value = left * right;
    } else if (expr->kind == DIV_EXPRESSION) {
        expr->u.double_value = left / right;
    } else if (expr->kind == MOD_EXPRESSION) {
        expr->u.double_value = fmod(left, right);
    } else {
        DBG_assert(0, ("expr->kind..%d\n", expr->kind));
    }
    expr->kind = DOUBLE_EXPRESSION;
    expr->type = dkc_alloc_type_specifier(DVM_DOUBLE_TYPE);

    return expr;
}
// 字符串加法，二元字符串运算，将两个字符串连接后返回新的字符串表达式
static Expression* chain_string(Expression *expr){
    DVM_Char *left_str = expr->u.binary_expression.left->u.string_value;
    DVM_Char *right_str;
    int         len;
    DVM_Char    *new_str;
	// 将右边表达式转换为字符串
	// 字符串加法支持右边操作数为表达式
    right_str = dkc_expression_to_string(expr->u.binary_expression.right);
    // 如果右边的表达式无法转换为字符串，则直接返回
	if (!right_str) {
        return expr;
    }
    // 获得新的字符串的长度
    len = dvm_wcslen(left_str) + dvm_wcslen(right_str);
    new_str = MEM_malloc(sizeof(DVM_Char) * (len + 1));
    dvm_wcscpy(new_str, left_str);
    dvm_wcscat(new_str, right_str);
    MEM_free(left_str);
    MEM_free(right_str);
    expr->kind = STRING_EXPRESSION;
    expr->type = dkc_alloc_type_specifier(DVM_STRING_TYPE);
    expr->u.string_value = new_str;

    return expr;
}
// 评估数学表达式
static Expression* eval_math_expression(Block *current_block, Expression *expr){
	// 两边的类型都是int
    if (expr->u.binary_expression.left->kind == INT_EXPRESSION
        && expr->u.binary_expression.right->kind == INT_EXPRESSION) {
        expr = eval_math_expression_int(expr,
                                        expr->u.binary_expression.left
                                        ->u.int_value,
                                        expr->u.binary_expression.right
                                        ->u.int_value);
    } 
	// 两边的类型都是double
	else if (expr->u.binary_expression.left->kind == DOUBLE_EXPRESSION
               && expr->u.binary_expression.right->kind == DOUBLE_EXPRESSION) {
        expr = eval_math_expression_double(expr,
                                           expr->u.binary_expression.left
                                           ->u.double_value,
                                           expr->u.binary_expression.right
                                           ->u.double_value);

    }
	// 左边是int，右边是double
	else if (expr->u.binary_expression.left->kind == INT_EXPRESSION
               && expr->u.binary_expression.right->kind == DOUBLE_EXPRESSION) {
        expr = eval_math_expression_double(expr,
                                           expr->u.binary_expression.left
                                           ->u.int_value,
                                           expr->u.binary_expression.right
                                           ->u.double_value);

    }
	// 左边是double，右边是int
	else if (expr->u.binary_expression.left->kind == DOUBLE_EXPRESSION
               && expr->u.binary_expression.right->kind == INT_EXPRESSION) {
        expr = eval_math_expression_double(expr,
                                           expr->u.binary_expression.left
                                           ->u.double_value,
                                           expr->u.binary_expression.right
                                           ->u.int_value);

    }
	// 字符串连接
	else if (expr->u.binary_expression.left->kind == STRING_EXPRESSION
               && expr->kind == ADD_EXPRESSION) {
        expr = chain_string(expr);
    }

    return expr;
}
// 二元表达式的类型转换
static Expression* cast_binary_expression(Expression *expr){
	Expression *cast_expression;
	// 左边是int，右边是double，应将左边的int转换为double
	if (dkc_is_int(expr->u.binary_expression.left->type)
		&& dkc_is_double(expr->u.binary_expression.right->type)) {
		cast_expression
			= alloc_cast_expression(INT_TO_DOUBLE_CAST,
			expr->u.binary_expression.left);
		expr->u.binary_expression.left = cast_expression;

	}
	// 左边是double，右边是int，应将右边的int转换为double
	else if (dkc_is_double(expr->u.binary_expression.left->type)
		&& dkc_is_int(expr->u.binary_expression.right->type)) {
		cast_expression
			= alloc_cast_expression(INT_TO_DOUBLE_CAST,
			expr->u.binary_expression.right);
		expr->u.binary_expression.right = cast_expression;

	}
	// 左边是字符串，右边是bool，应将右边的bool转换为字符串
	else if (dkc_is_string(expr->u.binary_expression.left->type)
		&& dkc_is_boolean(expr->u.binary_expression.right->type)) {
		cast_expression
			= alloc_cast_expression(BOOLEAN_TO_STRING_CAST,
			expr->u.binary_expression.right);
		expr->u.binary_expression.right = cast_expression;

	}
	// 左边是字符串，右边是int，应将右边的int转换为字符串
	else if (dkc_is_string(expr->u.binary_expression.left->type)
		&& dkc_is_int(expr->u.binary_expression.right->type)) {
		cast_expression
			= alloc_cast_expression(INT_TO_STRING_CAST,
			expr->u.binary_expression.right);
		expr->u.binary_expression.right = cast_expression;

	}
	// 左边是字符串，右边是double，应将右边的double转换为字符串
	else if (dkc_is_string(expr->u.binary_expression.left->type)
		&& dkc_is_double(expr->u.binary_expression.right->type)) {
		cast_expression
			= alloc_cast_expression(DOUBLE_TO_STRING_CAST,
			expr->u.binary_expression.right);
		expr->u.binary_expression.right = cast_expression;
	}

	return expr;
}
// 修复二元数学表达式
static Expression* fix_math_binary_expression(Block *current_block, Expression *expr){
    // 分别修复二元表达式的左边和右边的表达式
	expr->u.binary_expression.left
        = fix_expression(current_block, expr->u.binary_expression.left,
                         expr);
    expr->u.binary_expression.right
        = fix_expression(current_block, expr->u.binary_expression.right,
                         expr);
	// 评估数学表达式
    expr = eval_math_expression(current_block, expr);
	// 如果评估结果为int，double，string类型之一，直接将结果返回
    if (expr->kind == INT_EXPRESSION || expr->kind == DOUBLE_EXPRESSION
        || expr->kind == STRING_EXPRESSION) {
        return expr;
    }
	// 如果不是则需要对结果进行类型转换
    expr = cast_binary_expression(expr);
	// 左右都为int
    if (dkc_is_int(expr->u.binary_expression.left->type)
        && dkc_is_int(expr->u.binary_expression.right->type)) {
        expr->type = dkc_alloc_type_specifier(DVM_INT_TYPE);
    } 
	// 左右都为double
	else if (dkc_is_double(expr->u.binary_expression.left->type)
               && dkc_is_double(expr->u.binary_expression.right->type)) {
        expr->type = dkc_alloc_type_specifier(DVM_DOUBLE_TYPE);
    }
	// 字符串分为两种情况，左右都为字符串或者左边为字符串右边为null
	else if (expr->kind == ADD_EXPRESSION
               && ((dkc_is_string(expr->u.binary_expression.left->type)
                    && dkc_is_string(expr->u.binary_expression.right->type))
                   || (dkc_is_string(expr->u.binary_expression.left->type)
                       && expr->u.binary_expression.right->kind
                       == NULL_EXPRESSION))) {
        expr->type = dkc_alloc_type_specifier(DVM_STRING_TYPE);
    } else {
        dkc_compile_error(expr->line_number,
                          MATH_TYPE_MISMATCH_ERR,
                          MESSAGE_ARGUMENT_END);
    }

    return expr;
}
// 评估bool类型比较表达式
static Expression* eval_compare_expression_boolean(Expression *expr,
	DVM_Boolean left, DVM_Boolean right){
	// 相等
	if (expr->kind == EQ_EXPRESSION) {
		expr->u.boolean_value = (left == right);
	}
	// 不等
	else if (expr->kind == NE_EXPRESSION) {
		expr->u.boolean_value = (left != right);
	}
	else {
		DBG_assert(0, ("expr->kind..%d\n", expr->kind));
	}

	expr->kind = BOOLEAN_EXPRESSION;
	expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);

	return expr;
}
// 评估int型比较表达式
static Expression* eval_compare_expression_int(Expression *expr, int left, int right){
    if (expr->kind == EQ_EXPRESSION) {
        expr->u.boolean_value = (left == right);
    } else if (expr->kind == NE_EXPRESSION) {
        expr->u.boolean_value = (left != right);
    } else if (expr->kind == GT_EXPRESSION) {
        expr->u.boolean_value = (left > right);
    } else if (expr->kind == GE_EXPRESSION) {
        expr->u.boolean_value = (left >= right);
    } else if (expr->kind == LT_EXPRESSION) {
        expr->u.boolean_value = (left < right);
    } else if (expr->kind == LE_EXPRESSION) {
        expr->u.boolean_value = (left <= right);
    } else {
        DBG_assert(0, ("expr->kind..%d\n", expr->kind));
    }

    expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);
    expr->kind = BOOLEAN_EXPRESSION;

    return expr;
}
// 评估double型比较表达式
static Expression* eval_compare_expression_double(Expression *expr, int left, int right){
    if (expr->kind == EQ_EXPRESSION) {
        expr->u.boolean_value = (left == right);
    } else if (expr->kind == NE_EXPRESSION) {
        expr->u.boolean_value = (left != right);
    } else if (expr->kind == GT_EXPRESSION) {
        expr->u.boolean_value = (left > right);
    } else if (expr->kind == GE_EXPRESSION) {
        expr->u.boolean_value = (left >= right);
    } else if (expr->kind == LT_EXPRESSION) {
        expr->u.boolean_value = (left < right);
    } else if (expr->kind == LE_EXPRESSION) {
        expr->u.boolean_value = (left <= right);
    } else {
        DBG_assert(0, ("expr->kind..%d\n", expr->kind));
    } 

    expr->kind = BOOLEAN_EXPRESSION;
    expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);

    return expr;
}
// 评估字符串比较表达式
static Expression* eval_compare_expression_string(Expression *expr,
	DVM_Char *left, DVM_Char *right){
	int cmp;
	// 内部以宽字符来处理所有字符串
	cmp = dvm_wcscmp(left, right);

	if (expr->kind == EQ_EXPRESSION) {
		expr->u.boolean_value = (cmp == 0);
	}
	else if (expr->kind == NE_EXPRESSION) {
		expr->u.boolean_value = (cmp != 0);
	}
	else if (expr->kind == GT_EXPRESSION) {
		expr->u.boolean_value = (cmp > 0);
	}
	else if (expr->kind == GE_EXPRESSION) {
		expr->u.boolean_value = (cmp >= 0);
	}
	else if (expr->kind == LT_EXPRESSION) {
		expr->u.boolean_value = (cmp < 0);
	}
	else if (expr->kind == LE_EXPRESSION) {
		expr->u.boolean_value = (cmp <= 0);
	}
	else {
		DBG_assert(0, ("expr->kind..%d\n", expr->kind));
	}

	MEM_free(left);
	MEM_free(right);

	expr->kind = BOOLEAN_EXPRESSION;
	expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);

	return expr;
}
// 评估比较表达式
static Expression* eval_compare_expression(Expression *expr){
	// 左右都是bool
	if (expr->u.binary_expression.left->kind == BOOLEAN_EXPRESSION
		&& expr->u.binary_expression.right->kind == BOOLEAN_EXPRESSION) {
		expr = eval_compare_expression_boolean(expr,
			expr->u.binary_expression.left
			->u.boolean_value,
			expr->u.binary_expression.right
			->u.boolean_value);

	}
	// 左右都是int
	else if (expr->u.binary_expression.left->kind == INT_EXPRESSION
		&& expr->u.binary_expression.right->kind == INT_EXPRESSION) {
		expr = eval_compare_expression_int(expr,
			expr->u.binary_expression.left
			->u.int_value,
			expr->u.binary_expression.right
			->u.int_value);

	}
	// 左右都是double
	else if (expr->u.binary_expression.left->kind == DOUBLE_EXPRESSION
		&& expr->u.binary_expression.right->kind == DOUBLE_EXPRESSION) {
		expr = eval_compare_expression_double(expr,
			expr->u.binary_expression.left
			->u.double_value,
			expr->u.binary_expression.right
			->u.double_value);

	}
	// 左边是int，右边是double
	else if (expr->u.binary_expression.left->kind == INT_EXPRESSION
		&& expr->u.binary_expression.right->kind == DOUBLE_EXPRESSION) {
		expr = eval_compare_expression_double(expr,
			expr->u.binary_expression.left
			->u.int_value,
			expr->u.binary_expression.right
			->u.double_value);

	}
	// 左边是double，右边是int
	else if (expr->u.binary_expression.left->kind == DOUBLE_EXPRESSION
		&& expr->u.binary_expression.right->kind == INT_EXPRESSION) {
		expr = eval_compare_expression_double(expr,
			expr->u.binary_expression.left
			->u.double_value,
			expr->u.binary_expression.right
			->u.int_value);

	}
	// 左右都是字符串
	else if (expr->u.binary_expression.left->kind == STRING_EXPRESSION
		&& expr->u.binary_expression.right->kind == STRING_EXPRESSION) {
		expr = eval_compare_expression_string(expr,
			expr->u.binary_expression.left
			->u.string_value,
			expr->u.binary_expression.right
			->u.string_value);
	}
	// 左右都是null
	else if (expr->u.binary_expression.left->kind == NULL_EXPRESSION
		&& expr->u.binary_expression.right->kind == NULL_EXPRESSION) {
		expr->kind = BOOLEAN_EXPRESSION;
		expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);
		expr->u.boolean_value = DVM_TRUE;
	}
	return expr;
}
// 修复比较表达式
static Expression* fix_compare_expression(Block *current_block, Expression *expr){
	// 分别对比较表达式的左表达式和右表达式进行修复
	expr->u.binary_expression.left
		= fix_expression(current_block, expr->u.binary_expression.left,
		expr);
	expr->u.binary_expression.right
		= fix_expression(current_block, expr->u.binary_expression.right,
		expr);
	// 评估比较表达式，如果结果是bool类型，则直接返回结果
	expr = eval_compare_expression(expr);
	if (expr->kind == BOOLEAN_EXPRESSION) {
		return expr;
	}
	// 否则需要类型转换
	expr = cast_binary_expression(expr);
	// 如果左右两边的类型仍然不想等，或者左边为object而右边为null
	// 或者右边为object左边为null，此时需要报编译时错误，比较类型错误
	if (!(dkc_compare_type(expr->u.binary_expression.left->type,
		expr->u.binary_expression.right->type)
		|| (dkc_is_object(expr->u.binary_expression.left->type)
		&& expr->u.binary_expression.right->kind == NULL_EXPRESSION)
		|| (dkc_is_object(expr->u.binary_expression.right->type)
		&& expr->u.binary_expression.left->kind == NULL_EXPRESSION))) {
		dkc_compile_error(expr->line_number,
			COMPARE_TYPE_MISMATCH_ERR,
			MESSAGE_ARGUMENT_END);
	}
	expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);

	return expr;
}
// 修复逻辑与和逻辑或表达式
static Expression* fix_logical_and_or_expression(Block *current_block, Expression *expr){
    // 分别修复二元表达式的左和右表达式
	expr->u.binary_expression.left
        = fix_expression(current_block, expr->u.binary_expression.left,
                         expr);
    expr->u.binary_expression.right
        = fix_expression(current_block, expr->u.binary_expression.right,
                         expr);
    // 左和右表达式必须都为bool
    if (dkc_is_boolean(expr->u.binary_expression.left->type)
        && dkc_is_boolean(expr->u.binary_expression.right->type)) {
        expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);
    } else {
        dkc_compile_error(expr->line_number,
                          LOGICAL_TYPE_MISMATCH_ERR,
                          MESSAGE_ARGUMENT_END);
    }

    return expr;
}
// 修复取负数表达式
static Expression* fix_minus_expression(Block *current_block, Expression *expr){
	// 修复表达式
	expr->u.minus_expression
		= fix_expression(current_block, expr->u.minus_expression, expr);
	// 只能对int或double取负值
	if (!dkc_is_int(expr->u.minus_expression->type)
		&& !dkc_is_double(expr->u.minus_expression->type)) {
		dkc_compile_error(expr->line_number,
			MINUS_TYPE_MISMATCH_ERR,
			MESSAGE_ARGUMENT_END);
	}
	expr->type = expr->u.minus_expression->type;
	// 实际的取负运算
	if (expr->u.minus_expression->kind == INT_EXPRESSION) {
		expr->kind = INT_EXPRESSION;
		expr->u.int_value = -expr->u.minus_expression->u.int_value;

	}
	else if (expr->u.minus_expression->kind == DOUBLE_EXPRESSION) {
		expr->kind = DOUBLE_EXPRESSION;
		expr->u.double_value = -expr->u.minus_expression->u.double_value;
	}


	return expr;
}
// 修复逻辑取反表达式
static Expression* fix_logical_not_expression(Block *current_block, Expression *expr){
	// 修复表达式
	expr->u.logical_not
		= fix_expression(current_block, expr->u.logical_not, expr);
	// 实际取反操作
	if (expr->u.logical_not->kind == BOOLEAN_EXPRESSION) {
		expr->kind = BOOLEAN_EXPRESSION;
		expr->u.boolean_value = !expr->u.logical_not->u.boolean_value;
		return expr;
	}
	// 取反的运算数必须为bool
	if (!dkc_is_boolean(expr->u.logical_not->type)) {
		dkc_compile_error(expr->line_number,
			LOGICAL_NOT_TYPE_MISMATCH_ERR,
			MESSAGE_ARGUMENT_END);
	}

	expr->type = expr->u.logical_not->type;

	return expr;
}
// 检查实参
static void check_argument(Block *current_block, FunctionDefinition *fd, Expression *expr){
	// 形参
	ParameterList *param;
	// 实参
	ArgumentList *arg;

	for (param = fd->parameter, arg = expr->u.function_call_expression.argument;
		// 确保实参和形参数量一致
		param && arg;
	param = param->next, arg = arg->next) {
		// 修复实参表达式
		arg->expression
			= fix_expression(current_block, arg->expression, expr);
		// 创建赋值转换
		// 如果实参和形参类型不同，并且实参可以向形参转换类型的话
		// 要执行类型转换
		arg->expression
			= create_assign_cast(arg->expression, param->type);
	}
	// 判断实参和形参数量是否一致
	if (param || arg) {
		dkc_compile_error(expr->line_number,
			ARGUMENT_COUNT_MISMATCH_ERR,
			MESSAGE_ARGUMENT_END);
	}
}
// 修复函数调用表达式
static Expression* fix_function_call_expression(Block *current_block, Expression *expr){
	Expression *func_expr;
	FunctionDefinition *fd;
	// 修复函数调用表达式
	func_expr = fix_expression(current_block,
		expr->u.function_call_expression.function,
		expr);
	// 如果修复结果不是标识符类型的话，报错
	if (func_expr->kind != IDENTIFIER_EXPRESSION) {
		dkc_compile_error(expr->line_number,
			FUNCTION_NOT_IDENTIFIER_ERR,
			MESSAGE_ARGUMENT_END);
	}
	// 根据函数名搜寻函数
	fd = dkc_search_function(func_expr->u.identifier.name);
	// 如果没有找到，则报编译时错误
	if (fd == NULL) {
		dkc_compile_error(expr->line_number,
			FUNCTION_NOT_FOUND_ERR,
			STRING_MESSAGE_ARGUMENT, "name",
			func_expr->u.identifier.name,
			MESSAGE_ARGUMENT_END);
	}
	// 检查函数实参
	check_argument(current_block, fd, expr);

	expr->type = dkc_alloc_type_specifier(fd->type->basic_type);
	expr->type->derive = fd->type->derive;

	return expr;
}
// 修复数组字面值表达式
static Expression* fix_array_literal_expression(Block *current_block, Expression *expr){
	ExpressionList *literal = expr->u.array_literal;
	TypeSpecifier *elem_type;
	ExpressionList *epos;
	// 如果字面值表达式为空，则报编译时错误
	if (literal == NULL) {
		dkc_compile_error(expr->line_number,
			ARRAY_LITERAL_EMPTY_ERR,
			MESSAGE_ARGUMENT_END);
	}
	// 修复字面值表达式
	literal->expression = fix_expression(current_block, literal->expression,
		expr);
	// 数组字面值类型
	elem_type = literal->expression->type;
	// 遍历数组字面值表达式链表并修复每一个表达式
	for (epos = literal->next; epos; epos = epos->next) {
		epos->expression = fix_expression(current_block, epos->expression, expr);
		// 创建赋值表达式
		epos->expression = create_assign_cast(epos->expression, elem_type);
	}

	expr->type = dkc_alloc_type_specifier(elem_type->basic_type);
	expr->type->derive = dkc_alloc_type_derive(ARRAY_DERIVE);
	expr->type->derive->next = elem_type->derive;

	return expr;
}
// 修复索引表达式
static Expression* fix_index_expression(Block *current_block, Expression *expr){
	IndexExpression *ie = &expr->u.index_expression;
	// 分别修复索引表达式中的数组表达式和索引表达式
	ie->array = fix_expression(current_block, ie->array, expr);
	ie->index = fix_expression(current_block, ie->index, expr);
	// 如果索引表达式的标志无效
	if (ie->array->type->derive == NULL
		|| ie->array->type->derive->tag != ARRAY_DERIVE) {
		dkc_compile_error(expr->line_number,
			INDEX_LEFT_OPERAND_NOT_ARRAY_ERR,
			MESSAGE_ARGUMENT_END);
	}
	// 索引必须为int
	if (!dkc_is_int(ie->index->type)) {
		dkc_compile_error(expr->line_number,
			INDEX_NOT_INT_ERR,
			MESSAGE_ARGUMENT_END);
	}
	expr->type = dkc_alloc_type_specifier(ie->array->type->basic_type);
	// 意义不明
	expr->type->derive = ie->array->type->derive->next;

	return expr;
}
// 修复自增和自减表达式
static Expression* fix_inc_dec_expression(Block *current_block, Expression *expr){
	// 修复自增自减晕算数表达式
	expr->u.inc_dec.operand
		= fix_expression(current_block, expr->u.inc_dec.operand, expr);
	// 自增自减的运算数必须为int
	if (!dkc_is_int(expr->u.inc_dec.operand->type)) {
		dkc_compile_error(expr->line_number,
			INC_DEC_TYPE_MISMATCH_ERR,
			MESSAGE_ARGUMENT_END);
	}
	expr->type = expr->u.inc_dec.operand->type;

	return expr;
}
// 修复数组创建表达式
static Expression* fix_array_creation_expression(Block *current_block, Expression *expr){
	// 数组维数
	ArrayDimension *dim_pos;
	// 类型继承
	TypeDerive *derive = NULL;
	TypeDerive *tmp_derive;
	// 遍历数组维数的表达式，如果表达式存在，则修复，并且数组维数表达式必须为int
	for (dim_pos = expr->u.array_creation.dimension; dim_pos; dim_pos = dim_pos->next) {
		if (dim_pos->expression) {
			dim_pos->expression = fix_expression(current_block, dim_pos->expression, expr);
			if (!dkc_is_int(dim_pos->expression->type)) {
				dkc_compile_error(expr->line_number,
					ARRAY_SIZE_NOT_INT_ERR,
					MESSAGE_ARGUMENT_END);
			}
		}
		tmp_derive = dkc_alloc_type_derive(ARRAY_DERIVE);
		// 将当前类型继承的前插入类型继承链表
		// 意义不明
		tmp_derive->next = derive;
		derive = tmp_derive;
	}

	expr->type
		= dkc_alloc_type_specifier(expr->u.array_creation.type->basic_type);
	// 继承链表意义不明
	expr->type->derive = derive;

	return expr;
}
// 修复表达式
static Expression* fix_expression(Block *current_block, Expression *expr, Expression *parent){
	if (expr == NULL)
		return NULL;
	// 根据表达式种类进行操作
	switch (expr->kind) {
	case BOOLEAN_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_BOOLEAN_TYPE);
		break;
	case INT_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_INT_TYPE);
		break;
	case DOUBLE_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_DOUBLE_TYPE);
		break;
	case STRING_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_STRING_TYPE);
		break;
		// 修复标识符表达式
	case IDENTIFIER_EXPRESSION:
		expr = fix_identifier_expression(current_block, expr, parent);
		break;
		// 修复逗号表达式
	case COMMA_EXPRESSION:
		expr = fix_comma_expression(current_block, expr);
		break;
		// 修复赋值表达式
	case ASSIGN_EXPRESSION:
		expr = fix_assign_expression(current_block, expr);
		break;
		// 修复二元数学运算表达式
	case ADD_EXPRESSION:        /* FALLTHRU */
	case SUB_EXPRESSION:        /* FALLTHRU */
	case MUL_EXPRESSION:        /* FALLTHRU */
	case DIV_EXPRESSION:        /* FALLTHRU */
	case MOD_EXPRESSION:        /* FALLTHRU */
		expr = fix_math_binary_expression(current_block, expr);
		break;
		// 修复比较表达式
	case EQ_EXPRESSION: /* FALLTHRU */
	case NE_EXPRESSION: /* FALLTHRU */
	case GT_EXPRESSION: /* FALLTHRU */
	case GE_EXPRESSION: /* FALLTHRU */
	case LT_EXPRESSION: /* FALLTHRU */
	case LE_EXPRESSION: /* FALLTHRU */
		expr = fix_compare_expression(current_block, expr);
		break;
		// 修复逻辑与和逻辑或表达式
	case LOGICAL_AND_EXPRESSION:        /* FALLTHRU */
	case LOGICAL_OR_EXPRESSION:         /* FALLTHRU */
		expr = fix_logical_and_or_expression(current_block, expr);
		break;
		// 修复取负表达式
	case MINUS_EXPRESSION:
		expr = fix_minus_expression(current_block, expr);
		break;
		// 修复取反表达式
	case LOGICAL_NOT_EXPRESSION:
		expr = fix_logical_not_expression(current_block, expr);
		break;
		// 修复函数调用表达式
	case FUNCTION_CALL_EXPRESSION:
		expr = fix_function_call_expression(current_block, expr);
		break;
	case MEMBER_EXPRESSION:
		break;
	case NULL_EXPRESSION:
		expr->type = dkc_alloc_type_specifier(DVM_NULL_TYPE);
		break;
		// 修复数组字面值表达式
	case ARRAY_LITERAL_EXPRESSION:
		expr = fix_array_literal_expression(current_block, expr);
		break;
		// 修复索引表达式
	case INDEX_EXPRESSION:
		expr = fix_index_expression(current_block, expr);
		break;
		// 修复自增和自减表达式
	case INCREMENT_EXPRESSION:  /* FALLTHRU */
	case DECREMENT_EXPRESSION:
		expr = fix_inc_dec_expression(current_block, expr);
		break;
	case CAST_EXPRESSION:
		break;
		// 修复数组创建表达式
	case ARRAY_CREATION_EXPRESSION:
		expr = fix_array_creation_expression(current_block, expr);
		break;
	case EXPRESSION_KIND_COUNT_PLUS_1:
		break;
	default:
		DBG_assert(0, ("bad case. kind..%d\n", expr->kind));
	}

	return expr;
}
// 在函数中添加局部变量
static void add_local_variable(FunctionDefinition *fd, Declaration *decl){
	// 为函数内的局部变量声明重新分配内存
	fd->local_variable
		= MEM_realloc(fd->local_variable,
		sizeof(Declaration*) * (fd->local_variable_count + 1));
	// 将新的局部变量加入局部变量中
	fd->local_variable[fd->local_variable_count] = decl;
	// 设定该局部变量的索引，增加函数内的局部变量计数
	decl->variable_index = fd->local_variable_count;
	fd->local_variable_count++;
}
// 函数前向声明，修复语句链表
static void fix_statement_list(Block *current_block, StatementList *list,
                               FunctionDefinition *fd);
// 修复if语句
static void fix_if_statement(Block *current_block, IfStatement *if_s, FunctionDefinition *fd){
	Elsif *pos;
	// 修复条件表达式
	fix_expression(current_block, if_s->condition, NULL);
	// 修复then语句
	fix_statement_list(if_s->then_block, if_s->then_block->statement_list,fd);
	// 遍历elsif语句链表，修复每一个elsif表达式
	for (pos = if_s->elsif_list; pos; pos = pos->next) {
		fix_expression(current_block, pos->condition, NULL);
		// 如果存在语句块，则修复elsif语句链表
		if (pos->block) {
			fix_statement_list(pos->block, pos->block->statement_list,fd);
		}
	}
	// 如果存在else语句块，则修复else语句链表
	if (if_s->else_block) {
		fix_statement_list(if_s->else_block, if_s->else_block->statement_list,
			fd);
	}
}
// 修复函数的返回语句
static void fix_return_statement(Block *current_block, ReturnStatement *return_s,
	FunctionDefinition *fd){
	// 返回值表达式
	Expression *return_value;
	// 转换表达式
	Expression *casted_expression;
	// 修复返回值表达式
	return_value = fix_expression(current_block, return_s->return_value, NULL);
	// 如果返回值为null
	if (return_value == NULL) {
		// 如果函数的类型继承存在，并且为数组类型，则返回值为null表达式
		if (fd->type->derive) {
			if (fd->type->derive->tag == ARRAY_DERIVE) {
				return_value = dkc_alloc_expression(NULL_EXPRESSION);
			}
			else {
				DBG_assert(0, (("fd->type->derive..%d\n"), fd->type->derive));
			}
		}
		else {
			// 如果函数的类型继承不存在
			// 根据类型的基本类型选择
			switch (fd->type->basic_type) {
			case DVM_BOOLEAN_TYPE:
				return_value = dkc_alloc_expression(BOOLEAN_EXPRESSION);
				return_value->u.boolean_value = DVM_FALSE;
				break;
			case DVM_INT_TYPE:
				return_value = dkc_alloc_expression(INT_EXPRESSION);
				return_value->u.int_value = 0;
				break;
			case DVM_DOUBLE_TYPE:
				return_value = dkc_alloc_expression(DOUBLE_EXPRESSION);
				return_value->u.int_value = 0.0;
				break;
			case DVM_STRING_TYPE:
				return_value = dkc_alloc_expression(NULL_EXPRESSION);
				return_value->u.string_value = L"";
				break;
			case DVM_NULL_TYPE: /* FALLTHRU */
			default:
				DBG_assert(0, ("basic_type..%d\n"));
				break;
			}
		}
		return_s->return_value = return_value;

		return;
	}
	// 如果返回值与函数定义的返回值类型不同且可以转型，则创建类型转换表达式
	casted_expression = create_assign_cast(return_s->return_value, fd->type);
	return_s->return_value = casted_expression;
}
// 添加变量
static void add_declaration(Block *current_block, Declaration *decl,
	FunctionDefinition *fd, int line_number){
	// 在当前语句块中搜寻该变量的名称，如果找到则报变量重定义错误
	if (dkc_search_declaration(decl->name, current_block)) {
		dkc_compile_error(line_number,
			VARIABLE_MULTIPLE_DEFINE_ERR,
			STRING_MESSAGE_ARGUMENT, "name", decl->name,
			MESSAGE_ARGUMENT_END);
	}
	// 如果当前语句块存在，则将当前函数声明插入到当前语句块的声明链表中
	if (current_block) {
		current_block->declaration_list
			= dkc_chain_declaration(current_block->declaration_list, decl);
		// 在函数内添加局部变量
		add_local_variable(fd, decl);
		decl->is_local = DVM_TRUE;
	}
	// 当前语句块不存在的话，将当前的变量声明加入到编译器的全局声明链表中
	else {
		DKC_Compiler *compiler = dkc_get_current_compiler();
		compiler->declaration_list
			= dkc_chain_declaration(compiler->declaration_list, decl);
		decl->is_local = DVM_FALSE;
	}
}
// 修复函数内的语句
static void fix_statement(Block *current_block, Statement *statement,
	FunctionDefinition *fd){
	// 根据语句的类型选择操作
	switch (statement->type) {
	case EXPRESSION_STATEMENT:
		fix_expression(current_block, statement->u.expression_s, NULL);
		break;
	case IF_STATEMENT:
		fix_if_statement(current_block, &statement->u.if_s, fd);
		break;
	case WHILE_STATEMENT:
		// 修复while的条件表达式
		fix_expression(current_block, statement->u.while_s.condition, NULL);
		// 修复while的语句
		fix_statement_list(statement->u.while_s.block,
			statement->u.while_s.block->statement_list, fd);
		break;
		// 修复for语句的初始化，条件，最后表达式，以及语句块
	case FOR_STATEMENT:
		fix_expression(current_block, statement->u.for_s.init, NULL);
		fix_expression(current_block, statement->u.for_s.condition, NULL);
		fix_expression(current_block, statement->u.for_s.post, NULL);
		fix_statement_list(statement->u.for_s.block,
			statement->u.for_s.block->statement_list, fd);
		break;
		// 修复foreach语句
	case FOREACH_STATEMENT:
		// 修复foreach集合中的表达式
		fix_expression(current_block, statement->u.foreach_s.collection, NULL);
		fix_statement_list(statement->u.for_s.block,
			statement->u.for_s.block->statement_list, fd);
		break;
	case RETURN_STATEMENT:
		fix_return_statement(current_block,
			&statement->u.return_s, fd);
		break;
	case BREAK_STATEMENT:
		break;
	case CONTINUE_STATEMENT:
		break;
	case TRY_STATEMENT:
		/* BUGBUG */
		break;
		// 修复throw表达式
	case THROW_STATEMENT:
		fix_expression(current_block, statement->u.throw_s.exception, NULL);
		/* BUGBUG */
		break;
		// 修复函数内的声明语句
	case DECLARATION_STATEMENT:
		// 添加声明
		add_declaration(current_block, statement->u.declaration_s, fd,
			statement->line_number);
		// 修复声明的标识符
		fix_expression(current_block, statement->u.declaration_s->initializer,
			NULL);
		// 如果声明有初始化语句的话，并且初始化语句需要类型转换，则创建赋值转换
		if (statement->u.declaration_s->initializer) {
			statement->u.declaration_s->initializer
				= create_assign_cast(statement->u.declaration_s->initializer,
				statement->u.declaration_s->type);
		}
		break;
	case STATEMENT_TYPE_COUNT_PLUS_1: /* FALLTHRU */
	default:
		DBG_assert(0, ("bad case. type..%d\n", statement->type));
	}
}
// 修复函数内的语句链表
static void fix_statement_list(Block *current_block, StatementList *list,
	FunctionDefinition *fd){
	StatementList *pos;
	// 遍历语句链表并修复每一个语句
	for (pos = list; pos; pos = pos->next) {
		fix_statement(current_block, pos->statement,fd);
	}
}
// 添加形参，函数的形参被当作变量声明，所以在函数作用域内，不允许有变量名和
// 形参名重复
static void add_parameter_as_declaration(FunctionDefinition *fd){
	Declaration *decl;
	ParameterList *param;

	for (param = fd->parameter; param; param = param->next) {
		if (dkc_search_declaration(param->name, fd->block)) {
			dkc_compile_error(param->line_number,
				PARAMETER_MULTIPLE_DEFINE_ERR,
				STRING_MESSAGE_ARGUMENT, "name", param->name,
				MESSAGE_ARGUMENT_END);
		}
		decl = dkc_alloc_declaration(param->type, param->name);
		add_declaration(fd->block, decl, fd, param->line_number);
	}
}
// 为函数添加返回语句
static void add_return_function(FunctionDefinition *fd){
	// 最后的语句链表节点
	StatementList *last;
	// 最后的语句链表节点的地址
	StatementList **last_p;
	Statement *ret;
	// 如果函数的语句块中的语句链表为空
	if (fd->block->statement_list == NULL) {
		// 设定地址为函数的语句块的语句链表
		last_p = &fd->block->statement_list;
	}
	// 如果不为空
	else {
		// 移动到语句链表的最后位置
		for (last = fd->block->statement_list; last->next; last = last->next)
			;
		// 如果最后一条语句为return语句，则直接返回
		if (last->statement->type == RETURN_STATEMENT) {
			return;
		}
		// 获得最后一条语句的的next指针
		last_p = &last->next;
	}
	// 创建返回语句
	ret = dkc_create_return_statement(NULL);
	ret->line_number = fd->end_line_number;
	// 如果return语句存在返回值
	if (ret->u.return_s.return_value) {
		ret->u.return_s.return_value->line_number = fd->end_line_number;
	}
	// 修复此函数的返回语句
	fix_return_statement(fd->block, &ret->u.return_s, fd);
	// 最后的返回值语句的地址加入到语句链表中
	*last_p = dkc_create_statement_list(ret);
}
// 修复表达式树的公共接口
void dkc_fix_tree(DKC_Compiler *compiler){
	FunctionDefinition *func_pos;
	DeclarationList *dl;
	int var_count = 0;
	// 修复编译器的语句链表
	fix_statement_list(NULL, compiler->statement_list, 0);
	// 修复编译器的函数链表中的函数
	for (func_pos = compiler->function_list; func_pos;
		func_pos = func_pos->next) {
		// 如果函数没有语句，则没有必要修复
		if (func_pos->block == NULL)
			continue;
		// 修复形参
		add_parameter_as_declaration(func_pos);
		// 修复函数语句链表
		fix_statement_list(func_pos->block,
			func_pos->block->statement_list, func_pos);
		// 添加返回值语句
		add_return_function(func_pos);
	}
	// 遍历编译器的变量声明，并修复每个变量的索引
	for (dl = compiler->declaration_list; dl; dl = dl->next) {
		dl->declaration->variable_index = var_count;
		var_count++;
	}
}
