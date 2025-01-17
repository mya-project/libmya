#pragma once

typedef enum operator
{
  OP_AND = 0,
  OP_DIV,
  OP_MINUS,
  OP_MULT,
  OP_NOT,
  OP_OR,
  OP_PLUS,
  OP_SHIFT_LEFT,
  OP_SHIFT_RIGHT,
  OP_XOR,
} operator_t;

extern const char* mya_operators[];
