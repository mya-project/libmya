#pragma once

#include "err.h"
#include "types/module.h"

/**
 * Initialize a module struct.
 *
 * Open the `filepath` and initializes the `tokens` list.
 *
 * @param module    The module to be initialized.
 * @param filepath  The filepath for the module file.
 *
 * @return           ERR_FILE_NOT_FOUND on module file is not found.
 * @return           ERR_OK on success.
 */
error_code_t
module_init(module_t* module, const char* filepath);

/**
 * Add a new token to module.
 *
 * @param module  The module where the token will be added.
 *
 * @return        A pointer to the added token.
 */
token_t*
module_add_token(module_t* module);
