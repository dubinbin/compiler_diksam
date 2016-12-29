#include "stdafx.h"
//#include <math.h>
//#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "dvm_pri.h"

extern OpcodeInfo dvm_opcode_info[];
// 创建虚拟机
DVM_VirtualMachine* DVM_create_virtual_machine(void){
	DVM_VirtualMachine *dvm;

	dvm = MEM_malloc(sizeof(DVM_VirtualMachine));
	dvm->stack.alloc_size = STACK_ALLOC_SIZE;
	dvm->stack.stack = MEM_malloc(sizeof(DVM_Value) * STACK_ALLOC_SIZE);
	dvm->stack.pointer_flags = MEM_malloc(sizeof(DVM_Boolean) * STACK_ALLOC_SIZE);
	dvm->stack.stack_pointer = 0;
	dvm->heap.current_heap_size = 0;
	dvm->heap.header = NULL;
	dvm->heap.current_threshold = HEAP_THRESHOLD_SIZE;
	dvm->current_executable = NULL;
	dvm->function = NULL;
	dvm->function_count = 0;
	dvm->executable = NULL;

	dvm_add_native_functions(dvm);

	return dvm;
}
// 添加本地函数，接受本地函数的名称和函数指针及本地函数的参数数量
void DVM_add_native_function(DVM_VirtualMachine *dvm, char *func_name, DVM_NativeFunctionProc *proc, int arg_count){
	
	dvm->function = MEM_realloc(dvm->function, sizeof(Function) * (dvm->function_count + 1));
	dvm->function[dvm->function_count].name = MEM_strdup(func_name);
	dvm->function[dvm->function_count].kind = NATIVE_FUNCTION;
	dvm->function[dvm->function_count].u.native_f.proc = proc;
	dvm->function[dvm->function_count].u.native_f.arg_count = arg_count;
	dvm->function_count++;
}
// 添加自定义函数
static void add_functions(DVM_VirtualMachine *dvm, DVM_Executable *executable){
	int src_idx;
	int dest_idx;
	int func_count = 0;
	// 遍历执行体的函数链表，如果函数是自定义函数，则增加一次自定义函数的计数
	// 如果编虚拟机中的函数名称与执行体中的函数名称相同，则报函数重定义错误
	for (src_idx = 0; src_idx < executable->function_count; src_idx++) {
		if (executable->function[src_idx].is_implemented) {
			func_count++;
			for (dest_idx = 0; dest_idx < dvm->function_count; dest_idx++) {
				if (!strcmp(dvm->function[dest_idx].name, executable->function[src_idx].name)) {
					dvm_error(NULL, NULL, NO_LINE_NUMBER_PC,
						FUNCTION_MULTIPLE_DEFINE_ERR,
						STRING_MESSAGE_ARGUMENT, "name",
						dvm->function[dest_idx].name,
						MESSAGE_ARGUMENT_END);
				}
			}
		}
	}
	// 重新分配虚拟机中的函数链表的内存
	dvm->function = MEM_realloc(dvm->function, sizeof(Function) * (dvm->function_count + func_count));
	// 遍历执行体中函数链表，如果是本地函数则跳过，如果是自定义函数，则为虚拟机函数链表的新节点初始化
	for (src_idx = 0, dest_idx = dvm->function_count; src_idx < executable->function_count; src_idx++) {
		if (!executable->function[src_idx].is_implemented)
			continue;
		dvm->function[dest_idx].name = MEM_strdup(executable->function[src_idx].name);
		dvm->function[dest_idx].u.diksam_f.executable = executable;
		dvm->function[dest_idx].u.diksam_f.index = src_idx;
		dest_idx++;
	}
	dvm->function_count += func_count;
}
// 根据参数提供的名称寻找函数
static int search_function(DVM_VirtualMachine *dvm, char *name){
	int i;
	// 遍历虚拟机函数链表，比对名称，如果相同则返回该节点的索引
	// 否则报函数未定义错误
	for (i = 0; i < dvm->function_count; i++) {
		if (!strcmp(dvm->function[i].name, name)) {
			return i;
		}
	}
	dvm_error(NULL, NULL, NO_LINE_NUMBER_PC, FUNCTION_NOT_FOUND_ERR,
		STRING_MESSAGE_ARGUMENT, "name", name,
		MESSAGE_ARGUMENT_END);
	return 0; /* make compiler happy */
}
// 转换函数的字节码
static void convert_code(DVM_VirtualMachine *dvm, DVM_Executable *exe, DVM_Byte *code, int code_size, DVM_Function *func){
	int i;
	int j;
	OpcodeInfo *info;
	int src_idx;
	unsigned int dest_idx;
	// 按字节遍历字节码缓冲区
	for (i = 0; i < code_size; i++) {
		// 如果当前的字节码为 PUSH_STACK_INT PUSH_STACK_DOUBLE PUSH_STACK_OBJECT
		// POP_STACK_INT POP_STACK_DOUBLE POP_STACK_OBJECT
		// 则获取跟随在操作码之后的第一个字节的操作数的2字节形式（还原在字节码生成阶段被分开的操作数）
		// 如果提取出的操作数（其实是基于base的偏移值）大于等于函数的参数数量（也就是说是此偏移值指向一个局部变量）
		// 则需要将此索引退后CALL_INFO_ALIGN_SIZE个字节，之前保存着函数调用时必要的保存信息，否则是参数，参数在
		// 函数调用信息之前不需要更改索引值
		if (code[i] == DVM_PUSH_STACK_INT || code[i] == DVM_PUSH_STACK_DOUBLE || code[i] == DVM_PUSH_STACK_OBJECT
			|| code[i] == DVM_POP_STACK_INT || code[i] == DVM_POP_STACK_DOUBLE || code[i] == DVM_POP_STACK_OBJECT) {

			DBG_assert(func != NULL, ("func == NULL!\n"));

			src_idx = GET_2BYTE_INT(&code[i + 1]);
			if (src_idx >= func->parameter_count) {
				dest_idx = src_idx + CALL_INFO_ALIGN_SIZE;
			}
			else {
				dest_idx = src_idx;
			}
			SET_2BYTE_INT(&code[i + 1], dest_idx);

		}
		// 如果操作码是 PUSH_FUNCTION
		else if (code[i] == DVM_PUSH_FUNCTION) {
			int idx_in_exe;
			unsigned int func_idx;
			// 获得此函数在执行体中的索引值
			// 此索引值为编译器在生成字节码时写入的值
			idx_in_exe = GET_2BYTE_INT(&code[i + 1]);
			// 在虚拟机中寻找函数并获取其在执行体中的索引
			func_idx = search_function(dvm, exe->function[idx_in_exe].name);
			// 重新写入索引值
			SET_2BYTE_INT(&code[i + 1], func_idx);
		}
		info = &dvm_opcode_info[code[i]];
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
}
// 初始化值，虚拟机会对所有的值进行初始化
static void initialize_value(DVM_VirtualMachine *dvm,DVM_TypeSpecifier *type, DVM_Value *value){
    if (type->derive_count > 0) {
        if (type->derive[0].tag == DVM_ARRAY_DERIVE) {
            value->object = NULL;
        } else {
            DBG_assert(0, ("tag..%d", type->derive[0].tag));
        }
    } else {
        switch (type->basic_type) {
        case DVM_BOOLEAN_TYPE: /* FALLTHRU */
        case DVM_INT_TYPE:
            value->int_value = 0;
            break;
        case DVM_DOUBLE_TYPE:
            value->double_value = 0.0;
            break;
        case DVM_STRING_TYPE:
            value->object = NULL;
            break;
        case DVM_NULL_TYPE: /* FALLTHRU */
        default:
            DBG_assert(0, ("basic_type..%d", type->basic_type));
        }
    }
}
// 添加静态变量
static void add_static_variables(DVM_VirtualMachine *dvm, DVM_Executable *exe){
	int i;

	dvm->static_v.variable = MEM_malloc(sizeof(DVM_Value) * exe->global_variable_count);
	dvm->static_v.variable_count = exe->global_variable_count;
	// 遍历执行体的全局变量，将所有字符串类型加入静态池中
	for (i = 0; i < exe->global_variable_count; i++) {
		if (exe->global_variable[i].type->basic_type == DVM_STRING_TYPE) {
			dvm->static_v.variable[i].object = NULL;
		}
	}
	// 初始化形态池中的所有变量
	for (i = 0; i < exe->global_variable_count; i++) {
		initialize_value(dvm, exe->global_variable[i].type, &dvm->static_v.variable[i]);
	}
}
// 根据参数添加执行体
void DVM_add_executable(DVM_VirtualMachine *dvm, DVM_Executable *executable){
	int i;
	// 设定执行体
	dvm->executable = executable;
	add_functions(dvm, executable);
	// 修复函数调用字节码
	convert_code(dvm, executable, executable->code, executable->code_size, NULL);
	// 遍历执行体的函数链表，并修复每一个函数的字节码
	for (i = 0; i < executable->function_count; i++) {
		convert_code(dvm, executable, executable->function[i].code, executable->function[i].code_size, &executable->function[i]);
	}
	// 添加静态变量
	add_static_variables(dvm, executable);
}
// 连接由参数指定的两个字符串
static DVM_Object* chain_string(DVM_VirtualMachine *dvm, DVM_Object *str1, DVM_Object *str2){
	int result_len;
	DVM_Char    *left;
	DVM_Char    *right;
	DVM_Char    *result;
	DVM_Object *ret;

	if (str1 == NULL) {
		left = NULL_STRING;
	}
	else {
		left = str1->u.string.string;
	}
	if (str2 == NULL) {
		right = NULL_STRING;
	}
	else {
		right = str2->u.string.string;
	}
	result_len = dvm_wcslen(left) + dvm_wcslen(right);
	result = MEM_malloc(sizeof(DVM_Char) * (result_len + 1));

	dvm_wcscpy(result, left);
	dvm_wcscat(result, right);

	ret = dvm_create_dvm_string_i(dvm, result);

	return ret;
}
// 调用本地函数
static void invoke_native_function(DVM_VirtualMachine *dvm, Function *func, int *sp_p){
	DVM_Value   *stack;
	int         sp;
	DVM_Value   ret;
	// 保存虚拟机栈
	stack = dvm->stack.stack;
	// 保存栈指针
	sp = *sp_p;

	DBG_assert(func->kind == NATIVE_FUNCTION, ("func->kind..%d", func->kind));
	// 执行本地函数调用
	// （sp - func->u.native_f.arg_count - 1）应指向传递给本地函数的以一个变量
	ret = func->u.native_f.proc(dvm, func->u.native_f.arg_count, &stack[sp - func->u.native_f.arg_count - 1]);
	// 将返回值放入栈中
	stack[sp - func->u.native_f.arg_count - 1] = ret;
	// 返回当前的栈指针
	*sp_p = sp - (func->u.native_f.arg_count);
}
// 初始化函数的局部变量，提供一个栈指针
static void initialize_local_variables(DVM_VirtualMachine *dvm, DVM_Function *func, int from_sp){
	int i;
	int sp_idx;
	// 遍历函数的局部变量，将相应的栈指针标志复位
	for (i = 0, sp_idx = from_sp; i < func->local_variable_count; i++, sp_idx++) {
		dvm->stack.pointer_flags[i] = DVM_FALSE;
	}
	// 遍历栈中的局部变量，对其进行初始化，如果栈元素为字符串，则将对应栈指针标志置位
	for (i = 0, sp_idx = from_sp; i < func->local_variable_count; i++, sp_idx++) {
		initialize_value(dvm, func->local_variable[i].type, &dvm->stack.stack[sp_idx]);
		if (func->local_variable[i].type->basic_type == DVM_STRING_TYPE) {
			dvm->stack.pointer_flags[i] = DVM_TRUE;
		}
	}
}
// 扩展栈容量
static void expand_stack(DVM_VirtualMachine *dvm, int need_stack_size){
	int revalue_up;
	int rest;
	// 计算栈目前的剩余量，如果剩余量小于等于当前栈需求量
	// 则需要扩展栈空间
	rest = dvm->stack.alloc_size - dvm->stack.stack_pointer;
	if (rest <= need_stack_size) {
		revalue_up = ((rest / STACK_ALLOC_SIZE) + 1) * STACK_ALLOC_SIZE;
		dvm->stack.alloc_size += revalue_up;
		dvm->stack.stack = MEM_realloc(dvm->stack.stack, dvm->stack.alloc_size * sizeof(DVM_Value));
		dvm->stack.pointer_flags = MEM_realloc(dvm->stack.pointer_flags, dvm->stack.alloc_size * sizeof(DVM_Boolean));
	}
}
// 调用自定义函数
static void invoke_diksam_function(DVM_VirtualMachine *dvm, Function **caller_p, Function *callee, DVM_Byte **code_p,
	int *code_size_p, int *pc_p, int *sp_p, int *base_p, DVM_Executable **exe_p){

	// 调用信息
	CallInfo *callInfo;
	// 被调用的函数
	DVM_Function *callee_p;
	int i;
	// 获取被调用函数的执行体的地址
	*exe_p = callee->u.diksam_f.executable;
	// 根据被调用函数所给出的执行体提供的函数索引在执行体中找到被调用函数的地址
	callee_p = &(*exe_p)->function[callee->u.diksam_f.index];
	// 扩展栈容量，CALL_INFO_ALIGN_SIZE为调用信息所占空间，还有被调用函数的局部变量的空间以及函数的栈需求量
	expand_stack(dvm, CALL_INFO_ALIGN_SIZE + callee_p->local_variable_count + (*exe_p)->function[callee->u.diksam_f.index].need_stack_size);
	// 获取虚拟机栈顶部的调用信息（目的是被备份）
	// 栈指针为第一个可写的栈空间，而栈指针-1是栈顶（栈的实现是栈向上增长）
	callInfo = (CallInfo*)&dvm->stack.stack[*sp_p - 1];
	callInfo->caller = *caller_p;
	callInfo->caller_address = *pc_p;
	callInfo->base = *base_p;
	// 将调用信息所占的栈内存标志复位
	for (i = 0; i < CALL_INFO_ALIGN_SIZE; i++) {
		dvm->stack.pointer_flags[*sp_p - 1 + i] = DVM_FALSE;
	}
	// 基地址为栈地址减去1（即调用信息首地址）再减去被调用函数的形参数量
	*base_p = *sp_p - 1 - callee_p->parameter_count;
	// 调用者指针目前指向被掉函数，一个新的函数栈建立完成，所以此时
	// 被掉函数就变成了下一个调用的调用者
	*caller_p = callee;
	// 初始化局部变量栈指针在调用信息的上方（栈向下增长的情况），所以跳过调用信息，便是被掉函数的
	// 局部变量的开始位置
	initialize_local_variables(dvm, callee_p, *sp_p + CALL_INFO_ALIGN_SIZE - 1);
	// 修改栈指针指向调用信息上方的函数局部变量的上方
	*sp_p += CALL_INFO_ALIGN_SIZE + callee_p->local_variable_count - 1;
	// 程序计数器复位
	*pc_p = 0;
	// 获取函数字节码及字节码大小
	*code_p = (*exe_p)->function[callee->u.diksam_f.index].code;
	*code_size_p = (*exe_p)->function[callee->u.diksam_f.index].code_size;
}
// 函数返回
static void return_function(DVM_VirtualMachine *dvm, Function **func_p, DVM_Byte **code_p, int *code_size_p, int *pc_p,
	int *sp_p, int *base_p, DVM_Executable **exe_p){
	DVM_Value return_value;
	CallInfo *callInfo;
	DVM_Function *caller_p;
	DVM_Function *callee_p;
	// 返回值被存放在当前栈顶（栈指针指向第一个可用栈空间，减一为栈顶）
	return_value = dvm->stack.stack[(*sp_p) - 1];
	// 根据被掉函数在其执行体内的索引获得被掉函数的地址
	callee_p = &(*exe_p)->function[(*func_p)->u.diksam_f.index];
	// 获得在调用被掉函数在栈上保存的调用信息
	callInfo = (CallInfo*)&dvm->stack.stack[*sp_p - 1 - callee_p->local_variable_count - CALL_INFO_ALIGN_SIZE];
	if (callInfo->caller) {
		// 恢复调用者的执行体
		*exe_p = callInfo->caller->u.diksam_f.executable;
		// 获得调用者的函数地址，及相应信息
		caller_p = &(*exe_p)->function[callInfo->caller->u.diksam_f.index];
		*code_p = caller_p->code;
		*code_size_p = caller_p->code_size;
	}
	else {
		*exe_p = dvm->executable;
		*code_p = dvm->executable->code;
		*code_size_p = dvm->executable->code_size;
	}
	*func_p = callInfo->caller;
	// 程序计数器应跳转到函数之后的第一个地址
	*pc_p = callInfo->caller_address + 1;
	// 恢复基地址
	*base_p = callInfo->base;
	// 恢复栈指针，减去被掉函数的局部变量以及调用信息和形参数量
	// 顺序从上至下（向上增长）
	*sp_p -= callee_p->local_variable_count + CALL_INFO_ALIGN_SIZE + callee_p->parameter_count;
	// 将返回值重新保存在栈顶
	dvm->stack.stack[*sp_p - 1] = return_value;
}
// STI(int),STD(double),STO(object) 这三个宏以当前的栈指针加上sp作为索引值，返回栈上对应的元素值
// 主要用于四则运算等，也可用于双目或单目运算符操作栈顶附近的值
#define STI(dvm, sp) \
  ((dvm)->stack.stack[(dvm)->stack.stack_pointer+(sp)].int_value)
#define STD(dvm, sp) \
  ((dvm)->stack.stack[(dvm)->stack.stack_pointer+(sp)].double_value)
#define STO(dvm, sp) \
  ((dvm)->stack.stack[(dvm)->stack.stack_pointer+(sp)].object)
// STI_I,STD_I,STO_I 这三个宏直接以sp为索引值取得栈上对应元素值
// 使用了push_stack_xxx,pop_stack_xxx系列的指令
// 这些指令不是用来引用栈顶附近的值的，而是用来引用以base为起点的索引值对应的栈元素
#define STI_I(dvm, sp) \
  ((dvm)->stack.stack[(sp)].int_value)
#define STD_I(dvm, sp) \
  ((dvm)->stack.stack[(sp)].double_value)
#define STO_I(dvm, sp) \
  ((dvm)->stack.stack[(sp)].object)
// 这三个宏用与STx等相同的方法来指定栈上的元素，并在对应元素的位置写入r
// 必须跟定值类型是否为指针来设定栈上的对应标志位
#define STI_WRITE(dvm, sp, r) \
  ((dvm)->stack.stack[(dvm)->stack.stack_pointer+(sp)].int_value = r,\
   (dvm)->stack.pointer_flags[(dvm)->stack.stack_pointer+(sp)] = DVM_FALSE)
#define STD_WRITE(dvm, sp, r) \
  ((dvm)->stack.stack[(dvm)->stack.stack_pointer+(sp)].double_value = r, \
   (dvm)->stack.pointer_flags[(dvm)->stack.stack_pointer+(sp)] = DVM_FALSE)
#define STO_WRITE(dvm, sp, r) \
  ((dvm)->stack.stack[(dvm)->stack.stack_pointer+(sp)].object = r, \
   (dvm)->stack.pointer_flags[(dvm)->stack.stack_pointer+(sp)] = DVM_TRUE)
// 这三个宏 直接以sp为索引值实现STx_WRITE
#define STI_WRITE_I(dvm, sp, r) \
  ((dvm)->stack.stack[(sp)].int_value = r,\
   (dvm)->stack.pointer_flags[(sp)] = DVM_FALSE)
#define STD_WRITE_I(dvm, sp, r) \
  ((dvm)->stack.stack[(sp)].double_value = r, \
   (dvm)->stack.pointer_flags[(sp)] = DVM_FALSE)
#define STO_WRITE_I(dvm, sp, r) \
  ((dvm)->stack.stack[(sp)].object = r, \
   (dvm)->stack.pointer_flags[(sp)] = DVM_TRUE)
// 创建数组的子函数
DVM_Object* create_array_sub(DVM_VirtualMachine *dvm, int dim, int dim_index, DVM_TypeSpecifier *type){
	DVM_Object *ret = NULL;
	int size;
	int i;
	// 获取数组大小
	size = STI(dvm, -dim);
	// 如果维数索引值等于类型继承数量
	if (dim_index == type->derive_count - 1) {
		switch (type->basic_type) {
		case DVM_BOOLEAN_TYPE: /* FALLTHRU */
		case DVM_INT_TYPE:
			ret = DVM_create_array_int(dvm, size);
			break;
		case DVM_DOUBLE_TYPE:
			ret = DVM_create_array_double(dvm, size);
			break;
		case DVM_STRING_TYPE:
			ret = DVM_create_array_object(dvm, size);
			break;
		case DVM_NULL_TYPE: /* FALLTHRU */
		default:
			DBG_assert(0, ("type->basic_type..%d\n", type->basic_type));
			break;
		}
	}
	// 类型继承不能为函数
	else if (type->derive[dim_index].tag == DVM_FUNCTION_DERIVE) {
		/* BUGBUG */
		ret = NULL;
	}
	// 类型继承链表存在
	else {
		ret = DVM_create_array_object(dvm, size);
		// 如果维数索引小于维数
		if (dim_index < dim - 1) {
			// 将返回值写入栈顶
			STO_WRITE(dvm, 0, ret);
			// 栈指针前移
			dvm->stack.stack_pointer++;
			// 根据数组大小
			for (i = 0; i < size; i++) {
				DVM_Object *child;
				child = create_array_sub(dvm, dim, dim_index + 1, type);
				// 根据索引设定元素的object值
				DVM_array_set_object(dvm, ret, i, child);
			}
			// 恢复栈指针
			dvm->stack.stack_pointer--;
		}
	}
	return ret;
}
// 创建数组
DVM_Object* create_array(DVM_VirtualMachine *dvm, int dim, DVM_TypeSpecifier *type){
    return create_array_sub(dvm, dim, 0, type);
}
// 创建int型数组字面值
DVM_Object* create_array_literal_int(DVM_VirtualMachine *dvm, int size){
    DVM_Object *array;
    int i;

    array = dvm_create_array_int_i(dvm, size);
    for (i = 0; i < size; i++) {
		// 数组的值按顺序保存在栈上，现在需要按序取出来初始化每一个数组元素
        array->u.array.u.int_array[i] = STI(dvm, -size+i);
    }

    return array;
}
// 创建double型数组字面值
DVM_Object* create_array_literal_double(DVM_VirtualMachine *dvm, int size){
	DVM_Object *array;
	int i;

	array = dvm_create_array_double_i(dvm, size);
	for (i = 0; i < size; i++) {
		array->u.array.u.double_array[i] = STD(dvm, -size + i);
	}

	return array;
}
// 创建object型数组字面值
DVM_Object* create_array_literal_object(DVM_VirtualMachine *dvm, int size){
	DVM_Object *array;
	int i;

	array = dvm_create_array_object_i(dvm, size);
	for (i = 0; i < size; i++) {
		array->u.array.u.object[i] = STO(dvm, -size + i);
	}

	return array;
}
// 根据参数恢复程序计数器
static void restore_pc(DVM_VirtualMachine *dvm, DVM_Executable *exe, Function *func, int pc){
	dvm->current_executable = exe;
	dvm->current_function = func;
	dvm->pc = pc;
}
// 执行虚拟机的字节码
static DVM_Value execute(DVM_VirtualMachine *dvm, Function *func, DVM_Byte *code, int code_size){
	int         base;
	DVM_Executable *exe;
	int         pc;
	DVM_Value   ret;
	ret.int_value = 0;

	pc = dvm->pc;
	exe = dvm->current_executable;
	// 确保程序计数器的范围在字节码缓冲区内
	while (pc < code_size) {
		/*
		fprintf(stderr, "%s  sp(%d)\t\n",
		dvm_opcode_info[code[pc]].mnemonic,
		dvm->stack.stack_pointer);
		*/

		switch (code[pc]) {
		case DVM_PUSH_INT_1BYTE:
			// 将1字节整数入栈
			STI_WRITE(dvm, 0, code[pc + 1]);
			dvm->stack.stack_pointer++;
			// 跳过操作码和操作数，共2个字节
			pc += 2;
			break;
		case DVM_PUSH_INT_2BYTE:
			// 将2字节整数入栈
			STI_WRITE(dvm, 0, GET_2BYTE_INT(&code[pc + 1]));
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_INT:
			// 操作数为常量池索引，将常量池内的一个整数入栈
			STI_WRITE(dvm, 0,
				exe->constant_pool[GET_2BYTE_INT(&code[pc + 1])].u.c_int);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_DOUBLE_0:
			// 将double型0.0入栈
			STD_WRITE(dvm, 0, 0.0);
			dvm->stack.stack_pointer++;
			pc++;
			break;
		case DVM_PUSH_DOUBLE_1:
			// 将double型1.0入栈
			STD_WRITE(dvm, 0, 1.0);
			dvm->stack.stack_pointer++;
			pc++;
			break;
		case DVM_PUSH_DOUBLE:
			// 将常量池内的double值入栈
			STD_WRITE(dvm, 0, exe->constant_pool[GET_2BYTE_INT(&code[pc + 1])].u.c_double);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_STRING:
			// 将常量池中的字符串入栈
			STO_WRITE(dvm, 0, dvm_literal_to_dvm_string_i(dvm, exe->constant_pool[GET_2BYTE_INT(&code[pc + 1])].u.c_string));
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_NULL:
			STO_WRITE(dvm, 0, NULL);
			dvm->stack.stack_pointer++;
			pc++;
			break;
		case DVM_PUSH_STACK_INT:
			// 将栈中以base为基准以操作数为偏移的的int值入栈
			STI_WRITE(dvm, 0, STI_I(dvm, base + GET_2BYTE_INT(&code[pc + 1])));
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_STACK_DOUBLE:
			// 将栈中以base为基准以操作数为偏移的的double值入栈
			STD_WRITE(dvm, 0, STD_I(dvm, base + GET_2BYTE_INT(&code[pc + 1])));
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_STACK_OBJECT:
			// 将栈中以base为基准以操作数为偏移的的object值入栈
			STO_WRITE(dvm, 0, STO_I(dvm, base + GET_2BYTE_INT(&code[pc + 1])));
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_POP_STACK_INT:
			// 将栈中以base为基准以操作数为偏移的的int值弹出到操作数指定地址
			STI_WRITE_I(dvm, base + GET_2BYTE_INT(&code[pc + 1]), STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc += 3;
			break;
		case DVM_POP_STACK_DOUBLE:
			// 将栈中以base为基准以操作数为偏移的的double值弹出到操作数指定地址
			STD_WRITE_I(dvm, base + GET_2BYTE_INT(&code[pc + 1]), STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc += 3;
			break;
		case DVM_POP_STACK_OBJECT:
			// 将栈中以base为基准以操作数为偏移的的object值弹出到操作数指定地址
			STO_WRITE_I(dvm, base + GET_2BYTE_INT(&code[pc + 1]), STO(dvm, -1));
			dvm->stack.stack_pointer--;
			pc += 3;
			break;
		case DVM_PUSH_STATIC_INT:
			// 以操作数为索引值，将对应的int型静态变量入栈
			STI_WRITE(dvm, 0, dvm->static_v.variable[GET_2BYTE_INT(&code[pc + 1])].int_value);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_STATIC_DOUBLE:
			// 以操作数为索引值，将对应的double型静态变量入栈
			STD_WRITE(dvm, 0, dvm->static_v.variable[GET_2BYTE_INT(&code[pc + 1])].double_value);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_PUSH_STATIC_OBJECT:
			// 以操作数为索引值，将对应的object型静态变量入栈
			STO_WRITE(dvm, 0, dvm->static_v.variable[GET_2BYTE_INT(&code[pc + 1])].object);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_POP_STATIC_INT:
			// 将栈顶的int值弹出保存在由操作数指定索引的静态变量池中
			dvm->static_v.variable[GET_2BYTE_INT(&code[pc + 1])].int_value = STI(dvm, -1);
			dvm->stack.stack_pointer--;
			pc += 3;
			break;
		case DVM_POP_STATIC_DOUBLE:
			// 将栈顶的double值弹出保存在由操作数指定索引的静态变量池中
			dvm->static_v.variable[GET_2BYTE_INT(&code[pc + 1])].double_value = STD(dvm, -1);
			dvm->stack.stack_pointer--;
			pc += 3;
			break;
		case DVM_POP_STATIC_OBJECT:
			// 将栈顶的object值弹出保存在由操作数指定索引的静态变量池中
			dvm->static_v.variable[GET_2BYTE_INT(&code[pc + 1])].object = STO(dvm, -1);
			dvm->stack.stack_pointer--;
			pc += 3;
			break;
		case DVM_PUSH_ARRAY_INT:{
			// PUSH_ARRAY_INT 根据栈中的数组和下标获取数组中的元素（int）并入栈
			DVM_Object *array = STO(dvm, -2);
			int index = STI(dvm, -1);
			int int_value;

			restore_pc(dvm, exe, func, pc);
			int_value = DVM_array_get_int(dvm, array, index);
			// 将获取到的元素保存在栈顶的下边，因为之后栈顶要减少一层
			STI_WRITE(dvm, -2, int_value);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		}
		case DVM_PUSH_ARRAY_DOUBLE:{
			// PUSH_ARRAY_INT 根据栈中的数组和下标获取数组中的元素（double）并入栈
			DVM_Object *array = STO(dvm, -2);
			int index = STI(dvm, -1);
			double double_value;

			restore_pc(dvm, exe, func, pc);
			double_value = DVM_array_get_double(dvm, array, index);

			STD_WRITE(dvm, -2, double_value);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		}
		case DVM_PUSH_ARRAY_OBJECT:{
			// PUSH_ARRAY_INT 根据栈中的数组和下标获取数组中的元素（object）并入栈
			DVM_Object *array = STO(dvm, -2);
			int index = STI(dvm, -1);
			DVM_Object *object;

			restore_pc(dvm, exe, func, pc);
			object = DVM_array_get_object(dvm, array, index);

			STO_WRITE(dvm, -2, object);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		}
		case DVM_POP_ARRAY_INT:{
			// 将栈上的值（int1）赋值给数组array中下标为int2的元素
			int value = STI(dvm, -3);
			DVM_Object *array = STO(dvm, -2);
			int index = STI(dvm, -1);

			restore_pc(dvm, exe, func, pc);
			DVM_array_set_int(dvm, array, index, value);
			// 删除栈上的int1值，数组array和int2值
			dvm->stack.stack_pointer -= 3;
			pc++;
			break;
		}
		case DVM_POP_ARRAY_DOUBLE:{
			// 将栈上的值（double）赋值给数组array中下标为int2的元素
			double value = STD(dvm, -3);
			DVM_Object *array = STO(dvm, -2);
			int index = STI(dvm, -1);

			restore_pc(dvm, exe, func, pc);
			DVM_array_set_double(dvm, array, index, value);
			dvm->stack.stack_pointer -= 3;
			pc++;
			break;
		}
		case DVM_POP_ARRAY_OBJECT:{
			// 将栈上的值（object）赋值给数组array中下标为int2的元素
			DVM_Object *value = STO(dvm, -3);
			DVM_Object *array = STO(dvm, -2);
			int index = STI(dvm, -1);

			restore_pc(dvm, exe, func, pc);
			DVM_array_set_object(dvm, array, index, value);
			dvm->stack.stack_pointer -= 3;
			pc++;
			break;
		}
		case DVM_ADD_INT:
			// 进行int加法运算，并将结果入栈
			// 栈顶下方和栈顶存放这两个操作数，然后结果存放在栈顶下方，然后降低当前栈顶
			STI(dvm, -2) = STI(dvm, -2) + STI(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_ADD_DOUBLE:
			// 进行double加法运算，并将结果入栈
			STD(dvm, -2) = STD(dvm, -2) + STD(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_ADD_STRING:
			// 进行字符串连接运算，并将结果入栈
			STO(dvm, -2) = chain_string(dvm, STO(dvm, -2), STO(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_SUB_INT:
			// 进行int减法运算，并将结果入栈
			STI(dvm, -2) = STI(dvm, -2) - STI(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_SUB_DOUBLE:
			// 进行double减法运算，并将结果入栈
			STD(dvm, -2) = STD(dvm, -2) - STD(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_MUL_INT:
			// 进行int乘法运算，并将结果入栈
			STI(dvm, -2) = STI(dvm, -2) * STI(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_MUL_DOUBLE:
			// 进行double乘法运算，并将结果入栈
			STD(dvm, -2) = STD(dvm, -2) * STD(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_DIV_INT:
			// // 进行int除法运算，并将结果入栈
			if (STI(dvm, -1) == 0) {
				dvm_error(exe, func, pc, DIVISION_BY_ZERO_ERR, MESSAGE_ARGUMENT_END);
			}
			STI(dvm, -2) = STI(dvm, -2) / STI(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_DIV_DOUBLE:
			// 进行double乘法运算，并将结果入栈
			STD(dvm, -2) = STD(dvm, -2) / STD(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_MOD_INT:
			// 进行int取余运算，并将结果入栈
			STI(dvm, -2) = STI(dvm, -2) % STI(dvm, -1);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_MOD_DOUBLE:
			// 进行double取余运算，并将结果入栈
			STD(dvm, -2) = fmod(STD(dvm, -2), STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_MINUS_INT:
			// 对栈顶的int值取反
			STI(dvm, -1) = -STI(dvm, -1);
			pc++;
			break;
		case DVM_MINUS_DOUBLE:
			// 对栈顶的double值取反
			STD(dvm, -1) = -STD(dvm, -1);
			pc++;
			break;
		case DVM_INCREMENT:
			// 自增栈顶的int值
			STI(dvm, -1)++;
			pc++;
			break;
		case DVM_DECREMENT:
			// 自减栈顶的int值
			STI(dvm, -1)--;
			pc++;
			break;
		case DVM_CAST_INT_TO_DOUBLE:
			// 将栈顶的int值转换为double
			STD(dvm, -1) = (double)STI(dvm, -1);
			pc++;
			break;
		case DVM_CAST_DOUBLE_TO_INT:
			// 将栈顶的double值转换为int
			STI(dvm, -1) = (int)STD(dvm, -1);
			pc++;
			break;
		case DVM_CAST_BOOLEAN_TO_STRING:
			// 将栈顶的bool值转换为字符串（true或者false）
			if (STI(dvm, -1)) {
				STO_WRITE(dvm, -1, dvm_literal_to_dvm_string_i(dvm, TRUE_STRING));
			}
			else {
				STO_WRITE(dvm, -1, dvm_literal_to_dvm_string_i(dvm, FALSE_STRING));
			}
			pc++;
			break;
		case DVM_CAST_INT_TO_STRING:{
			// 将栈顶的int值转换为字符串
			char buf[LINE_BUF_SIZE];
			DVM_Char *wc_str;

			sprintf(buf, "%d", STI(dvm, -1));
			restore_pc(dvm, exe, func, pc);
			wc_str = dvm_mbstowcs_alloc(dvm, buf);
			STO_WRITE(dvm, -1, dvm_create_dvm_string_i(dvm, wc_str));
			pc++;
			break;
		}
		case DVM_CAST_DOUBLE_TO_STRING:{
			// 将栈顶的double值转换为字符串
			char buf[LINE_BUF_SIZE];
			DVM_Char *wc_str;

			sprintf(buf, "%f", STD(dvm, -1));
			restore_pc(dvm, exe, func, pc);
			wc_str = dvm_mbstowcs_alloc(dvm, buf);
			STO_WRITE(dvm, -1,
				dvm_create_dvm_string_i(dvm, wc_str));
			pc++;
			break;
		}
		case DVM_EQ_INT:
			// 进行int间的==比较并将结果入栈
			// 比较数分别存放在栈顶下方和栈顶，结果存放在栈顶下方
			STI(dvm, -2) = (STI(dvm, -2) == STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_EQ_DOUBLE:
			// 进行double间==的比较并将结果入栈
			STI(dvm, -2) = (STD(dvm, -2) == STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_EQ_OBJECT:
			// 进行object间的==比较并将结果入栈
			STI_WRITE(dvm, -2, STO(dvm, -2) == STO(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_EQ_STRING:
			// 判断两个字符串是否相等并将结果入栈
			STI_WRITE(dvm, -2, !dvm_wcscmp(STO(dvm, -2)->u.string.string, STO(dvm, -1)->u.string.string));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_GT_INT:
			// 进行int间的>比较并将结果入栈
			STI(dvm, -2) = (STI(dvm, -2) > STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_GT_DOUBLE:
			// 进行double间的>比较并将结果入栈
			STI(dvm, -2) = (STD(dvm, -2) > STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_GT_STRING:
			// 进行字符串间的>比较并将结果入栈
			STI_WRITE(dvm, -2, dvm_wcscmp(STO(dvm, -2)->u.string.string, STO(dvm, -1)->u.string.string) > 0);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_GE_INT:
			// 进行int间的>=比较并将结果入栈
			STI(dvm, -2) = (STI(dvm, -2) >= STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_GE_DOUBLE:
			// 进行double间的>=比较并将结果入栈
			STI(dvm, -2) = (STD(dvm, -2) >= STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_GE_STRING:
			// 进行字符串间的>=比较并将结果入栈
			STI_WRITE(dvm, -2, dvm_wcscmp(STO(dvm, -2)->u.string.string, STO(dvm, -1)->u.string.string) >= 0);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LT_INT:
			// 进行int间的<比较并将结果入栈
			STI(dvm, -2) = (STI(dvm, -2) < STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LT_DOUBLE:
			// 进行double间的<比较并将结果入栈
			STI(dvm, -2) = (STD(dvm, -2) < STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LT_STRING:
			// 进行字符串间的<比较并将结果入栈
			STI_WRITE(dvm, -2, dvm_wcscmp(STO(dvm, -2)->u.string.string, STO(dvm, -1)->u.string.string) < 0);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LE_INT:
			// 进行int间的<=比较并将结果入栈
			STI(dvm, -2) = (STI(dvm, -2) <= STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LE_DOUBLE:
			// 进行double间的<=比较并将结果入栈
			STI(dvm, -2) = (STD(dvm, -2) <= STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LE_STRING:
			// 进行字符串间的<=比较并将结果入栈
			STI_WRITE(dvm, -2, dvm_wcscmp(STO(dvm, -2)->u.string.string, STO(dvm, -1)->u.string.string) <= 0);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_NE_INT:
			// 进行int间的!=比较并将结果入栈
			STI(dvm, -2) = (STI(dvm, -2) != STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_NE_DOUBLE:
			// 进行double间的!=比较并将结果入栈
			STI(dvm, -2) = (STD(dvm, -2) != STD(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_NE_OBJECT:
			// 进行object间的!=比较并将结果入栈
			STI_WRITE(dvm, -2, STO(dvm, -2) != STO(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_NE_STRING:
			// 进行字符串间的!=比较并将结果入栈
			STI_WRITE(dvm, -2, dvm_wcscmp(STO(dvm, -2)->u.string.string, STO(dvm, -1)->u.string.string) != 0);
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LOGICAL_AND:
			// 将栈上两操作数的逻辑与的结果入栈
			STI(dvm, -2) = (STI(dvm, -2) && STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LOGICAL_OR:
			// 将栈上两操作数的逻辑或的结果入栈
			STI(dvm, -2) = (STI(dvm, -2) || STI(dvm, -1));
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_LOGICAL_NOT:
			// 将栈顶的逻辑值取反
			STI(dvm, -1) = !STI(dvm, -1);
			pc++;
			break;
		case DVM_POP:
			// 舍弃栈顶的一个值
			// 直接修改栈指针，原先栈顶值丢弃
			dvm->stack.stack_pointer--;
			pc++;
			break;
		case DVM_DUPLICATE:
			// 复制栈顶的一个值
			// 将栈顶的值复制到栈顶之上的区域里，增加一层栈指针
			dvm->stack.stack[dvm->stack.stack_pointer] = dvm->stack.stack[dvm->stack.stack_pointer - 1];
			dvm->stack.stack_pointer++;
			pc++;
			break;
		case DVM_JUMP:
			// 跳转到操作数指定的地址
			// 修改pc的地址
			pc = GET_2BYTE_INT(&code[pc + 1]);
			break;
		case DVM_JUMP_IF_TRUE:
			// 如果栈顶的值为真，则跳转到操作数指定的地址，并弹出此操作数
			if (STI(dvm, -1)) {
				pc = GET_2BYTE_INT(&code[pc + 1]);
			}
			else {
				pc += 3;
			}
			dvm->stack.stack_pointer--;
			break;
		case DVM_JUMP_IF_FALSE:
			// 如果栈顶的值为真，则跳转到操作数指定的地址，并弹出此操作数
			if (!STI(dvm, -1)) {
				pc = GET_2BYTE_INT(&code[pc + 1]);
			}
			else {
				pc += 3;
			}
			dvm->stack.stack_pointer--;
			break;
		case DVM_PUSH_FUNCTION:
			// 将操作数指示的函数的索引值入栈
			STI_WRITE(dvm, 0, GET_2BYTE_INT(&code[pc + 1]));
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		case DVM_INVOKE:{
			// 调用栈顶的函数
			// 获取栈顶的函数索引
			int func_idx = STI(dvm, -1);
			// 如果是本地函数
			if (dvm->function[func_idx].kind == NATIVE_FUNCTION) {
				invoke_native_function(dvm, &dvm->function[func_idx], &dvm->stack.stack_pointer);
				pc++;
			}
			// 自定义函数
			else {
				invoke_diksam_function(dvm, &func, &dvm->function[func_idx], &code, &code_size, &pc,
					&dvm->stack.stack_pointer, &base, &exe);
			}
			break;
		}
		case DVM_RETURN:
			// 将栈顶的值作为函数返回值并将函数返回
			return_function(dvm, &func, &code, &code_size, &pc,
				&dvm->stack.stack_pointer, &base, &exe);
			break;
		case DVM_NEW_ARRAY:{
			// 创建以操作数short所示类型组成的byte维数组（用栈中指定个数的元素）并入栈
			// 获取维数
			int dim = code[pc + 1];
			// 获取类型
			DVM_TypeSpecifier *type = &exe->type_specifier[GET_2BYTE_INT(&code[pc + 2])];
			DVM_Object *array;

			restore_pc(dvm, exe, func, pc);
			array = create_array(dvm, dim, type);
			dvm->stack.stack_pointer -= dim;
			STO_WRITE(dvm, 0, array);
			dvm->stack.stack_pointer++;
			pc += 4;
			break;
		}
		case DVM_NEW_ARRAY_LITERAL_INT: /* FALLTHRU */{
			// 以已经入栈的给定数量的int型的操作数作为元素创建数组，并将其入栈
			// 获取栈上的数组元素大小
			int size = GET_2BYTE_INT(&code[pc + 1]);
			DVM_Object *array;

			restore_pc(dvm, exe, func, pc);
			array = create_array_literal_int(dvm, size);
			// 丢弃之前在栈中的数组元素
			dvm->stack.stack_pointer -= size;
			STO_WRITE(dvm, 0, array);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		}
		case DVM_NEW_ARRAY_LITERAL_DOUBLE: /* FALLTHRU */{
			// 以已经入栈的给定数量的double型的操作数作为元素创建数组，并将其入栈
			int size = GET_2BYTE_INT(&code[pc + 1]);
			DVM_Object *array;

			restore_pc(dvm, exe, func, pc);
			array = create_array_literal_double(dvm, size);
			dvm->stack.stack_pointer -= size;
			STO_WRITE(dvm, 0, array);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		}
		case DVM_NEW_ARRAY_LITERAL_OBJECT: /* FALLTHRU */{
			// 以已经入栈的给定数量的object型的操作数作为元素创建数组，并将其入栈
			int size = GET_2BYTE_INT(&code[pc + 1]);
			DVM_Object *array;

			restore_pc(dvm, exe, func, pc);
			array = create_array_literal_object(dvm, size);
			dvm->stack.stack_pointer -= size;
			STO_WRITE(dvm, 0, array);
			dvm->stack.stack_pointer++;
			pc += 3;
			break;
		}
		default:
			DBG_assert(0, ("code[pc]..%d\n", code[pc]));
		}
		/* MEM_check_all_blocks(); */
	}

	return ret;
}
// 虚拟机执行函数公共接口
DVM_Value DVM_execute(DVM_VirtualMachine *dvm){
	DVM_Value ret;
	ret.int_value = 0;

	dvm->current_executable = dvm->executable;
	dvm->current_function = NULL;
	dvm->pc = 0;
	expand_stack(dvm, dvm->executable->need_stack_size);
	execute(dvm, NULL, dvm->executable->code, dvm->executable->code_size);

	return ret;
}
// 回收虚拟机
void DVM_dispose_virtual_machine(DVM_VirtualMachine *dvm){
	int i;

	dvm->static_v.variable_count = 0;
	dvm_garbage_collect(dvm);

	MEM_free(dvm->stack.stack);
	MEM_free(dvm->stack.pointer_flags);

	MEM_free(dvm->static_v.variable);

	for (i = 0; i < dvm->function_count; i++) {
		MEM_free(dvm->function[i].name);
	}
	MEM_free(dvm->function);

	dvm_dispose_executable(dvm->executable);
	MEM_free(dvm);
}
