#include <stdlib.h>

#include "dstring.h"
#include "hashtable.h"

static hash_t
_hash_djb2(const char* key);

void
hashtable_init(hashtable_t* hashtable, unsigned int size)
{
  hashtable->length = 0;
  hashtable->_size = size;

  hashtable->items = calloc(size, sizeof(hashitem_t));
}

void
hashtable_set(hashtable_t* hashtable, const char* key, int64_t value)
{
  hash_t index = _hash_djb2(key) % hashtable->_size;
  hashitem_t* item = &hashtable->items[index];

  if (item->_collisions == NULL) {
    item->value = value;
    dstring_init(&item->key, 0);
    dstring_copy(&item->key, key);
    return;
  }
}

static hash_t
_hash_djb2(const char* key)
{
  hash_t hash = 5381;

  while (*key) {
    hash = (hash * 33) ^ *key++;
  }

  return hash;
}
