#include "stdafx.h"
//#include <stdio.h>
//#include <string.h>
//#include <wchar.h>
//#include <limits.h>
#include "DBG.h"
#include "MEM.h"
#include "DVM.h"

// 获得宽字符长度
size_t dvm_wcslen(wchar_t *str){
    return wcslen(str);
}
// 拷贝宽字符串
wchar_t* dvm_wcscpy(wchar_t *dest, wchar_t *src){
    return wcscpy(dest, src);
}
// 拷贝宽字符串，长度有n指定
wchar_t* dvm_wcsncpy(wchar_t *dest, wchar_t *src, size_t n){
    return wcsncpy(dest, src, n);
}
// 比较两个宽字符串
int dvm_wcscmp(wchar_t *s1, wchar_t *s2){
    return wcscmp(s1, s2);
}
// 连接连个宽字符串
wchar_t* dvm_wcscat(wchar_t *s1, wchar_t *s2){
    return wcscat(s1, s2);
}
// 获得多字节字符串的长度
int dvm_mbstowcs_len(const char *src){
    int src_idx, dest_idx;
    int status;
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src[src_idx] != '\0'; ) {
        status = mbrtowc(NULL, &src[src_idx], MB_LEN_MAX, &ps);
        if (status < 0) {
            return status;
        }
        dest_idx++;
        src_idx += status;
    }

    return dest_idx;
}
// 将多字节字符串转换为宽字符串
void dvm_mbstowcs(const char *src, wchar_t *dest){
    int src_idx, dest_idx;
    int status;
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src[src_idx] != '\0'; ) {
        status = mbrtowc(&dest[dest_idx], &src[src_idx],
                         MB_LEN_MAX, &ps);
        dest_idx++;
        src_idx += status;
    }
    dest[dest_idx] = L'\0';
}
// 获得宽字符串长度
int dvm_wcstombs_len(const wchar_t *src){
    int src_idx, dest_idx;
    int status;
    char dummy[MB_LEN_MAX];
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src[src_idx] != L'\0'; ) {
        status = wcrtomb(dummy, src[src_idx], &ps);
        src_idx++;
        dest_idx += status;
    }

    return dest_idx;
}
// 将宽字符串转换为多字节字符串
void dvm_wcstombs(const wchar_t *src, char *dest){
    int src_idx, dest_idx;
    int status;
    mbstate_t ps;

    memset(&ps, 0, sizeof(mbstate_t));
    for (src_idx = dest_idx = 0; src[src_idx] != '\0'; ) {
        status = wcrtomb(&dest[dest_idx], src[src_idx], &ps);
        src_idx++;
        dest_idx += status;
    }
    dest[dest_idx] = '\0';
}
// 将宽字符串转换为多字节字符串，结果由返回值提供
char* dvm_wcstombs_alloc(const wchar_t *src){
    int len;
    char *ret;

    len = dvm_wcstombs_len(src);
    ret = MEM_malloc(len + 1);
    dvm_wcstombs(src, ret);

    return ret;
}
// 将宽字符串转换为多字节字符串，结果由返回值提供
char dvm_wctochar(wchar_t src){
    mbstate_t ps;
    int status;
    char dest;

    memset(&ps, 0, sizeof(mbstate_t));
    status = wcrtomb(&dest, src, &ps);
    DBG_assert(status == 1, ("wcrtomb status..%d\n", status));

    return dest;
}
// 打印宽字符串，输出流有fp提供
int dvm_print_wcs(FILE *fp, wchar_t *str){
    char *tmp;
    int mb_len;
    int result;

    mb_len = dvm_wcstombs_len(str);
    MEM_check_all_blocks();
    tmp = MEM_malloc(mb_len + 1);
    dvm_wcstombs(str, tmp);
    result = fprintf(fp, "%s", tmp);
    MEM_free(tmp);

    return result;
}
// 获得宽字符串的长度，宽字符串被输出到fp中
int dvm_print_wcs_ln(FILE *fp, wchar_t *str){
    int result;

    result = dvm_print_wcs(fp, str);
    fprintf(fp, "\n");

    return result;
}
// 判断是否为宽字符中的数字
DVM_Boolean dvm_iswdigit(wchar_t ch){
    return ch >= L'0' && ch <= L'9';
}
