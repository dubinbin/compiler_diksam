#include "stdafx.h"
//#include <stdio.h>
//#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "diksamc.h"

// 当前的编译器
static DKC_Compiler *st_current_compiler;

DKC_Compiler *
dkc_get_current_compiler(void)
{
    return st_current_compiler;
}

void
dkc_set_current_compiler(DKC_Compiler *compiler)
{
    st_current_compiler = compiler;
}
// 使用编译器的存储器为应用程序申请的指定大小内存分配空间
void *
dkc_malloc(size_t size)
{
    void *p;
    DKC_Compiler *compiler;

    compiler = dkc_get_current_compiler();
    p = MEM_storage_malloc(compiler->compile_storage, size);

    return p;
}
// 为指定的字符串分配存储空间并返回其首地址
char *
dkc_strdup(char *src)
{
    char *p;
    DKC_Compiler *compiler;

    compiler = dkc_get_current_compiler();
    p = MEM_storage_malloc(compiler->compile_storage, strlen(src)+1);
    strcpy(p, src);

    return p;
}
// 为指定类型的类型指示器分配内存，并返回其地址
TypeSpecifier *
dkc_alloc_type_specifier(DVM_BasicType type)
{
    TypeSpecifier *ts = dkc_malloc(sizeof(TypeSpecifier));

    ts->basic_type = type;
    ts->derive = NULL;

    return ts;
}
// 为指定类型的类型继承分配内存并返回其地址
TypeDerive *
dkc_alloc_type_derive(DeriveTag derive_tag)
{
    TypeDerive *td = dkc_malloc(sizeof(TypeDerive));
    td->tag = derive_tag;
    td->next = NULL;

    return td;
}
// 比较两个形参链表中的形参
DVM_Boolean
dkc_compare_parameter(ParameterList *param1, ParameterList *param2)
{
    ParameterList *pos1;
    ParameterList *pos2;

    for (pos1 = param1, pos2 = param2; pos1 && pos2;
         pos1 = pos1->next, pos2 = pos2->next) {
		// 先比对名称
        if (strcmp(pos1->name, pos2->name) != 0) {
            return DVM_FALSE;
        }
		// 再比对类型
        if (!dkc_compare_type(pos1->type, pos2->type)) {
            return DVM_FALSE;
        }
    }
	// 如果两边的形参链表数量不一致，返回错误
    if (pos1 || pos2) {
        return DVM_FALSE;
    }
	// 否则就是一样的
    return DVM_TRUE;
}
// 比较两个类型指定器的类型
DVM_Boolean
dkc_compare_type(TypeSpecifier *type1, TypeSpecifier *type2)
{
    TypeDerive *d1;
    TypeDerive *d2;
	// 比对基本类型
    if (type1->basic_type != type2->basic_type) {
        return DVM_FALSE;
    }
	// 比对继承类型
    for (d1 = type1->derive, d2 = type2->derive;
         d1 && d2; d1 = d1->next, d2 = d2->next) {
		// 比对继承标志
        if (d1->tag != d2->tag) {
            return DVM_FALSE;
        }
		// 如果是函数的话，就要比对两个函数的形参链表
        if (d1->tag == FUNCTION_DERIVE) {
            if (!dkc_compare_parameter(d1->u.function_d.parameter_list,
                                       d2->u.function_d.parameter_list)) {
                return DVM_FALSE;
            }
        }
    }
	// 如果两边类型继承链表的数量不一致，则返回错误
    if (d1 || d2) {
        return DVM_FALSE;
    }

    return DVM_TRUE;
}
// 根据函数名寻找函数
FunctionDefinition* dkc_search_function(char *name){
	DKC_Compiler *compiler;
	FunctionDefinition *pos;

	compiler = dkc_get_current_compiler();
	// 在函数链表中搜寻
	for (pos = compiler->function_list; pos; pos = pos->next) {
		if (!strcmp(pos->name, name))
			break;
	}
	return pos;
}
// 根据指定语句块和标识符寻找声明
Declaration* dkc_search_declaration(char *identifier, Block *block){
    Block *b_pos;
    DeclarationList *d_pos;
    DKC_Compiler *compiler;
	// 首先在当前指定的语句块中寻找，比对语句块中声明链表和标识符是否相等
	// 如果找到了咋返回该声明的地址，如果没有找到，则向上一层的语句块中寻找
    for (b_pos = block; b_pos; b_pos = b_pos->outer_block) {
        for (d_pos = b_pos->declaration_list; d_pos; d_pos = d_pos->next) {
            if (!strcmp(identifier, d_pos->declaration->name)) {
                return d_pos->declaration;
            }
        }
    }

    compiler = dkc_get_current_compiler();
	// 如果在最外层的语句块中依然没有找到，则在编译器的声明链表中寻找
	// 如果没有找到，则返回null
    for (d_pos = compiler->declaration_list; d_pos; d_pos = d_pos->next) {
        if (!strcmp(identifier, d_pos->declaration->name)) {
            return d_pos->declaration;
        }
    }

    return NULL;
}

void
dkc_vstr_clear(VString *v)
{
    v->string = NULL;
}

static int
my_strlen(char *str)
{
    if (str == NULL) {
        return 0;
    }
    return strlen(str);
}

void
dkc_vstr_append_string(VString *v, char *str)
{
    int new_size;
    int old_len;

    old_len = my_strlen(v->string);
    new_size = old_len + strlen(str)  + 1;
    v->string = MEM_realloc(v->string, new_size);
    strcpy(&v->string[old_len], str);
}

void
dkc_vstr_append_character(VString *v, int ch)
{
    int current_len;
    
    current_len = my_strlen(v->string);
    v->string = MEM_realloc(v->string, current_len + 2);
    v->string[current_len] = ch;
    v->string[current_len+1] = '\0';
}

void
dkc_vwstr_clear(VWString *v)
{
    v->string = NULL;
}

static int
my_wcslen(DVM_Char *str)
{
    if (str == NULL) {
        return 0;
    }
    return dvm_wcslen(str);
}

void
dkc_vwstr_append_string(VWString *v, DVM_Char *str)
{
    int new_size;
    int old_len;

    old_len = my_wcslen(v->string);
    new_size = sizeof(DVM_Char) * (old_len + dvm_wcslen(str)  + 1);
    v->string = MEM_realloc(v->string, new_size);
    dvm_wcscpy(&v->string[old_len], str);
}

void
dkc_vwstr_append_character(VWString *v, int ch)
{
    int current_len;
    
    current_len = my_wcslen(v->string);
    v->string = MEM_realloc(v->string,sizeof(DVM_Char) * (current_len + 2));
    v->string[current_len] = ch;
    v->string[current_len+1] = L'\0';
}
// 根据基本类型获得基本类型名称
char *
dkc_get_basic_type_name(DVM_BasicType type)
{
    switch (type) {
    case DVM_BOOLEAN_TYPE:
        return "boolean";
        break;
    case DVM_INT_TYPE:
        return "int";
        break;
    case DVM_DOUBLE_TYPE:
        return "double";
        break;
    case DVM_STRING_TYPE:
        return "string";
        break;
    case DVM_NULL_TYPE:
        return "null";
        break;
    default:
        DBG_assert(0, ("bad case. type..%d\n", type));
    }
    return NULL;
}
// 根据类型指定符获得类型名称
char *
dkc_get_type_name(TypeSpecifier *type)
{
    VString     vstr;
    TypeDerive  *derive_pos;

    dkc_vstr_clear(&vstr);
    dkc_vstr_append_string(&vstr, dkc_get_basic_type_name(type->basic_type));

    for (derive_pos = type->derive; derive_pos;
         derive_pos = derive_pos->next) {
        switch (derive_pos->tag) {
        case FUNCTION_DERIVE:
            DBG_assert(0, ("derive_tag..%d\n", derive_pos->tag));
            break;
        case ARRAY_DERIVE:
            dkc_vstr_append_string(&vstr, "[]");
            break;
        default:
            DBG_assert(0, ("derive_tag..%d\n", derive_pos->tag));
        }
    }

    return vstr.string;
}
// 将表达式转换为字符串
DVM_Char *
dkc_expression_to_string(Expression *expr)
{
	// 字符串缓冲区，用于临时缓冲
    char        buf[LINE_BUF_SIZE];
	// 宽字符串缓冲区
    DVM_Char    wc_buf[LINE_BUF_SIZE];
    int         len;
    DVM_Char    *new_str;
	// 如果表达式类型为bool，则将true或者false拷贝搭配缓冲区内
    if (expr->kind == BOOLEAN_EXPRESSION) {
        if (expr->u.boolean_value) {
            dvm_mbstowcs("true", wc_buf);
        } else {
            dvm_mbstowcs("false", wc_buf);
        }
    }else if (expr->kind == INT_EXPRESSION) {
        sprintf(buf, "%d", expr->u.int_value);
        dvm_mbstowcs(buf, wc_buf);
    } else if (expr->kind == DOUBLE_EXPRESSION) {
        sprintf(buf, "%f", expr->u.double_value);
        dvm_mbstowcs(buf, wc_buf);
    } else if (expr->kind == STRING_EXPRESSION) {
        return expr->u.string_value;
    } else {
        return NULL;
    }
	// 获取长度
    len = dvm_wcslen(wc_buf);
	// 为最终要返回的字符串分配地址并拷贝字符串
    new_str = MEM_malloc(sizeof(DVM_Char) * (len + 1));
    dvm_wcscpy(new_str, wc_buf);

    return new_str;
}
