#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dstring.h"
#include "hashtable.h"

static void
_hashtable_add_collision(hashitem_t* item, const char* key, int64_t value);

static hashitem_t*
_hashtable_find_collision(hashitem_t* item, const char* key);

static hash_t
_hash_djb2(const char* key);

void
hashtable_init(hashtable_t* hashtable, unsigned int size)
{
  hashtable->_size = size;

  hashtable->items = calloc(size, sizeof(hashitem_t));
}

void
hashtable_close(hashtable_t* hashtable)
{
  for (int i = 0; i < hashtable->_size; i++) {
    if (! hashtable->items[i].is_set) {
      continue;
    }

    dstring_close(&hashtable->items[i].key);

    if (hashtable->items[i]._collisions_length == 0) {
      continue;
    }

    for (int j = 0; j < hashtable->items[i]._collisions_length; j++) {
      dstring_close(&hashtable->items[i]._collisions[j].key);
    }

    free(hashtable->items[i]._collisions);
  }

  free(hashtable->items);
  hashtable->items = NULL;
}

void
hashtable_set(hashtable_t* hashtable, const char* key, int64_t value)
{
  hash_t index = _hash_djb2(key) % hashtable->_size;
  hashitem_t* item = &hashtable->items[index];

  if (! item->is_set) {
    item->is_set = true;
    item->value = value;
    dstring_init(&item->key, 0);
    dstring_copy(&item->key, key);
    return;
  }

  if (strcmp(item->key.data, key) == 0) {
    item->value = value;
    return;
  }

  _hashtable_add_collision(item, key, value);
}

error_code_t
hashtable_get(hashtable_t* hashtable, const char* key, int64_t* value)
{
  hash_t index = _hash_djb2(key) % hashtable->_size;
  hashitem_t* item = &hashtable->items[index];

  if (! item->is_set) {
    return ERR_INVALID_INDEX;
  }

  if (strcmp(item->key.data, key) == 0) {
    *value = item->value;
    return ERR_OK;
  }

  item = _hashtable_find_collision(item, key);
  if (item == NULL) {
    return ERR_INVALID_INDEX;
  }

  *value = item->value;
  return ERR_OK;
}

static void
_hashtable_add_collision(hashitem_t* item, const char* key, int64_t value)
{
  hashitem_t* collision = _hashtable_find_collision(item, key);

  if (collision != NULL) {
    collision->value = value;
    return;
  }

  if (item->_collisions_size < item->_collisions_length + 1) {
    item->_collisions_size += HASHTABLE_COLLISION_CHUNK_SIZE;
    item->_collisions = realloc(item->_collisions, sizeof(hashitem_t) * item->_collisions_size);
  }

  collision = &item->_collisions[item->_collisions_length++];
  collision->is_set = true;
  collision->value = value;

  dstring_init(&collision->key, 0);
  dstring_copy(&collision->key, key);
}

static hashitem_t*
_hashtable_find_collision(hashitem_t* item, const char* key)
{
  for (int i = 0; i < item->_collisions_length; i++) {
    if (strcmp(item->_collisions[i].key.data, key) == 0) {
      return &item->_collisions[i];
    }
  }

  return NULL;
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
