#ifndef PUBLIC_DVM_H_INCLUDED
#define PUBLIC_DVM_H_INCLUDED

typedef struct DVM_Excecutable_tag DVM_Executable;
typedef struct DVM_VirtualMachine_tag DVM_VirtualMachine;

typedef struct DVM_Object_tag DVM_Object;
typedef struct DVM_String_tag DVM_String;
// 虚拟机bool类型
typedef enum {
    DVM_FALSE = 0,
    DVM_TRUE = 1
} DVM_Boolean;
// 虚拟机值类型，包括int，double，object，函数索引
typedef union {
    int         int_value;
    double      double_value;
    DVM_Object  *object;
    int         function_index;
} DVM_Value;
// 创建虚拟机
DVM_VirtualMachine *DVM_create_virtual_machine(void);
// 向虚拟机内添加执行体
void DVM_add_executable(DVM_VirtualMachine *dvm, DVM_Executable *executable);
// 启动虚拟机
DVM_Value DVM_execute(DVM_VirtualMachine *dvm);
// 释放虚拟机
void DVM_dispose_virtual_machine(DVM_VirtualMachine *dvm);

#endif /* PUBLIC_DVM_CODE_H_INCLUDED */
