#include <string.h>

#include "dstring.h"
#include "token.h"

void
token_init(token_t* token, const char* lexeme, token_type_t type, unsigned int line, unsigned int column)
{
  token->type = type;
  token->line = line;
  token->column = column;

  dstring_init(&token->lexeme, 25);  // 25 is big enough to fit the major of the tokens.
  dstring_copy(&token->lexeme, lexeme);
}
