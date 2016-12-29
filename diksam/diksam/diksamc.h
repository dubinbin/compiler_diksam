#ifndef PRIVATE_DIKSAMC_H_INCLUDED
#define PRIVATE_DIKSAMC_H_INCLUDED

#include "stdafx.h"
//#include <stdio.h>
//#include <setjmp.h>
//#include <wchar.h>
#include "MEM.h"
#include "DKC.h"
#include "DVM_code.h"
#include "share.h"

#define smaller(a, b) ((a) < (b) ? (a) : (b))
#define larger(a, b) ((a) > (b) ? (a) : (b))

#define MESSAGE_ARGUMENT_MAX    (256)
#define LINE_BUF_SIZE           (1024)

#define ARRAY_SIZE(array)  (sizeof(array) / sizeof((array)[0]))

#define UTF8_ALLOC_LEN (256)

#define UNDEFINED_LABEL (-1)
// 消息实参类型
typedef enum {
    INT_MESSAGE_ARGUMENT = 1,
    DOUBLE_MESSAGE_ARGUMENT,
    STRING_MESSAGE_ARGUMENT,
    CHARACTER_MESSAGE_ARGUMENT,
    POINTER_MESSAGE_ARGUMENT,
    MESSAGE_ARGUMENT_END
} MessageArgumentType;
// 错误类型定义
typedef struct {
    char *format;
} ErrorDefinition;
// 编译时错误
typedef enum {
    PARSE_ERR = 1,
    CHARACTER_INVALID_ERR,
    FUNCTION_MULTIPLE_DEFINE_ERR,
    BAD_MULTIBYTE_CHARACTER_ERR,
    UNEXPECTED_WIDE_STRING_IN_COMPILE_ERR,
    ARRAY_ELEMENT_CAN_NOT_BE_FINAL_ERR,
    COMPLEX_ASSIGNMENT_OPERATOR_TO_FINAL_ERR,
    PARAMETER_MULTIPLE_DEFINE_ERR,
    VARIABLE_MULTIPLE_DEFINE_ERR,
    IDENTIFIER_NOT_FOUND_ERR,
    FUNCTION_IDENTIFIER_ERR,
    DERIVE_TYPE_CAST_ERR,
    CAST_MISMATCH_ERR,
    MATH_TYPE_MISMATCH_ERR,
    COMPARE_TYPE_MISMATCH_ERR,
    LOGICAL_TYPE_MISMATCH_ERR,
    MINUS_TYPE_MISMATCH_ERR,
    LOGICAL_NOT_TYPE_MISMATCH_ERR,
    INC_DEC_TYPE_MISMATCH_ERR,
    FUNCTION_NOT_IDENTIFIER_ERR,
    FUNCTION_NOT_FOUND_ERR,
    ARGUMENT_COUNT_MISMATCH_ERR,
    NOT_LVALUE_ERR,
    LABEL_NOT_FOUND_ERR,
    ARRAY_LITERAL_EMPTY_ERR,
    INDEX_LEFT_OPERAND_NOT_ARRAY_ERR,
    INDEX_NOT_INT_ERR,
    ARRAY_SIZE_NOT_INT_ERR,
    DIVISION_BY_ZERO_IN_COMPILE_ERR,
    COMPILE_ERROR_COUNT_PLUS_1
} CompileError;

typedef struct Expression_tag Expression;
// 表达式类型
typedef enum {
    BOOLEAN_EXPRESSION = 1,
    INT_EXPRESSION,
    DOUBLE_EXPRESSION,
    STRING_EXPRESSION,
    IDENTIFIER_EXPRESSION,
    COMMA_EXPRESSION,
    ASSIGN_EXPRESSION,
    ADD_EXPRESSION,
    SUB_EXPRESSION,
    MUL_EXPRESSION,
    DIV_EXPRESSION,
    MOD_EXPRESSION,
    EQ_EXPRESSION,
    NE_EXPRESSION,
    GT_EXPRESSION,
    GE_EXPRESSION,
    LT_EXPRESSION,
    LE_EXPRESSION,
    LOGICAL_AND_EXPRESSION,
    LOGICAL_OR_EXPRESSION,
    MINUS_EXPRESSION,
    LOGICAL_NOT_EXPRESSION,
    FUNCTION_CALL_EXPRESSION,
    MEMBER_EXPRESSION,
    NULL_EXPRESSION,
    ARRAY_LITERAL_EXPRESSION,
    INDEX_EXPRESSION,
    INCREMENT_EXPRESSION,
    DECREMENT_EXPRESSION,
    CAST_EXPRESSION,
    ARRAY_CREATION_EXPRESSION,
    EXPRESSION_KIND_COUNT_PLUS_1
} ExpressionKind;

#define dkc_is_numeric_type(type)\
  ((type) == DKC_INT_VALUE || (type) == DKC_DOUBLE_VALUE)

#define dkc_is_math_operator(operator) \
  ((operator) == ADD_EXPRESSION || (operator) == SUB_EXPRESSION\
   || (operator) == MUL_EXPRESSION || (operator) == DIV_EXPRESSION\
   || (operator) == MOD_EXPRESSION)

#define dkc_is_compare_operator(operator) \
  ((operator) == EQ_EXPRESSION || (operator) == NE_EXPRESSION\
   || (operator) == GT_EXPRESSION || (operator) == GE_EXPRESSION\
   || (operator) == LT_EXPRESSION || (operator) == LE_EXPRESSION)

#define dkc_is_int(type) \
  ((type)->basic_type == DVM_INT_TYPE && (type)->derive == NULL)

#define dkc_is_double(type) \
  ((type)->basic_type == DVM_DOUBLE_TYPE && (type)->derive == NULL)

#define dkc_is_boolean(type) \
  ((type)->basic_type == DVM_BOOLEAN_TYPE && (type)->derive == NULL)

#define dkc_is_string(type) \
  ((type)->basic_type == DVM_STRING_TYPE && (type)->derive == NULL)

#define dkc_is_array(type) \
  ((type)->derive && ((type)->derive->tag == ARRAY_DERIVE))

#define dkc_is_object(type) \
  (dkc_is_string(type) || dkc_is_array(type))

#define dkc_is_logical_operator(operator) \
  ((operator) == LOGICAL_AND_EXPRESSION || (operator) == LOGICAL_OR_EXPRESSION)
// 实参链表
typedef struct ArgumentList_tag {
    Expression *expression;
    struct ArgumentList_tag *next;
} ArgumentList;

typedef struct TypeSpecifier_tag TypeSpecifier;
// 形参链表，包括形参名称，形参类型，形参所在行号，链表next指针
typedef struct ParameterList_tag {
    char                *name;
    TypeSpecifier       *type;
    int                 line_number;
    struct ParameterList_tag *next;
} ParameterList;
// 继承标志，包括函数和数组
typedef enum {
    FUNCTION_DERIVE,
    ARRAY_DERIVE
} DeriveTag;
// 函数继承定义，包括一个形参链表
typedef struct {
    ParameterList       *parameter_list;
} FunctionDerive;
// 数组继承定义
typedef struct {
    int dummy; /* make compiler happy */
} ArrayDerive;
// 类型继承链表定义
typedef struct TypeDerive_tag {
    DeriveTag   tag;
    union {
        FunctionDerive  function_d;
        ArrayDerive     array_d;
    } u;
    struct TypeDerive_tag       *next;
} TypeDerive;
// 类型指定器定义，包括虚拟机基本类型和继承类型链表
struct TypeSpecifier_tag {
    DVM_BasicType       basic_type;
    TypeDerive  *derive;
};

typedef struct FunctionDefinition_tag FunctionDefinition;
// 声明定义，包括名称，类型指定，初始化表达式，变量索引，是否为本地
typedef struct {
    char        *name;
    TypeSpecifier       *type;
    Expression  *initializer;
    int variable_index;
    DVM_Boolean is_local;
} Declaration;
// 声明链表定义
typedef struct DeclarationList_tag {
    Declaration *declaration;
    struct DeclarationList_tag *next;
} DeclarationList;
// 标识符表达式定义，包括标识符名称，是否为函数，函数定义或声明的值
typedef struct {
    char        *name;
    DVM_Boolean is_function;
    union {
        FunctionDefinition *function;
        Declaration     *declaration;
    } u;
} IdentifierExpression;
// 逗号表达式，包括左和右表达式
typedef struct {
    Expression  *left;
    Expression  *right;
} CommaExpression;
// 赋值运算符，包括正常的=，以及+=，-=，*=，/=，%=
typedef enum {
    NORMAL_ASSIGN = 1,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN
} AssignmentOperator;
// 赋值表达式定义，包括赋值运算符，左表达式和右表达式
typedef struct {
    AssignmentOperator  operator;
    Expression  *left;
    Expression  *operand;
} AssignExpression;
// 二元表达式，包括左表达式和右表达式
typedef struct {
    Expression  *left;
    Expression  *right;
} BinaryExpression;
// 函数调用表达式定义，包括函数表达式和实参表达式链表
typedef struct {
    Expression          *function;
    ArgumentList        *argument;
} FunctionCallExpression;
// 表达式链表定义
typedef struct ExpressionList_tag {
    Expression          *expression;
    struct ExpressionList_tag   *next;
} ExpressionList;
// 索引表达式定义，包括一个数组表达式和一个索引
typedef struct {
    Expression  *array;
    Expression  *index;
} IndexExpression;
// 成员表达式定义，包括表达式和成员名称
typedef struct {
    Expression          *expression;
    char                *member_name;
} MemberExpression;
// 自增或自减表达式
typedef struct {
    Expression  *operand;
} IncrementOrDecrement;
// 转换类型
typedef enum {
    INT_TO_DOUBLE_CAST,
    DOUBLE_TO_INT_CAST,
    BOOLEAN_TO_STRING_CAST,
    INT_TO_STRING_CAST,
    DOUBLE_TO_STRING_CAST
} CastType;
// 类型转换表达式，包括转换类型和操作数
typedef struct {
    CastType    type;
    Expression  *operand;
} CastExpression;
// 数组维数链表
typedef struct ArrayDimension_tag {
    Expression  *expression;
    struct ArrayDimension_tag   *next;
} ArrayDimension;
// 数组创建定义，包括数组类型和数组维数
typedef struct {
    TypeSpecifier       *type;
    ArrayDimension      *dimension;
} ArrayCreation;
// 表达式结构体定义
struct Expression_tag {
    TypeSpecifier *type;
    ExpressionKind kind;
    int line_number;
    union {
        DVM_Boolean             boolean_value;
        int                     int_value;
        double                  double_value;
        DVM_Char                        *string_value;
        IdentifierExpression    identifier;
        CommaExpression         comma;
        AssignExpression        assign_expression;
        BinaryExpression        binary_expression;
        Expression              *minus_expression;
        Expression              *logical_not;
        FunctionCallExpression  function_call_expression;
        MemberExpression        member_expression;
        ExpressionList          *array_literal;
        IndexExpression         index_expression;
        IncrementOrDecrement    inc_dec;
        CastExpression          cast;
        ArrayCreation           array_creation;
    } u;
};

typedef struct Statement_tag Statement;
// 语句链表定义
typedef struct StatementList_tag {
    Statement   *statement;
    struct StatementList_tag    *next;
} StatementList;
// 语句块类型
typedef enum {
    UNDEFINED_BLOCK = 1,
    FUNCTION_BLOCK,
    WHILE_STATEMENT_BLOCK,
    FOR_STATEMENT_BLOCK
} BlockType;
// 语句块信息结构体定义
typedef struct {
    Statement   *statement;
    int         continue_label;
    int         break_label;
} StatementBlockInfo;
// 函数语句块信息结构体定义
typedef struct {
    FunctionDefinition  *function;
    int         end_label;
} FunctionBlockInfo;
// 语句块定义
typedef struct Block_tag {
    BlockType           type;
	// 上层作用域的语句块地址
    struct Block_tag    *outer_block;
    StatementList       *statement_list;
    DeclarationList     *declaration_list;
	// 父节点信息
    union {
        StatementBlockInfo      statement;
        FunctionBlockInfo       function;
    } parent;
} Block;

typedef struct Elsif_tag {
    Expression  *condition;
    Block       *block;
    struct Elsif_tag    *next;
} Elsif;

typedef struct {
    Expression  *condition;
    Block       *then_block;
    Elsif       *elsif_list;
    Block       *else_block;
} IfStatement;

typedef struct {
    char        *label;
    Expression  *condition;
    Block       *block;
} WhileStatement;

typedef struct {
    char        *label;
    Expression  *init;
    Expression  *condition;
    Expression  *post;
    Block       *block;
} ForStatement;
// foueach语句定义
typedef struct {
    char        *label;
    char        *variable;
    Expression  *collection;
    Block       *block;
} ForeachStatement;

typedef struct {
    Expression *return_value;
} ReturnStatement;

typedef struct {
    char        *label;
} BreakStatement;

typedef struct {
    char        *label;
} ContinueStatement;
// try语句
typedef struct {
    Block       *try_block;
    Block       *catch_block;
    char        *exception;
    Block       *finally_block;
} TryStatement;
// throw语句
typedef struct {
    Expression  *exception;
} ThrowStatement;
// 语句类型
typedef enum {
    EXPRESSION_STATEMENT = 1,
    IF_STATEMENT,
    WHILE_STATEMENT,
    FOR_STATEMENT,
    FOREACH_STATEMENT,
    RETURN_STATEMENT,
    BREAK_STATEMENT,
    CONTINUE_STATEMENT,
    TRY_STATEMENT,
    THROW_STATEMENT,
    DECLARATION_STATEMENT,
    STATEMENT_TYPE_COUNT_PLUS_1
} StatementType;
// 语句结构体定义
struct Statement_tag {
    StatementType       type;
    int                 line_number;
    union {
        Expression      *expression_s;
        IfStatement     if_s;
        WhileStatement  while_s;
        ForStatement    for_s;
        ForeachStatement        foreach_s;
        BreakStatement  break_s;
        ContinueStatement       continue_s;
        ReturnStatement return_s;
        TryStatement    try_s;
        ThrowStatement  throw_s;
        Declaration     *declaration_s;
    } u;
};
// 函数链表定义，包括返回值类型指定器，函数名，形参链表，语句块，局部变量类型，局部变量声明
// 索引，终止行号
struct FunctionDefinition_tag {
	// 函数返回值类型
    TypeSpecifier       *type;
    char                *name;
    ParameterList       *parameter;
    Block               *block;
    int                 local_variable_count;
    Declaration         **local_variable;
    int                 index;
    int                 end_line_number;
    struct FunctionDefinition_tag       *next;
};
// 编码类型
typedef enum {
    EUC_ENCODING = 1,
    SHIFT_JIS_ENCODING,
    UTF_8_ENCODING
} Encoding;
// 编译器结构体定义
struct DKC_Compiler_tag {
	// 编译器存储器
    MEM_Storage         compile_storage;
	// 函数定义链表
    FunctionDefinition  *function_list;
	// 函数数量
    int                 function_count;
	// 声明链表
    DeclarationList     *declaration_list;
	// 语句链表
    StatementList       *statement_list;
	// 当前行号
    int                 current_line_number;
	// 当前语句块
    Block               *current_block;
	// 输入模式
    DKC_InputMode       input_mode;
	// 编码方式
    Encoding            source_encoding;
};
// 字符串
typedef struct {
    char        *string;
} VString;
// 宽字符串
typedef struct {
    DVM_Char    *string;
} VWString;

/* diksam.l */
void dkc_set_source_string(char **source);

/* create.c */
DeclarationList *dkc_chain_declaration(DeclarationList *list,
                                       Declaration *decl);
Declaration *dkc_alloc_declaration(TypeSpecifier *type, char *identifier);
void dkc_function_define(TypeSpecifier *type, char *identifier,
                         ParameterList *parameter_list, Block *block);
ParameterList *dkc_create_parameter(TypeSpecifier *type, char *identifier);
ParameterList *dkc_chain_parameter(ParameterList *list, TypeSpecifier *type,
                                   char *identifier);
ArgumentList *dkc_create_argument_list(Expression *expression);
ArgumentList *dkc_chain_argument_list(ArgumentList *list, Expression *expr);
ExpressionList *dkc_create_expression_list(Expression *expression);
ExpressionList *dkc_chain_expression_list(ExpressionList *list,
                                          Expression *expr);
StatementList *dkc_create_statement_list(Statement *statement);
StatementList *dkc_chain_statement_list(StatementList *list,
                                        Statement *statement);
TypeSpecifier *dkc_create_type_specifier(DVM_BasicType basic_type);
TypeSpecifier *dkc_create_array_type_specifier(TypeSpecifier *base);
Expression *dkc_alloc_expression(ExpressionKind type);
Expression *dkc_create_comma_expression(Expression *left, Expression *right);
Expression *dkc_create_assign_expression(Expression *left,
                                         AssignmentOperator operator,
                                         Expression *operand);
Expression *dkc_create_binary_expression(ExpressionKind operator,
                                         Expression *left,
                                         Expression *right);
Expression *dkc_create_minus_expression(Expression *operand);
Expression *dkc_create_logical_not_expression(Expression *operand);
Expression *dkc_create_index_expression(Expression *array, Expression *index);
Expression *dkc_create_incdec_expression(Expression *operand,
                                         ExpressionKind inc_or_dec);
Expression *dkc_create_identifier_expression(char *identifier);
Expression *dkc_create_function_call_expression(Expression *function,
                                                ArgumentList *argument);
Expression *dkc_create_member_expression(Expression *expression,
                                         char *member_name);
Expression *dkc_create_boolean_expression(DVM_Boolean value);
Expression *dkc_create_null_expression(void);
Expression *dkc_create_array_literal_expression(ExpressionList *list);
Expression *dkc_create_array_creation(DVM_BasicType basic_type,
                                      ArrayDimension *dim_expr_list,
                                      ArrayDimension *dim_ilst);
ArrayDimension *dkc_create_array_dimension(Expression *expr);
ArrayDimension *dkc_chain_array_dimension(ArrayDimension *list,
                                          ArrayDimension *dim);
Statement *dkc_create_if_statement(Expression *condition,
                                   Block *then_block, Elsif *elsif_list,
                                   Block *else_block);
Elsif *dkc_chain_elsif_list(Elsif *list, Elsif *add);
Elsif *dkc_create_elsif(Expression *expr, Block *block);
Statement *dkc_create_while_statement(char *label,
                                      Expression *condition, Block *block);
Statement *
dkc_create_foreach_statement(char *label, char *variable,
                             Expression *collection, Block *block);
Statement *dkc_create_for_statement(char *label,
                                    Expression *init, Expression *cond,
                                    Expression *post, Block *block);
Block * dkc_open_block(void);
Block *dkc_close_block(Block *block, StatementList *statement_list);
Statement *dkc_create_expression_statement(Expression *expression);
Statement *dkc_create_return_statement(Expression *expression);
Statement *dkc_create_break_statement(char *label);
Statement *dkc_create_continue_statement(char *label);
Statement *dkc_create_try_statement(Block *try_block, char *exception,
                                    Block *catch_block,
                                    Block *finally_block);
Statement *dkc_create_throw_statement(Expression *expression);
Statement *dkc_create_declaration_statement(TypeSpecifier *type,
                                            char *identifier,
                                            Expression *initializer);
/* string.c */
char *dkc_create_identifier(char *str);
void dkc_open_string_literal(void);
void dkc_add_string_literal(int letter);
void dkc_reset_string_literal_buffer(void);
DVM_Char *dkc_close_string_literal(void);

/* fix_tree.c */
void dkc_fix_tree(DKC_Compiler *compiler);

/* generate.c */
DVM_Executable *dkc_generate(DKC_Compiler *compiler);

/* util.c */
DKC_Compiler *dkc_get_current_compiler(void);
void dkc_set_current_compiler(DKC_Compiler *compiler);
void *dkc_malloc(size_t size);
char *dkc_strdup(char *src);
TypeSpecifier *dkc_alloc_type_specifier(DVM_BasicType type);
TypeDerive *dkc_alloc_type_derive(DeriveTag derive_tag);
DVM_Boolean dkc_compare_parameter(ParameterList *param1,
                                  ParameterList *param2);
DVM_Boolean dkc_compare_type(TypeSpecifier *type1, TypeSpecifier *type2);
FunctionDefinition *dkc_search_function(char *name);
Declaration *dkc_search_declaration(char *identifier, Block *block);
void dkc_vstr_clear(VString *v);
void dkc_vstr_append_string(VString *v, char *str);
void dkc_vstr_append_character(VString *v, int ch);
void dkc_vwstr_clear(VWString *v);
void dkc_vwstr_append_string(VWString *v, DVM_Char *str);
void dkc_vwstr_append_character(VWString *v, int ch);
char *dkc_get_type_name(TypeSpecifier *type);
char *dkc_get_basic_type_name(DVM_BasicType type);
DVM_Char *dkc_expression_to_string(Expression *expr);

/* wchar.c */
size_t dkc_wcslen(DVM_Char *str);
DVM_Char *dkc_wcscpy(DVM_Char *dest, DVM_Char *src);
DVM_Char *dkc_wcsncpy(DVM_Char *dest, DVM_Char *src, size_t n);
int dkc_wcscmp(DVM_Char *s1, DVM_Char *s2);
DVM_Char *dkc_wcscat(DVM_Char *s1, DVM_Char *s2);
int dkc_mbstowcs_len(const char *src);
void dkc_mbstowcs(const char *src, DVM_Char *dest);
DVM_Char *dkc_mbstowcs_alloc(int line_number, const char *src);
int dkc_wcstombs_len(const DVM_Char *src);
void dkc_wcstombs(const DVM_Char *src, char *dest);
char *dkc_wcstombs_alloc(const DVM_Char *src);
char dkc_wctochar(DVM_Char src);
int dkc_print_wcs(FILE *fp, DVM_Char *str);
int dkc_print_wcs_ln(FILE *fp, DVM_Char *str);
DVM_Boolean dkc_iswdigit(DVM_Char ch);

/* error.c */
void dkc_compile_error(int line_number, CompileError id, ...);

/* disassemble.c */
void dkc_disassemble(DVM_Executable *exe);

#endif /* PRIVATE_DIKSAMC_H_INCLUDED */
