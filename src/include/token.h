#pragma once

#include "types/token.h"

/**
 * Initializes a token struct.
 *
 * @param token   The token to be initialized.
 * @param lexeme  Token's lexeme with LEXEME_MAX_SIZE maximum size.
 * @param type    Token type.
 * @param line    Token's line inside the module.
 * @param column  Token's column on line.
 */
void
token_init(token_t* token, const char* lexeme, token_type_t type, unsigned int line, unsigned int column);

/**
 * Closes the given token.
 *
 * @param token  The token to be closed.
 */
void
token_close(token_t* token);
