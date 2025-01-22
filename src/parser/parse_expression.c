#include "ast.h"
#include "module.h"
#include "parser.h"
#include "stack.h"
#include "types/operators.h"

static unsigned int
_parse_operator(module_t* module, ast_node_t* parent, stack_t* stack, token_t* token);

static unsigned int
_parse_binary_operator(module_t* module, ast_node_t* parent, stack_t* stack, token_t* token);

static unsigned int
_parse_unary_operator(module_t* module, ast_node_t* parent, stack_t* stack, token_t* token);

unsigned int
parse_expression(module_t* module, ast_node_t* parent, token_t* token)
{
  stack_t stack;
  ast_node_t node;
  token_t* current_token;
  ast_node_t* child;
  unsigned int ntokens = 0;

  if (token->type == TK_IDENTIFIER && token[1].type == TK_OPEN_BRACES) {
    return parse_bitfield_spec(module, parent, token);
  }

  stack_init(&stack);

  for (;;) {
    current_token = &token[ntokens];

    switch (current_token->type) {
    case TK_OPEN_PARENS:
      child = stack_push(&stack, NT_EXPRESSION, current_token);
      ntokens += 1 + parse_expression(module, child, current_token + 1);

      if (token[ntokens].type != TK_CLOSE_PARENS) {
        module_add_error(
          module,
          child->token->line,
          child->token->column,
          child->token->lexeme.length,
          "Open parentheses starting here has not a expected close parentheses matching it."
        );

        return ntokens;
      }

      ntokens++;
      break;
    case TK_IDENTIFIER:
    case TK_NUMBER:
      stack_push(&stack, NT_EXPRESSION, current_token);
      ntokens++;
      break;
    case TK_OPERATOR:
      ntokens += _parse_operator(module, parent, &stack, current_token);
      break;
    case TK_EQUAL:
      ntokens += _parse_binary_operator(module, parent, &stack, current_token);
      break;
    case TK_SEMICOLON:
    case TK_CLOSE_PARENS:
    case TK_CLOSE_BRACES:
    case TK_CLOSE_BRACKET:
    case TK_COMMA:
    case TK_EOF:
      goto finish_expression;
    default:
      module_add_error(
        module,
        current_token->line,
        current_token->column,
        current_token->lexeme.length,
        "Unexpected token inside an expression."
      );

      ntokens++;
      goto finish_expression;
    }
  }


finish_expression:
  // We expect to only have one expression on stack at end. It's the root node of the expression.

  if (stack_isempty(&stack)) {
    module_add_error(module, token->line, token->column, token->lexeme.length, "Malformed expression starting here.");
    return ntokens;
  }

  stack_pop(&stack, &node);

  if (! stack_isempty(&stack)) {
    stack_pop(&stack, &node);

    module_add_error(
      module,
      node.token->line,
      node.token->column,
      node.token->lexeme.length,
      "Unexpected expression starting here."
    );

    return ntokens;
  }

  ast_insert_children(parent, &node);

  return ntokens;
}

static unsigned int
_parse_operator(module_t* module, ast_node_t* parent, stack_t* stack, token_t* token)
{
  switch (token->value) {
  case OP_NOT:
    return _parse_unary_operator(module, parent, stack, token);
  case OP_MINUS:
    if (stack_isempty(stack)) {
      return _parse_unary_operator(module, parent, stack, token);
    }
  case OP_AND:
  case OP_DIV:
  case OP_MULT:
  case OP_OR:
  case OP_PLUS:
  case OP_SHIFT_LEFT:
  case OP_SHIFT_RIGHT:
  case OP_XOR:
    return _parse_binary_operator(module, parent, stack, token);
  default:
    module_add_error(
      module,
      token->line,
      token->column,
      token->lexeme.length,
      "Unrecognized operator here. It's really a valid expression operator?"
    );

    return 1;
  }
}

static unsigned int
_parse_binary_operator(module_t* module, ast_node_t* parent, stack_t* stack, token_t* token)
{
  ast_node_t value1;

  if (stack_pop(stack, &value1) != ERR_OK) {
    module_add_error(
      module,
      token->line,
      token->column,
      token->lexeme.length,
      "Binary operator expects a valid value before it, like in: `value OPERATOR value`."
    );

    return 1;
  };

  ast_node_t* op = stack_push(stack, NT_EXPRESSION, token);
  ast_insert_children(op, &value1);

  return 1 + parse_expression(module, op, token + 1);
}

static unsigned int
_parse_unary_operator(module_t* module, ast_node_t* parent, stack_t* stack, token_t* token)
{
  ast_node_t* op = stack_push(stack, NT_EXPRESSION, token);

  return 1 + parse_expression(module, op, token + 1);
}
