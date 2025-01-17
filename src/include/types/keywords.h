#pragma once

typedef enum keyword
{
  KEY_BITFIELD = 0,
  KEY_INCLUDE,
  KEY_INST,
  KEY_REGISTER,
} keyword_t;

static const char mya_keywords[][32] = {
  [KEY_BITFIELD] = "bitfield",
  [KEY_INCLUDE] = "include",
  [KEY_INST] = "inst",
  [KEY_REGISTER] = "register",
};

#define KEYWORKDS_NUMBER (sizeof mya_keywords / sizeof *mya_keywords)
