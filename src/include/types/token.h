#pragma once

#include "dstring.h"

/**
 * Enumeration of token types.
 */
typedef enum token_type
{
  TK_CLOSE_BRACES,
  TK_CLOSE_BRACKET,
  TK_CLOSE_PARENS,
  TK_COLON,
  TK_COMMA,
  TK_EQUAL,
  TK_IDENTIFIER,
  TK_KEYWORD,
  TK_NUMBER,
  TK_OPEN_BRACES,
  TK_OPEN_BRACKET,
  TK_OPEN_PARENS,
  TK_OPERATOR,
  TK_SEMICOLON,
  TK_STRING,
} token_type_t;

/**
 * Struct for a Mya token.
 */
typedef struct token
{
  token_type_t type;    ///< Token type.
  unsigned int line;    ///< Token line inside the module.
  unsigned int column;  ///< Column of the token position on the line.
  long long int value;  ///< Integer value of the token on TK_NUMBER tokens.
  dstring_t lexeme;     ///< Lexeme of the token.
} token_t;

extern const char* mya_token_types[];
