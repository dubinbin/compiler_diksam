#include "stdafx.h"
#include "MEM.h"
#include "DBG.h"
#include "DVM_code.h"

// 函数前向声明，释放本地变量
static void dispose_local_variable(int local_variable_count,
                                   DVM_LocalVariable *local_variable_list);
// 释放类型继承
static void
dispose_type_derive(DVM_TypeSpecifier *type)
{
    int i;
	// 根据继承数量遍历类型继承数组
	// 类型继承数组为动态分配
    for (i = 0; i < type->derive_count; i++) {
        switch (type->derive[i].tag) {
		// 根据类型标志选择操作
        case DVM_FUNCTION_DERIVE:
			// 如果是函数，则释放局部变量
			// 局部变量链表由相应的类型继承链表内的形参数量和形参提供
            dispose_local_variable(type->derive[i].u
                                   .function_d.parameter_count,
                                   type->derive[i].u
                                   .function_d.parameter);
            break;
        case DVM_ARRAY_DERIVE:
			// 如果是数组
            break;
        default:
            DBG_assert(0, ("derive->tag..%d\n", type->derive[i].tag));
        }
    }
	// 将内存返回存储器
    MEM_free(type->derive);
}
// 释放类型指示器
static void
dispose_type_specifier(DVM_TypeSpecifier *type)
{
	// 释放类型继承
    dispose_type_derive(type);
	// 将内存返回存储器
    MEM_free(type);
}
// 释放局部变量
static void
dispose_local_variable(int local_variable_count,
                       DVM_LocalVariable *local_variable)
{
    int i;
	// 根据局部变量的数量遍历并根据局部变量的名称归还内存
    for (i = 0; i < local_variable_count; i++) {
        MEM_free(local_variable[i].name);
		// 释放本地变量的类型指示器
        dispose_type_specifier(local_variable[i].type);
    }
	// 归还此内存
    MEM_free(local_variable);
}
// 释放执行体
void
dvm_dispose_executable(DVM_Executable *exe)
{
    int i;
	// 根据变量池大小遍历常量池，如果当前常量池内内容为字符串类型
	// 则将字符串的内存归还，最后释放常量池
    for (i = 0; i < exe->constant_pool_count; i++) {
        if (exe->constant_pool[i].tag == DVM_CONSTANT_STRING) {
            MEM_free(exe->constant_pool[i].u.c_string);
        }
    }
    MEM_free(exe->constant_pool);
    // 根据全局变量数量遍历全局变量，释放全局变量标识符所使用内存
	// 释放类型指定器，释放全局变量内存
    for (i = 0; i < exe->global_variable_count; i++) {
        MEM_free(exe->global_variable[i].name);
        dispose_type_specifier(exe->global_variable[i].type);
    }
    MEM_free(exe->global_variable);
	// 遍历函数链表
    for (i = 0; i < exe->function_count; i++) {
		// 释放当前函数的类型指定器
        dispose_type_specifier(exe->function[i].type);
		// 释放函数名所占内存
        MEM_free(exe->function[i].name);
		// 释放形参链表（形参被当作局部变量）
        dispose_local_variable(exe->function[i].parameter_count,
                               exe->function[i].parameter);
        // 如果是自定义函数的话，需要释放局部变量
		if (exe->function[i].is_implemented) {
            dispose_local_variable(exe->function[i].local_variable_count,
                                   exe->function[i].local_variable);
            // 释放代码存储和行号存储内存
			MEM_free(exe->function[i].code);
            MEM_free(exe->function[i].line_number);
        }
    }
	// 释放函数内存
    MEM_free(exe->function);

    for (i = 0; i < exe->type_specifier_count; i++) {
        dispose_type_derive(&exe->type_specifier[i]);
    }
    MEM_free(exe->type_specifier);

    MEM_free(exe->code);
    MEM_free(exe->line_number);
	// 释放执行体内存
    MEM_free(exe);
}