#include <stdlib.h>

#include "types/keywords.h"
#include "types/operators.h"
#include "version.h"

const char* mya_version = VERSION;

const char* mya_keywords[] = {
  [KEY_BITFIELD] = "bitfield",
  // clang-format hates me.
  [KEY_IMMEDIATE] = "immediate",
  [KEY_INCLUDE] = "include",
  [KEY_INST] = "inst",
  [KEY_REGISTER] = "register",
  [KEY_SET] = "set",
  NULL,
};

const char* mya_operators[] = {
  [OP_AND] = "&",
  // clang-format hates me.
  [OP_DIV] = "/",
  [OP_MINUS] = "-",
  [OP_MULT] = "*",
  [OP_NOT] = "~",
  [OP_OR] = "|",
  [OP_PLUS] = "+",
  [OP_SHIFT_LEFT] = "<<",
  [OP_SHIFT_RIGHT] = ">>",
  [OP_XOR] = "^",
  NULL,
};
