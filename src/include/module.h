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
 */
error_code_t
module_init(module_t* module, const char* filepath);
