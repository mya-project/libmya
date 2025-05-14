#pragma once

#include "types/token.h"

/**
 * Queue of tokens.
 */
typedef struct tkqueue
{
  unsigned int length;  ///< The current number of items on the queue.
  token_t** data;       ///< Pointer to queue data with allocated space to fit `_size` items.
  unsigned int _size;   ///< Current number of elements that fits on the queue.
  int _current;         ///< The index for the current item.
} tkqueue_t;
