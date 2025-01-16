#pragma once

/// The size of the chunk of a dynamic string. The string buffer size is increased aligned by this size when
/// reallocated.
#define DSTRING_CHUNK_SIZE 100

/**
 * A dynamic string (dstring) that automatically reallocate her buffer when needed.
 */
typedef struct dstring
{
  char* data;                 ///< Pointer for the raw string content (a normal C string).
  unsigned int length;        ///< The length of the string.
  unsigned int _buffer_size;  ///< The size of the allocated buffer for the string.
} dstring_t;
