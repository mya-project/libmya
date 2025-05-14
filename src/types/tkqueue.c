#include <stdlib.h>

#include "tkqueue.h"

void
_queue_ensure_size(tkqueue_t* queue);

void
tkqueue_init(tkqueue_t* queue, unsigned int initial_size)
{
  queue->length = 0;
  queue->_current = 0;
  queue->_size = initial_size;
  queue->data = malloc(sizeof(token_t) * initial_size);
}

void
tkqueue_close(tkqueue_t* queue)
{
  free(queue->data);
  queue->data = NULL;
}

void
tkqueue_add(tkqueue_t* queue, token_t* token)
{
  _queue_ensure_size(queue);
  queue->data[queue->length++] = token;
}

token_t*
tkqueue_get(tkqueue_t* queue)
{
  if (tkqueue_isempty(queue)) {
    return NULL;
  }

  return queue->data[queue->_current++];
}

token_t*
tkqueue_lookup(const tkqueue_t* queue)
{
  if (tkqueue_isempty(queue)) {
    return NULL;
  }

  return queue->data[queue->_current];
}

int
tkqueue_isempty(const tkqueue_t* queue)
{
  return queue->length == 0 || queue->_current >= queue->length;
}

void
_queue_ensure_size(tkqueue_t* queue)
{
  if (queue->length < queue->_size) {
    return;
  }

  queue->_size += QUEUE_LENGTH_INCREMENT;
  queue->data = realloc(queue->data, sizeof(token_t) * queue->_size);
}
