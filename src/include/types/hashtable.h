#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "types/dstring.h"

/// The number of collisions items to (re)alloc when a collision occurs.
#define HASHTABLE_COLLISION_CHUNK_SIZE 5

typedef uint64_t hash_t;

/**
 * An item inside a hashtable.
 */
typedef struct hashitem
{
  bool is_set;                      ///< Is true if this item has set.
  dstring_t key;                    ///< The item's key.
  int64_t value;                    ///< The value of the item.
  struct hashitem* _collisions;     ///< List of another items with hash colliding with this. Is NULL if doesn't
                                    ///< has collisions.
  unsigned int _collisions_length;  ///< The number of items on the `_collisions` list.
  unsigned int _collisions_size;    ///< The number of item slots allocated to `_collisions` memory.
} hashitem_t;

/**
 * A hashtable.
 */
typedef struct hashtable
{
  hashitem_t* items;   ///< List of items on the hashtable.
  unsigned int _size;  ///< The number of item slots of the `items` allocated memory.
} hashtable_t;
