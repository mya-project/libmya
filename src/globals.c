#include <stdlib.h>

#include "types/ast.h"
#include "types/keywords.h"
#include "types/mir.h"
#include "types/operators.h"
#include "version.h"

const char* mya_version = LIBMYA_VERSION;

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

const char* mya_types[] = {
  [TYPE_IMMEDIATE] = "immediate",
  // clang-format hates me.
  [TYPE_REGISTER] = "register",
  NULL,
};

const char* mya_token_types[] = {
  [TK_CLOSE_BRACES] = "close_braces",
  // clang-format hates me.
  [TK_CLOSE_BRACKET] = "close_bracket",
  [TK_CLOSE_PARENS] = "close_parentheses",
  [TK_COLON] = "colon",
  [TK_COMMA] = "comma",
  [TK_EOF] = "end_of_file",
  [TK_EQUAL] = "equal",
  [TK_IDENTIFIER] = "identifier",
  [TK_KEYWORD] = "keyword",
  [TK_NUMBER] = "number",
  [TK_OPEN_BRACES] = "open_braces",
  [TK_OPEN_BRACKET] = "open_bracket",
  [TK_OPEN_PARENS] = "open_parentheses",
  [TK_OPERATOR] = "operator",
  [TK_SEMICOLON] = "semicolon",
  [TK_STRING] = "string",
  NULL,
};

const char* mya_node_types[] = {
  [NT_ARG_LIST] = "argument_list",
  // clang-format hates me.
  [NT_ARG] = "argument",
  [NT_BITFIELD_BODY] = "bitfield_body",
  [NT_BITFIELD_SPEC] = "bitfield_spec",
  [NT_EXPRESSION] = "expression",
  [NT_FIELD_SPEC] = "field_spec",
  [NT_FIELD] = "field",
  [NT_IDENTIFIER] = "identifier",
  [NT_INST_BODY] = "inst_body",
  [NT_ROOT] = "root",
  [NT_SIZE_SPEC] = "size_spec",
  [NT_STATEMENT] = "statement",
  [NT_STRING] = "string",
  [NT_TYPE] = "type_name",
  NULL,
};
