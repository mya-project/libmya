#pragma once

#include "types/err.h"
#include "types/tkqueue.h"

#define QUEUE_LENGTH_INCREMENT 32

/**
 * Initializes the token queue.
 *
 * @param queue         The queue to be initialized.
 * @param initial_size  The initial number of items that fit the queue's memory data.
 */
void
tkqueue_init(tkqueue_t* queue, unsigned int initial_size);

/**
 * Close the given queue.
 *
 * @param  The queue to be closed.
 */
void
tkqueue_close(tkqueue_t* queue);

/**
 * Add a value to the token queue.
 *
 * @param queue  The queue where to add the item.
 * @param item   The value to add.
 */
void
tkqueue_add(tkqueue_t* queue, token_t* token);

/**
 * Get the current value from the queue and increment the position for the next value.
 *
 * @param queue  The queue where to get the value.
 *
 * @return       NULL when the queue is empty.
 * @return       Pointer to the item.
 */
token_t*
tkqueue_get(tkqueue_t* queue);

/**
 * Get the current value from the queue without increment the queue position.
 *
 * @param queue  The queue where to get the value.
 *
 * @return       NULL when the queue is empty.
 * @return       Pointer to the item.
 */
token_t*
tkqueue_peek(const tkqueue_t* queue);

/**
 * Check if the given queue is empty.
 *
 * @param queue  The queue to check if it's empty.
 *
 * @return       1 on the queue is empty.
 * @return       0 on the queue has items.
 */
int
tkqueue_isempty(const tkqueue_t* queue);
