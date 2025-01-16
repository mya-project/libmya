#pragma once

#include "types/err.h"
#include "types/queue.h"

/**
 * Initializes a circular queue.
 *
 * @param queue       The queue to be initialized.
 * @param max_length  The maximum number of items to fit inside the queue.
 */
void
cqueue_init(cqueue_t* queue, unsigned int max_length);

/**
 * Add a value to the circular queue.
 *
 * @param queue  The queue where to add the item.
 * @param item   The value to add.
 *
 * @return       ERR_MAX_SIZE_EXCEEDED on queue is full.
 * @return       ERR_OK on added successful.
 */
error_code_t
cqueue_add(cqueue_t* queue, int item);

/**
 * Get the current value from the circular queue, removing it from the queue.
 *
 * @param queue  The queue where to remove the value.
 * @param item   The pointer where the value will be saved.
 *
 * @return       ERR_EMPTY on queue is empty.
 * @return       ERR_OK on value as get successful.
 */
error_code_t
cqueue_get(cqueue_t* queue, int* item);

/**
 * Get a value from the circular queue, without removing it from the queue.
 *
 * @param queue  The queue where to get the value.
 * @param item   The pointer where the value will be saved.
 * @param seek   The index of the value to get (0 means the current, 1 the next and so one).
 *
 * @return       ERR_EMPTY on queue is empty.
 * @return       ERR_INVALID_INDEX on the `seek` is invalid.
 * @return       ERR_OK on value as get successful.
 */
error_code_t
cqueue_lookup(const cqueue_t* queue, int* item, unsigned int seek);

/**
 * Check if the given circular queue is empty.
 *
 * @param queue  The queue to check if it's empty.
 *
 * @return       1 on the queue is empty.
 * @return       0 on the queue has items.
 */
int
cqueue_isempty(const cqueue_t* queue);

/**
 * Check if the given circular queue is full.
 *
 * @param queue  The queue to check if it's full.
 *
 * @return       1 on the queue is full.
 * @return       0 on the queue is not full.
 */
int
cqueue_isfull(const cqueue_t* queue);

/**
 * Close the given circular queue.
 *
 * @param  The queue to be closed.
 */
void
cqueue_close(cqueue_t* queue);
