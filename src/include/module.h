#pragma once

#include "types/err.h"
#include "types/module.h"

/**
 * Initialize a module struct.
 *
 * Open the `filepath` and initializes the `tokens` list.
 *
 * @param module    The module to be initialized.
 * @param filepath  The filepath for the module file.
 *
 * @return          ERR_FILE_NOT_FOUND on module file is not found.
 * @return          ERR_OK on success.
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

/**
 * Get next character on module's file, removing it from the queue.
 *
 * @param module  The module to get the character.
 * @param chret   Pointer where the character will be saved.
 *
 * @return       ERR_EMPTY on file doesn't have more characters.
 * @return       ERR_OK on character as get successful.
 */
error_code_t
module_getc(module_t* module, int* chret);

/**
 * Get a character on module's file, without removing it from the queue.
 *
 * @param module  The module to get the character.
 * @param chret   Pointer where the character will be saved.
 * @param seek    The index of the character to get (0 means the current, 1 the next and so one).
 *                Should not be >= MODULE_MIN_QUEUE_LENGTH to avoid possible errors.
 *
 * @return       ERR_EMPTY on file doesn't have more characters.
 * @return       ERR_INVALID_INDEX on the `seek` is invalid.
 * @return       ERR_OK on character as get successful.
 */
error_code_t
module_lookup(module_t* module, int* chret, unsigned int seek);

/**
 * Close the given module.
 *
 * @param module  The module to be closed.
 */
void
module_close(module_t* module);
