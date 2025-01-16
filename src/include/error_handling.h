#pragma once

#include "colors.h"
#include "module.h"
#include "types/err.h"

/**
 * Print a error message formated to show the code context inside the module.
 *
 * @param module   The module where the error will be showed.
 * @param line     The module's line where the error is.
 * @param column   The line's column where the error starts.
 * @param length   The length of the part where has an error in the line. It's starts on `column` and ends on
 *                 `column + length`.
 * @param message  The error message to print.
 */
void
error_module_ctx(module_t* module, unsigned int line, unsigned int column, unsigned int length, const char* message);
