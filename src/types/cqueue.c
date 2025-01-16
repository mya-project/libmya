#include <stdlib.h>

#include "queue.h"
#include "types/err.h"

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

void
cqueue_init(cqueue_t* queue, unsigned int max_length)
{
  queue->length = 0;
  queue->_current = 0;
  queue->_last = -1;
  queue->_max_length = max_length;
  queue->data = malloc(sizeof(int) * max_length);
}

error_code_t
cqueue_add(cqueue_t* queue, int item)
{
  if (cqueue_isfull(queue)) {
    return ERR_MAX_SIZE_EXCEEDED;
  }

  queue->_last = (queue->_last + 1) % queue->_max_length;
  queue->data[queue->_last] = item;

  queue->length = MIN(queue->length + 1, queue->_max_length);

  return ERR_OK;
}

error_code_t
cqueue_get(cqueue_t* queue, int* item)
{
  if (cqueue_isempty(queue)) {
    return ERR_EMPTY;
  }

  *item = queue->data[queue->_current];

  queue->_current = (queue->_current + 1) % queue->_max_length;
  queue->length--;

  return ERR_OK;
}

error_code_t
cqueue_lookup(const cqueue_t* queue, int* item, unsigned int seek)
{
  if (cqueue_isempty(queue)) {
    return ERR_EMPTY;
  }

  unsigned int index = (queue->_current + seek) % queue->_max_length;

  if ((seek >= queue->length) || (queue->_last > queue->_current && index > queue->_last) ||
      (queue->_last < queue->_current && index < queue->_current && index > queue->_last)) {
    return ERR_INVALID_INDEX;
  }

  *item = queue->data[index];
  return ERR_OK;
}

int
cqueue_isempty(const cqueue_t* queue)
{
  return queue->length == 0;
}

int
cqueue_isfull(const cqueue_t* queue)
{
  return queue->length >= queue->_max_length;
}

void
cqueue_close(cqueue_t* queue)
{
  free(queue->data);
  queue->data = NULL;
}
