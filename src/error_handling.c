#include <stdbool.h>
#include <stdio.h>

#include "error_handling.h"
#include "module.h"


#define LBUFF_SIZE 127


static inline int
_error_print_line(module_t* module, unsigned int line, unsigned int err_column, bool has_error);

static void
_error_print_indicator(unsigned int start_column, unsigned int length);

static void
_error_print_info(module_t* module, unsigned int err_line, unsigned int err_column);

static void
_error_remove_line(module_t* module);

void
error_module_ctx(module_t* module, unsigned int line, unsigned int column, unsigned int length, const char* message)
{
  unsigned int ctx_start_line = line - ERR_CTX_SIZE;
  unsigned int ctx_end_line = line + ERR_CTX_SIZE;
  unsigned int current_line = 0;

  fseek(module->file, 0, SEEK_SET);


  while (feof(module->file) == 0 && current_line < line - 1) {
    current_line++;

    if (current_line >= ctx_start_line) {
      _error_print_line(module, current_line, 0, false);
      continue;
    }

    _error_remove_line(module);
  }

  current_line++;

  unsigned int correction = _error_print_line(module, current_line, column, true);
  _error_print_indicator(column + correction, length);
  fprintf(stderr, "%s%s\n", ERR_PREFIX, message);

  while (feof(module->file) == 0 && current_line < ctx_end_line) {
    current_line++;

    _error_print_line(module, current_line, 0, false);
  }

  _error_print_info(module, line, column);
}

#define COL_PREFIX_SIZE 7  // The size of the prefix "xxxx | " printed on the start of the line.

/**
 * Returns column position correction based on line wrapping.
 *
 * This value should be used to change start and end column positions. Example:
 *   start_column += _error_print_line(...);
 */
static inline int
_error_print_line(module_t* module, unsigned int line, unsigned int err_column, bool has_error)
{
  int ch;
  unsigned int column = COL_PREFIX_SIZE;
  unsigned int column_correction = COL_PREFIX_SIZE;
  unsigned int buffer_index = 0;
  char buffer[LBUFF_SIZE + 1];

  if (has_error) {
    fprintf(stderr, "%4d" C_RED "->" C_NORMAL " ", line);
  } else {
    fprintf(stderr, "%4d | ", line);
  }

  while ((ch = fgetc(module->file)) != EOF) {
    column++;

    if (column > ERR_CTX_LINE_WRAP) {
      column_correction -= ERR_CTX_LINE_WRAP;
      column = 1;

      buffer[buffer_index] = '\n';
      buffer[buffer_index + 1] = '\0';
      fputs(buffer, stderr);

      buffer_index = 0;
    }

    buffer[buffer_index++] = ch;

    if (ch == '\n') {
      break;
    }

    if (buffer_index >= LBUFF_SIZE) {
      buffer[LBUFF_SIZE] = '\0';
      fputs(buffer, stderr);

      buffer_index = 0;
    }
  }

  if (buffer_index > 0) {
    buffer[buffer_index] = '\0';
    fputs(buffer, stderr);
  }

  return column_correction;
}

static void
_error_print_indicator(unsigned int start_column, unsigned int length)
{
  // unsigned int size = end_column - start_column + 1;

  fprintf(stderr, "%*c" C_RED, start_column - 1, ' ');

  for (int i = 0; i < length; i++) {
    fputc('^', stderr);
  }

  fprintf(stderr, C_NORMAL "\n");
}

static void
_error_print_info(module_t* module, unsigned int err_line, unsigned int err_column)
{
  fprintf(stderr, "On module %s:%d:%d.\n", module->filepath, err_line, err_column);
}

static void
_error_remove_line(module_t* module)
{
  int ch;

  do {
    ch = fgetc(module->file);
  } while (ch != '\n' && ch != EOF);
}
