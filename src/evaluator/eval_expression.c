#include <stdbool.h>

#include "evaluator.h"
#include "hashtable.h"
#include "module.h"
#include "types/operators.h"

inline int64_t
_op_binary_eval(int64_t a, operator_t op, int64_t b);

inline int64_t
_op_unary_eval(operator_t op, int64_t a);

int64_t
eval_expression(hashtable_t* variables, module_t* module, ast_node_t* ast)
{
  int64_t result;

  if (ast->type != NT_EXPRESSION) {
    module_add_error(
      module,
      ast->token->line,
      ast->token->column,
      ast->token->lexeme.length,
      "Unexpected token inside an expression."
    );

    return 0;
  }

  switch (ast->token->type) {
  case TK_OPEN_PARENS:
    return eval_expression(variables, module, ast->children);
  case TK_NUMBER:
    return ast->token->value;
  case TK_IDENTIFIER:
    if (hashtable_get(variables, ast->token->lexeme.data, &result) != ERR_OK) {
      module_add_error(module, ast->token->line, ast->token->column, ast->token->lexeme.length, "Undefined variable.");
      return 0;
    }

    return result;
  case TK_OPERATOR:
    bool is_binary = (ast->children_count == 2);
    ast_node_t* a = &ast->children[0];

    if (is_binary) {
      ast_node_t* b = &ast->children[1];
      return _op_binary_eval(
        eval_expression(variables, module, a),
        ast->token->value,
        eval_expression(variables, module, b)
      );
    }

    return _op_unary_eval(ast->token->value, eval_expression(variables, module, a));
  default:
    return 0;
  }
}

inline int64_t
_op_binary_eval(int64_t a, operator_t op, int64_t b)
{
  switch (op) {
  case OP_DIV:
    return a / b;
  case OP_MULT:
    return a * b;
  case OP_MINUS:
    return a - b;
  case OP_PLUS:
    return a + b;
  case OP_SHIFT_LEFT:
    return a << b;
  case OP_SHIFT_RIGHT:
    return a >> b;
  case OP_AND:
    return a & b;
  case OP_XOR:
    return a ^ b;
  case OP_OR:
    return a | b;
  default:
    return 0;
  }
}

inline int64_t
_op_unary_eval(operator_t op, int64_t a)
{
  switch (op) {
  case OP_NOT:
    return ~a;
  case OP_NEGATE:
    return -a;
  default:
    return 0;
  }
}
