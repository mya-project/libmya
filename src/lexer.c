#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "dstring.h"
#include "module.h"
#include "queue.h"
#include "token.h"
#include "types/err.h"


static inline void
_mod_rm_line(module_t* module);

static inline unsigned int
_mod_read_number(module_t* module, unsigned int line, unsigned int column);

static inline unsigned int
_char2base(int ch);

static inline bool
_isbasedigit(unsigned int base, int ch);

#define MOD_ADD(lexeme, type)                                                                                          \
  token = module_add_token(module);                                                                                    \
  token_init(token, lexeme, type, line, column);                                                                       \
  DPRINTF3("Added token `%s` at %s:%d:%d.\n", lexeme, module->filepath, line, column)

error_code_t
mya_lexer(module_t* module)
{
  int ch;
  unsigned int line = 1;
  unsigned int column = 1;
  token_t* token;

  for (; module_lookup(module, &ch, 0) == ERR_OK; column++) {
    if (isblank(ch)) {
      module_getc(module, &ch);
      continue;
    }

    switch (ch) {
    case '#':
      _mod_rm_line(module);
    case '\n':
      line++;
      column = 1;
      break;
    case '{':
      MOD_ADD("{", TK_OPEN_BRACES);
      break;
    case '}':
      MOD_ADD("}", TK_CLOSE_BRACES);
      break;
    case '(':
      MOD_ADD("(", TK_OPEN_PARENS);
      break;
    case ')':
      MOD_ADD(")", TK_CLOSE_PARENS);
      break;
    case '[':
      MOD_ADD("[", TK_OPEN_BRACKET);
      break;
    case ']':
      MOD_ADD("]", TK_CLOSE_BRACKET);
      break;
    case '=':
      MOD_ADD("=", TK_OPERATOR);
      break;
    case '+':
      MOD_ADD("+", TK_OPERATOR);
      break;
    case '-':
      MOD_ADD("-", TK_OPERATOR);
      break;
    case '*':
      MOD_ADD("*", TK_OPERATOR);
      break;
    case '/':
      MOD_ADD("/", TK_OPERATOR);
      break;
    case '~':
      MOD_ADD("~", TK_OPERATOR);
      break;
    case '|':
      MOD_ADD("|", TK_OPERATOR);
      break;
    case '&':
      MOD_ADD("&", TK_OPERATOR);
      break;
    case '<':  // <<
      break;
    case '>':  // >>
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      column += _mod_read_number(module, line, column) - 1;
      continue;
    }

    module_getc(module, &ch);
  }

  return ERR_OK;
}

static inline void
_mod_rm_line(module_t* module)
{
  error_code_t err;
  int ch;

  do {
    err = module_getc(module, &ch);
  } while (err == ERR_OK && ch != '\n' && ch != EOF);
}

static inline unsigned int
_mod_read_number(module_t* module, unsigned int line, unsigned int column)
{
  char message[128];
  int firstchar;
  int secondchar;
  dstring_t* lexeme;
  unsigned int base = 10;

  token_t* token = module_add_token(module);
  token_init(token, "", TK_NUMBER, line, column);
  lexeme = &token->lexeme;

  module_getc(module, &firstchar);
  module_lookup(module, &secondchar, 0);

  if (! isalnum(secondchar)) {
    dstring_putchar(lexeme, firstchar);
    token->value = firstchar - '0';
    DPRINTF3("Added token `%s` at %s:%d:%d.\n", lexeme->data, module->filepath, line, column);
    return 1;
  }

  if (firstchar == '0') {
    base = _char2base(secondchar);

    if (base == 0) {
      dstring_putchar(lexeme, firstchar);
      token->value = firstchar - '0';
      DPRINTF3("Added token `%s` at %s:%d:%d.\n", lexeme->data, module->filepath, line, column);

      sprintf(
        message,
        "Character '%c' is an invalid base indicator. It should be 'x' (hexadecimal), 'b' (binary) or 'o' (octal).",
        secondchar
      );

      module_add_error(module, line, column + 1, 1, message);
      return 1;
    }
  }

  if (base == 10) {
    dstring_putchar(lexeme, firstchar);
  } else {
    module_getc(module, &secondchar);
    dstring_putchar(lexeme, firstchar);
    dstring_putchar(lexeme, secondchar);
  }

  module_lookup(module, &firstchar, 0);
  while (_isbasedigit(base, firstchar)) {
    dstring_putchar(lexeme, firstchar);

    module_getc(module, &secondchar);
    module_lookup(module, &firstchar, 0);
  }

  if (isalnum(firstchar)) {
    sprintf(message, "Character '%c' is invalid for base %d literal number.", firstchar, base);

    module_add_error(module, line, column + lexeme->length, 1, message);
  }

  char* number_start = lexeme->data + 2 * (base != 10);
  token->value = strtoll(number_start, NULL, base);

  DPRINTF3("Added token `%s` at %s:%d:%d.\n", lexeme->data, module->filepath, line, column);
  return lexeme->length;
}

/**
 * Converts characters 'x', 'o', 'b' or any digit to base 16, 8, 2 or 10 respectivaly.
 * Returns 0 if character is invalid.
 */
static inline unsigned int
_char2base(int ch)
{
  switch (ch) {
  case 'x':
    return 16;
  case 'o':
    return 8;
  case 'b':
    return 2;
  default:
    return isdigit(ch) ? 10 : 0;
  }
}

static inline bool
_isbasedigit(unsigned int base, int ch)
{
  switch (base) {
  case 16:
    return isxdigit(ch);
  case 10:
    return isdigit(ch);
  case 8:
    return isdigit(ch) && (ch - '0') <= 7;
  case 2:
    return ch == '1' || ch == '0';
  default:
    return false;
  }
}