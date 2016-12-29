#include "stdafx.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdarg.h>
#include "MEM.h"
#include "DBG.h"
#include "diksamc.h"

// 操作代码信息
extern OpcodeInfo dvm_opcode_info[];

#define OPCODE_ALLOC_SIZE (256)
#define LABEL_TABLE_ALLOC_SIZE (256)
// 标签表定义，包含一个int类型标签地址
typedef struct {
    int label_address;
} LabelTable;
// 操作代码缓冲区，包含代码大小，标签表大小，行号等相关信息
typedef struct {
    int         size;
    int         alloc_size;
    DVM_Byte    *code;

    int         label_table_size;
    int         label_table_alloc_size;
    LabelTable  *label_table;
    // 行号数量
	int         line_number_size;
	// 每一行的具体信息
    DVM_LineNumber      *line_number;
} OpcodeBuf;
// 分配执行体内存
static DVM_Executable* alloc_executable(void){
	DVM_Executable      *exe;
	// 分配空间
	exe = MEM_malloc(sizeof(DVM_Executable));
	exe->constant_pool_count = 0;
	exe->constant_pool = NULL;
	exe->global_variable_count = 0;
	exe->global_variable = NULL;
	exe->function_count = 0;
	exe->function = NULL;
	exe->type_specifier_count = 0;
	exe->type_specifier = NULL;
	exe->code_size = 0;
	exe->code = NULL;
	return exe;
}
// 添加常量池
static int add_constant_pool(DVM_Executable *exe, DVM_ConstantPool *cp){
    int ret;
	// 重新分配执行体的内存
    exe->constant_pool
        = MEM_realloc(exe->constant_pool,
                      sizeof(DVM_ConstantPool)
                      * (exe->constant_pool_count + 1));
    // 添加常量池并修改常量池计数器
	exe->constant_pool[exe->constant_pool_count] = *cp;

    ret = exe->constant_pool_count;
    exe->constant_pool_count++;

    return ret;
}
// 函数前向声明，复制类型指定器
static DVM_TypeSpecifier *copy_type_specifier(TypeSpecifier *src);
// 复制形参链表，并返回形参和其数量
static DVM_LocalVariable* copy_parameter_list(ParameterList *src, int *param_count_p){
	int param_count = 0;
	ParameterList *param;
	DVM_LocalVariable *dest;
	int i;
	// 记录形参数量
	for (param = src; param; param = param->next) {
		param_count++;
	}
	// 
	*param_count_p = param_count;
	// 为形参分配内存，形参在函数内被当作局部变量
	dest = MEM_malloc(sizeof(DVM_LocalVariable) * param_count);
	for (param = src, i = 0; param; param = param->next, i++) {
		dest[i].name = MEM_strdup(param->name);
		dest[i].type = copy_type_specifier(param->type);
	}

	return dest;
}
// 复制局部变量，并返回局部变量
static DVM_LocalVariable* copy_local_variables(FunctionDefinition *fd, int param_count){
	int i;
	int local_variable_count;
	DVM_LocalVariable *dest;
	// 形参不是真正的局部变量
	local_variable_count = fd->local_variable_count - param_count;

	dest = MEM_malloc(sizeof(DVM_LocalVariable) * local_variable_count);

	for (i = 0; i < local_variable_count; i++) {
		// 形参占用了局部变量链表的前部分
		dest[i].name
			= MEM_strdup(fd->local_variable[i + param_count]->name);
		dest[i].type
			= copy_type_specifier(fd->local_variable[i + param_count]->type);
	}

	return dest;
}
// 复制类型指定器子函数
static void copy_type_specifier_no_alloc(TypeSpecifier *src, DVM_TypeSpecifier *dest){
	// 类型继承数量
	int derive_count = 0;
	TypeDerive *derive;
	// 形参数量
	int param_count;
	int i;

	dest->basic_type = src->basic_type;
	// 记录类型继承数量
	for (derive = src->derive; derive; derive = derive->next) {
		derive_count++;
	}
	dest->derive_count = derive_count;
	dest->derive = MEM_malloc(sizeof(DVM_TypeDerive) * derive_count);
	// 复制类型继承
	for (i = 0, derive = src->derive; derive; derive = derive->next, i++) {
		switch (derive->tag) {
		case FUNCTION_DERIVE:
			dest->derive[i].tag = DVM_FUNCTION_DERIVE;
			dest->derive[i].u.function_d.parameter
				= copy_parameter_list(derive->u.function_d.parameter_list,
				&param_count);
			dest->derive[i].u.function_d.parameter_count = param_count;
			break;
		case ARRAY_DERIVE:
			dest->derive[i].tag = DVM_ARRAY_DERIVE;
			break;
		default:
			DBG_assert(0, ("derive->tag..%d\n", derive->tag));
		}
	}
}
// 赋值类型指定器
static DVM_TypeSpecifier* copy_type_specifier(TypeSpecifier *src){
	DVM_TypeSpecifier *dest;
	// 为目的类型指定器分配内存
	dest = MEM_malloc(sizeof(DVM_TypeSpecifier));
	// 赋值类型指定器
	copy_type_specifier_no_alloc(src, dest);

	return dest;
}
// 添加全局变量
static void add_global_variable(DKC_Compiler *compiler, DVM_Executable *exe){
	DeclarationList *dl;
	int i;
	int var_count = 0;
	// 记录编译器内的全局变量数量
	for (dl = compiler->declaration_list; dl; dl = dl->next) {
		var_count++;
	}
	exe->global_variable_count = var_count;
	exe->global_variable = MEM_malloc(sizeof(DVM_Variable) * var_count);
	// 为执行体设定全局变量相关类型
	for (dl = compiler->declaration_list, i = 0; dl; dl = dl->next, i++) {
		exe->global_variable[i].name = MEM_strdup(dl->declaration->name);
		exe->global_variable[i].type
			= copy_type_specifier(dl->declaration->type);
	}
}
// 添加类型指定器，并返回该类型指定器的索引
static int add_type_specifier(TypeSpecifier *src, DVM_Executable *exe){
	int ret;

	exe->type_specifier
		= MEM_realloc(exe->type_specifier,
		sizeof(DVM_TypeSpecifier)
		* (exe->type_specifier_count + 1));
	copy_type_specifier_no_alloc(src,
		&exe->type_specifier
		[exe->type_specifier_count]);

	ret = exe->type_specifier_count;
	exe->type_specifier_count++;

	return ret;
}
// 添加代码行数计数器
static void add_line_number(OpcodeBuf *ob, int line_number, int start_pc){
	// 行数计数器不存在或者切换到新行的情况下需要为其重新分配内存
	if (ob->line_number == NULL
		|| (ob->line_number[ob->line_number_size - 1].line_number
		!= line_number)) {
		ob->line_number = MEM_realloc(ob->line_number,
			sizeof(DVM_LineNumber)
			* (ob->line_number_size + 1));

		ob->line_number[ob->line_number_size].line_number = line_number;
		ob->line_number[ob->line_number_size].start_pc = start_pc;
		// 程序计数器的步进由当前缓冲区大小减去程序计数器起始位置
		ob->line_number[ob->line_number_size].pc_count = ob->size - start_pc;
		ob->line_number_size++;
	}
	else {
		// 否则就添加程序计数器的值
		ob->line_number[ob->line_number_size - 1].pc_count += ob->size - start_pc;
	}
}
// 操作码生成，该函数向ob内填充字节码，code指示操作代码，后面的可变参数指示操作数
static void generate_code(OpcodeBuf *ob, int line_number, DVM_Opcode code, ...){
	va_list     ap;
	int         i;
	// 字节码的参数
	char        *param;
	// 参数数量
	int         param_count;
	// 程序计数器起始位置
	int         start_pc;
	// 可变参数的开头
	va_start(ap, code);
	// 获得该操作码所需参数
	param = dvm_opcode_info[(int)code].parameter;
	// 获得参数长度
	param_count = strlen(param);
	// 如果当前已分配内存小于操作码缓冲区需要的内存，则需要重新分配
	if (ob->alloc_size < ob->size + 1 + (param_count * 2)) {
		ob->code = MEM_realloc(ob->code, ob->alloc_size + OPCODE_ALLOC_SIZE);
		ob->alloc_size += OPCODE_ALLOC_SIZE;
	}
	// 程序计数器的起始地址设为当前缓冲区的第一个空位置
	start_pc = ob->size;
	// 先向缓冲区增加字节码的操作码
	ob->code[ob->size] = code;
	ob->size++;
	// 再根据参数指示获取可变参数
	for (i = 0; param[i] != '\0'; i++) {
		// 获得可变参数，并将可变参数位置向前移动一位
		unsigned int value = va_arg(ap, int);
		switch (param[i]) {
		case 'b': /* byte */
			// 1字节的参数
			ob->code[ob->size] = (DVM_Byte)value;
			ob->size++;
			break;
		case 's': /* short(2byte int) */
			// 2字节的参数按照大端法将参数存放到操作数之后2字节
			// 先将参数右移8位（获取高8位）,放在缓冲区低字节内
			ob->code[ob->size] = (DVM_Byte)(value >> 8);
			// 缓冲区地址高字节存放参数低8位
			ob->code[ob->size + 1] = (DVM_Byte)(value & 0xff);
			ob->size += 2;
			break;
		case 'p': /* constant pool index */
			// 常量缓冲区索引
			ob->code[ob->size] = (DVM_Byte)(value >> 8);
			ob->code[ob->size + 1] = (DVM_Byte)(value & 0xff);
			ob->size += 2;
			break;
		default:
			DBG_assert(0, ("param..%s, i..%d", param, i));
		}
	}
	// 添加行号
	add_line_number(ob, line_number, start_pc);
	// 可变参数结束
	va_end(ap);
}
// 生成bool表达式
static void generate_boolean_expression(DVM_Executable *cf, Expression *expr, OpcodeBuf *ob){
	// 根据bool的值生成字节码
	// PUSH_INT_1BYTE 将操作数指定的1个字节入栈
	// 虚拟机内部将bool值当作int值对待
	if (expr->u.boolean_value) {
		generate_code(ob, expr->line_number, DVM_PUSH_INT_1BYTE, 1);
	}
	else {
		generate_code(ob, expr->line_number, DVM_PUSH_INT_1BYTE, 0);
	}
}
// 生成int表达式
static void generate_int_expression(DVM_Executable *cf, Expression *expr, OpcodeBuf *ob){
	// 如果int值为1个字节，则使用
	// PUSH_INT_1BYTE
	if (expr->u.int_value >= 0 && expr->u.int_value < 256) {
		generate_code(ob, expr->line_number,
			DVM_PUSH_INT_1BYTE, expr->u.int_value);
	}
	// 如果int值为2个字节，则使用
	//	PUSH_INT_2BYTE 将操作数指定的2个字节的整数入栈
	else if (expr->u.int_value >= 0 && expr->u.int_value < 65536) {
		generate_code(ob, expr->line_number,
			DVM_PUSH_INT_2BYTE, expr->u.int_value);
	}
	// 否则将该int值加入int常量缓冲区
	// PUSH_INT 将常量池中的int值入栈
	else {
		DVM_ConstantPool cp;
		int cp_idx;
		cp.tag = DVM_CONSTANT_INT;
		cp.u.c_int = expr->u.int_value;
		cp_idx = add_constant_pool(cf, &cp);
		generate_code(ob, expr->line_number, DVM_PUSH_INT, cp_idx);
	}
}
// 生成double型表达式
static void generate_double_expression(DVM_Executable *cf, Expression *expr, OpcodeBuf *ob){
	// 对于0.0和1.0两种double值，虚拟机使用两个特殊的指令
	// PUSH_DOUBLE_0 PUSH_DOUBLE_1 将double常量0和1入栈
	if (expr->u.double_value == 0.0) {
		generate_code(ob, expr->line_number, DVM_PUSH_DOUBLE_0);
	}
	else if (expr->u.double_value == 1.0) {
		generate_code(ob, expr->line_number, DVM_PUSH_DOUBLE_1);
	}
	else {
		// 否则使用double常量池索引
		// 其他所有double值都被加入常量池中
		DVM_ConstantPool cp;
		int cp_idx;
		cp.tag = DVM_CONSTANT_DOUBLE;
		cp.u.c_double = expr->u.double_value;
		cp_idx = add_constant_pool(cf, &cp);
		generate_code(ob, expr->line_number, DVM_PUSH_DOUBLE, cp_idx);
	}
}
// 生成字符串表达式，字符串全部加入字符串常量池
// PUSH_STRING 将常量池中的字符串入栈
static void generate_string_expression(DVM_Executable *cf, Expression *expr, OpcodeBuf *ob){
	DVM_ConstantPool cp;
	int cp_idx;
	cp.tag = DVM_CONSTANT_STRING;
	cp.u.c_string = expr->u.string_value;
	cp_idx = add_constant_pool(cf, &cp);
	generate_code(ob, expr->line_number, DVM_PUSH_STRING, cp_idx);
}
// 获取字节码类型偏移，int和bool同样对待，之后分别是double和string
// string和类型继承同样对待
static int get_opcode_type_offset(TypeSpecifier *type){
	if (type->derive != NULL) {
		DBG_assert(type->derive->tag = ARRAY_DERIVE,
			("type->derive->tag..%d", type->derive->tag));
		return 2;
	}

	switch (type->basic_type) {
	case DVM_BOOLEAN_TYPE:
		return 0;
		break;
	case DVM_INT_TYPE:
		return 0;
		break;
	case DVM_DOUBLE_TYPE:
		return 1;
		break;
	case DVM_STRING_TYPE:
		return 2;
		break;
	case DVM_NULL_TYPE: /* FALLTHRU */
	default:
		DBG_assert(0, ("basic_type..%d", type->basic_type));
	}

	return 0;
}
// 生成标识符表达式
static void generate_identifier_expression(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	// 如果标识符为函数名称
	// 则使用 PUSH_FUNCTION 将函数的索引值入栈
	if (expr->u.identifier.is_function) {
		generate_code(ob, expr->line_number, DVM_PUSH_FUNCTION, expr->u.identifier.u.function->index);
		return;
	}
	// 如果标识符为局部变量的声明
	// 则使用 PUSH_STACK_OP 将栈中以base为基准，以操作数为偏移量的位置的op值入栈
	if (expr->u.identifier.u.declaration->is_local) {
		generate_code(ob, expr->line_number, 
			DVM_PUSH_STACK_INT + get_opcode_type_offset(expr->u.identifier.u.declaration->type),
			expr->u.identifier.u.declaration->variable_index);
	}
	else {
		// 否则使用 PUSH_STATIC_OP 以操作数为索引值，将对应的op值入栈
		generate_code(ob, expr->line_number,
			DVM_PUSH_STATIC_INT + get_opcode_type_offset(expr->u.identifier.u.declaration->type), 
			expr->u.identifier.u.declaration->variable_index);
	}
}
// 函数前向声明，生成表达式
static void generate_expression(DVM_Executable *exe, Block *current_block, Expression *expr, OpcodeBuf *ob);
// 生成标识符出栈
static void generate_pop_to_identifier(Declaration *decl, int line_number, OpcodeBuf *ob){
	// 如果标识符声明为局部的,则使用
	// POP_STACK_INT 将栈中以base为基准，以操作数为偏移量的op值出栈
	if (decl->is_local) {
		generate_code(ob, line_number, DVM_POP_STACK_INT + get_opcode_type_offset(decl->type), decl->variable_index);
	}
	// 否则使用 POP_STATIC_OP 将栈顶的值出栈保存为op型的静态变量，其索引有操作数决定
	else {
		generate_code(ob, line_number, DVM_POP_STATIC_INT + get_opcode_type_offset(decl->type), decl->variable_index);
	}
}
// 生成将出栈的值存入左值
static void generate_pop_to_lvalue(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	// 如果表达式为标识符表达式
	if (expr->kind == IDENTIFIER_EXPRESSION) {
		// 则将标识符表达式弹出到声明索引指定的常量池位置中
		generate_pop_to_identifier(expr->u.identifier.u.declaration,
			expr->line_number,
			ob);
	}
	// 如果为数组表达式
	else {
		DBG_assert(expr->kind == INDEX_EXPRESSION,
			("expr->kind..%d", expr->kind));
		// 生成数组和索引表达式的字节码
		generate_expression(exe, block, expr->u.index_expression.array, ob);
		generate_expression(exe, block, expr->u.index_expression.index, ob);
		// POP_ARRAY_INT 将栈上的值（op）赋值给数组array中下标为op的元素
		generate_code(ob, expr->line_number,
			DVM_POP_ARRAY_INT + get_opcode_type_offset(expr->type));

	}
}
// 生成赋值表达式字节码
static void generate_assign_expression(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob, DVM_Boolean is_toplevel){
	// 如果该赋值表达式不是普通的（+=，-=，*=，/=，%=）
	// 生成赋值语句左边的表达式的字节码
	if (expr->u.assign_expression.operator != NORMAL_ASSIGN) {
		generate_expression(exe, block, expr->u.assign_expression.left, ob);
	}
	// 生成赋值语句右边的表达式的字节码
	generate_expression(exe, block, expr->u.assign_expression.operand, ob);
	// 根据操作子类型
	switch (expr->u.assign_expression.operator) {
	case NORMAL_ASSIGN: /* FALLTHRU */
		break;
	case ADD_ASSIGN:
		// ADD_OP 进行op类型的加法运算，并将结果入栈
		generate_code(ob, expr->line_number, DVM_ADD_INT + get_opcode_type_offset(expr->type));
		break;
	case SUB_ASSIGN:
		// SUB_OP 进行op类型的减法运算，并将结果入栈
		generate_code(ob, expr->line_number, DVM_SUB_INT + get_opcode_type_offset(expr->type));
		break;
	case MUL_ASSIGN:
		// MUL_OP 进行op类型的乘法运算，并将结果入栈
		generate_code(ob, expr->line_number, DVM_MUL_INT + get_opcode_type_offset(expr->type));
		break;
	case DIV_ASSIGN:
		// DIV_OP 进行op类型的除法运算，并将结果入栈
		generate_code(ob, expr->line_number, DVM_DIV_INT + get_opcode_type_offset(expr->type));
		break;
	case MOD_ASSIGN:
		// MOD_OP 进行op类型的取余运算，并将结果入栈
		generate_code(ob, expr->line_number, DVM_MOD_INT + get_opcode_type_offset(expr->type));
		break;
	default:
		DBG_assert(0, ("operator..%d\n", expr->u.assign_expression.operator));
	}
	// is_toplevel参数意义不明
	if (!is_toplevel) {
		// DUPLICATE 复制栈顶的一个值
		generate_code(ob, expr->line_number, DVM_DUPLICATE);
	}
	// 生成向左值弹出的字节码
	generate_pop_to_lvalue(exe, block, expr->u.assign_expression.left, ob);
}
// 生成二元表达式字节码
static void generate_binary_expression(DVM_Executable *exe, Block *block, Expression *expr, DVM_Opcode code, OpcodeBuf *ob){
	int offset;
	Expression *left = expr->u.binary_expression.left;
	Expression *right = expr->u.binary_expression.right;
	// 分别生成左边和右边的表达式的字节码
	generate_expression(exe, block, left, ob);
	generate_expression(exe, block, right, ob);

	if ((left->kind == NULL_EXPRESSION && right->kind != NULL_EXPRESSION)
		|| (left->kind != NULL_EXPRESSION && right->kind == NULL_EXPRESSION)) {
		offset = 2; /* object type */
	}
	// EQ_INT 和 NE_INT 进行int间的比较，并将结果入栈 
	else if ((code == DVM_EQ_INT || code == DVM_NE_INT) && dkc_is_string(left->type)) {
		offset = 3; /* string type */
	}
	else {
		offset = get_opcode_type_offset(expr->u.binary_expression.left->type);
	}
	generate_code(ob, expr->line_number, code + offset);
}
// 获取标签
static int get_label(OpcodeBuf *ob){
	int ret;
	// 如果标签表空间已满，则重新分配内存，每次增加一倍
	if (ob->label_table_alloc_size < ob->label_table_size + 1) {
		ob->label_table = MEM_realloc(ob->label_table,
			(ob->label_table_alloc_size + LABEL_TABLE_ALLOC_SIZE)* sizeof(LabelTable));
		ob->label_table_alloc_size += LABEL_TABLE_ALLOC_SIZE;
	}
	// 返回当前标签表的第一个可用位置索引
	ret = ob->label_table_size;
	ob->label_table_size++;
	return ret;
}
// 设置标签的内容
static void set_label(OpcodeBuf *ob, int label){
    ob->label_table[label].label_address = ob->size;
}
// 生成逻辑与表达式字节码
static void generate_logical_and_expression(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	int false_label;
	// 获取false标签的索引
	false_label = get_label(ob);
	// 生成左边的表达式字节码
	generate_expression(exe, block, expr->u.binary_expression.left, ob);
	// 复制栈顶的一个值
	generate_code(ob, expr->line_number, DVM_DUPLICATE);
	// JUMP_IF_FALSE 如果栈顶的值为false，则跳转到false标签上
	generate_code(ob, expr->line_number, DVM_JUMP_IF_FALSE, false_label);
	// 生成右边的表达式字节码
	generate_expression(exe, block, expr->u.binary_expression.right, ob);
	// LOGICAL_AND 逻辑与结果入栈
	generate_code(ob, expr->line_number, DVM_LOGICAL_AND);
	// 设置false标签
	set_label(ob, false_label);
}
// 生成逻辑或表达式字节码
static void generate_logical_or_expression(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	int true_label;
	// 获取true标签
	// 下面的过程同逻辑与相同
	true_label = get_label(ob);
	generate_expression(exe, block, expr->u.binary_expression.left, ob);
	generate_code(ob, expr->line_number, DVM_DUPLICATE);
	generate_code(ob, expr->line_number, DVM_JUMP_IF_TRUE, true_label);
	generate_expression(exe, block, expr->u.binary_expression.right, ob);
	generate_code(ob, expr->line_number, DVM_LOGICAL_OR);
	set_label(ob, true_label);
}
// 生成类型转换表达式
static void generate_cast_expression(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	// 生成转换表达式操作数的表达式字节码
	generate_expression(exe, block, expr->u.cast.operand, ob);
	// 根据转换类型选择生成字节码
	// CAST_SRC_TO_DEST 将栈顶的src值转换为dest
	switch (expr->u.cast.type) {
	case INT_TO_DOUBLE_CAST:
		generate_code(ob, expr->line_number, DVM_CAST_INT_TO_DOUBLE);
		break;
	case DOUBLE_TO_INT_CAST:
		generate_code(ob, expr->line_number, DVM_CAST_DOUBLE_TO_INT);
		break;
	case BOOLEAN_TO_STRING_CAST:
		generate_code(ob, expr->line_number, DVM_CAST_BOOLEAN_TO_STRING);
		break;
	case INT_TO_STRING_CAST:
		generate_code(ob, expr->line_number, DVM_CAST_INT_TO_STRING);
		break;
	case DOUBLE_TO_STRING_CAST:
		generate_code(ob, expr->line_number, DVM_CAST_DOUBLE_TO_STRING);
		break;
	default:
		DBG_assert(0, ("expr->u.cast.type..%d", expr->u.cast.type));
	}
}
// 生成数组字面值表达式字节码
static void generate_array_literal_expression(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	ExpressionList *pos;
	int count = 0;

	DBG_assert(expr->type->derive
		&& expr->type->derive->tag == ARRAY_DERIVE,
		("array literal is not array."));
	// 遍历字面值链表，为每一个字面值生成字节码
	for (pos = expr->u.array_literal; pos; pos = pos->next) {
		generate_expression(exe, block, pos->expression, ob);
		count++;
	}
	DBG_assert(count > 0, ("empty array literal"));
	// NEW_ARRAY_LITERAL_OP 以已经入栈的给定数量的int类型的的操作数为元素创建
	// 数组，并将其入栈
	generate_code(ob, expr->line_number,
		DVM_NEW_ARRAY_LITERAL_INT + get_opcode_type_offset(expr->u.array_literal->expression->type),
		count);
}
// 生成索引表达式
static void generate_index_expression(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	generate_expression(exe, block, expr->u.index_expression.array, ob);
	generate_expression(exe, block, expr->u.index_expression.index, ob);
	// PUSH_ARRAY_INT 根据栈中的数组和下标获取数组中的元素（op型），并将其入栈
	generate_code(ob, expr->line_number, DVM_PUSH_ARRAY_INT+ get_opcode_type_offset(expr->type));
}
// 生成自增或者自减表达式字节码
static void generate_inc_dec_expression(DVM_Executable *exe, Block *block,
	Expression *expr, ExpressionKind kind,
	OpcodeBuf *ob, DVM_Boolean is_toplevel){
	// 生成操作数表达式的字节码
	generate_expression(exe, block, expr->u.inc_dec.operand, ob);
	// INCREMENT DECREMENT 自增或者自减栈顶的int值
	if (kind == INCREMENT_EXPRESSION) {
		generate_code(ob, expr->line_number, DVM_INCREMENT);
	}
	else {
		DBG_assert(kind == DECREMENT_EXPRESSION, ("kind..%d\n", kind));
		generate_code(ob, expr->line_number, DVM_DECREMENT);
	}
	// is_toplevel意义不明
	if (!is_toplevel) {
		generate_code(ob, expr->line_number, DVM_DUPLICATE);
	}
	// 将栈中的值出栈并且保存在左值中
	generate_pop_to_lvalue(exe, block,
		expr->u.inc_dec.operand, ob);
}
// 生成函数调用表达式字节码
static void generate_function_call_expression(DVM_Executable *exe, Block *block,
	Expression *expr, OpcodeBuf *ob){
	FunctionCallExpression *fce = &expr->u.function_call_expression;
	ArgumentList *arg_pos;
	// 遍历函数的实参链表，并生成每个实参表达式的字节码
	for (arg_pos = fce->argument; arg_pos; arg_pos = arg_pos->next) {
		generate_expression(exe, block, arg_pos->expression, ob);
	}
	// 生成函数表达式字节码
	generate_expression(exe, block, fce->function, ob);
	// INVOKE 调用栈顶的函数
	generate_code(ob, expr->line_number, DVM_INVOKE);
}
// 生成null表达式的字节码
// PUSH_NULL 将null入栈
static void generate_null_expression(DVM_Executable *exe, Expression *expr, OpcodeBuf *ob){
	generate_code(ob, expr->line_number, DVM_PUSH_NULL);
}
// 生成数组创建表达式字节码
static void generate_array_creation_expression(DVM_Executable *exe, Block *block,
	Expression *expr, OpcodeBuf *ob){
	int index;
	TypeSpecifier type;
	ArrayDimension *dim_pos;
	int dim_count;
	// 添加并获得类型指定器的索引
	index = add_type_specifier(expr->type, exe);

	DBG_assert(expr->type->derive->tag == ARRAY_DERIVE,
		("expr->type->derive->tag..%d", expr->type->derive->tag));

	type.basic_type = expr->type->basic_type;
	type.derive = expr->type->derive;
	// 数组维数
	dim_count = 0;
	// 遍历数组维数表达式链表，如果维数表达式存在，在生成每个表达式的字节码
	for (dim_pos = expr->u.array_creation.dimension;
		dim_pos; dim_pos = dim_pos->next) {
		if (dim_pos->expression == NULL)
			break;
		generate_expression(exe, block, dim_pos->expression, ob);
		dim_count++;
	}
	// NEW_ARRAY BYTE SHORT 创建以操作数short所示类型组成的byte维数组（用栈中指定个数的元素）
	// 并将其入栈
	generate_code(ob, expr->line_number, DVM_NEW_ARRAY, dim_count, index);
}
// 生成表达式字节码
static void generate_expression(DVM_Executable *exe, Block *current_block, Expression *expr, OpcodeBuf *ob){
	switch (expr->kind) {
	case BOOLEAN_EXPRESSION:
		generate_boolean_expression(exe, expr, ob);
		break;
	case INT_EXPRESSION:
		generate_int_expression(exe, expr, ob);
		break;
	case DOUBLE_EXPRESSION:
		generate_double_expression(exe, expr, ob);
		break;
	case STRING_EXPRESSION:
		generate_string_expression(exe, expr, ob);
		break;
	case IDENTIFIER_EXPRESSION:
		generate_identifier_expression(exe, current_block,
			expr, ob);
		break;
	case COMMA_EXPRESSION:
		generate_expression(exe, current_block, expr->u.comma.left, ob);
		generate_expression(exe, current_block, expr->u.comma.right, ob);
		break;
	case ASSIGN_EXPRESSION:
		generate_assign_expression(exe, current_block, expr, ob, DVM_FALSE);
		break;
	case ADD_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_ADD_INT, ob);
		break;
	case SUB_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_SUB_INT, ob);
		break;
	case MUL_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_MUL_INT, ob);
		break;
	case DIV_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_DIV_INT, ob);
		break;
	case MOD_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_MOD_INT, ob);
		break;
	case EQ_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_EQ_INT, ob);
		break;
	case NE_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_NE_INT, ob);
		break;
	case GT_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_GT_INT, ob);
		break;
	case GE_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_GE_INT, ob);
		break;
	case LT_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_LT_INT, ob);
		break;
	case LE_EXPRESSION:
		generate_binary_expression(exe, current_block, expr,
			DVM_LE_INT, ob);
		break;
	case LOGICAL_AND_EXPRESSION:
		generate_logical_and_expression(exe, current_block, expr, ob);
		break;
	case LOGICAL_OR_EXPRESSION:
		generate_logical_or_expression(exe, current_block, expr, ob);
		break;
	case MINUS_EXPRESSION:
		generate_expression(exe, current_block, expr->u.minus_expression, ob);
		generate_code(ob, expr->line_number,
			DVM_MINUS_INT
			+ get_opcode_type_offset(expr->type));
		break;
	case LOGICAL_NOT_EXPRESSION:
		generate_expression(exe, current_block, expr->u.logical_not, ob);
		generate_code(ob, expr->line_number, DVM_LOGICAL_NOT);
		break;
	case FUNCTION_CALL_EXPRESSION:
		generate_function_call_expression(exe, current_block,
			expr, ob);
		break;
	case MEMBER_EXPRESSION:
		break;
	case NULL_EXPRESSION:
		generate_null_expression(exe, expr, ob);
		break;
	case ARRAY_LITERAL_EXPRESSION:
		generate_array_literal_expression(exe, current_block, expr, ob);
		break;
	case INDEX_EXPRESSION:
		generate_index_expression(exe, current_block, expr, ob);
		break;
	case INCREMENT_EXPRESSION:  /* FALLTHRU */
	case DECREMENT_EXPRESSION:
		generate_inc_dec_expression(exe, current_block, expr, expr->kind,
			ob, DVM_FALSE);
		break;
	case CAST_EXPRESSION:
		generate_cast_expression(exe, current_block, expr, ob);
		break;
	case ARRAY_CREATION_EXPRESSION:
		generate_array_creation_expression(exe, current_block, expr, ob);
		break;
	case EXPRESSION_KIND_COUNT_PLUS_1:  /* FALLTHRU */
	default:
		DBG_assert(0, ("expr->kind..%d", expr->kind));
	}
}
// 生成表达式语句字节码
static void generate_expression_statement(DVM_Executable *exe, Block *block, Expression *expr, OpcodeBuf *ob){
	// 如果表达式种类为赋值表达式
	if (expr->kind == ASSIGN_EXPRESSION) {
		generate_assign_expression(exe, block, expr, ob, DVM_TRUE);
	}
	// 如果表达式是自增或自减表达式
	else if (expr->kind == INCREMENT_EXPRESSION
		|| expr->kind == DECREMENT_EXPRESSION) {
		generate_inc_dec_expression(exe, block, expr, expr->kind, ob,
			DVM_TRUE);
	}
	else {
		generate_expression(exe, block, expr, ob);
		// POP 舍弃栈顶的一个值
		generate_code(ob, expr->line_number, DVM_POP);
	}
}
// 函数前向声明，生成语句链表字节码
static void generate_statement_list(DVM_Executable *exe, Block *current_block, StatementList *statement_list, OpcodeBuf *ob);
// 生成if语句字节码
static void generate_if_statement(DVM_Executable *exe, Block *block,Statement *statement, OpcodeBuf *ob){
    // if条件失败标签
	int if_false_label;
	// 终止标签
    int end_label;
    IfStatement *if_s = &statement->u.if_s;
    Elsif *elsif;
	// 生成条件表达式字节码
    generate_expression(exe, block, if_s->condition, ob);
	// 获得标签
    if_false_label = get_label(ob);
    // 栈顶的值如果是false就跳转到指定标签
	generate_code(ob, statement->line_number,
                  DVM_JUMP_IF_FALSE, if_false_label);
    // 生成then语句块中的语句字节码
	generate_statement_list(exe, if_s->then_block,
                            if_s->then_block->statement_list, ob);
    // 获得终止标签
	end_label = get_label(ob);
	// JUMP SHORT 跳转到操作数指定的地址
    generate_code(ob, statement->line_number, DVM_JUMP, end_label);
	// 设定if_else标签
    set_label(ob, if_false_label);
	// 遍历elsif语句链表
    for (elsif = if_s->elsif_list; elsif; elsif = elsif->next) {
        // 生成每一个elsif条件表达式的字节码
		generate_expression(exe, block, elsif->condition, ob);
        // 获得elsif里的if_else标签
		if_false_label = get_label(ob);
		// 如果条件表达式测试失败，直接跳转到下一个elsif，也就是下一个循环里填充的字节码
        generate_code(ob, statement->line_number,
                      DVM_JUMP_IF_FALSE, if_false_label);
		// 生成语句链表字节码
        generate_statement_list(exe, elsif->block,
                                elsif->block->statement_list, ob);
        generate_code(ob, statement->line_number, DVM_JUMP, end_label);
        set_label(ob, if_false_label);
    }
	// 如果有else语句，则生成else语句链表的字节码
    if (if_s->else_block) {
        generate_statement_list(exe, if_s->else_block,
                                if_s->else_block->statement_list,
                                ob);
    }
    set_label(ob, end_label);
}
// 生成while语句的字节码
static void generate_while_statement(DVM_Executable *exe, Block *block, Statement *statement, OpcodeBuf *ob){
	// 循环标签
	int loop_label;
	WhileStatement *while_s = &statement->u.while_s;
	// 获取循环标签并设置
	loop_label = get_label(ob);
	set_label(ob, loop_label);
	// 生成条件表达式的字节码
	generate_expression(exe, block, while_s->condition, ob);
	// 获取break标签
	while_s->block->parent.statement.break_label = get_label(ob);
	// 获取continue标签
	while_s->block->parent.statement.continue_label = get_label(ob);
	// 如果条件表达式的值为假，就跳转到break标签
	generate_code(ob, statement->line_number,DVM_JUMP_IF_FALSE,while_s->block->parent.statement.break_label);
	// 生成while语句链表字节码
	generate_statement_list(exe, while_s->block,while_s->block->statement_list, ob);
	// 设置continue标签
	set_label(ob, while_s->block->parent.statement.continue_label);
	// 跳转到loop标签
	generate_code(ob, statement->line_number, DVM_JUMP, loop_label);
	// 设置break标签
	set_label(ob, while_s->block->parent.statement.break_label);
}
// 生成for语句字节码
static void generate_for_statement(DVM_Executable *exe, Block *block, Statement *statement, OpcodeBuf *ob){
	int loop_label;
	ForStatement *for_s = &statement->u.for_s;
	// 如果初始化表达式存在就生成初始化字节码
	if (for_s->init) {
		generate_expression_statement(exe, block, for_s->init, ob);
	}
	// 获得并设置loop标签
	loop_label = get_label(ob);
	set_label(ob, loop_label);
	// 如果条件表达式存在，则生成条件表达式字节码
	if (for_s->condition) {
		generate_expression(exe, block, for_s->condition, ob);
	}
	// 获得break和continue标签
	for_s->block->parent.statement.break_label = get_label(ob);
	for_s->block->parent.statement.continue_label = get_label(ob);
	// 如果条件表达式存在
	// 并且条件表达式测试失败，就跳转到break标签
	if (for_s->condition) {
		generate_code(ob, statement->line_number, DVM_JUMP_IF_FALSE, for_s->block->parent.statement.break_label);
	}
	// 生成for语句链表字节码
	generate_statement_list(exe, for_s->block, for_s->block->statement_list, ob);
	set_label(ob, for_s->block->parent.statement.continue_label);
	// 如果后表达式存在，就生成其字节码
	if (for_s->post) {
		generate_expression_statement(exe, block, for_s->post, ob);
	}
	// 跳转到loop语句
	generate_code(ob, statement->line_number, DVM_JUMP, loop_label);
	// 设置break标签
	set_label(ob, for_s->block->parent.statement.break_label);
}
// 生成返回语句
static void generate_return_statement(DVM_Executable *exe, Block *block, Statement *statement, OpcodeBuf *ob){
	DBG_assert(statement->u.return_s.return_value != NULL,
		("return value is null."));
	// 生成返回值表达式字节码
	generate_expression(exe, block, statement->u.return_s.return_value, ob);
	// RETURN 以栈顶的值作为返回值并将函数return
	generate_code(ob, statement->line_number, DVM_RETURN);
}
// 生成break语句
static void generate_break_statement(DVM_Executable *exe, Block *block, Statement *statement, OpcodeBuf *ob){
	BreakStatement *break_s = &statement->u.break_s;
	Block       *block_p;
	// 从当前语句块范围内开始由内层向外层寻找
	for (block_p = block; block_p; block_p = block_p->outer_block) {
		// 如果当前块不是for语句或者while语句，则向上一层
		if (block_p->type != WHILE_STATEMENT_BLOCK && block_p->type != FOR_STATEMENT_BLOCK)
			continue;
		// 如果没有break标签，则退出查找
		if (break_s->label == NULL) {
			break;
		}
		// 如果是whild语句
		if (block_p->type == WHILE_STATEMENT_BLOCK) {
			// 如果标签不存在，则向上一层
			if (block_p->parent.statement.statement->u.while_s.label == NULL)
				continue;
			// 如果两标签相同，则退出查找
			if (!strcmp(break_s->label,block_p->parent.statement.statement->u.while_s.label)) {
				break;
			}
		}
		// 如果是for语句
		else if (block_p->type == FOR_STATEMENT_BLOCK) {
			if (block_p->parent.statement.statement->u.for_s.label == NULL)
				continue;
			// 如果找到了此标签，则退出查找
			if (!strcmp(break_s->label, block_p->parent.statement.statement->u.for_s.label)) {
				break;
			}
		}
	}
	// 如果最后标签为null，则报编译时错误，未能找到标签
	if (block_p == NULL) {
		dkc_compile_error(statement->line_number,
			LABEL_NOT_FOUND_ERR,
			STRING_MESSAGE_ARGUMENT, "label", break_s->label,
			MESSAGE_ARGUMENT_END);
	}
	// 生成字节码，跳转到break标签
	generate_code(ob, statement->line_number,DVM_JUMP,block_p->parent.statement.break_label);
}
// 生成continue语句字节码
static void generate_continue_statement(DVM_Executable *exe, Block *block, Statement *statement, OpcodeBuf *ob){
	ContinueStatement *continue_s = &statement->u.continue_s;
	Block       *block_p;
	// 遍历当前语句块，由内向外查找标签，必须是while和for语句
	for (block_p = block; block_p; block_p = block_p->outer_block) {
		if (block_p->type != WHILE_STATEMENT_BLOCK && block_p->type != FOR_STATEMENT_BLOCK)
			continue;
		if (continue_s->label == NULL) {
			break;
		}
		if (block_p->type == WHILE_STATEMENT_BLOCK) {
			if (block_p->parent.statement.statement->u.while_s.label == NULL)
				continue;
			if (!strcmp(continue_s->label, block_p->parent.statement.statement->u.while_s.label)) {
				break;
			}
		}
		else if (block_p->type == FOR_STATEMENT_BLOCK) {
			if (block_p->parent.statement.statement->u.for_s.label == NULL)
				continue;
			if (!strcmp(continue_s->label, block_p->parent.statement.statement->u.for_s.label)) {
				break;
			}
		}
	}
	// 如果没有找到，报编译时错误
	if (block_p == NULL) {
		dkc_compile_error(statement->line_number,
			LABEL_NOT_FOUND_ERR,
			STRING_MESSAGE_ARGUMENT, "label", continue_s->label,
			MESSAGE_ARGUMENT_END);
	}
	// 生成字节码跳转到continue标签
	generate_code(ob, statement->line_number, DVM_JUMP, block_p->parent.statement.continue_label);
}
// 生成初始化语句字节码
static void generate_initializer(DVM_Executable *exe, Block *block, Statement *statement, OpcodeBuf *ob){
	Declaration *decl = statement->u.declaration_s;
	if (decl->initializer == NULL)
		return;
	generate_expression(exe, block, decl->initializer, ob);
	// 将栈顶的值弹出保存在初始化表达式所作用的标识符上
	generate_pop_to_identifier(decl, statement->line_number, ob);
}
// 生成语句链表字节码
static void generate_statement_list(DVM_Executable *exe, Block *current_block, StatementList *statement_list, OpcodeBuf *ob){
	StatementList *pos;
	// 遍历语句链表，根据语句的类型生成字节码
	for (pos = statement_list; pos; pos = pos->next) {
		switch (pos->statement->type) {
		case EXPRESSION_STATEMENT:
			generate_expression_statement(exe, current_block, pos->statement->u.expression_s, ob);
			break;
		case IF_STATEMENT:
			generate_if_statement(exe, current_block, pos->statement, ob);
			break;
		case WHILE_STATEMENT:
			generate_while_statement(exe, current_block, pos->statement, ob);
			break;
		case FOR_STATEMENT:
			generate_for_statement(exe, current_block, pos->statement, ob);
			break;
		case FOREACH_STATEMENT:
			break;
		case RETURN_STATEMENT:
			generate_return_statement(exe, current_block, pos->statement, ob);
			break;
		case BREAK_STATEMENT:
			generate_break_statement(exe, current_block, pos->statement, ob);
			break;
		case CONTINUE_STATEMENT:
			generate_continue_statement(exe, current_block,
				pos->statement, ob);
			break;
		case TRY_STATEMENT:
			break;
		case THROW_STATEMENT:
			break;
		case DECLARATION_STATEMENT:
			generate_initializer(exe, current_block, pos->statement, ob);
			break;
		case STATEMENT_TYPE_COUNT_PLUS_1: /* FALLTHRU */
		default:
			DBG_assert(0, ("pos->statement->type..", pos->statement->type));
		}
	}
}

static void init_opcode_buf(OpcodeBuf *ob){
    ob->size = 0;
    ob->alloc_size = 0;
    ob->code = NULL;
    ob->label_table_size = 0;
    ob->label_table_alloc_size = 0;
    ob->label_table = NULL;
    ob->line_number_size = 0;
    ob->line_number = NULL;
}
// 修复表
static void fix_labels(OpcodeBuf *ob){
	int i;
	int j;
	OpcodeInfo *info;
	int label;
	int address;
	// 按字节遍历整个字节码缓冲区
	for (i = 0; i < ob->size; i++) {
		// 遍历操作代码部分
		// 如果当前字节码是JUMP,JUMP_IF_TRUE,JUMP_IF_FALSE
		if (ob->code[i] == DVM_JUMP || ob->code[i] == DVM_JUMP_IF_TRUE || ob->code[i] == DVM_JUMP_IF_FALSE) {
			// 操作码之后第一个字节左移8位加上之后第二个字节的内容为标签
			label = (ob->code[i + 1] << 8) + (ob->code[i + 2]);
			// 根据标签获取标签表中的地址
			address = ob->label_table[label].label_address;
			// 将地址右移8位，放在操作码之后的第一个字节内（高8位），再将操作码的低8位放在之后的2字节
			ob->code[i + 1] = (DVM_Byte)(address >> 8);
			ob->code[i + 2] = (DVM_Byte)(address & 0xff);
		}
		info = &dvm_opcode_info[ob->code[i]];
		// 遍历操作数部分
		for (j = 0; info->parameter[j] != '\0'; j++) {
			switch (info->parameter[j]) {
			case 'b':
				i++;
				break;
				// 碰到p和s前进两个字节
			case 's': /* FALLTHRU */
			case 'p':
				i += 2;
				break;
			default:
				DBG_assert(0, ("param..%s, j..%d", info->parameter, j));
			}
		}
	}
}
// 修复字节码缓冲区
static DVM_Byte* fix_opcode_buf(OpcodeBuf *ob){
    DVM_Byte *ret;
	// 修复表
    fix_labels(ob);
	// 重新分配字节码存储器的内存
    ret = MEM_realloc(ob->code, ob->size);
    // 释放标签表的内存
	MEM_free(ob->label_table);
    return ret;
}
// 拷贝函数
static void copy_function(FunctionDefinition *src, DVM_Function *dest){
	// 拷贝类型指定器
	dest->type = copy_type_specifier(src->type);
	// 拷贝函数名
	dest->name = MEM_strdup(src->name);
	// 拷贝形参链表
	dest->parameter = copy_parameter_list(src->parameter, &dest->parameter_count);
	// 如果存在语句块
	if (src->block) {
		// 拷贝局部变量链表
		dest->local_variable = copy_local_variables(src, dest->parameter_count);
		dest->local_variable_count = src->local_variable_count - dest->parameter_count;
	}
	else {
		dest->local_variable = NULL;
		dest->local_variable_count = 0;
	}
}
// 计算栈内存需要量
static int calc_need_stack_size(DVM_Byte *code, int code_size){
	int i, j;
	int stack_size = 0;
	OpcodeInfo  *info;
	// 按字节遍历整个字节码缓冲区
	for (i = 0; i < code_size; i++) {
		// 获取反编译信息
		info = &dvm_opcode_info[code[i]];
		// 提取每条字节码所需的栈内存数量，并增加栈总量
		if (info->stack_increment > 0) {
			stack_size += info->stack_increment;
		}
		// 遍历操作数，前进相应的字节数
		for (j = 0; info->parameter[j] != '\0'; j++) {
			switch (info->parameter[j]) {
			case 'b':
				i++;
				break;
			case 's': /* FALLTHRU */
			case 'p':
				i += 2;
				break;
			default:
				DBG_assert(0, ("param..%s, j..%d", info->parameter, j));
			}
		}
	}
	// 返回栈需求总量
	return stack_size;
}
// 添加函数
static void add_functions(DKC_Compiler *compiler, DVM_Executable *exe){
	FunctionDefinition  *fd;
	int         i;
	int         func_count = 0;
	OpcodeBuf           ob;
	// 遍历编译器的函数链表获得函数数量
	for (fd = compiler->function_list; fd; fd = fd->next) {
		func_count++;
	}
	exe->function_count = func_count;
	exe->function = MEM_malloc(sizeof(DVM_Function) * func_count);
	// 遍历函数链表
	for (fd = compiler->function_list, i = 0; fd; fd = fd->next, i++) {
		// 复制函数
		copy_function(fd, &exe->function[i]);
		// 如果函数语句块存在
		if (fd->block) {
			// 初始化字节码缓冲区
			init_opcode_buf(&ob);
			// 生成语句链表字节码
			generate_statement_list(exe, fd->block, fd->block->statement_list, &ob);
			// 是自定义函数
			exe->function[i].is_implemented = DVM_TRUE;
			exe->function[i].code_size = ob.size;
			exe->function[i].code = fix_opcode_buf(&ob);
			exe->function[i].line_number_size = ob.line_number_size;
			exe->function[i].line_number = ob.line_number;
			exe->function[i].need_stack_size = calc_need_stack_size(exe->function[i].code, exe->function[i].code_size);
		}
		else {
			exe->function[i].is_implemented = DVM_FALSE;
		}
	}
}
// 添加顶层信息
static void add_top_level(DKC_Compiler *compiler, DVM_Executable *exe){
	OpcodeBuf           ob;
	// 初始化字节码缓冲区
	init_opcode_buf(&ob);
	// 生成语句链表字节码
	generate_statement_list(exe, NULL, compiler->statement_list,
		&ob);
	exe->code_size = ob.size;
	exe->code = fix_opcode_buf(&ob);
	exe->line_number_size = ob.line_number_size;
	exe->line_number = ob.line_number;
	exe->need_stack_size = calc_need_stack_size(exe->code, exe->code_size);
}

// 生成字节码的公共接口
DVM_Executable* dkc_generate(DKC_Compiler *compiler){
	DVM_Executable      *exe;

	exe = alloc_executable();
	// 添加全局变量
	add_global_variable(compiler, exe);
	// 添加函数
	add_functions(compiler, exe);
	// 添加顶层信息
	add_top_level(compiler, exe);

	return exe;
}
