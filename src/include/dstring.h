#pragma once

#include "types/dstring.h"

/**
 * Initializes a dynamic string (dstring).
 *
 * The dynamic string automatically realloc her buffer when needed. So you don't need to care about buffer sizes.
 *
 * @param string       Pointer for the dstring to be initialized.
 * @param buffer_size  The initial buffer size for the string.
 */
void
dstring_init(dstring_t* string, unsigned int buffer_size);

/**
 * Closes the dynamic string.
 *
 * @param string  The string to be closed.
 */
void
dstring_close(dstring_t* string);

/**
 * Concatenates a character on the end of the dstring.
 *
 * @param string     The dstring where to concatenate the character.
 * @param character  The character to be concatenated.
 */
void
dstring_putchar(dstring_t* string, int character);

/**
 * Concatenates a string on the end of the dstring.
 *
 * @param string  The dstring where to concatenate the string.
 * @param source  The string to be concatenated.
 */
void
dstring_concat(dstring_t* string, const char* source);

/**
 * Copies the content of `source` to the dstring.
 *
 * @param string  The dstring where to copy.
 * @param source  The string to be copied.
 */
void
dstring_copy(dstring_t* string, const char* source);
