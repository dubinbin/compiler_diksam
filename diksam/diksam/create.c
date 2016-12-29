#include "stdafx.h"
#include "MEM.h"
#include "DBG.h"
#include "diksamc.h"

// 将由参数指定声明的新的声明节点插入声明链表的尾端
DeclarationList* dkc_chain_declaration(DeclarationList *list, Declaration *decl){
	DeclarationList *new_item;
	DeclarationList *pos;

	new_item = dkc_malloc(sizeof(DeclarationList));
	new_item->declaration = decl;
	new_item->next = NULL;
	// 如果链表不存在，则将此节点作为头节点
	if (list == NULL) {
		return new_item;
	}

	for (pos = list; pos->next != NULL; pos = pos->next)
		;
	pos->next = new_item;

	return list;
}
// 为指定表达式类型和标识符的声明分配内存
Declaration *
dkc_alloc_declaration(TypeSpecifier *type, char *identifier)
{
    Declaration *decl;

    decl = dkc_malloc(sizeof(Declaration));
    decl->name = identifier;
    decl->type = type;
    decl->variable_index = -1;

    return decl;
}
// 根据参数指定创建函数定义节点
static FunctionDefinition *
create_function_definition(TypeSpecifier *type, char *identifier,
                           ParameterList *parameter_list, Block *block)
{
    FunctionDefinition *fd;
    DKC_Compiler *compiler;

    compiler = dkc_get_current_compiler();
	// 为函数定义分配内存
    fd = dkc_malloc(sizeof(FunctionDefinition));
    fd->type = type;
    fd->name = identifier;
    fd->parameter = parameter_list;
    fd->block = block;
	// 根据编译器函数数量设定此函数的索引
    fd->index = compiler->function_count;
    compiler->function_count++;
    fd->local_variable_count = 0;
    fd->local_variable = NULL;
    fd->end_line_number = compiler->current_line_number;
    fd->next = NULL;

    return fd;
}
// 根据指定参数创建函数定义并将其插入函数定义链表的尾端
void
dkc_function_define(TypeSpecifier *type, char *identifier,
                    ParameterList *parameter_list, Block *block)
{
    FunctionDefinition *fd;
    FunctionDefinition *pos;
    DKC_Compiler *compiler;
	// 确保函数名未重定义，且变量名不能与函数名重名
    if (dkc_search_function(identifier)
        || dkc_search_declaration(identifier, NULL)) {
        dkc_compile_error(dkc_get_current_compiler()->current_line_number,
                          FUNCTION_MULTIPLE_DEFINE_ERR,
                          STRING_MESSAGE_ARGUMENT, "name", identifier,
                          MESSAGE_ARGUMENT_END);
        return;
    }
    fd = create_function_definition(type, identifier, parameter_list,
                                    block);
    if (block) {
		// 设定语句块的类型和父节点
        block->type = FUNCTION_BLOCK;
        block->parent.function.function = fd;
    }

    compiler = dkc_get_current_compiler();
    if (compiler->function_list) {
        for (pos = compiler->function_list; pos->next; pos = pos->next)
            ;
        pos->next = fd;
    } else {
        compiler->function_list = fd;
    }
}
// 创建形参链表节点
ParameterList *
dkc_create_parameter(TypeSpecifier *type, char *identifier)
{
    ParameterList       *p;

    p = dkc_malloc(sizeof(ParameterList));
    p->name = identifier;
    p->type = type;
    p->line_number = dkc_get_current_compiler()->current_line_number;
    p->next = NULL;

    return p;
}
// 根据指定参数创建形参节点并插入形参链表的尾端
ParameterList *
dkc_chain_parameter(ParameterList *list, TypeSpecifier *type,
                    char *identifier)
{
    ParameterList *pos;

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = dkc_create_parameter(type, identifier);

    return list;
}

ArgumentList *
dkc_create_argument_list(Expression *expression)
{
    ArgumentList *al;

    al = dkc_malloc(sizeof(ArgumentList));
    al->expression = expression;
    al->next = NULL;

    return al;
}

ArgumentList *
dkc_chain_argument_list(ArgumentList *list, Expression *expr)
{
    ArgumentList *pos;

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = dkc_create_argument_list(expr);

    return list;
}

ExpressionList *
dkc_create_expression_list(Expression *expression)
{
    ExpressionList *el;

    el = dkc_malloc(sizeof(ExpressionList));
    el->expression = expression;
    el->next = NULL;

    return el;
}

ExpressionList *
dkc_chain_expression_list(ExpressionList *list, Expression *expr)
{
    ExpressionList *pos;

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = dkc_create_expression_list(expr);

    return list;
}

StatementList *
dkc_create_statement_list(Statement *statement)
{
    StatementList *sl;

    sl = dkc_malloc(sizeof(StatementList));
    sl->statement = statement;
    sl->next = NULL;

    return sl;
}

StatementList *
dkc_chain_statement_list(StatementList *list, Statement *statement)
{
    StatementList *pos;

    if (list == NULL)
        return dkc_create_statement_list(statement);

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = dkc_create_statement_list(statement);

    return list;
}
// 根据基本类型创建类型指定器
TypeSpecifier *
dkc_create_type_specifier(DVM_BasicType basic_type)
{
    TypeSpecifier *type;

    type = dkc_malloc(sizeof(TypeSpecifier));
    type->basic_type = basic_type;
    type->derive = NULL;

    return type;
}
// 创建数组类型的类型指示器
TypeSpecifier *
dkc_create_array_type_specifier(TypeSpecifier *base)
{
    TypeDerive *new_derive;
    
    new_derive = dkc_alloc_type_derive(ARRAY_DERIVE);

    if (base->derive == NULL) {
        base->derive = new_derive;
    } else {
        TypeDerive *derive_p;
        for (derive_p = base->derive; derive_p->next != NULL;
             derive_p = derive_p->next)
            ;
        derive_p->next = new_derive;
    }

    return base;
}
// 根据表达式种类创建表达式
Expression* dkc_alloc_expression(ExpressionKind kind){
    Expression  *exp;

    exp = dkc_malloc(sizeof(Expression));
    exp->type = NULL;
    exp->kind = kind;
    exp->line_number = dkc_get_current_compiler()->current_line_number;

    return exp;
}
// 创建逗号表达式
Expression *
dkc_create_comma_expression(Expression *left, Expression *right)
{
    Expression *exp;

    exp = dkc_alloc_expression(COMMA_EXPRESSION);
    exp->u.comma.left = left;
    exp->u.comma.right = right;

    return exp;
}

Expression *
dkc_create_assign_expression(Expression *left, AssignmentOperator operator,
                             Expression *operand)
{
    Expression *exp;

    exp = dkc_alloc_expression(ASSIGN_EXPRESSION);
    exp->u.assign_expression.left = left;
    exp->u.assign_expression.operator = operator;
    exp->u.assign_expression.operand = operand;

    return exp;
}

Expression *
dkc_create_binary_expression(ExpressionKind operator,
                             Expression *left, Expression *right)
{
#if 0
    if ((left->kind == INT_EXPRESSION
         || left->kind == DOUBLE_EXPRESSION)
        && (right->kind == INT_EXPRESSION
            || right->kind == DOUBLE_EXPRESSION)) {
        DKC_Value v;
        v = dkc_eval_binary_expression(dkc_get_current_compiler(),
                                       NULL, operator, left, right);
        /* Overwriting left hand expression. */
        *left = convert_value_to_expression(&v);

        return left;
    } else {
#endif
        Expression *exp;
        exp = dkc_alloc_expression(operator);
        exp->u.binary_expression.left = left;
        exp->u.binary_expression.right = right;
        return exp;
#if 0
    }
#endif
}

Expression *
dkc_create_minus_expression(Expression *operand)
{
#if 0
    if (operand->kind == INT_EXPRESSION
        || operand->kind == DOUBLE_EXPRESSION) {
        DKC_Value       v;
        v = dkc_eval_minus_expression(dkc_get_current_compiler(),
                                      NULL, operand);
        /* Notice! Overwriting operand expression. */
        *operand = convert_value_to_expression(&v);
        return operand;
    } else {
#endif
        Expression      *exp;
        exp = dkc_alloc_expression(MINUS_EXPRESSION);
        exp->u.minus_expression = operand;
        return exp;
#if 0
    }
#endif
}

Expression *
dkc_create_logical_not_expression(Expression *operand)
{
    Expression  *exp;

    exp = dkc_alloc_expression(LOGICAL_NOT_EXPRESSION);
    exp->u.logical_not = operand;

    return exp;
}

Expression *
dkc_create_index_expression(Expression *array, Expression *index)
{
    Expression *exp;

    exp = dkc_alloc_expression(INDEX_EXPRESSION);
    exp->u.index_expression.array = array;
    exp->u.index_expression.index = index;

    return exp;
}

Expression *
dkc_create_incdec_expression(Expression *operand, ExpressionKind inc_or_dec)
{
    Expression *exp;

    exp = dkc_alloc_expression(inc_or_dec);
    exp->u.inc_dec.operand = operand;

    return exp;
}


Expression *
dkc_create_identifier_expression(char *identifier)
{
    Expression  *exp;

    exp = dkc_alloc_expression(IDENTIFIER_EXPRESSION);
    exp->u.identifier.name = identifier;

    return exp;
}

Expression *
dkc_create_function_call_expression(Expression *function,
                                    ArgumentList *argument)
{
    Expression  *exp;

    exp = dkc_alloc_expression(FUNCTION_CALL_EXPRESSION);
    exp->u.function_call_expression.function = function;
    exp->u.function_call_expression.argument = argument;

    return exp;
}
// 创建成员表达式
Expression *
dkc_create_member_expression(Expression *expression, char *member_name)
{
    Expression  *exp;

    exp = dkc_alloc_expression(MEMBER_EXPRESSION);
    exp->u.member_expression.expression = expression;
    exp->u.member_expression.member_name = member_name;

    return exp;
}


Expression *
dkc_create_boolean_expression(DVM_Boolean value)
{
    Expression *exp;

    exp = dkc_alloc_expression(BOOLEAN_EXPRESSION);
    exp->u.boolean_value = value;

    return exp;
}

Expression *
dkc_create_null_expression(void)
{
    Expression  *exp;

    exp = dkc_alloc_expression(NULL_EXPRESSION);

    return exp;
}

Expression* dkc_create_array_literal_expression(ExpressionList *list){
	Expression  *exp;

	exp = dkc_alloc_expression(ARRAY_LITERAL_EXPRESSION);
	exp->u.array_literal = list;

	return exp;
}
// 创建数组，接受一个基本类型，维数表达式链表，数组维数节点
Expression *dkc_create_array_creation(DVM_BasicType basic_type, ArrayDimension *dim_expr_list, ArrayDimension *dim_list){
	Expression  *exp;

	exp = dkc_alloc_expression(ARRAY_CREATION_EXPRESSION);
	exp->u.array_creation.type = dkc_create_type_specifier(basic_type);
	exp->u.array_creation.dimension
		= dkc_chain_array_dimension(dim_expr_list, dim_list);

	return exp;
}
// 创建数组的维数
ArrayDimension *
dkc_create_array_dimension(Expression *expr){
    ArrayDimension *dim;
	
    dim = dkc_malloc(sizeof(ArrayDimension));
    // 维数可以用表达式计算
	dim->expression = expr;
    dim->next = NULL;

    return dim;
}
// 将数组维数节点插入到数组维数链表的尾端，并返回数组维数链表头节点
ArrayDimension *
dkc_chain_array_dimension(ArrayDimension *list, ArrayDimension *dim){
    ArrayDimension *pos;

    for (pos = list; pos->next != NULL; pos = pos->next)
        ;
    pos->next = dim;

    return list;
}

static Statement *
alloc_statement(StatementType type)
{
    Statement *st;

    st = dkc_malloc(sizeof(Statement));
    st->type = type;
    st->line_number = dkc_get_current_compiler()->current_line_number;

    return st;
}

Statement *
dkc_create_if_statement(Expression *condition,
                        Block *then_block, Elsif *elsif_list,
                        Block *else_block)
{
    Statement *st;

    st = alloc_statement(IF_STATEMENT);
    st->u.if_s.condition = condition;
    st->u.if_s.then_block = then_block;
    st->u.if_s.elsif_list = elsif_list;
    st->u.if_s.else_block = else_block;

    return st;
}

Elsif *
dkc_chain_elsif_list(Elsif *list, Elsif *add)
{
    Elsif *pos;

    for (pos = list; pos->next; pos = pos->next)
        ;
    pos->next = add;

    return list;
}

Elsif *
dkc_create_elsif(Expression *expr, Block *block)
{
    Elsif *ei;

    ei = dkc_malloc(sizeof(Elsif));
    ei->condition = expr;
    ei->block = block;
    ei->next = NULL;

    return ei;
}

Statement *
dkc_create_while_statement(char *label,
                           Expression *condition, Block *block)
{
    Statement *st;

    st = alloc_statement(WHILE_STATEMENT);
    st->u.while_s.label = label;
    st->u.while_s.condition = condition;
    st->u.while_s.block = block;
    block->type = WHILE_STATEMENT_BLOCK;
    block->parent.statement.statement = st;

    return st;
}

Statement *
dkc_create_for_statement(char *label, Expression *init, Expression *cond,
                         Expression *post, Block *block)
{
    Statement *st;

    st = alloc_statement(FOR_STATEMENT);
    st->u.for_s.label = label;
    st->u.for_s.init = init;
    st->u.for_s.condition = cond;
    st->u.for_s.post = post;
    st->u.for_s.block = block;
    block->type = FOR_STATEMENT_BLOCK;
    block->parent.statement.statement = st;

    return st;
}
// 创建foreach语句
Statement *
dkc_create_foreach_statement(char *label, char *variable,
                             Expression *collection, Block *block)
{
    Statement *st;

    st = alloc_statement(FOREACH_STATEMENT);
    st->u.foreach_s.label = label;
    st->u.foreach_s.variable = variable;
    st->u.foreach_s.collection = collection;
    st->u.for_s.block = block;

    return st;
}
// 语句块的开始，返回一个语句块
Block *
dkc_open_block(void)
{
    Block *new_block;

    DKC_Compiler *compiler = dkc_get_current_compiler();
    new_block = dkc_malloc(sizeof(Block));
    new_block->type = UNDEFINED_BLOCK;
	// 根据编译器的当前语句块设定此新语句块的上层语句块
    new_block->outer_block = compiler->current_block;
    new_block->declaration_list = NULL;
	// 编译器的当前语句块更新为这个新的语句块
    compiler->current_block = new_block;

    return new_block;
}
// 语句块结束，返回一个语句块
Block *
dkc_close_block(Block *block, StatementList *statement_list)
{
    DKC_Compiler *compiler = dkc_get_current_compiler();
	// 如果当前语句块和block指定的语句块不一致，说明出现编译错误
    DBG_assert(block == compiler->current_block,
               ("block mismatch.\n"));
    block->statement_list = statement_list;
	// 编译器退出当前语句块
    compiler->current_block = block->outer_block;

    return block;
}

Statement *
dkc_create_expression_statement(Expression *expression)
{
    Statement *st;

    st = alloc_statement(EXPRESSION_STATEMENT);
    st->u.expression_s = expression;

    return st;
}

Statement *
dkc_create_return_statement(Expression *expression)
{
    Statement *st;

    st = alloc_statement(RETURN_STATEMENT);
    st->u.return_s.return_value = expression;

    return st;
}

Statement *
dkc_create_break_statement(char *label)
{
    Statement *st;

    st = alloc_statement(BREAK_STATEMENT);
    st->u.break_s.label = label;

    return st;
}

Statement *
dkc_create_continue_statement(char *label)
{
    Statement *st;

    st = alloc_statement(CONTINUE_STATEMENT);
    st->u.continue_s.label = label;

    return st;
}
// 创建try语句
Statement *
dkc_create_try_statement(Block *try_block, char *exception,
                         Block *catch_block, Block *finally_block)
{
    Statement *st;

    st = alloc_statement(TRY_STATEMENT);
    st->u.try_s.try_block = try_block;
    st->u.try_s.catch_block = catch_block;
    st->u.try_s.exception = exception;
    st->u.try_s.finally_block = finally_block;

    return st;
}
// 创建throw语句
Statement *
dkc_create_throw_statement(Expression *expression)
{
    Statement *st;

    st = alloc_statement(THROW_STATEMENT);
    st->u.throw_s.exception = expression;

    return st;
}
// 创建声明语句
Statement *
dkc_create_declaration_statement(TypeSpecifier *type, char *identifier,
                                 Expression *initializer)
{
    Statement *st;
    Declaration *decl;

    st = alloc_statement(DECLARATION_STATEMENT);

    decl = dkc_alloc_declaration(type, identifier);

    decl->initializer = initializer;

    st->u.declaration_s = decl;

    return st;
}
