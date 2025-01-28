#include <string.h>

#include "dstring.h"
#include "token.h"

void
token_init(token_t* token, const char* lexeme, token_type_t type, unsigned int line, unsigned int column)
{
  token->type = type;
  token->line = line;
  token->column = column;
  token->value = 0;

  dstring_init(&token->lexeme, 0);
  dstring_copy(&token->lexeme, lexeme);
}

void
token_close(token_t* token)
{
  dstring_close(&token->lexeme);
}
