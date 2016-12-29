#include "stdafx.h"
//#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "dvm_pri.h"

// 检查数组，确定数组非空，并且检查数组索引值范围
static void check_array(DVM_Object *array, int index, DVM_Executable *exe, Function *func, int pc){
	if (array == NULL) {
		dvm_error(exe, func, pc, NULL_POINTER_ERR,
			MESSAGE_ARGUMENT_END);
	}
	if (index < 0 || index >= array->u.array.size) {
		dvm_error(exe, func, pc, INDEX_OUT_OF_BOUNDS_ERR,
			INT_MESSAGE_ARGUMENT, "index", index,
			INT_MESSAGE_ARGUMENT, "size", array->u.array.size,
			MESSAGE_ARGUMENT_END);
	}
}
// 返回指定索引的数组元素的int型值
int DVM_array_get_int(DVM_VirtualMachine *dvm, DVM_Object *array, int index){
	check_array(array, index,dvm->current_executable, dvm->current_function, dvm->pc);
	return array->u.array.u.int_array[index];
}
// 返回指定索引的数组元素的double型值
double DVM_array_get_double(DVM_VirtualMachine *dvm, DVM_Object *array, int index){
	check_array(array, index, dvm->current_executable, dvm->current_function, dvm->pc);
	return array->u.array.u.double_array[index];
}
// 返回指定索引的数组元素的object型值
DVM_Object* DVM_array_get_object(DVM_VirtualMachine *dvm, DVM_Object *array, int index){
	check_array(array, index, dvm->current_executable, dvm->current_function, dvm->pc);
	return array->u.array.u.object[index];
}
// 设置指定索引的数组元素的int型值
void DVM_array_set_int(DVM_VirtualMachine *dvm, DVM_Object *array, int index, int value){
	check_array(array, index, dvm->current_executable, dvm->current_function, dvm->pc);
	array->u.array.u.int_array[index] = value;
}
// 设置指定索引的数组元素的double型值
void DVM_array_set_double(DVM_VirtualMachine *dvm, DVM_Object *array, int index, double value){
	check_array(array, index, dvm->current_executable, dvm->current_function, dvm->pc);
	array->u.array.u.double_array[index] = value;
}
// 设置指定索引的数组元素的object型值
void DVM_array_set_object(DVM_VirtualMachine *dvm, DVM_Object *array, int index, DVM_Object *value){
	check_array(array, index, dvm->current_executable, dvm->current_function, dvm->pc);
	array->u.array.u.object[index] = value;
}
