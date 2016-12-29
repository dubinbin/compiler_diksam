#include "stdafx.h"
//#include <string.h>
#include "dvm_pri.h"

ErrorDefinition dvm_error_message_format[] = {
	{ "dummy\n" },
	{ "不正确的多字节字符。\n" },
	{ "找不到函数$(name)。\n" },
	{"重复定义函数$(name)。\n" },
	{ "数组下标越界。数组大小为$(size)，访问的下标为[$(index)]。\n" },
	{ "整数值不能被0除。\n" },
	{ "引用了null。\n" },
	{ "dummy\n" }
};