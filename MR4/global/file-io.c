#ifndef MR_MAINFILE
#define MR_MAINFILE "global/file-io.c"
#define DEPTH 4
#include "mr.3.h"
#else

#if MR_STAGE == MR_TYPEDEFS
static char* _mr_file2_name = "global/file-io.3.mr";
#endif
#define MR_FILE_NAME _mr_file2_name

/* MR4 compiler - File read and write functions */

/* Proxy functions to be mocked in tests */
#if MR_STAGE == MR_DECLARATIONS
Returncode file_getc(File* file, Char* ch);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_getc = "file-getc";
#define MR_FUNC_NAME _func_name_file_getc
Returncode file_getc(File* file, Char* ch) {
  CHECK(5, File_getc(file, &((*ch))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

#if MR_STAGE == MR_DECLARATIONS
Returncode file_write(File* file, String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_file_write = "file-write";
#define MR_FUNC_NAME _func_name_file_write
Returncode file_write(File* file, String* text) {
  CHECK(8, File_write(file, text) )
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* Read a single character from the input file */
#if MR_STAGE == MR_DECLARATIONS
Returncode read_c(Char* ch);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_read_c = "read-c";
#define MR_FUNC_NAME _func_name_read_c
Returncode read_c(Char* ch) {
  CHECK(13, file_getc(glob->input_file, &((*ch))) )
  if ((*ch) == '\n') {
    glob->line_number += 1;
  }
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* Expect `expected-text` to be read exaclty from the input file */
#if MR_STAGE == MR_DECLARATIONS
Returncode read_expect(String* expected_text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_read_expect = "read-expect";
#define MR_FUNC_NAME _func_name_read_expect
Returncode read_expect(String* expected_text) {
  String* actual_text = _new_string(expected_text->length + 1);
  if (actual_text == NULL) RAISE(20)
  {int n; for (n = (0); n < (expected_text->length); ++n) {
    Char _Char0;
    CHECK(22, read_c(&(_Char0)) )
    CHECK(22, String_append(actual_text, _Char0) )
  }}
  Bool _Bool1;
  CHECK(23, String_equal(actual_text, expected_text, &(_Bool1)) )
  if (!_Bool1) {
    CHECK(24, f_syntax_error2(&(String){9, 8, "expected"}, expected_text, &(String){4, 3, "got"}, actual_text) )
  }
  free(actual_text);
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* Read and check indentation spaces for a line break from the input file */
#if MR_STAGE == MR_DECLARATIONS
Returncode read_line_break_spaces();
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_read_line_break_spaces = "read-line-break-spaces";
#define MR_FUNC_NAME _func_name_read_line_break_spaces
Returncode read_line_break_spaces() {
  {int n; for (n = (0); n < (glob->spaces + 4); ++n) {
    Char _Char2;
    CHECK(32, read_c(&(_Char2)) )
    if (_Char2 != ' ') {
      String* expected_spaces = &(String){128, 0, (char[128]){0}};
      String* actual_spaces = &(String){128, 0, (char[128]){0}};
      CHECK(35, Int_str(glob->spaces + 4, expected_spaces) )
      CHECK(36, Int_str(n - 1, actual_spaces) )
      CHECK(37, f_syntax_error2(&(String){32, 31, "too short indentation, expected"}, expected_spaces, &(String){4, 3, "got"}, actual_spaces) )
    }
  }}
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* Read from the input file to `text` until a new-line, EOF, or one of the */
/* characters in `ends` is reached, and return the end character in `end`. */
/* If `indent` is true, ignore and count trailing spaces. */
#if MR_STAGE == MR_DECLARATIONS
Returncode read_until(String* text, String* ends, Bool indent, Char* end, Int* spaces);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_read_until = "read-until";
#define MR_FUNC_NAME _func_name_read_until
Returncode read_until(String* text, String* ends, Bool indent, Char* end, Int* spaces) {
  Char ch = EOF;
  Char quote = '\0';
  (*spaces) = 0;
  CHECK(52, read_c(&(ch)) )
  if (indent) {
    /* ignore and count indent */
    while (true) {
      if (!(ch == ' ')) break;
      (*spaces) += 1;
      CHECK(58, read_c(&(ch)) )
    }
  }
  while (true) {
    if (!(ch != EOF && ch != '\n')) break;
    if (quote == '\0') {
      Bool _Bool3;
      CHECK(62, String_has(ends, ch, &(_Bool3)) )
      if (!(!_Bool3)) break;
      if (ch == '\'' || ch == '"') {
        quote = ch;
      }
    }
    else {
      if (ch == '\\') {
        CHECK(66, String_append(text, ch) )
        CHECK(67, read_c(&(ch)) )
      }
      else {
        if (ch == quote) {
          quote = '\0';
        }
      }
    }
    CHECK(70, String_append(text, ch) )
    CHECK(71, read_c(&(ch)) )
  }
  (*end) = ch;
  return OK;
}
#undef MR_FUNC_NAME
#endif


/* Return in `new-text` a new allocated string read using `read-until`. */
#if MR_STAGE == MR_DECLARATIONS
Returncode read_new(String* ends, String** new_text, Char* end);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_read_new = "read-new";
#define MR_FUNC_NAME _func_name_read_new
Returncode read_new(String* ends, String** new_text, Char* end) {
  String* text = &(String){256, 0, (char[256]){0}};
  Int _Int4;
  CHECK(78, read_until(text, ends, false, &((*end)), &(_Int4)) )
  CHECK(79, f_new_copy(text, &((*new_text))) )
  return OK;
}
#undef MR_FUNC_NAME
#endif


#if MR_STAGE == MR_DECLARATIONS
Returncode write(String* text);
#elif MR_STAGE == MR_FUNCTIONS
static char* _func_name_write = "write";
#define MR_FUNC_NAME _func_name_write
Returncode write(String* text) {
  CHECK(83, file_write(glob->output_file, text) )
  return OK;
}
#undef MR_FUNC_NAME
#endif

#undef MR_FILE_NAME

#ifndef MR_INCLUDES
#define MR_INCLUDES
#include "global/common.c"
#include "global/global.c"
#include "global/map.c"
#include "global/type.c"
#include "expression/call.c"
#include "expression/constant.c"
#include "expression/container.c"
#include "expression/expression.c"
#include "expression/slice.c"
#include "expression/variable.c"
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
#endif
#undef MR_INCLUDES
#endif

#endif
