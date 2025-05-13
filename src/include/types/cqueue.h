#pragma once

/**
 * Circular queue of integers.
 */
typedef struct cqueue
{
  unsigned int length;       ///< The current number of items on the queue.
  unsigned int _max_length;  ///< The maximum number of items that fits on the queue.
  int _current;              ///< The index for the current item.
  int _last;                 ///< The index of the last item.
  int* data;                 ///< Pointer to queue data with allocated space to fit `max_size` items.
} cqueue_t;
