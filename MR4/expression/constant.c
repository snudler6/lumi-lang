#ifndef MR_MAINFILE
#define MR_MAINFILE "expression/constant.c"
#define DEPTH 5
#include "mr.3.h"
#else

#if MR_STAGE == MR_TYPEDEFS
static char* _mr_file8_name = "expression/constant.3.mr";
#endif
#define MR_FILE_NAME _mr_file8_name

/* MR4 compiler - Constant expressions */

/* Return whether `text` is a number of base with given `top-digit` */
#if MR_STAGE == MR_DECLARATIONS
Returncode f_is_number(String* text, Char top_digit, Bool* is_number);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_is_number = "f-is-number";
#define MR_FUNC_NAME _func_name_f_is_number
Returncode f_is_number(String* text, Char top_digit, Bool* is_number) {
  (*is_number) = true;
  {int n; for (n = (0); n < (text->length); ++n) {
    if ((n) < 0 || (n) >= (text)->length) RAISE(7)
    Char ch = ((text)->values[n]);
    if (ch < '0' || ch > top_digit) {
      (*is_number) = false;
      return OK;
    }
  }}
  return OK;
}
#undef MR_FUNC_NAME
#endif

/* Return whether `text` is a binary number */
#if MR_STAGE == MR_DECLARATIONS
Returncode f_is_binary(String* text, Bool* is_octal);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_is_binary = "f-is-binary";
#define MR_FUNC_NAME _func_name_f_is_binary
Returncode f_is_binary(String* text, Bool* is_octal) {
  CHECK(14, f_is_number(text, '1', &((*is_octal))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

/* Return whether `text` is an octal number */
#if MR_STAGE == MR_DECLARATIONS
Returncode f_is_octal(String* text, Bool* is_octal);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_is_octal = "f-is-octal";
#define MR_FUNC_NAME _func_name_f_is_octal
Returncode f_is_octal(String* text, Bool* is_octal) {
  CHECK(18, f_is_number(text, '7', &((*is_octal))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

/* Return whether `text` is a decimal number */
#if MR_STAGE == MR_DECLARATIONS
Returncode f_is_decimal(String* text, Bool* is_octal);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_is_decimal = "f-is-decimal";
#define MR_FUNC_NAME _func_name_f_is_decimal
Returncode f_is_decimal(String* text, Bool* is_octal) {
  CHECK(22, f_is_number(text, '9', &((*is_octal))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

/* Return whether `text` is a hexadecimal number */
#if MR_STAGE == MR_DECLARATIONS
Returncode f_is_hex(String* text, Bool* is_hex);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_f_is_hex = "f-is-hex";
#define MR_FUNC_NAME _func_name_f_is_hex
Returncode f_is_hex(String* text, Bool* is_hex) {
  (*is_hex) = true;
  {int n; for (n = (0); n < (text->length); ++n) {
    if ((n) < 0 || (n) >= (text)->length) RAISE(28)
    Char ch = ((text)->values[n]);
    if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'f') && (ch < 'A' || ch > 'F')) {
      (*is_hex) = false;
      return OK;
    }
  }}
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* A basic expression that has a single textual value */
#if MR_STAGE == MR_TYPEDEFS
typedef struct TextExpression TextExpression;
#elif MR_STAGE == MR_TYPES(2)
struct TextExpression {
  Expression _base;
  String* text;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode TextExpression_write(TextExpression* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_TextExpression_write = "TextExpression.write";
#define MR_FUNC_NAME _func_name_TextExpression_write
Returncode TextExpression_write(TextExpression* self) {
  CHECK(40, write(self->text) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func TextExpression__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func TextExpression__dtl[] = {(void*)SyntaxTreeNode_link_types, (void*)SyntaxTreeNode_analyze, (void*)TextExpression_write, (void*)Expression_write_dynamic, (void*)Expression_analyze_call, (void*)Expression_write_preactions};
#endif


/* Constant integer expression */
#if MR_STAGE == MR_TYPEDEFS
typedef struct IntExpression IntExpression;
#elif MR_STAGE == MR_TYPES(3)
struct IntExpression {
  TextExpression _base;
/* parsing `123` or `-123` or `0b0012` or `0x3d4f` */};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode IntExpression_parse_new(IntExpression* self, String* text, Expression** expression);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_IntExpression_parse_new = "IntExpression.parse-new";
#define MR_FUNC_NAME _func_name_IntExpression_parse_new
Returncode IntExpression_parse_new(IntExpression* self, String* text, Expression** expression) {
  IntExpression* int_expression = malloc(sizeof(IntExpression));
  if (int_expression == NULL) RAISE(46)
  *int_expression = (IntExpression){IntExpression__dtl, NULL, 0, NULL, NULL, false, false, false, NULL};
  int_expression->_base._base._base._dtl = IntExpression__dtl;
  CHECK(47, IntExpression_parse(int_expression, text) )
  (*expression) = &(int_expression->_base._base);
  return OK;
}
#undef MR_FUNC_NAME
#endif/* parsing `123` or `-123` or `0b0012` or `0x3d4f` */
#if MR_STAGE == MR_DECLARATIONS
Returncode IntExpression_parse(IntExpression* self, String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_IntExpression_parse = "IntExpression.parse";
#define MR_FUNC_NAME _func_name_IntExpression_parse
Returncode IntExpression_parse(IntExpression* self, String* text) {
  CHECK(52, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
  String* number = text;
  if ((0) < 0 || (0) >= (number)->length) RAISE(54)
  if (((number)->values[0]) == '-') {
    if ((1) < 0 || (number->length - 1) < 0 || (1) + (number->length - 1) > (number)->length) RAISE(55)
    number = (&(String){number->length - 1, number->length - 1, (number)->values + (1)});
  }
  if ((0) < 0 || (0) >= (number)->length) RAISE(56)
  if (((number)->values[0]) == '0' && number->length > 1) {
    if ((1) < 0 || (1) >= (number)->length) RAISE(57)
    Char second = ((number)->values[1]);
    if (second >= '0' && second <= '7') {
      Bool _Bool18;
      CHECK(59, f_is_octal(number, &(_Bool18)) )
      if (!_Bool18) {
        CHECK(60, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){21, 20, "illegal octal number"}, text) )
      }
    }
    else {
      if ((2) < 0 || (number->length - 2) < 0 || (2) + (number->length - 2) > (number)->length) RAISE(62)
      number = (&(String){number->length - 2, number->length - 2, (number)->values + (2)});
      if (second == 'b' || second == 'B') {
        Bool _Bool19;
        CHECK(64, f_is_binary(number, &(_Bool19)) )
        if (!_Bool19) {
          CHECK(65, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){22, 21, "illegal binary number"}, text) )
        }
        CHECK(66, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){36, 35, "binary numbers not supported yet..."}, text) )
      }
      else {
        if (second == 'x' || second == 'X') {
          Bool _Bool20;
          CHECK(69, f_is_hex(number, &(_Bool20)) )
          if (!_Bool20) {
            CHECK(70, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal hexadecimal number"}, text) )
          }
        }
        else {
          CHECK(72, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){15, 14, "illegal number"}, text) )
        }
      }
    }
  }
  else {
    Bool _Bool21;
    CHECK(73, f_is_decimal(number, &(_Bool21)) )
    if (!_Bool21) {
      CHECK(74, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){15, 14, "illegal number"}, text) )
    }
  }
  CHECK(75, Expression_set_simple_type(&(self->_base._base), &(glob->type_int->_base)) )
  self->_base.text = text;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func IntExpression__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func IntExpression__dtl[] = {(void*)SyntaxTreeNode_link_types, (void*)SyntaxTreeNode_analyze, (void*)TextExpression_write, (void*)Expression_write_dynamic, (void*)Expression_analyze_call, (void*)Expression_write_preactions};
#endif


/* Constant character expression */
#if MR_STAGE == MR_TYPEDEFS
typedef struct CharExpression CharExpression;
#elif MR_STAGE == MR_TYPES(3)
struct CharExpression {
  TextExpression _base;
/* parsing `'a'` or `'\n'` or `'\xf5'` or `'\270'` */};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode CharExpression_parse_new(CharExpression* self, String* text, Expression** expression);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_CharExpression_parse_new = "CharExpression.parse-new";
#define MR_FUNC_NAME _func_name_CharExpression_parse_new
Returncode CharExpression_parse_new(CharExpression* self, String* text, Expression** expression) {
  CharExpression* char_expression = malloc(sizeof(CharExpression));
  if (char_expression == NULL) RAISE(82)
  *char_expression = (CharExpression){CharExpression__dtl, NULL, 0, NULL, NULL, false, false, false, NULL};
  char_expression->_base._base._base._dtl = CharExpression__dtl;
  CHECK(83, CharExpression_parse(char_expression, text) )
  (*expression) = &(char_expression->_base._base);
  return OK;
}
#undef MR_FUNC_NAME
#endif/* parsing `'a'` or `'\n'` or `'\xf5'` or `'\270'` */
#if MR_STAGE == MR_DECLARATIONS
Returncode CharExpression_parse(CharExpression* self, String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_CharExpression_parse = "CharExpression.parse";
#define MR_FUNC_NAME _func_name_CharExpression_parse
Returncode CharExpression_parse(CharExpression* self, String* text) {
  CHECK(88, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
  Char ch = '\0';
  if (text->length == 3) {
    if ((1) < 0 || (1) >= (text)->length) RAISE(91)
    ch = ((text)->values[1]);
    if (ch == '\'' || ch == '\\') {
      CHECK(93, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
    }
  }
  else {
    if (text->length == 4) {
      if ((1) < 0 || (1) >= (text)->length) RAISE(95)
      if (((text)->values[1]) != '\\') {
        CHECK(96, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
      }
      if ((2) < 0 || (2) >= (text)->length) RAISE(97)
      Bool _Bool22;
      CHECK(97, String_has(&(String){12, 11, "'\"?\\abfnrtv"}, ((text)->values[2]), &(_Bool22)) )
      if (!_Bool22) {
        CHECK(98, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
      }
    }
    else {
      if (text->length == 6) {
        if ((1) < 0 || (1) >= (text)->length) RAISE(100)
        if (((text)->values[1]) != '\\') {
          CHECK(101, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
        }
        if ((2) < 0 || (2) >= (text)->length) RAISE(102)
        ch = ((text)->values[2]);
        if (ch == 'x') {
          if ((3) < 0 || (2) < 0 || (3) + (2) > (text)->length) RAISE(104)
          Bool _Bool23;
          CHECK(104, f_is_hex((&(String){2, 2, (text)->values + (3)}), &(_Bool23)) )
          if (!_Bool23) {
            CHECK(105, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
          }
        }
        else {
          if ((2) < 0 || (3) < 0 || (2) + (3) > (text)->length) RAISE(107)
          Bool _Bool24;
          CHECK(107, f_is_octal((&(String){3, 3, (text)->values + (2)}), &(_Bool24)) )
          if (!_Bool24) {
            CHECK(108, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
          }
        }
      }
      else {
        CHECK(110, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
      }
    }
  }
  if ((text->length - 1) < 0 || (text->length - 1) >= (text)->length) RAISE(111)
  if (((text)->values[text->length - 1]) != '\'') {
    CHECK(112, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){27, 26, "illegal character constant"}, text) )
  }
  CHECK(113, Expression_set_simple_type(&(self->_base._base), &(glob->type_char->_base)) )
  self->_base.text = text;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func CharExpression__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func CharExpression__dtl[] = {(void*)SyntaxTreeNode_link_types, (void*)SyntaxTreeNode_analyze, (void*)TextExpression_write, (void*)Expression_write_dynamic, (void*)Expression_analyze_call, (void*)Expression_write_preactions};
#endif


/* Constant string expression */
#if MR_STAGE == MR_TYPEDEFS
typedef struct StringExpression StringExpression;
#elif MR_STAGE == MR_TYPES(3)
struct StringExpression {
  TextExpression _base;
  SymbolExpression* symbol;
/* parsing `"some string"` */};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode StringExpression_parse_new(StringExpression* self, String* text, SyntaxTreeCode* code_node, Expression** expression);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_StringExpression_parse_new = "StringExpression.parse-new";
#define MR_FUNC_NAME _func_name_StringExpression_parse_new
Returncode StringExpression_parse_new(StringExpression* self, String* text, SyntaxTreeCode* code_node, Expression** expression) {
  StringExpression* string_expression = malloc(sizeof(StringExpression));
  if (string_expression == NULL) RAISE(123)
  *string_expression = (StringExpression){StringExpression__dtl, NULL, 0, NULL, NULL, false, false, false, NULL, NULL};
  string_expression->_base._base._base._dtl = StringExpression__dtl;
  CHECK(124, StringExpression_parse(string_expression, text, code_node) )
  (*expression) = &(string_expression->_base._base);
  return OK;
}
#undef MR_FUNC_NAME
#endif/* parsing `"some string"` */
#if MR_STAGE == MR_DECLARATIONS
Returncode StringExpression_parse(StringExpression* self, String* text, SyntaxTreeCode* code_node);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_StringExpression_parse = "StringExpression.parse";
#define MR_FUNC_NAME _func_name_StringExpression_parse
Returncode StringExpression_parse(StringExpression* self, String* text, SyntaxTreeCode* code_node) {
  self->_base._base.code_node = code_node;
  CHECK(130, SyntaxTreeNode_set_location(&(self->_base._base._base)) )
  if ((text->length - 1) < 0 || (text->length - 1) >= (text)->length) RAISE(131)
  if (((text)->values[text->length - 1]) != '\"') {
    CHECK(132, SyntaxTreeNode_m_syntax_error(&(self->_base._base._base), &(String){24, 23, "illegal string constant"}, text) )
  }
  CHECK(133, Expression_set_simple_type(&(self->_base._base), &(glob->type_string->_base)) )
  self->_base.text = text;
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode StringExpression_analyze(StringExpression* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_StringExpression_analyze = "StringExpression.analyze";
#define MR_FUNC_NAME _func_name_StringExpression_analyze
Returncode StringExpression_analyze(StringExpression* self) {
  CHECK(137, Expression_add_aux_variable(&(self->_base._base), ACCESS_AUX, self->_base._base.result_type, &(self->symbol)) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode StringExpression_write_preactions(StringExpression* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_StringExpression_write_preactions = "StringExpression.write-preactions";
#define MR_FUNC_NAME _func_name_StringExpression_write_preactions
Returncode StringExpression_write_preactions(StringExpression* self) {
  /* `symbol`_Var.max_length = `string-length + 1`; */
  /* `symbol`_Var.length = `string-length`; */
  /* `symbol`_Var.values = "`text`"; */
  CHECK(144, Expression_write_ref_init(&(self->_base._base), self->symbol) )
  CHECK(145, Expression_write_init_var_ref(&(self->_base._base), self->symbol) )
  Int real_length = 1;
  {int index; for (index = (1); index < (self->_base.text->length - 1); ++index) {
    if ((index) < 0 || (index) >= (self->_base.text)->length) RAISE(148)
    if (((self->_base.text)->values[index]) == '\\') {
      index += 1;
    }
    real_length = real_length + 1;
  }}
  CHECK(151, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
  CHECK(152, (self->symbol)->_base._base._dtl[2](self->symbol) )
  CHECK(153, write(&(String){19, 18, "_Var.max_length = "}) )
  CHECK(154, write_int(real_length) )
  CHECK(155, write(&(String){3, 2, ";\n"}) )
  CHECK(156, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
  CHECK(157, (self->symbol)->_base._base._dtl[2](self->symbol) )
  CHECK(158, write(&(String){15, 14, "_Var.length = "}) )
  CHECK(159, write_int(real_length - 1) )
  CHECK(160, write(&(String){3, 2, ";\n"}) )
  CHECK(161, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
  CHECK(162, (self->symbol)->_base._base._dtl[2](self->symbol) )
  CHECK(163, write(&(String){15, 14, "_Var.values = "}) )
  CHECK(164, write(self->_base.text) )
  CHECK(165, write(&(String){3, 2, ";\n"}) )
  CHECK(166, SyntaxTreeCode_write_spaces(self->_base._base.code_node) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode StringExpression_write(StringExpression* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_StringExpression_write = "StringExpression.write";
#define MR_FUNC_NAME _func_name_StringExpression_write
Returncode StringExpression_write(StringExpression* self) {
  CHECK(169, (self->symbol)->_base._base._dtl[2](self->symbol) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func StringExpression__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func StringExpression__dtl[] = {(void*)SyntaxTreeNode_link_types, (void*)StringExpression_analyze, (void*)StringExpression_write, (void*)Expression_write_dynamic, (void*)Expression_analyze_call, (void*)StringExpression_write_preactions};
#endif


/* Constant empty expression `_` */
#if MR_STAGE == MR_TYPEDEFS
typedef struct EmptyExpression EmptyExpression;
#elif MR_STAGE == MR_TYPES(2)
struct EmptyExpression {
  Expression _base;
};
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode EmptyExpression_parse_new(EmptyExpression* self, String* text, Expression** expression);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_EmptyExpression_parse_new = "EmptyExpression.parse-new";
#define MR_FUNC_NAME _func_name_EmptyExpression_parse_new
Returncode EmptyExpression_parse_new(EmptyExpression* self, String* text, Expression** expression) {
  EmptyExpression* _EmptyExpression25 = malloc(sizeof(EmptyExpression));
  if (_EmptyExpression25 == NULL) RAISE(175)
  *_EmptyExpression25 = (EmptyExpression){EmptyExpression__dtl, NULL, 0, NULL, NULL, false, false, false};
  _EmptyExpression25->_base._base._dtl = EmptyExpression__dtl;
  (*expression) = &(_EmptyExpression25->_base);
  CHECK(176, SyntaxTreeNode_set_location(&((*expression)->_base)) )
  CHECK(177, Expression_set_simple_type((*expression), &(glob->type_empty->_base)) )
  free(text);
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode EmptyExpression_write(EmptyExpression* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_EmptyExpression_write = "EmptyExpression.write";
#define MR_FUNC_NAME _func_name_EmptyExpression_write
Returncode EmptyExpression_write(EmptyExpression* self) {
  CHECK(181, write(&(String){5, 4, "NULL"}) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
Returncode EmptyExpression_write_dynamic(EmptyExpression* self);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_EmptyExpression_write_dynamic = "EmptyExpression.write-dynamic";
#define MR_FUNC_NAME _func_name_EmptyExpression_write_dynamic
Returncode EmptyExpression_write_dynamic(EmptyExpression* self) {
  CHECK(184, (self)->_base._base._dtl[2](self) )
  return OK;
}
#undef MR_FUNC_NAME
#endif
#if MR_STAGE == MR_DECLARATIONS
extern Func EmptyExpression__dtl[];
#endif
#if MR_STAGE == MR_FUNCTIONS
Func EmptyExpression__dtl[] = {(void*)SyntaxTreeNode_link_types, (void*)SyntaxTreeNode_analyze, (void*)EmptyExpression_write, (void*)EmptyExpression_write_dynamic, (void*)Expression_analyze_call, (void*)Expression_write_preactions};
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
#include "expression/container.c"
#include "expression/expression.c"
#include "expression/slice.c"
#include "expression/symbol.c"
#include "syntax-tree/block.c"
#include "syntax-tree/branch.c"
#include "syntax-tree/code.c"
#include "syntax-tree/code-flow.c"
#include "syntax-tree/function.c"
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
