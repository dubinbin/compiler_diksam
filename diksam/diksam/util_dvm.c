#include "stdafx.h"
//#include <stdio.h>
//#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "dvm_pri.h"

// 清楚字符串
void dvm_vstr_clear(VString *v){
    v->string = NULL;
}
// 获取字符串长度
static int my_strlen(DVM_Char *str){
    if (str == NULL) {
        return 0;
    }
    return dvm_wcslen(str);
}
// 在字符串尾部添加字符串
void dvm_vstr_append_string(VString *v, DVM_Char *str){
    int new_size;
    int old_len;

    old_len = my_strlen(v->string);
    new_size = sizeof(DVM_Char) * (old_len + dvm_wcslen(str)  + 1);
    v->string = MEM_realloc(v->string, new_size);
    dvm_wcscpy(&v->string[old_len], str);
}
// 在字符串尾部添加字符
void dvm_vstr_append_character(VString *v, DVM_Char ch){
	int current_len;

	current_len = my_strlen(v->string);
	v->string = MEM_realloc(v->string, sizeof(DVM_Char) * (current_len + 2));
	v->string[current_len] = ch;
	v->string[current_len + 1] = L'\0';
}
