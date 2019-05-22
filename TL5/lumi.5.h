#ifndef LUMI_TL5_LUMI_5_H_INCLUDED_
#define LUMI_TL5_LUMI_5_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int Int;
typedef char Char;
typedef unsigned char Byte;

typedef enum {
  false = 0,
  true = 1
} Bool;

typedef enum {
  OK = EXIT_SUCCESS,
  ERR = EXIT_FAILURE,
  FAIL = EXIT_FAILURE > EXIT_SUCCESS? EXIT_FAILURE + 1 : EXIT_SUCCESS + 1
} Returncode;

typedef struct {
  int count;
  void* value;
  void* ref;
} Ref_Manager;

typedef Returncode (*Func)();

typedef struct {
  FILE* fobj;
} File;

typedef void* Ref;

typedef struct {
  char const* filename;
  int lines_number;
  int* line_count;
} File_Coverage;

typedef void (*Dynamic_Del)(void*);

typedef void Generic_Type;
typedef struct { Dynamic_Del _del; } Generic_Type_Dynamic;
extern Generic_Type_Dynamic* dynamic_Void;


typedef struct {
  char* str;
  int length;
  Ref_Manager refman;
} Error_Message;

typedef struct {
  Error_Message empty_object;
  Error_Message outdated_weak_reference;
  Error_Message object_memory;
  Error_Message managed_object_memory;
  Error_Message empty_base_output;
  Error_Message slice_index;
  Error_Message string_too_long;
  Error_Message file_not_opened;
  Error_Message file_write_failed;
} Error_Messages;

extern Error_Messages LUMI_error_messages;
extern char* LUMI_raise_format;
extern char* LUMI_assert_format;
extern char* LUMI_traceline_format;
extern int LUMI_trace_ignore_count;
extern char* LUMI_expected_error;
extern int LUMI_expected_error_trace_ignore_count;

void LUMI_trace_print(
  char const* format,
  char const* filename,
  int line,
  char const* funcname,
  char const* message,
  int message_length,
  Ref_Manager* message_refman);

#define START_TRACE(line, cleanup, value, format, message, message_length, message_refman) \
  LUMI_trace_print( \
      format, \
      LUMI_FILE_NAME, \
      line, \
      LUMI_FUNC_NAME, \
      message, \
      message_length, \
      message_refman); \
  LUMI_err = value; \
  LUMI_loop_depth = 0; \
  goto cleanup;

#define START_TRACE_STATIC(line, cleanup, err_value, format, message_length, message) { \
  Ref_Manager LUMI_msg_refman = { 1, NULL, NULL }; \
  LUMI_msg_refman.value = message; \
  START_TRACE( \
      line, \
      cleanup, \
      err_value, \
      format, \
      message, \
      message_length, \
      &LUMI_msg_refman) }

#define RAISE(line, cleanup, message) { \
  START_TRACE( \
      line, \
      cleanup, \
      ERR, \
      LUMI_raise_format, \
      LUMI_error_messages.message.str, \
      LUMI_error_messages.message.length, \
      &(LUMI_error_messages.message.refman)) }

#define USER_RAISE(line, cleanup, message, message_length, message_refman) \
  { START_TRACE( \
      line, \
      cleanup, \
      ERR, \
      LUMI_raise_format, \
      message, \
      message_length, \
      message_refman) }

#define TEST_FAIL(line, cleanup, message_length, message) \
  START_TRACE_STATIC( \
      line, cleanup, FAIL, LUMI_assert_format, message_length, message)

#define TEST_ASSERT(line, cleanup, condition) if (!(condition)) \
  TEST_FAIL(line, cleanup, 21, "condition is not true")

#define TEST_FAIL_NULL(line, cleanup) \
  START_TRACE_STATIC(line, cleanup, FAIL, LUMI_assert_format, 0, NULL)

#define CHECK(line, cleanup) if (LUMI_err != OK) { \
  LUMI_trace_print( \
      LUMI_traceline_format, LUMI_FILE_NAME, line, LUMI_FUNC_NAME, \
      NULL, 0, NULL); \
  goto cleanup; }

#define IGNORE_ERRORS(call) \
  ++LUMI_trace_ignore_count; (void)call; --LUMI_trace_ignore_count;

#define CHECK_REF(line, cleanup, ref, refman) \
  if (ref == NULL) RAISE(line, cleanup, empty_object) \
  if ((refman)->value == NULL) RAISE(line, cleanup, outdated_weak_reference)

int LUMI_main(int argc, char* argv[]);
int LUMI_test_main(int argc, char* argv[]);

#define MAIN_PROXY(func) int main(int argc, char* argv[]) { \
  return func(argc, argv); \
}

#define MAIN_FUNC MAIN_PROXY(LUMI_main)
#define TEST_MAIN_FUNC MAIN_PROXY(LUMI_test_main)
#define USER_MAIN_HEADER Returncode LUMI_user_main(void)

#define ARRAY_DEL(Type, array, length) if (array != NULL) { \
  int LUMI_n = 0; \
  for (; LUMI_n < length; ++LUMI_n) \
    Type##_Del(array + LUMI_n); \
}

#define SELF_REF_DEL(Type, field) \
while (self->field != NULL) { \
  Type* value = self->field; \
  Ref_Manager* value_Refman = self->field##_Refman; \
  self->field = value->field; \
  self->field##_Refman = value->field##_Refman; \
  value->field = NULL; \
  value->field##_Refman = NULL; \
  Type##_Del(value); \
  LUMI_owner_dec_ref(value_Refman); \
}

#define DYN_SELF_REF_DEL(Type, bases, field) \
while (self->field != NULL) { \
  Type* value = self->field; \
  Ref_Manager* value_Refman = self->field##_Refman; \
  Type##_Dynamic* value_Dynamic = self->field##_Dynamic; \
  self->field = value->field; \
  self->field##_Refman = value->field##_Refman; \
  self->field##_Dynamic = value->field##_Dynamic; \
  value->field = NULL; \
  value->field##_Refman = NULL; \
  value->field##_Dynamic = NULL; \
  value_Dynamic->bases##del(value); \
  LUMI_owner_dec_ref(value_Refman); \
}

#define INIT_VAR_REFMAN(line, cleanup, name) \
  name##_Refman = LUMI_new_ref(name); \
  if (name##_Refman == NULL) { RAISE(line, cleanup, managed_object_memory) }

#define INIT_NEW_REFMAN(line, cleanup, name) \
  name##_Refman = LUMI_new_ref(name); \
  if (name##_Refman == NULL) { \
    free(name); \
    name = NULL; \
    RAISE(line, cleanup, managed_object_memory) }

#define INIT_VAR(line, cleanup, name) \
  name = &name##_Var; \
  INIT_VAR_REFMAN(line, cleanup, name)

#define INIT_NEW(line, cleanup, name, type, size) \
  name = LUMI_alloc(sizeof(type) * size); \
  if (name == NULL) RAISE(line, cleanup, object_memory) \
  INIT_NEW_REFMAN(line, cleanup, name)

#define INIT_NEW_STRING(line, cleanup, name, size) \
  name##_Max_length = size; \
  INIT_NEW(line, cleanup, name, char, name##_Max_length)

#define INIT_NEW_ARRAY(line, cleanup, name, type, length, value_size) \
  name##_Length = length; \
  INIT_NEW(line, cleanup, name, type, name##_Length * value_size)

#define INIT_STRING_CONST(line, cleanup, name, text) \
  name = text; \
  name##_Max_length = sizeof(text); \
  name##_Length = sizeof(text) - 1; \
  INIT_VAR_REFMAN(line, cleanup, name)

void* LUMI_alloc(size_t size);
Ref_Manager* LUMI_new_ref(void* value);
void LUMI_inc_ref(Ref_Manager* ref);
void LUMI_dec_ref(Ref_Manager* ref);
void LUMI_var_dec_ref(Ref_Manager* ref);
void LUMI_owner_dec_ref(Ref_Manager* ref);

Bool LUMI_run_test(char* test_name, Func test_func);
Bool LUMI_test_coverage(File_Coverage* file_coverage, int files_number);

Returncode Array_length(void*, int length, Ref_Manager*, Int* length_out);

void String_Del(char*);
extern Generic_Type_Dynamic String_dynamic;
Returncode String_length(
  char*, int max_length, int length, Ref_Manager*, Int* length_out);
Returncode String_max_length(
  char*, int max_length, int length, Ref_Manager*, Int* length_out);
Returncode String_clear(
  char*, int max_length, int* length, Ref_Manager**);
Returncode String_equal(
  char*, int max_length, int length, Ref_Manager*,
  char* other, int other_max_length, int other_length, Ref_Manager*,
  Bool* equal);
Returncode String_get(
  char*, int max_length, int length, Ref_Manager*, Int index, Char* ch);
Returncode String_set(
  char*, int max_length, int length, Ref_Manager*, Int index, Char ch);
Returncode String_append(
  char*, int max_length, int* length, Ref_Manager**, Char ch);
Returncode String_copy(
  char*, int max_length, int* length, Ref_Manager**,
  char* source, int source_max_length, int source_length, Ref_Manager*);
Returncode String_concat(
  char*, int max_length, int* length, Ref_Manager**,
  char* ext, int ext_max_length, int ext_length, Ref_Manager*);
Returncode String_concat_int(
  char*, int max_length, int* length, Ref_Manager**, Int num);
Returncode String_find(
  char*, int max_length, int length, Ref_Manager*,
  char* pattern, int pattern_max_length, int pattern_length, Ref_Manager*,
  Int* index);
Returncode String_has(
  char*, int max_length, int length, Ref_Manager*, Char ch, Bool* found);

Returncode Int_str(
  Int value, char* str, int str_max_length, int* str_length, Ref_Manager**);

Returncode file_open_read(
  char* name, int name_max_length, int name_length, Ref_Manager*,
  File** file, Ref_Manager**);
Returncode file_open_write(
  char* name, int name_max_length, int name_length, Ref_Manager*,
  File** file, Ref_Manager**);
Returncode file_close(File* file, Ref_Manager* file_Refman);
void File_Del(File*);
extern Generic_Type_Dynamic File_dynamic;
Returncode File_getc(File*, Ref_Manager*, Char* ch, Bool* is_eof);
Returncode File_putc(File*, Ref_Manager*, Char ch);
Returncode File_write(
  File*, Ref_Manager*,
  char* text, int text_max_length, int text_length, Ref_Manager*);

typedef struct {
  char* argv;
  int argv_Length;
  int argv_Value_length;
  int* argv_String_length;
  Ref_Manager* argv_Refman;
  File* stdout_Cname;
  Ref_Manager* stdout_Cname_Refman;
  File* stdin_Cname;
  Ref_Manager* stdin_Cname_Refman;
  File* stderr_Cname;
  Ref_Manager* stderr_Cname_Refman;
} Sys;
extern Sys* sys;
extern Ref_Manager* sys_Refman;
void Sys_Del(Sys*);
extern Generic_Type_Dynamic Sys_dynamic;
Returncode Sys_print(
  Sys*, Ref_Manager*,
  char* text, int text_max_length, int text_length, Ref_Manager*);
Returncode Sys_println(
  Sys*, Ref_Manager*,
  char* text, int text_max_length, int text_length, Ref_Manager*);
Returncode Sys_getchar(Sys*, Ref_Manager*, char* ch, Bool* is_eof);
Returncode Sys_getline(
  Sys*, Ref_Manager*,
  char* line, int line_max_length, int* line_length, Ref_Manager**);
Returncode Sys_exit(Sys*, Ref_Manager*, Int status);
Returncode Sys_system(
  Sys*, Ref_Manager*,
  char* command, int command_max_length, int command_length, Ref_Manager*,
  Int* status);
Returncode Sys_getenv(
  Sys*, Ref_Manager*,
  char* name, int name_max_length, int name_length, Ref_Manager*,
  char* value, int value_max_length, int* value_length, Ref_Manager**,
  Bool* exists);

extern int lumi_debug_value;


#endif  /*LUMI_TL5_LUMI_5_H_INCLUDED_*/
