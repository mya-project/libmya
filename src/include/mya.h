#pragma once

#include "module.h"
#include "token.h"

/**
 * Make the lexical analysis on the given module.
 *
 * It will construct the `module->tokens` list and maybe registry some errors on `module->errors` list.
 *
 * @param module  The module for make the lexical analysis.
 */
error_code_t
mya_lexer(module_t* module);
