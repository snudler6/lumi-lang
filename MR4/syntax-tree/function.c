#ifndef MR_MAINFILE
#define MR_MAINFILE "syntax-tree/function.c"
#define DEPTH 5
#include "mr.3.h"
#else

#if MR_STAGE == MR_TYPEDEFS
static char* _mr_file17_name = "syntax-tree/function.3.mr";
#endif
#define MR_FILE_NAME _mr_file17_name

/* MR4 compiler - Syntax tree function */

/* Function node in the syntax tree */
#if MR_STAGE == MR_TYPEDEFS
typedef struct SyntaxTreeFunction SyntaxTreeFunction;
#elif MR_STAGE == MR_TYPES(3)
struct SyntaxTreeFunction {
  SyntaxTreeBlock _base;
  List* aux_variables_owner;
  TypeData* parent_type;
  String* name;
  FunctionArguments* arguments;
  Bool is_dynamic;
/* write function body */};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_parse_new(SyntaxTreeFunction* self, TypeData* parent_type, Char* end, SyntaxTreeFunction** new_node);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_parse_new = "SyntaxTreeFunction.parse-new";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_parse_new
Returncode SyntaxTreeFunction_parse_new(SyntaxTreeFunction* self, TypeData* parent_type, Char* end, SyntaxTreeFunction** new_node) {
  (*new_node) = malloc(sizeof(SyntaxTreeFunction));
  if ((*new_node) == NULL) RAISE(13)
  *(*new_node) = (SyntaxTreeFunction){SyntaxTreeFunction__dtl, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, false, NULL, NULL, NULL, NULL, false};
  (*new_node)->_base._base._base._dtl = SyntaxTreeFunction__dtl;
  CHECK(14, SyntaxTreeFunction_parse((*new_node), parent_type, &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_parse(SyntaxTreeFunction* self, TypeData* parent_type, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_parse = "SyntaxTreeFunction.parse";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_parse
Returncode SyntaxTreeFunction_parse(SyntaxTreeFunction* self, TypeData* parent_type, Char* end) {
  CHECK(17, SyntaxTreeFunction_init(self) )
  self->parent_type = parent_type;
  if (NULL != self->parent_type) {
    self->_base._base.indentation_spaces = 4;
    if (self->parent_type->is_dynamic) {
      String* meth_type = NULL;
      Int _Int73;
      CHECK(23, read_until(&(String){2, 1, " "}, false, &(meth_type), &((*end)), &(_Int73)) )
      Bool _Bool74;
      CHECK(24, String_equal(meth_type, &(String){8, 7, "dynamic"}, &(_Bool74)) )
      if (_Bool74) {
        self->is_dynamic = true;
      }
      else {
        Bool _Bool75;
        CHECK(26, String_equal(meth_type, &(String){5, 4, "inst"}, &(_Bool75)) )
        if (!_Bool75) {
          CHECK(27, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){46, 45, "expected \"dynamic\" or \"inst\" method type, got"}, meth_type) )
        }
      }
    }
  }
  CHECK(30, SyntaxTreeFunction_parse_header(self, &((*end))) )
  CHECK(31, SyntaxTreeFunction_parse_body(self, &((*end))) )
  self->_base._base.indentation_spaces = 2;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_init(SyntaxTreeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_init = "SyntaxTreeFunction.init";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_init
Returncode SyntaxTreeFunction_init(SyntaxTreeFunction* self) {
  CHECK(35, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
  self->aux_variables_owner = malloc(sizeof(List));
  if (self->aux_variables_owner == NULL) RAISE(36)
  *self->aux_variables_owner = (List){NULL, NULL};
  self->_base.aux_variables = self->aux_variables_owner;
  self->_base._base.indentation_spaces = 2;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_parse_body(SyntaxTreeFunction* self, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_parse_body = "SyntaxTreeFunction.parse-body";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_parse_body
Returncode SyntaxTreeFunction_parse_body(SyntaxTreeFunction* self, Char* end) {
  CHECK(41, SyntaxTreeBlock_parse_block(&(self->_base), &((*end))) )
  Bool _Bool76;
  CHECK(42, SyntaxTreeBlock_m_has_end_point(&(self->_base), &(_Bool76)) )
  if (!_Bool76) {
    SyntaxTreeReturn* _SyntaxTreeReturn77;
    CHECK(43, SyntaxTreeReturn_parse_new(NULL, &(self->_base), &((*end)), &(_SyntaxTreeReturn77)) )
    CHECK(43, List_add(self->_base.code_nodes, &(_SyntaxTreeReturn77->_base)) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_parse_header(SyntaxTreeFunction* self, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_parse_header = "SyntaxTreeFunction.parse-header";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_parse_header
Returncode SyntaxTreeFunction_parse_header(SyntaxTreeFunction* self, Char* end) {
  CHECK(47, read_new(&(String){2, 1, "("}, &(self->name), &((*end))) )
  if ((*end) != '(') {
    CHECK(49, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base._base), &(String){38, 37, "expected \"(\" after function name, got"}, (*end)) )
  }
  self->arguments = malloc(sizeof(FunctionArguments));
  if (self->arguments == NULL) RAISE(51)
  *self->arguments = (FunctionArguments){FunctionArguments__dtl, NULL, 0, NULL, NULL};
  self->arguments->_base._dtl = FunctionArguments__dtl;
  DeclarationArgumentFactory* argument_factory = &(DeclarationArgumentFactory){DeclarationArgumentFactory__dtl};
  argument_factory->_base._dtl = DeclarationArgumentFactory__dtl;
  CHECK(53, FunctionArguments_parse(self->arguments, &(argument_factory->_base), NULL, self->parent_type, &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_m_get_parent_type(SyntaxTreeFunction* self, TypeData** parent_type);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_m_get_parent_type = "SyntaxTreeFunction.m-get-parent-type";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_m_get_parent_type
Returncode SyntaxTreeFunction_m_get_parent_type(SyntaxTreeFunction* self, TypeData** parent_type) {
  (*parent_type) = self->parent_type;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_m_find_variable(SyntaxTreeFunction* self, String* name, SyntaxTreeVariable** variable);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_m_find_variable = "SyntaxTreeFunction.m-find-variable";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_m_find_variable
Returncode SyntaxTreeFunction_m_find_variable(SyntaxTreeFunction* self, String* name, SyntaxTreeVariable** variable) {
  CHECK(61, SyntaxTreeBlock_m_find_variable(&(self->_base), name, &((*variable))) )
  if (!(NULL != (*variable))) {
    CHECK(63, FunctionArguments_m_find_variable(self->arguments, name, &((*variable))) )
  }
  if (!(NULL != (*variable))) {
    CHECK(65, (glob->root)->_base._base._base._dtl[3](glob->root, name, &((*variable))) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_analyze(SyntaxTreeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_analyze = "SyntaxTreeFunction.analyze";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_analyze
Returncode SyntaxTreeFunction_analyze(SyntaxTreeFunction* self) {
  CHECK(68, FunctionArguments_analyze(self->arguments) )
  CHECK(69, SyntaxTreeBlock_analyze(&(self->_base)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_m_compare(SyntaxTreeFunction* self, SyntaxTreeFunction* other);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_m_compare = "SyntaxTreeFunction.m-compare";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_m_compare
Returncode SyntaxTreeFunction_m_compare(SyntaxTreeFunction* self, SyntaxTreeFunction* other) {
  if (self->is_dynamic != other->is_dynamic) {
    CHECK(73, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){28, 27, "illegal dynamic in function"}, self->name) )
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif/* write function body */
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_write(SyntaxTreeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_write = "SyntaxTreeFunction.write";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_write
Returncode SyntaxTreeFunction_write(SyntaxTreeFunction* self) {
  /* Returncode `Type`_`name`(`args`) { */
  /*   `block...` */
  /* } */
  CHECK(80, SyntaxTreeFunction_write_header(self) )
  CHECK(81, SyntaxTreeBlock_write_block(&(self->_base)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_write_header(SyntaxTreeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_write_header = "SyntaxTreeFunction.write-header";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_write_header
Returncode SyntaxTreeFunction_write_header(SyntaxTreeFunction* self) {
  CHECK(84, write(&(String){12, 11, "Returncode "}) )
  if (NULL != self->parent_type) {
    CHECK(86, write_cname(self->parent_type->name) )
    CHECK(87, write(&(String){2, 1, "_"}) )
  }
  CHECK(88, write_cname(self->name) )
  CHECK(89, FunctionArguments_write(self->arguments, true) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_write_pointer(SyntaxTreeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_write_pointer = "SyntaxTreeFunction.write-pointer";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_write_pointer
Returncode SyntaxTreeFunction_write_pointer(SyntaxTreeFunction* self) {
  CHECK(92, write(&(String){14, 13, "Returncode (*"}) )
  CHECK(93, write_cname(self->name) )
  CHECK(94, write(&(String){2, 1, ")"}) )
  CHECK(95, FunctionArguments_write(self->arguments, true) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeFunction_write_declaration(SyntaxTreeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeFunction_write_declaration = "SyntaxTreeFunction.write-declaration";
#define MR_FUNC_NAME _func_name_SyntaxTreeFunction_write_declaration
Returncode SyntaxTreeFunction_write_declaration(SyntaxTreeFunction* self) {
  /* Returncode `Type`_`name`(`args`); */
  CHECK(99, write(&(String){2, 1, "\n"}) )
  CHECK(100, SyntaxTreeFunction_write_header(self) )
  CHECK(101, write(&(String){3, 2, ";\n"}) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func SyntaxTreeFunction__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func SyntaxTreeFunction__dtl[] = {(void*)SyntaxTreeFunction_analyze, (void*)SyntaxTreeFunction_write, (void*)SyntaxTreeBlock_parse_child, (void*)SyntaxTreeFunction_m_find_variable, (void*)SyntaxTreeFunction_m_get_parent_type};
#endif


/* Main function node in the syntax tree */
#if MR_STAGE == MR_TYPEDEFS
typedef struct SyntaxTreeMainFunction SyntaxTreeMainFunction;
#elif MR_STAGE == MR_TYPES(4)
struct SyntaxTreeMainFunction {
  SyntaxTreeFunction _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeMainFunction_parse_new(SyntaxTreeMainFunction* self, Char* end, SyntaxTreeMainFunction** new_node);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeMainFunction_parse_new = "SyntaxTreeMainFunction.parse-new";
#define MR_FUNC_NAME _func_name_SyntaxTreeMainFunction_parse_new
Returncode SyntaxTreeMainFunction_parse_new(SyntaxTreeMainFunction* self, Char* end, SyntaxTreeMainFunction** new_node) {
  (*new_node) = malloc(sizeof(SyntaxTreeMainFunction));
  if ((*new_node) == NULL) RAISE(107)
  *(*new_node) = (SyntaxTreeMainFunction){SyntaxTreeMainFunction__dtl, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, false, NULL, NULL, NULL, NULL, false};
  (*new_node)->_base._base._base._base._dtl = SyntaxTreeMainFunction__dtl;
  CHECK(108, SyntaxTreeMainFunction_parse((*new_node), &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeMainFunction_parse(SyntaxTreeMainFunction* self, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeMainFunction_parse = "SyntaxTreeMainFunction.parse";
#define MR_FUNC_NAME _func_name_SyntaxTreeMainFunction_parse
Returncode SyntaxTreeMainFunction_parse(SyntaxTreeMainFunction* self, Char* end) {
  CHECK(111, SyntaxTreeFunction_init(&(self->_base)) )
  CHECK(112, string_new_copy(&(String){5, 4, "main"}, &(self->_base.name)) )
  self->_base.arguments = malloc(sizeof(FunctionArguments));
  if (self->_base.arguments == NULL) RAISE(113)
  *self->_base.arguments = (FunctionArguments){FunctionArguments__dtl, NULL, 0, NULL, NULL};
  self->_base.arguments->_base._dtl = FunctionArguments__dtl;
  CHECK(114, FunctionArguments_init(self->_base.arguments) )
  CHECK(115, SyntaxTreeFunction_parse_body(&(self->_base), &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeMainFunction_write(SyntaxTreeMainFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeMainFunction_write = "SyntaxTreeMainFunction.write";
#define MR_FUNC_NAME _func_name_SyntaxTreeMainFunction_write
Returncode SyntaxTreeMainFunction_write(SyntaxTreeMainFunction* self) {
  /* USER_MAIN_HEADER { */
  /*   `block...` */
  /* } */
  /* MAIN_FUNC */
  CHECK(122, write(&(String){18, 17, "\nUSER_MAIN_HEADER"}) )
  CHECK(123, SyntaxTreeBlock_write_block(&(self->_base._base)) )
  CHECK(124, write(&(String){12, 11, "\nMAIN_FUNC\n"}) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func SyntaxTreeMainFunction__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func SyntaxTreeMainFunction__dtl[] = {(void*)SyntaxTreeFunction_analyze, (void*)SyntaxTreeMainFunction_write, (void*)SyntaxTreeBlock_parse_child, (void*)SyntaxTreeFunction_m_find_variable, (void*)SyntaxTreeFunction_m_get_parent_type};
#endif


/* Native function declaration in the syntax tree */
#if MR_STAGE == MR_TYPEDEFS
typedef struct SyntaxTreeNativeFunction SyntaxTreeNativeFunction;
#elif MR_STAGE == MR_TYPES(4)
struct SyntaxTreeNativeFunction {
  SyntaxTreeFunction _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeNativeFunction_parse_new(SyntaxTreeNativeFunction* self, Char* end, SyntaxTreeNativeFunction** new_node);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeNativeFunction_parse_new = "SyntaxTreeNativeFunction.parse-new";
#define MR_FUNC_NAME _func_name_SyntaxTreeNativeFunction_parse_new
Returncode SyntaxTreeNativeFunction_parse_new(SyntaxTreeNativeFunction* self, Char* end, SyntaxTreeNativeFunction** new_node) {
  (*new_node) = malloc(sizeof(SyntaxTreeNativeFunction));
  if ((*new_node) == NULL) RAISE(130)
  *(*new_node) = (SyntaxTreeNativeFunction){SyntaxTreeNativeFunction__dtl, NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, false, NULL, NULL, NULL, NULL, false};
  (*new_node)->_base._base._base._base._dtl = SyntaxTreeNativeFunction__dtl;
  CHECK(131, SyntaxTreeNativeFunction_parse((*new_node), &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeNativeFunction_parse(SyntaxTreeNativeFunction* self, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeNativeFunction_parse = "SyntaxTreeNativeFunction.parse";
#define MR_FUNC_NAME _func_name_SyntaxTreeNativeFunction_parse
Returncode SyntaxTreeNativeFunction_parse(SyntaxTreeNativeFunction* self, Char* end) {
  CHECK(134, SyntaxTreeNode_set_location(&(self->_base._base._base._base)) )
  self->_base._base._base.indentation_spaces = 2;
  CHECK(136, SyntaxTreeFunction_parse_header(&(self->_base), &((*end))) )
  self->_base._base.code_nodes = malloc(sizeof(List));
  if (self->_base._base.code_nodes == NULL) RAISE(137)
  *self->_base._base.code_nodes = (List){NULL, NULL};
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeNativeFunction_write(SyntaxTreeNativeFunction* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeNativeFunction_write = "SyntaxTreeNativeFunction.write";
#define MR_FUNC_NAME _func_name_SyntaxTreeNativeFunction_write
Returncode SyntaxTreeNativeFunction_write(SyntaxTreeNativeFunction* self) {
  /* do nothing */
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func SyntaxTreeNativeFunction__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func SyntaxTreeNativeFunction__dtl[] = {(void*)SyntaxTreeFunction_analyze, (void*)SyntaxTreeNativeFunction_write, (void*)SyntaxTreeBlock_parse_child, (void*)SyntaxTreeFunction_m_find_variable, (void*)SyntaxTreeFunction_m_get_parent_type};
#endif


/* Function declaration argument */
#if MR_STAGE == MR_TYPEDEFS
typedef struct DeclarationArgument DeclarationArgument;
#elif MR_STAGE == MR_TYPES(2)
struct DeclarationArgument {
  Argument _base;
  SyntaxTreeVariable* variable;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode DeclarationArgument_m_copy_new(DeclarationArgument* self, DeclarationArgument** new_argument);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_DeclarationArgument_m_copy_new = "DeclarationArgument.m-copy-new";
#define MR_FUNC_NAME _func_name_DeclarationArgument_m_copy_new
Returncode DeclarationArgument_m_copy_new(DeclarationArgument* self, DeclarationArgument** new_argument) {
  (*new_argument) = malloc(sizeof(DeclarationArgument));
  if ((*new_argument) == NULL) RAISE(148)
  *(*new_argument) = (DeclarationArgument){DeclarationArgument__dtl, NULL, 0, 0, false, NULL};
  (*new_argument)->_base._base._dtl = DeclarationArgument__dtl;
  (*new_argument)->_base.access = self->_base.access;
  (*new_argument)->variable = malloc(sizeof(SyntaxTreeVariable));
  if ((*new_argument)->variable == NULL) RAISE(150)
  *(*new_argument)->variable = (SyntaxTreeVariable){SyntaxTreeVariable__dtl, NULL, 0, NULL, NULL, 0, NULL, NULL, false};
  (*new_argument)->variable->_base._base._dtl = SyntaxTreeVariable__dtl;
  (*new_argument)->variable->access = self->variable->access;
  CHECK(152, TypeInstance_m_copy_new(self->variable->type_instance, &((*new_argument)->variable->type_instance)) )
  CHECK(154, string_new_copy(self->variable->name, &((*new_argument)->variable->name)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode DeclarationArgument_parse_value(DeclarationArgument* self, SyntaxTreeCode* code_node, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_DeclarationArgument_parse_value = "DeclarationArgument.parse-value";
#define MR_FUNC_NAME _func_name_DeclarationArgument_parse_value
Returncode DeclarationArgument_parse_value(DeclarationArgument* self, SyntaxTreeCode* code_node, Char* end) {
  self->variable = malloc(sizeof(SyntaxTreeVariable));
  if (self->variable == NULL) RAISE(157)
  *self->variable = (SyntaxTreeVariable){SyntaxTreeVariable__dtl, NULL, 0, NULL, NULL, 0, NULL, NULL, false};
  self->variable->_base._base._dtl = SyntaxTreeVariable__dtl;
  self->variable->access = self->_base.access;
  self->variable->is_output = self->_base.is_output;
  self->variable->type_instance = malloc(sizeof(TypeInstance));
  if (self->variable->type_instance == NULL) RAISE(160)
  *self->variable->type_instance = (TypeInstance){NULL, NULL, NULL, NULL, NULL};
  CHECK(161, TypeInstance_parse(self->variable->type_instance, &(String){2, 1, " "}, &(self->_base._base), NULL, &((*end))) )
  if ((*end) != ' ') {
    CHECK(163, SyntaxTreeNode_m_syntax_error_c(&(self->_base._base), &(String){31, 30, "expected space after type, got"}, (*end)) )
  }
  CHECK(164, read_new(&(String){3, 2, ",)"}, &(self->variable->name), &((*end))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode DeclarationArgument_analyze(DeclarationArgument* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_DeclarationArgument_analyze = "DeclarationArgument.analyze";
#define MR_FUNC_NAME _func_name_DeclarationArgument_analyze
Returncode DeclarationArgument_analyze(DeclarationArgument* self) {
  CHECK(167, TypeInstance_analyze(self->variable->type_instance, &(self->_base._base)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode DeclarationArgument_get_type_instance(DeclarationArgument* self, TypeInstance** type_instance);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_DeclarationArgument_get_type_instance = "DeclarationArgument.get-type-instance";
#define MR_FUNC_NAME _func_name_DeclarationArgument_get_type_instance
Returncode DeclarationArgument_get_type_instance(DeclarationArgument* self, TypeInstance** type_instance) {
  (*type_instance) = self->variable->type_instance;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode DeclarationArgument_get_variable(DeclarationArgument* self, SyntaxTreeVariable** variable);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_DeclarationArgument_get_variable = "DeclarationArgument.get-variable";
#define MR_FUNC_NAME _func_name_DeclarationArgument_get_variable
Returncode DeclarationArgument_get_variable(DeclarationArgument* self, SyntaxTreeVariable** variable) {
  (*variable) = self->variable;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode DeclarationArgument_write(DeclarationArgument* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_DeclarationArgument_write = "DeclarationArgument.write";
#define MR_FUNC_NAME _func_name_DeclarationArgument_write
Returncode DeclarationArgument_write(DeclarationArgument* self) {
  /* `type`** `name` */
  CHECK(177, write_cname(self->variable->type_instance->type_data->name) )
  if (self->_base.access != ACCESS_COPY) {
    CHECK(179, write(&(String){2, 1, "*"}) )
  }
  if (self->_base.is_output) {
    CHECK(181, write(&(String){2, 1, "*"}) )
  }
  CHECK(182, write(&(String){2, 1, " "}) )
  CHECK(183, write_cname(self->variable->name) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func DeclarationArgument__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func DeclarationArgument__dtl[] = {(void*)DeclarationArgument_analyze, (void*)DeclarationArgument_write, (void*)DeclarationArgument_m_copy_new, (void*)DeclarationArgument_parse_value, (void*)DeclarationArgument_get_type_instance, (void*)DeclarationArgument_get_variable, (void*)Argument_get_output, (void*)Argument_write_preactions};
#endif


#if MR_STAGE == MR_TYPEDEFS
typedef struct DeclarationArgumentFactory DeclarationArgumentFactory;
#elif MR_STAGE == MR_TYPES(1)
struct DeclarationArgumentFactory {
  ArgumentFactory _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode DeclarationArgumentFactory_m_new_argument(DeclarationArgumentFactory* self, Argument** new_argument);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_DeclarationArgumentFactory_m_new_argument = "DeclarationArgumentFactory.m-new-argument";
#define MR_FUNC_NAME _func_name_DeclarationArgumentFactory_m_new_argument
Returncode DeclarationArgumentFactory_m_new_argument(DeclarationArgumentFactory* self, Argument** new_argument) {
  DeclarationArgument* _DeclarationArgument78 = malloc(sizeof(DeclarationArgument));
  if (_DeclarationArgument78 == NULL) RAISE(188)
  *_DeclarationArgument78 = (DeclarationArgument){DeclarationArgument__dtl, NULL, 0, 0, false, NULL};
  _DeclarationArgument78->_base._base._dtl = DeclarationArgument__dtl;
  (*new_argument) = &(_DeclarationArgument78->_base);
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func DeclarationArgumentFactory__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func DeclarationArgumentFactory__dtl[] = {(void*)DeclarationArgumentFactory_m_new_argument};
#endif

#undef MR_FILE_NAME

#ifndef MR_INCLUDES
#define MR_INCLUDES
#include "global/argument.c"
#include "global/common.c"
#include "global/file-io.c"
#include "global/global.c"
#include "global/list.c"
#include "global/map.c"
#include "expression/call.c"
#include "expression/constant.c"
#include "expression/container.c"
#include "expression/expression.c"
#include "expression/slice.c"
#include "expression/symbol.c"
#include "syntax-tree/block.c"
#include "syntax-tree/branch.c"
#include "syntax-tree/code.c"
#include "syntax-tree/code-flow.c"
#include "syntax-tree/node.c"
#include "syntax-tree/root.c"
#include "syntax-tree/test.c"
#include "syntax-tree/type.c"
#include "syntax-tree/variable.c"
#include "mr4-compiler.c"
#if MR_STAGE == MR_TYPES(1)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(2)
#elif MR_STAGE == MR_TYPES(2)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(3)
#elif MR_STAGE == MR_TYPES(3)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(4)
#elif MR_STAGE == MR_TYPES(4)
#undef MR_STAGE
#define MR_STAGE MR_TYPES(5)
#endif
#undef MR_INCLUDES
#endif

#endif
