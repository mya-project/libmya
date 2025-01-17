#pragma once

typedef enum keyword
{
  KEY_BITFIELD = 1,
  KEY_IMMEDIATE,
  KEY_INCLUDE,
  KEY_INST,
  KEY_REGISTER,
  KEY_SET,
} keyword_t;

static const char mya_keywords[][32] = {
  [KEY_BITFIELD] = "bitfield",
  // clang-format hates me.
  [KEY_IMMEDIATE] = "immediate",
  [KEY_INCLUDE] = "include",
  [KEY_INST] = "inst",
  [KEY_REGISTER] = "register",
  [KEY_SET] = "set",
};

#define KEYWORKDS_NUMBER (sizeof mya_keywords / sizeof *mya_keywords)
