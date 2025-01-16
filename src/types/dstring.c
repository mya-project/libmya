#include <stdlib.h>
#include <string.h>

#include "dstring.h"

static void
_dstring_ensure_size(dstring_t* string, unsigned int size);

void
dstring_init(dstring_t* string, unsigned int buffer_size)
{
  string->length = 0;
  string->_buffer_size = buffer_size;
  string->data = malloc(buffer_size);
}

void
dstring_close(dstring_t* string)
{
  free(string->data);
  string->data = NULL;
}

void
dstring_putchar(dstring_t* string, int character)
{
  _dstring_ensure_size(string, string->length + 2);

  string->data[string->length++] = character;
  string->data[string->length] = '\0';
}

void
dstring_concat(dstring_t* string, const char* source)
{
  size_t source_length = strlen(source);

  _dstring_ensure_size(string, string->length + source_length + 1);

  memcpy(string->data + string->length, source, source_length + 1);

  string->length += source_length;
}

void
dstring_copy(dstring_t* string, const char* source)
{
  size_t source_length = strlen(source);

  _dstring_ensure_size(string, source_length + 1);

  memcpy(string->data, source, source_length + 1);

  string->length = source_length;
}

/**
 * Ensures that the string has memory sufficient to fit `size` bytes.
 */
static void
_dstring_ensure_size(dstring_t* string, unsigned int size)
{
  if (size < string->_buffer_size) {
    // We will never decrease the buffer size.
    return;
  }

  unsigned int new_size = ((size + DSTRING_CHUNK_SIZE) / DSTRING_CHUNK_SIZE) * DSTRING_CHUNK_SIZE;

  string->data = realloc(string->data, new_size);
  string->_buffer_size = new_size;
}
