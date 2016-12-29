#ifndef PUBLIC_DVM_CODE_H_INCLUDED
#define PUBLIC_DVM_CODE_H_INCLUDED

#include "stdafx.h"
//#include <stdio.h>
//#include <wchar.h>
#include "DVM.h"

// 虚拟机基本类型
typedef enum {
    DVM_BOOLEAN_TYPE,
    DVM_INT_TYPE,
    DVM_DOUBLE_TYPE,
    DVM_STRING_TYPE,
    DVM_NULL_TYPE
} DVM_BasicType;

typedef struct DVM_TypeSpecifier_tag DVM_TypeSpecifier;
// 虚拟机局部变量定义，包括变量名，变量类型
typedef struct {
    char                *name;
    DVM_TypeSpecifier   *type;
} DVM_LocalVariable;
// 虚拟机继承标志，包括函数和数组
typedef enum {
    DVM_FUNCTION_DERIVE,
    DVM_ARRAY_DERIVE
} DVM_DeriveTag;
// 虚拟机函数继承定义，包括一个形参数量，和一个局部变量地址
typedef struct {
    int                 parameter_count;
    DVM_LocalVariable   *parameter;
} DVM_FunctionDerive;
// 虚拟机数组继承
typedef struct {
    int dummy; /* make compiler happy */
} DVM_ArrayDerive;
// 虚拟机类型继承定义，包括一个虚拟机继承标志和函数继承的值
typedef struct DVM_TypeDerive_tag {
    DVM_DeriveTag       tag;
    union {
        DVM_FunctionDerive      function_d;
    } u;
} DVM_TypeDerive;
// 虚拟机类型指定器定义，包含基本类型，继承数量，和类型继承
struct DVM_TypeSpecifier_tag {
    DVM_BasicType       basic_type;
    int                 derive_count;
    DVM_TypeDerive      *derive;
};
// 虚拟机内部使用宽字符
typedef wchar_t DVM_Char;
// 虚拟机byte类型为一个字节
typedef unsigned char DVM_Byte;
// 虚拟机的操作码
typedef enum {
    DVM_PUSH_INT_1BYTE = 1,
    DVM_PUSH_INT_2BYTE,
    DVM_PUSH_INT,
    DVM_PUSH_DOUBLE_0,
    DVM_PUSH_DOUBLE_1,
    DVM_PUSH_DOUBLE,
    DVM_PUSH_STRING,
    DVM_PUSH_NULL,
    /**********/
    DVM_PUSH_STACK_INT,
    DVM_PUSH_STACK_DOUBLE,
    DVM_PUSH_STACK_OBJECT,
    DVM_POP_STACK_INT,
    DVM_POP_STACK_DOUBLE,
    DVM_POP_STACK_OBJECT,
    /**********/
    DVM_PUSH_STATIC_INT,
    DVM_PUSH_STATIC_DOUBLE,
    DVM_PUSH_STATIC_OBJECT,
    DVM_POP_STATIC_INT,
    DVM_POP_STATIC_DOUBLE,
    DVM_POP_STATIC_OBJECT,
    /**********/
    DVM_PUSH_ARRAY_INT,
    DVM_PUSH_ARRAY_DOUBLE,
    DVM_PUSH_ARRAY_OBJECT,
    DVM_POP_ARRAY_INT,
    DVM_POP_ARRAY_DOUBLE,
    DVM_POP_ARRAY_OBJECT,
    /**********/
    DVM_ADD_INT,
    DVM_ADD_DOUBLE,
    DVM_ADD_STRING,
    DVM_SUB_INT,
    DVM_SUB_DOUBLE,
    DVM_MUL_INT,
    DVM_MUL_DOUBLE,
    DVM_DIV_INT,
    DVM_DIV_DOUBLE,
    DVM_MOD_INT,
    DVM_MOD_DOUBLE,
    DVM_MINUS_INT,
    DVM_MINUS_DOUBLE,
    DVM_INCREMENT,
    DVM_DECREMENT,
    DVM_CAST_INT_TO_DOUBLE,
    DVM_CAST_DOUBLE_TO_INT,
    DVM_CAST_BOOLEAN_TO_STRING,
    DVM_CAST_INT_TO_STRING,
    DVM_CAST_DOUBLE_TO_STRING,
    DVM_EQ_INT,
    DVM_EQ_DOUBLE,
    DVM_EQ_OBJECT,
    DVM_EQ_STRING,
    DVM_GT_INT,
    DVM_GT_DOUBLE,
    DVM_GT_STRING,
    DVM_GE_INT,
    DVM_GE_DOUBLE,
    DVM_GE_STRING,
    DVM_LT_INT,
    DVM_LT_DOUBLE,
    DVM_LT_STRING,
    DVM_LE_INT,
    DVM_LE_DOUBLE,
    DVM_LE_STRING,
    DVM_NE_INT,
    DVM_NE_DOUBLE,
    DVM_NE_OBJECT,
    DVM_NE_STRING,
    DVM_LOGICAL_AND,
    DVM_LOGICAL_OR,
    DVM_LOGICAL_NOT,
    DVM_POP,
    DVM_DUPLICATE,
    DVM_JUMP,
    DVM_JUMP_IF_TRUE,
    DVM_JUMP_IF_FALSE,
    /**********/
    DVM_PUSH_FUNCTION,
    DVM_INVOKE,
    DVM_RETURN,
    /**********/
    DVM_NEW_ARRAY,
    DVM_NEW_ARRAY_LITERAL_INT,
    DVM_NEW_ARRAY_LITERAL_DOUBLE,
    DVM_NEW_ARRAY_LITERAL_OBJECT
} DVM_Opcode;
// 虚拟机常量池类型，包括int，double，string
typedef enum {
    DVM_CONSTANT_INT,
    DVM_CONSTANT_DOUBLE,
    DVM_CONSTANT_STRING
} DVM_ConstantPoolTag;
// 虚拟机常量池定义，包括常量池类型，和对应常量池的值
typedef struct {
    DVM_ConstantPoolTag tag;
    union {
        int     c_int;
        double  c_double;
        DVM_Char *c_string;
    } u;
} DVM_ConstantPool;
// 虚拟机变量定义，包括变量名，虚拟机类型指定器
typedef struct {
    char                *name;
    DVM_TypeSpecifier   *type;
} DVM_Variable;
// 次虚拟机行号定义，包括行号，程序计数器起始地址，程序计数器计数
typedef struct {
    int line_number;
    int start_pc;
    int pc_count;
} DVM_LineNumber;
// 虚拟机函数定义
typedef struct {
    // 函数类型指定器
	DVM_TypeSpecifier   *type;
    // 函数名
	char                *name;
    // 形参数量
	int                 parameter_count;
    // 形参链表
	DVM_LocalVariable   *parameter;
    // 是自定义函数还是本地函数
	DVM_Boolean         is_implemented;
    // 局部变量数量
	int                 local_variable_count;
	// 局部变量链表
    DVM_LocalVariable   *local_variable;
    // 代码数量
	int                 code_size;
    DVM_Byte            *code;
	// 行数大小
    int                 line_number_size;
    DVM_LineNumber      *line_number;
	// 对于stack的需求大小
    int                 need_stack_size;
} DVM_Function;
// 执行体结构体定义
struct DVM_Excecutable_tag {
	// 常量池数量
    int                 constant_pool_count;
    DVM_ConstantPool    *constant_pool;
	// 全局变量数量
    int                 global_variable_count;
    DVM_Variable        *global_variable;
	// 函数数量
    int                 function_count;
    DVM_Function        *function;
	// 类型指定器数量
    int                 type_specifier_count;
    DVM_TypeSpecifier   *type_specifier;
	// 代码大小
    int                 code_size;
    DVM_Byte            *code;
	// 代码行数
    int                 line_number_size;
    DVM_LineNumber      *line_number;
	// stack需求量
    int                 need_stack_size;
};

#endif /* PUBLIC_DVM_CODE_H_INCLUDED */
