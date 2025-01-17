#pragma once

typedef enum keyword
{
  KEY_BITFIELD = 0,
  KEY_IMMEDIATE,
  KEY_INCLUDE,
  KEY_INST,
  KEY_REGISTER,
  KEY_SET,
} keyword_t;

extern const char* mya_keywords[];
