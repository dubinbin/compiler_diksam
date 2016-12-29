#include "stdafx.h"
//#include <stdio.h>
//#include <string.h>
//#include <wchar.h>
#include "DBG.h"
#include "diksamc.h"

// 多字节字符串到宽字节字符串转换，需要提供代码行号和字符串首地址
wchar_t *
dkc_mbstowcs_alloc(int line_number, const char *src)
{
    int len;
    wchar_t *ret;
	// 获取多字节字符串长度
    len = dvm_mbstowcs_len(src);
    if (len < 0) {
        return NULL;
        dkc_compile_error(line_number,
                          BAD_MULTIBYTE_CHARACTER_ERR,
                          MESSAGE_ARGUMENT_END);
    }
    ret = MEM_malloc(sizeof(wchar_t) * (len+1));
	// 实际的执行转换函数
    dvm_mbstowcs(src, ret);

    return ret;
}
