#pragma once

#include "module.h"
#include "token.h"
#include "types/mir.h"

/**
 * Make the lexical analysis on the given module.
 *
 * It will construct the `module->tokens` list and maybe registry some errors on `module->errors` list.
 *
 * @param module  The module for make the lexical analysis.
 *
 * @return  ERR_INVALID_CODE  on lexer found some errors on module.
 * @return  ERR_OK            on finished successful.
 */
error_code_t
mya_lexer(module_t* module);

/**
 * Make the syntactical analysis on the given module and construct the AST.
 *
 * @param module  The module for make the syntactical analysis.
 *
 * @return  ERR_INVALID_CODE  on parser found some errors on module.
 * @return  ERR_OK            on finished successful.
 */
error_code_t
mya_parser(module_t* module);

/**
 * Make the semantic analysis on the given module and evaluates the statements, constructing the in-memory intermediate
 * representation.
 *
 * @param mir     Where the intermediate representation will be added.
 * @param module  The module to be evaluated.
 *
 * @return  ERR_INVALID_CODE  on evaluator found some errors on module.
 * @return  ERR_OK            on finished successful.
 */
error_code_t
mya_evaluator(mir_t* mir, module_t* module);
