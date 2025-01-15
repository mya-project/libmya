#pragma once

#define LEXEME_MAX_SIZE 127

/**
 * Enumeration of token types.
 */
typedef enum token_type
{
  TK_CLOSE_BRACKET,
  TK_CLOSE_PARENS,
  TK_IDENTIFIER,
  TK_KEYWORD,
  TK_NUMBER,
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
  token_type_t type;                 ///< Token type.
  unsigned int line;                 ///< Token line inside the module.
  unsigned int column;               ///< Column of the token position on the line.
  char lexeme[LEXEME_MAX_SIZE + 1];  ///< Lexeme of the token.
} token_t;
