#ifndef MR_MAINFILE
#define MR_MAINFILE "syntax-tree/root.c"
#define DEPTH 5
#include "mr.3.h"
#else

#if MR_STAGE == MR_TYPEDEFS
static char* _mr_file17_name = "syntax-tree/root.3.mr";
#endif
#define MR_FILE_NAME _mr_file17_name

/* MR4 compiler - Syntax tree root */

/* The syntax tree root */
#if MR_STAGE == MR_TYPEDEFS
typedef struct SyntaxTreeRoot SyntaxTreeRoot;
#elif MR_STAGE == MR_TYPES(3)
struct SyntaxTreeRoot {
  SyntaxTreeNamespace _base;
  List* types;
  String* output_file_name;
/*  write C file in this order:
  1. type declarations
  2. type structs (ordered by depth)
  3. function declarations
  4. global variables
  5. function bodies
   */};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_parse(SyntaxTreeRoot* self, Array* argv);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_parse = "SyntaxTreeRoot.parse";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_parse
Returncode SyntaxTreeRoot_parse(SyntaxTreeRoot* self, Array* argv) {
  if (argv->length < 3) {
    CHECK(10, Sys_print(sys, &(String){58, 57, "usage: mr-4compiler OUTPUT-C-FILE-NAME INPUT-MR3-FILES..."}) )
    RAISE(12)
  }
  
  CHECK(14, SyntaxTreeNamespace_init(&(self->_base)) )
  if ((1) < 0 || (1) >= (argv)->length) RAISE(15)
  self->output_file_name = (&(((String*)((argv)->values))[1]));
  self->types = malloc(sizeof(List));
  if (self->types == NULL) RAISE(16)
  *self->types = (List){NULL, NULL};
  {int n; for (n = (2); n < (argv->length); ++n) {
    if ((n) < 0 || (n) >= (argv)->length) RAISE(18)
    glob->input_file_name = (&(((String*)((argv)->values))[n]));
    glob->line_number = 0;
    CHECK(20, file_open(glob->input_file_name, true, &(glob->input_file)) )
    
    Char _Char60;
    CHECK(22, SyntaxTreeBranch_parse_children(&(self->_base._base), NULL, &(_Char60)) )
    
    if (glob->input_buffer->length > 0 || glob->input_spaces > 0) {
      CHECK(25, f_syntax_error_msg(&(String){28, 27, "no new-line before file end"}) )
    }
    
    CHECK(27, file_close(glob->input_file) )
  }}
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_parse_child(SyntaxTreeRoot* self, String* keyword, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_parse_child = "SyntaxTreeRoot.parse-child";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_parse_child
Returncode SyntaxTreeRoot_parse_child(SyntaxTreeRoot* self, String* keyword, Char* end) {
  Bool _Bool61;
  CHECK(30, SyntaxTreeNamespace_parse_if_function(&(self->_base), keyword, NULL, &((*end)), &(_Bool61)) )
  if (_Bool61) {
    return OK;
  }
  
  Bool _Bool62;
  CHECK(33, String_equal(keyword, &(String){7, 6, "struct"}, &(_Bool62)) )
  if (_Bool62) {
    if ((*end) != ' ') {
      CHECK(35, f_syntax_error_c(&(String){35, 34, "expected space after \"struct\", got"}, (*end)) )
    }
    SyntaxTreeType* _SyntaxTreeType63;
    CHECK(36, SyntaxTreeType_parse_new(NULL, &((*end)), &(_SyntaxTreeType63)) )
    CHECK(36, List_add(self->types, _SyntaxTreeType63) )
    
  }
  else {
    Bool _Bool64;
    CHECK(38, String_equal(keyword, &(String){6, 5, "class"}, &(_Bool64)) )
    if (_Bool64) {
      if ((*end) != ' ') {
        CHECK(40, f_syntax_error_c(&(String){34, 33, "expected space after \"class\", got"}, (*end)) )
      }
      SyntaxTreeType* _SyntaxTreeType65;
      CHECK(41, SyntaxTreeType_parse_new(NULL, &((*end)), &(_SyntaxTreeType65)) )
      CHECK(41, List_add(self->types, _SyntaxTreeType65) )
      
    }
    else {
      Bool _Bool66;
      CHECK(43, String_equal(keyword, &(String){5, 4, "main"}, &(_Bool66)) )
      if (_Bool66) {
        if ((*end) != '\n') {
          CHECK(45, f_syntax_error_c(&(String){36, 35, "expected new-line after \"main\", got"}, (*end)) )
        }
        SyntaxTreeMainFunction* _SyntaxTreeMainFunction67;
        CHECK(46, SyntaxTreeMainFunction_parse_new(NULL, &((*end)), &(_SyntaxTreeMainFunction67)) )
        CHECK(46, List_add(self->_base.functions, &(_SyntaxTreeMainFunction67->_base)) )
        
      }
      else {
        Bool _Bool68;
        CHECK(49, String_equal(keyword, &(String){7, 6, "native"}, &(_Bool68)) )
        if (_Bool68) {
          if ((*end) != ' ') {
            CHECK(51, f_syntax_error_c(&(String){35, 34, "expected space after \"native\", got"}, (*end)) )
          }
          SyntaxTreeNativeFunction* _SyntaxTreeNativeFunction69;
          CHECK(52, SyntaxTreeNativeFunction_parse_new(NULL, &((*end)), &(_SyntaxTreeNativeFunction69)) )
          CHECK(52, List_add(self->_base.functions, &(_SyntaxTreeNativeFunction69->_base)) )
          
        }
        else {
          Bool _Bool70;
          CHECK(55, String_equal(keyword, &(String){5, 4, "test"}, &(_Bool70)) )
          if (_Bool70) {
            if ((*end) != ' ') {
              CHECK(57, f_syntax_error_c(&(String){33, 32, "expected space after \"test\", got"}, (*end)) )
            }
            SyntaxTreeTestFunction* _SyntaxTreeTestFunction71;
            CHECK(58, SyntaxTreeTestFunction_parse_new(NULL, &((*end)), &(_SyntaxTreeTestFunction71)) )
            CHECK(58, List_add(self->_base.functions, &(_SyntaxTreeTestFunction71->_base)) )
            
          }
          else {
            Bool _Bool72;
            CHECK(61, String_equal(keyword, &(String){5, 4, "mock"}, &(_Bool72)) )
            if (_Bool72) {
              if ((*end) != ' ') {
                CHECK(63, f_syntax_error_c(&(String){33, 32, "expected space after \"mock\", got"}, (*end)) )
              }
              SyntaxTreeMockFunction* _SyntaxTreeMockFunction73;
              CHECK(64, SyntaxTreeMockFunction_parse_new(NULL, &((*end)), &(_SyntaxTreeMockFunction73)) )
              CHECK(64, List_add(self->_base.functions, &(_SyntaxTreeMockFunction73->_base)) )
              
            }
            else {
              CHECK(68, f_syntax_error(&(String){16, 15, "unknown keyword"}, keyword) )
            }
          }
        }
      }
    }
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif/*  write C file in this order:
  1. type declarations
  2. type structs (ordered by depth)
  3. function declarations
  4. global variables
  5. function bodies
   */
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_write(SyntaxTreeRoot* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_write = "SyntaxTreeRoot.write";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_write
Returncode SyntaxTreeRoot_write(SyntaxTreeRoot* self) {
  CHECK(78, file_open(self->output_file_name, false, &(glob->output_file)) )
  
  CHECK(80, write_global(&(String){19, 18, "#include \"mr.4.h\"\n"}) )
  
  CHECK(82, write_global(&(String){27, 26, "\n\n/* types declaration */\n"}) )
  SyntaxTreeTypeDeclarationWriter* type_declaration_writer = &(SyntaxTreeTypeDeclarationWriter){SyntaxTreeTypeDeclarationWriter__dtl};
  type_declaration_writer->_base._dtl = SyntaxTreeTypeDeclarationWriter__dtl;
  CHECK(84, SyntaxTreeRoot_write_for_type(self, &(type_declaration_writer->_base)) )
  
  /* will write type structs */
  CHECK(87, write_global(&(String){22, 21, "\n\n/* types struct */\n"}) )
  CHECK(88, SyntaxTreeBranch_write_children(&(self->_base._base), self->types) )
  
  CHECK(90, write_global(&(String){35, 34, "\n\n/* types methods declaration */\n"}) )
  SyntaxTreeTypeMethodsDeclarationWriter* type_methods_declaration_writer = &(SyntaxTreeTypeMethodsDeclarationWriter){SyntaxTreeTypeMethodsDeclarationWriter__dtl};
  type_methods_declaration_writer->_base._dtl = SyntaxTreeTypeMethodsDeclarationWriter__dtl;
  CHECK(92, SyntaxTreeRoot_write_for_type(self, &(type_methods_declaration_writer->_base)) )
  
  CHECK(94, write_global(&(String){19, 18, "\n\n/* types DTL */\n"}) )
  SyntaxTreeTypeDtlWriter* type_dtl_writer = &(SyntaxTreeTypeDtlWriter){SyntaxTreeTypeDtlWriter__dtl};
  type_dtl_writer->_base._dtl = SyntaxTreeTypeDtlWriter__dtl;
  CHECK(96, SyntaxTreeRoot_write_for_type(self, &(type_dtl_writer->_base)) )
  
  /* will write global variables */
  CHECK(99, write_global(&(String){26, 25, "\n\n/* global variables */\n"}) )
  CHECK(100, SyntaxTreeBranch_write_children(&(self->_base._base), self->_base._base.variables) )
  
  CHECK(102, write_global(&(String){31, 30, "\n\n/* functions declaration */\n"}) )
  CHECK(103, SyntaxTreeNamespace_write_functions_declaration(&(self->_base)) )
  
  CHECK(105, write_global(&(String){28, 27, "\n\n/* types methods body */\n"}) )
  SyntaxTreeTypeMethodsBodyWriter* type_methods_body_writer = &(SyntaxTreeTypeMethodsBodyWriter){SyntaxTreeTypeMethodsBodyWriter__dtl};
  type_methods_body_writer->_base._dtl = SyntaxTreeTypeMethodsBodyWriter__dtl;
  CHECK(107, SyntaxTreeRoot_write_for_type(self, &(type_methods_body_writer->_base)) )
  
  /* will write global functions bodies */
  CHECK(110, write_global(&(String){31, 30, "\n\n/* global functions body */\n"}) )
  CHECK(111, SyntaxTreeBranch_write_children(&(self->_base._base), self->_base.functions) )
  
  CHECK(113, file_close(glob->output_file) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode SyntaxTreeRoot_write_for_type(SyntaxTreeRoot* self, SyntaxTreeTypeWriter* type_writer);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_SyntaxTreeRoot_write_for_type = "SyntaxTreeRoot.write-for-type";
#define MR_FUNC_NAME _func_name_SyntaxTreeRoot_write_for_type
Returncode SyntaxTreeRoot_write_for_type(SyntaxTreeRoot* self, SyntaxTreeTypeWriter* type_writer) {
  ListNode* child = self->types->first;
  while (true) {
    if (!(NULL != child)) break;
    CHECK(119, write(&(String){2, 1, "\n"}) )
    CHECK(120, (type_writer)->_dtl[0](type_writer, child->item) )
    CHECK(121, write(&(String){2, 1, "\n"}) )
    child = child->next;
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func SyntaxTreeRoot__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func SyntaxTreeRoot__dtl[] = {(void*)SyntaxTreeNode_analyze, (void*)SyntaxTreeRoot_write, (void*)SyntaxTreeRoot_parse_child};
#endif


/* proxy write function to be mocked on unit-tests */
#if MR_STAGE == MR_DECLARATIONS
Returncode write_global(String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_write_global = "write-global";
#define MR_FUNC_NAME _func_name_write_global
Returncode write_global(String* text) {
  CHECK(127, write(text) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

#undef MR_FILE_NAME

#ifndef MR_INCLUDES
#define MR_INCLUDES
#include "global/common.c"
#include "global/file-io.c"
#include "global/global.c"
#include "global/list.c"
#include "global/map.c"
#include "global/type.c"
#include "expression/call.c"
#include "expression/constant.c"
#include "expression/container.c"
#include "expression/expression.c"
#include "expression/slice.c"
#include "expression/variable.c"
#include "syntax-tree/code.c"
#include "syntax-tree/code-flow.c"
#include "syntax-tree/function.c"
#include "syntax-tree/node.c"
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
