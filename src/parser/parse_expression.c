#include <stdbool.h>

#include "ast.h"
#include "aststack.h"
#include "module.h"
#include "parser.h"
#include "tkqueue.h"
#include "tkstack.h"
#include "types/operators.h"

static void
_generate_ast(module_t* module, ast_node_t* parent, tkqueue_t* queue);

static unsigned int
_parse_bitfield_expression(module_t* module, ast_node_t* parent, tkqueue_t* queue, token_t* token);

static int
_op_precedence(token_t* token);

static bool
_op_is_unary(token_t* token);

unsigned int
parse_expression(module_t* module, ast_node_t* parent, token_t* token)
{
  tkstack_t stack;
  tkqueue_t queue;
  token_t* current_token;
  bool is_unary = false;
  unsigned int ntokens = 0;

  if (token->type == TK_IDENTIFIER && token[1].type == TK_OPEN_BRACES) {
    return parse_bitfield_spec(module, parent, token);
  }

  tkstack_init(&stack);
  tkqueue_init(&queue, 30);

  for (;;) {
    current_token = &token[ntokens++];

    switch (current_token->type) {
    case TK_OPEN_PARENS:
      tkstack_push(&stack, current_token);
      is_unary = true;
      break;
    case TK_IDENTIFIER:
    case TK_NUMBER:
      tkqueue_add(&queue, current_token);
      is_unary = false;
      break;
    case TK_EQUAL:
      ntokens = _parse_bitfield_expression(module, parent, &queue, current_token);
      goto clean_and_exit;
    case TK_OPERATOR:
      if (is_unary && current_token->value == OP_MINUS) {
        current_token->value = OP_NEGATE;
      }

      while (! tkstack_isempty(&stack) && tkstack_peek(&stack)->type != TK_OPEN_PARENS &&
             _op_precedence(tkstack_peek(&stack)) >= _op_precedence(current_token)) {
        tkqueue_add(&queue, tkstack_pop(&stack));
      }

      tkstack_push(&stack, current_token);
      is_unary = true;
      break;
    case TK_CLOSE_PARENS:
      for (;;) {
        token_t* popped = tkstack_pop(&stack);
        if (! popped) {
          module_add_error(
            module,
            current_token->line,
            current_token->column,
            current_token->lexeme.length,
            "Close parentheses here is not matching a open parentheses."
          );

          goto clean_and_exit;
        }

        if (popped->type == TK_OPEN_PARENS) {
          break;
        }

        tkqueue_add(&queue, popped);
      }

      is_unary = false;
      break;
    case TK_SEMICOLON:
    case TK_CLOSE_BRACES:
    case TK_CLOSE_BRACKET:
    case TK_COMMA:
    case TK_EOF:
      ntokens--;
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
  while (! tkstack_isempty(&stack)) {
    tkqueue_add(&queue, tkstack_pop(&stack));
  }

  _generate_ast(module, parent, &queue);

clean_and_exit:
  tkstack_close(&stack);
  tkqueue_close(&queue);

  return ntokens;
}

static void
_generate_ast(module_t* module, ast_node_t* parent, tkqueue_t* queue)
{
  token_t* token;
  aststack_t stack;
  ast_node_t left;
  ast_node_t right;
  ast_node_t* op;

  aststack_init(&stack);

  for (; (token = tkqueue_get(queue));) {
    if (token->type != TK_OPERATOR) {
      aststack_push(&stack, NT_EXPRESSION, token);
      continue;
    }

    if (_op_is_unary(token)) {
      aststack_pop(&stack, &right);
      op = aststack_push(&stack, NT_EXPRESSION, token);
      ast_insert_children(op, &right);
      continue;
    }

    aststack_pop(&stack, &right);
    aststack_pop(&stack, &left);
    op = aststack_push(&stack, NT_EXPRESSION, token);
    ast_insert_children(op, &left);
    ast_insert_children(op, &right);
  }

  if (stack.length != 1) {
    printf("--> %d\n", stack.length);
    module_add_error(module, parent->token->line, parent->token->column, 1, "Invalid expression starting here.");
    goto clean;
  }

  aststack_pop(&stack, &left);
  ast_insert_children(parent, &left);

clean:
  aststack_close(&stack);
}

static unsigned int
_parse_bitfield_expression(module_t* module, ast_node_t* parent, tkqueue_t* queue, token_t* token)
{
  token_t* ident = tkqueue_get(queue);

  if (! ident || ident->type != TK_IDENTIFIER) {
    module_add_error(
      module,
      token->line,
      token->column,
      token->lexeme.length,
      "Bitfield expression expects a valid identifier before the `=`, like in: `some_identifier = Field { ... }`."
    );

    return 1;
  };

  ast_node_t* op = ast_add_children(parent, NT_EXPRESSION, token);
  ast_add_children(op, NT_EXPRESSION, ident);

  return 2 + parse_expression(module, op, token + 1);
}

static int
_op_precedence(token_t* token)
{
  if (token == NULL) {
    return -1;
  }

  if (token->type == TK_EQUAL) {
    return 999;
  }

  switch (token->value) {
  case OP_NEGATE:
  case OP_NOT:
    return 70;
  case OP_DIV:
  case OP_MULT:
    return 60;
  case OP_MINUS:
  case OP_PLUS:
    return 50;
  case OP_SHIFT_LEFT:
  case OP_SHIFT_RIGHT:
    return 40;
  case OP_AND:
    return 30;
  case OP_XOR:
    return 20;
  case OP_OR:
    return 10;
  default:
    return 0;
  }
}

static bool
_op_is_unary(token_t* token)
{
  switch (token->value) {
  case OP_NEGATE:
  case OP_NOT:
    return true;
  default:
    return false;
  }
}
