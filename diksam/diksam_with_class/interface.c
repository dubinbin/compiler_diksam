#include "stdafx.h"
#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "diksamc.h"

static CompilerList *st_compiler_list = NULL;

extern BuiltinScript dkc_builtin_script[];

// 内建方法参数定义，包括参数名，参数类型
typedef struct {
	char *name;
	DVM_BasicType type;
} BuiltInMethodParameter;

// 内建方法定义，包括内建方法名，返回值类型，内建方法参数，参数数量
typedef struct {
    char *name;
    DVM_BasicType return_type;
    BuiltInMethodParameter *parameter;
    int parameter_count;
} BuiltInMethod;

static BuiltInMethodParameter st_array_resize_arg[] = {
    {"new_size", DVM_INT_TYPE}
};
static BuiltInMethodParameter st_array_insert_arg[] = {
    {"index", DVM_INT_TYPE},
    {"new_item", DVM_BASE_TYPE}
};
static BuiltInMethodParameter st_array_remove_arg[] = {
    {"index", DVM_INT_TYPE}
};
static BuiltInMethodParameter st_array_add_arg[] = {
    {"new_item", DVM_BASE_TYPE}
};

// 数组内建方法
static BuiltInMethod st_array_method[] = {
	{ ARRAY_METHOD_SIZE, DVM_INT_TYPE, NULL, 0 },
	{ ARRAY_METHOD_RESIZE, DVM_VOID_TYPE, st_array_resize_arg, ARRAY_SIZE(st_array_resize_arg) },
	{ ARRAY_METHOD_INSERT, DVM_VOID_TYPE, st_array_insert_arg, ARRAY_SIZE(st_array_insert_arg) },
	{ ARRAY_METHOD_REMOVE, DVM_VOID_TYPE, st_array_remove_arg, ARRAY_SIZE(st_array_remove_arg) },
	{ ARRAY_METHOD_ADD, DVM_VOID_TYPE, st_array_add_arg, ARRAY_SIZE(st_array_add_arg) },
};

static BuiltInMethodParameter st_string_substr_arg[] = {
    {"start", DVM_INT_TYPE},
    {"length", DVM_INT_TYPE}
};

// 字符串内建方法
static BuiltInMethod st_string_method[] = {
    {"length", DVM_INT_TYPE, NULL, 0},
    {"substr", DVM_STRING_TYPE, st_string_substr_arg,
     ARRAY_SIZE(st_string_substr_arg)},
};

// 创建内建方法
static FunctionDefinition* create_built_in_method(BuiltInMethod *src, int method_count){
	int i;
	int param_idx;
	ParameterList *param_list;
	FunctionDefinition *fd_array;

	fd_array = dkc_malloc(sizeof(FunctionDefinition) * method_count);
	for (i = 0; i < method_count; i++) {
		fd_array[i].name = src[i].name;
		fd_array[i].type = dkc_alloc_type_specifier(src[i].return_type);
		param_list = NULL;
		for (param_idx = 0; param_idx < src[i].parameter_count; param_idx++) {
			TypeSpecifier *type = dkc_alloc_type_specifier(src[i].parameter[param_idx].type);
			if (param_list) {
				param_list = dkc_chain_parameter(param_list, type, src[i].parameter[param_idx].name);
			}
			else {
				param_list = dkc_create_parameter(type, src[i].parameter[param_idx].name);
			}
		}
		fd_array[i].parameter = param_list;
	}
	return fd_array;
}

// 创建编译器的公共接口
DKC_Compiler* DKC_create_compiler(void){
	MEM_Storage storage;
	DKC_Compiler *compiler;
	DKC_Compiler *compiler_backup;

	compiler_backup = dkc_get_current_compiler();
	storage = MEM_open_storage(0);
	compiler = MEM_storage_malloc(storage, sizeof(struct _DKC_Compiler));
	dkc_set_current_compiler(compiler);
	compiler->compile_storage = storage;
	compiler->package_name = NULL;
	compiler->source_suffix = DKM_SOURCE;
	compiler->require_list = NULL;
	compiler->rename_list = NULL;
	compiler->function_list = NULL;
	compiler->dvm_function_count = 0;
	compiler->dvm_function = NULL;
	compiler->dvm_class_count = 0;
	compiler->dvm_class = NULL;
	compiler->declaration_list = NULL;
	compiler->statement_list = NULL;
	compiler->class_definition_list = NULL;
	compiler->current_block = NULL;
	compiler->current_line_number = 1;
	compiler->current_class_definition = NULL;
	compiler->input_mode = FILE_INPUT_MODE;
	compiler->input_mode = STRING_INPUT_MODE;
	compiler->required_list = NULL;
	compiler->array_method_count = ARRAY_SIZE(st_array_method);
	compiler->array_method = create_built_in_method(st_array_method, ARRAY_SIZE(st_array_method));
	compiler->string_method_count = ARRAY_SIZE(st_string_method);
	compiler->string_method = create_built_in_method(st_string_method, ARRAY_SIZE(st_string_method));

#define UTF_8_SOURCE

#ifdef EUC_SOURCE
	compiler->source_encoding = EUC_ENCODING;
#else
#ifdef SHIFT_JIS_SOURCE
	compiler->source_encoding = SHIFT_JIS_ENCODING;
#else
#ifdef UTF_8_SOURCE
	compiler->source_encoding = UTF_8_ENCODING;
#else
	DBG_panic(("source encoding is not defined.\n"));
#endif
#endif
#endif

	dkc_set_current_compiler(compiler_backup);

	return compiler;
}

// 将第二个参数指定的编译器加入到编译器链表的尾端
static CompilerList* add_compiler_to_list(CompilerList *list, DKC_Compiler *compiler){
	CompilerList *pos;
	CompilerList *new_item;

	new_item = MEM_malloc(sizeof(CompilerList));
	new_item->compiler = compiler;
	new_item->next = NULL;
	if (list == NULL) {
		return new_item;
	}
	for (pos = list; pos->next; pos = pos->next);
	pos->next = new_item;

	return list;
}

// 根据包名在全局编译器链表中搜寻被定义为该包名的编译器，搜寻成功返回该编译器的地址，失败返回null
static DKC_Compiler* search_compiler(CompilerList *list, PackageName *package_name){
	CompilerList *pos;

	for (pos = list; pos; pos = pos->next) {
		if (dkc_compare_package_name(pos->compiler->package_name, package_name))
			break;
	}
	if (pos) {
		return pos->compiler;
	}
	else {
		return NULL;
	}
}

// 创建搜寻路径,首先获得包名称链表，遍历链表中的每一个包名称，将其组合成一个整体的字符串
// 并用适当的分隔符分割字符串，需要注意windows下和unix-like下的分隔符不一样，在windows下需要定义DKM_WINDOWS
static void make_search_path(int line_number, PackageName *package_name, char *buf){
    PackageName *pos;
    int len = 0;
    int prev_len = 0;
    int suffix_len;

    suffix_len = strlen(DIKSAM_REQUIRE_SUFFIX);
    buf[0] = '\0';
    for (pos = package_name; pos; pos = pos->next) {
        prev_len = len;
        len += strlen(pos->name);
        if (len > FILENAME_MAX - (2 + suffix_len)) {
            dkc_compile_error(line_number,
                              PACKAGE_NAME_TOO_LONG_ERR,
                              MESSAGE_ARGUMENT_END);
        }
        strcpy(&buf[prev_len], pos->name);
        if (pos->next) {
            buf[strlen(buf)] = FILE_SEPARATOR;
            len++;
        }
    }
    strcpy(&buf[len], DIKSAM_REQUIRE_SUFFIX);
}

// 创建源代码（实现文件而不是头文件）的搜寻路径
static void make_search_path_impl(char *package_name, char *buf){
	int suffix_len;
	int package_len;
	int i;

	suffix_len = strlen(DIKSAM_IMPLEMENTATION_SUFFIX);
	package_len = strlen(package_name);
	DBG_assert(package_len <= FILENAME_MAX - (2 + suffix_len), ("package name is too long(%s)", package_name));
	for (i = 0; package_name[i] != '\0'; i++) {
		if (package_name[i] == '.') {
			buf[i] = FILE_SEPARATOR;
		}
		else {
			buf[i] = package_name[i];
		}
	}
	buf[i] = '\0';
	strcat(buf, DIKSAM_IMPLEMENTATION_SUFFIX);
}

// 获取需求链表中的各个包的文件的文件指针，将文件指针保存在最后一个参数当中，
static void get_require_input(RequireList *req, char *found_path, SourceInput *source_input){
	char *search_path;
	char search_file[FILENAME_MAX];
	FILE *fp;
	SearchFileStatus status;

	search_path = getenv("DKM_REQUIRE_SEARCH_PATH");
	if (search_path == NULL) {
		search_path = ".";
	}
	make_search_path(req->line_number, req->package_name, search_file);
	status = dvm_search_file(search_path, search_file, found_path, &fp);
	if (status != SEARCH_FILE_SUCCESS) {
		if (status == SEARCH_FILE_NOT_FOUND) {
			dkc_compile_error(req->line_number,
				REQUIRE_FILE_NOT_FOUND_ERR,
				STRING_MESSAGE_ARGUMENT, "file", search_file,
				MESSAGE_ARGUMENT_END);
		}
		else {
			dkc_compile_error(req->line_number,
				REQUIRE_FILE_ERR,
				INT_MESSAGE_ARGUMENT, "status", (int)status,
				MESSAGE_ARGUMENT_END);
		}
	}
	source_input->input_mode = FILE_INPUT_MODE;
	source_input->u.file.fp = fp;
}

// 
static DVM_Boolean add_exe_to_list(DVM_Executable *exe, DVM_ExecutableList *list){
	DVM_ExecutableItem *new_item;
	DVM_ExecutableItem *pos;
	DVM_ExecutableItem *tail = NULL;

	// 遍历执行体链表，判断执行体中的编译器所代表的包名是否和待加入的编译器的包名相同并且这两者都定义了需求链表
	// 那么说明执行体里已经有过这个包的编译器了，不用再添加了，否则将新的编译器添加到执行体的尾部
	for (pos = list->list; pos; pos = pos->next) {
		if (dvm_compare_package_name(pos->executable->package_name, exe->package_name) && pos->executable->is_required == exe->is_required) {
			return DVM_FALSE;
		}
		tail = pos;
	}
	new_item = MEM_malloc(sizeof(DVM_ExecutableItem));
	new_item->executable = exe;
	new_item->next = NULL;
	if (list->list == NULL) {
		list->list = new_item;
	}
	else {
		tail->next = new_item;
	}

	return DVM_TRUE;
}

static void set_path_to_compiler(DKC_Compiler *compiler, char *path){
	compiler->path = MEM_storage_malloc(compiler->compile_storage, strlen(path) + 1);
	strcpy(compiler->path, path);
}

static DVM_Executable* do_compile(DKC_Compiler *compiler, DVM_ExecutableList *list, char *path, DVM_Boolean is_required){
    extern FILE *yyin;
    extern int yyparse(void);
    RequireList *req_pos;
    DKC_Compiler *req_comp;
    DVM_Executable *exe;
    DVM_Executable *req_exe;
    char found_path[FILENAME_MAX];
    DKC_Compiler *compiler_backup;
    SourceInput source_input;
	// 备份当前编译器，然后把参数指定的编译器当作当前的，开始执行编译，编译完成后分析需求链表
    compiler_backup = dkc_get_current_compiler();
    dkc_set_current_compiler(compiler);
    if (yyparse()) {
		fprintf(stderr, "Error ! Error ! Error !\n");
		getchar();
        exit(1);
    }
	// 首先遍历编译器的需求链表，根据需求链表中的包名搜寻（已经将该包编译完成的）编译器
	// 如果搜寻到并且得到了包含该包的编译器的地址，就将该编译器加入到当前编译器的编译器需求链表中
	// 如果没有找到，就需要先为这个包创建一个编译器，然后将其加入到当前编译器的编译器需求链表中
	// 也要将为需求链表中的包创建的编译器加入到全局编译器链表中，当然还要将此包编译才能使用它
	// 所以需要根据包名称和搜寻路径来寻找这个包的物理存储位置，获得源文件的指针，根据输入模式
	// 将代码送入词法分析器中，然后语法分析器获取此法分析器生成的符号，语法分析器调用create函数族
	// 创建语法树
	for (req_pos = compiler->require_list; req_pos;req_pos = req_pos->next) {
        req_comp = search_compiler(st_compiler_list, req_pos->package_name);
        if (req_comp) {
            compiler->required_list = add_compiler_to_list(compiler->required_list, req_comp);
            continue;
        }
        req_comp = DKC_create_compiler();
        /* BUGBUG req_comp references parent compiler's MEM_storage */
        req_comp->package_name = req_pos->package_name;
        req_comp->source_suffix = DKH_SOURCE;
        compiler->required_list = add_compiler_to_list(compiler->required_list, req_comp);
        st_compiler_list = add_compiler_to_list(st_compiler_list, req_comp);
		// 
        get_require_input(req_pos, found_path, &source_input);
        set_path_to_compiler(req_comp, found_path);
        req_comp->input_mode = source_input.input_mode;
        if (source_input.input_mode == FILE_INPUT_MODE) {
            yyin = source_input.u.file.fp;
        } else {
            dkc_set_source_string(source_input.u.string.lines);
        }
		// 递归调用编译器为需求链表中的每一个包创建编译器，所以最后一个参数为true
		// 表明该包定义了需求链表
        req_exe = do_compile(req_comp, list, found_path, DVM_TRUE);
    }
	// 语法树创建完毕后执行修复
	// 然后生成中间代码
	// 将当前执行体加入到执行体链表中
    dkc_fix_tree(compiler);
    exe = dkc_generate(compiler);
    if (path) {
        exe->path = MEM_strdup(path);
    } else {
        exe->path = NULL;
    }
    //dvm_disassemble(exe);
    exe->is_required = is_required;
    if (!add_exe_to_list(exe, list)) {
		// 如果没有添加到执行体中的话，这个编译器没有必要留着了，直接释放掉
        dvm_dispose_executable(exe);
    }
    dkc_set_current_compiler(compiler_backup);

    return exe;
}

static void dispose_compiler_list(void){
	CompilerList *temp;

	while (st_compiler_list) {
		temp = st_compiler_list;
		st_compiler_list = temp->next;
		MEM_free(temp);
	}
}

// 启动编译器公共接口
DVM_ExecutableList* DKC_compile(DKC_Compiler *compiler, FILE *fp, char *path){
    extern FILE *yyin;
    DVM_ExecutableList *list;
    DVM_Executable *exe;

    DBG_assert(st_compiler_list == NULL,("st_compiler_list != NULL(%p)", st_compiler_list));
    set_path_to_compiler(compiler, path);
    compiler->input_mode = FILE_INPUT_MODE;
	yyin = fp;
    list = MEM_malloc(sizeof(DVM_ExecutableList));
    list->list = NULL;
    exe = do_compile(compiler, list, NULL, DVM_FALSE);
    exe->path = MEM_strdup(path);
	// 第一个被编译的编译器成为执行体的顶级环境
    list->top_level = exe;
    //dvm_disassemble(exe);
    dispose_compiler_list();
    dkc_reset_string_literal_buffer();

    return list;
}

// 根据参数为编译器创建一个包名称节点，因为包名称可能是xxx.yyy.zzz这样的形式，这个函数只创建其中的一段字符
PackageName* create_one_package_name(DKC_Compiler *compiler, char *str, int start_idx, int to_idx){
	PackageName *pn;
	int i;

	MEM_Storage storage = compiler->compile_storage;
	pn = MEM_storage_malloc(storage, sizeof(PackageName));
	pn->name = MEM_storage_malloc(storage, to_idx - start_idx + 1);
	for (i = 0; i < to_idx - start_idx; i++) {
		pn->name[i] = str[start_idx + i];
	}
	pn->name[i] = '\0';
	pn->next = NULL;

	return pn;
}

// 创建一个包名称链表
static PackageName* string_to_package_name(DKC_Compiler *compiler, char *str){
	int start_idx;
	int i;
	PackageName *pn;
	PackageName *top = NULL;
	PackageName *tail = NULL;

	for (start_idx = i = 0; str[i] != '\0'; i++) {
		if (str[i] == '.') {
			pn = create_one_package_name(compiler, str, start_idx, i);
			start_idx = i + 1;
			if (tail) {
				tail->next = pn;
			}
			else {
				top = pn;
			}
			tail = pn;
		}
	}
	pn = create_one_package_name(compiler, str, start_idx, i);
	if (tail) {
		tail->next = pn;
	}
	else {
		top = pn;
	}

	return top;
}

// 动态加载需求链表中的包对应的实现代码
SearchFileStatus get_dynamic_load_input(char *package_name, char *found_path, char *search_file, SourceInput *source_input){
	SearchFileStatus status;
	char *search_path;
	FILE *fp;

	search_path = getenv("DKM_LOAD_SEARCH_PATH");
	if (search_path == NULL) {
		search_path = ".";
	}
	make_search_path_impl(package_name, search_file);
	status = dvm_search_file(search_path, search_file, found_path, &fp);
	if (status != SEARCH_FILE_SUCCESS) {
		return status;
	}
	source_input->input_mode = FILE_INPUT_MODE;
	source_input->u.file.fp = fp;

	return SEARCH_FILE_SUCCESS;
}

// 对需要动态加载的的代码进行编译
SearchFileStatus dkc_dynamic_compile(DKC_Compiler *compiler, char *package_name, DVM_ExecutableList *list, DVM_ExecutableItem **add_top, char *search_file){
	SearchFileStatus status;
	extern FILE *yyin;
	DVM_ExecutableItem *tail;
	DVM_Executable *exe;
	SourceInput source_input;
	char found_path[FILENAME_MAX];

	status = get_dynamic_load_input(package_name, found_path, search_file, &source_input);
	if (status != SEARCH_FILE_SUCCESS) {
		return status;
	}
	DBG_assert(st_compiler_list == NULL, ("st_compiler_list != NULL(%p)", st_compiler_list));
	// 遍历当前执行体中的执行器链表，并将指针移动到链表尾部
	for (tail = list->list; tail->next; tail = tail->next);
	compiler->package_name = string_to_package_name(compiler, package_name);
	set_path_to_compiler(compiler, found_path);
	compiler->input_mode = source_input.input_mode;
	if (source_input.input_mode == FILE_INPUT_MODE) {
		yyin = source_input.u.file.fp;
	}
	else {
		dkc_set_source_string(source_input.u.string.lines);
	}
	exe = do_compile(compiler, list, found_path, DVM_FALSE);
	dispose_compiler_list();
	dkc_reset_string_literal_buffer();
	*add_top = tail->next;

	return SEARCH_FILE_SUCCESS;
}

// 遍历编译器，如果参数所指编译器不存在链表中则将第二个参数指定的编译器加入到第一个参数指定的链表中
// 如果待加入的编译器存在需求链表，则将需求链表中的包的编译器也加入
static CompilerList* traversal_compiler(CompilerList *list, DKC_Compiler *compiler){
	CompilerList *list_pos;
	CompilerList *req_pos;

	if (list == NULL){
		list = add_compiler_to_list(list, compiler);
	}
	for (list_pos = list; list_pos; list_pos = list_pos->next) {
		if (list_pos->compiler == compiler)
			break;
	}
	//if (list_pos == NULL) {
	//	list = add_compiler_to_list(list, compiler);
	//}
	for (req_pos = compiler->required_list; req_pos; req_pos = req_pos->next) {
		list = traversal_compiler(list, req_pos->compiler);
	}

	return list;
}

void DKC_dispose_compiler(DKC_Compiler *compiler){
	CompilerList *list = NULL;
	CompilerList *pos;
	FunctionDefinition *fd_pos;
	CompilerList *temp;

	list = traversal_compiler(list, compiler);
	for (pos = list; pos;) {
		for (fd_pos = pos->compiler->function_list; fd_pos; fd_pos = fd_pos->next) {
			MEM_free(fd_pos->local_variable);
		}
		while (pos->compiler->required_list) {
			temp = pos->compiler->required_list;
			pos->compiler->required_list = temp->next;
			MEM_free(temp);
		}
		MEM_dispose_storage(pos->compiler->compile_storage);
		temp = pos->next;
		MEM_free(pos);
		pos = temp;
	}
}
