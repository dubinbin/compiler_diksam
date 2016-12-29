#ifndef PUBLIC_DKC_H_INCLUDED
#define PUBLIC_DKC_H_INCLUDED

#include "stdafx.h"
//#include <stdio.h>
#include "DVM_code.h"

typedef struct DKC_Compiler_tag DKC_Compiler;
// 输入模式，是从文件中输入还是从字符串中输入
typedef enum {
    DKC_FILE_INPUT_MODE = 1,
    DKC_STRING_INPUT_MODE
} DKC_InputMode;
// 创建编译器
DKC_Compiler *DKC_create_compiler(void);
// 编译文件，并返回一个执行体
DVM_Executable *DKC_compile(DKC_Compiler *compiler, FILE *fp);
// 编译字符串，返回一个执行体
DVM_Executable *DKC_compile_string(DKC_Compiler *compiler, char **lines);
// 释放编译器
void DKC_dispose_compiler(DKC_Compiler *compiler);

#endif /* PUBLIC_DKC_H_INCLUDED */
