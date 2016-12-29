#include "stdafx.h"
//#include <stdio.h>
//#include <string.h>
#include "DBG.h"
#include "share.h"

// 操作指令信息
extern OpcodeInfo dvm_opcode_info[];
// 显示常量池的内容
static void dump_constant_pool(int constant_pool_count, DVM_ConstantPool *constant_pool){
    int i;

    printf("** constant pool section ***********************************\n");
    // 遍历常量池
	for (i = 0; i < constant_pool_count; i++) {
        // 显示索引
		printf("%05d:", i);
		// 根据常量池的内容类型
        switch (constant_pool[i].tag) {
        case DVM_CONSTANT_INT:
            printf("int %d\n", constant_pool[i].u.c_int);
            break;
        case DVM_CONSTANT_DOUBLE:
            printf("double %f\n", constant_pool[i].u.c_double);
            break;
        case DVM_CONSTANT_STRING:
            printf("string ");
            dvm_print_wcs_ln(stdout, constant_pool[i].u.c_string);
            break;
        default:
            DBG_assert(0, ("tag..%d\n", constant_pool[i].tag));
        }
    }
}
// 函数前向声明，根据类型指示器显示类型
static void dump_type(DVM_TypeSpecifier *type);
// 显示形参链表
static void dump_parameter_list(int parameter_count, DVM_LocalVariable *parameter_list){
    int i;

    printf("(");
	// 遍历形参链表
    for (i = 0; i < parameter_count; i++) {
		// 显示类型
        dump_type(parameter_list[i].type);
		// 显示形参的名称
        printf(" %s", parameter_list[i].name);
        if (i < parameter_count-1) {
            printf(", ");
        }
    }
    printf(")");
}
// 显示类型
static void dump_type(DVM_TypeSpecifier *type){
    int i;
	// 根据类型指示器的基本类型选择
    switch (type->basic_type) {
    case DVM_BOOLEAN_TYPE:
        printf("boolean ");
        break;
    case DVM_INT_TYPE:
        printf("int ");
        break;
    case DVM_DOUBLE_TYPE:
        printf("double ");
        break;
    case DVM_STRING_TYPE:
        printf("string ");
        break;
    case DVM_NULL_TYPE: /* FALLTHRU */
    default:
        DBG_assert(0, ("basic_type..%d\n", type->basic_type));
    }
	// 遍历类型指示器的类型继承链表
    for (i = 0; i < type->derive_count; i++) {
        switch (type->derive[i].tag) {
		// 根据继承类型选择
        case DVM_FUNCTION_DERIVE:
			// 如果是函数，则显示函数的形参链表
            dump_parameter_list(type->derive[i].u.function_d.parameter_count,
                                type->derive[i].u.function_d.parameter);
            break;
        case DVM_ARRAY_DERIVE:
            printf("[]");
            break;
        default:
            DBG_assert(0, ("derive_tag..%d\n", type->derive->tag));
        }
    }
}
// 显示全局变量
static void dump_variable(int global_variable_count, DVM_Variable *global_variable){
    int i;

    printf("** global variable section *********************************\n");
	// 遍历全局变量链表
    for (i = 0; i < global_variable_count; i++) {
        printf("%5d:", i);
		// 显示全局变量的类型
        dump_type(global_variable[i].type);
		// 显示名称
        printf(" %s\n", global_variable[i].name);
    }
}
// 显示操作指令
static void dump_opcode(int code_size, DVM_Byte *code){
    int i;
	// 遍历整个操作代码存储
    for (i = 0; i < code_size; i++) {
        OpcodeInfo *info;
        int value;
        int j;
		// 获得特定的操作代码信息
        info = &dvm_opcode_info[code[i]];
        printf("%4d %s ", i, info->mnemonic);
        for (j = 0; info->parameter[j] != '\0'; j++) {
            switch (info->parameter[j]) {
            case 'b':
                value = code[i+1];
                printf(" %d", value);
                i++;
                break;
            case 's': /* FALLTHRU */
            case 'p':
                value = (code[i+1] << 8) + code[i+2];
                printf(" %d", value);
                i += 2;
                break;
            default:
                DBG_assert(0, ("param..%s, j..%d", info->parameter, j));
            }
        }
        printf("\n");
    }
}
// 显示行号，程序计数器起始地址，程序计数器数量
static void dump_line_number(int line_number_size, DVM_LineNumber *line_number){
    int i;

    printf("*** line number ***\n");
	// 遍历行号链表
    for (i = 0; i < line_number_size; i++) {
        printf("%5d: from %5d size %5d\n",
               line_number[i].line_number,
               line_number[i].start_pc,
               line_number[i].pc_count);
    }
}
// 显示函数
static void dump_function(int function_count, DVM_Function *function){
    int i;

    printf("** function section ****************************************\n");
    // 根据函数数量遍历函数链表
	for (i = 0; i < function_count; i++) {
		// 显示索引和函数名称
        printf("*** [%d] %s ***\n", i, function[i].name);
		// 显示函数类型
        dump_type(function[i].type);
        printf(" %s ", function[i].name);
		// 显示形参链表
        dump_parameter_list(function[i].parameter_count,
                            function[i].parameter);
        printf("\n");
		// 如果函数内存在语句的话，显示函数内的语句的操作码和行号等
        if (function[i].code_size > 0) {
            dump_opcode(function[i].code_size, function[i].code);
            dump_line_number(function[i].line_number_size,
                             function[i].line_number);
        }
        printf("*** end of %s ***\n", function[i].name);
    }
}
// 显示类型指示器指示的类型
static void dump_types(int type_count, DVM_TypeSpecifier *types){
    int i;

    printf("** type section ********************************************\n");
    for (i = 0; i < type_count; i++) {
        printf("%5d:", i);
        dump_type(&types[i]);
        printf("\n");
    }
}
// 对执行体执行反汇编
void dvm_disassemble(DVM_Executable *exe){
    dump_constant_pool(exe->constant_pool_count, exe->constant_pool);
    dump_variable(exe->global_variable_count, exe->global_variable);
    dump_function(exe->function_count, exe->function);
    dump_types(exe->type_specifier_count, exe->type_specifier);
    printf("** toplevel ********************\n");
    dump_opcode(exe->code_size, exe->code);
    dump_line_number(exe->line_number_size, exe->line_number);
}
