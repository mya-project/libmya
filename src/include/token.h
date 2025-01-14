#pragma once

#include "types/token.h"

void
token_init(token_t* token, const char* lexeme, token_type_t type, unsigned int line, unsigned int column);
