#pragma once

#define LEXEME_MAX_SIZE 127

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

typedef struct token
{
  token_type_t type;
  unsigned int line;
  unsigned int column;
  char lexeme[LEXEME_MAX_SIZE + 1];
} token_t;
