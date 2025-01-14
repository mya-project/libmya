#include <string.h>

#include "token.h"

void
token_init(token_t* token, const char* lexeme, token_type_t type, unsigned int line, unsigned int column)
{
  token->type = type;
  token->line = line;
  token->column = column;

  strncpy(token->lexeme, lexeme, LEXEME_MAX_SIZE);
  token->lexeme[LEXEME_MAX_SIZE] = '\0';
}
