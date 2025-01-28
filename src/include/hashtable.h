#pragma once

#include <stdint.h>

#include "types/err.h"
#include "types/hashtable.h"

/**
 * Initializes a hashtable.
 *
 * @param hashtable  The hashtable to be initialized.
 * @param size       The number of item slots of the `items` allocated memory. Bigger means: + memory, - collision.
 */
void
hashtable_init(hashtable_t* hashtable, unsigned int size);

/**
 * Close the given hashtable.
 *
 * @param hashtable  The hashtable to be closed.
 */
void
hashtable_close(hashtable_t* hashtable);

/**
 * Set the value of the specified key inside the hashtable.
 *
 * @param hashtable  The hashtable where the key is.
 * @param key        The key.
 * @param value      The value to set for the key.
 */
void
hashtable_set(hashtable_t* hashtable, const char* key, int64_t value);

/**
 * Get the value of the specified key inside the hashtable.
 *
 * @param hashtable  The hashtable where to get the value.
 * @param key        The key of the value.
 * @param value      Pointer to where the value will be saved.
 *
 * @return  ERR_OK on the key has found in hashtable and him value has get.
 * @return  ERR_INVALID_INDEX on the key is not set.
 */
error_code_t
hashtable_get(hashtable_t* hashtable, const char* key, int64_t* value);
