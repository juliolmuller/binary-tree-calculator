#include <string.h>
#include "boolean.h"
#include "strlist.h"
#include "utils.h"

int infix_to_postfix(char *, char *);

typedef struct _stack {
  int *array;
  int top;
} STACK;

STACK *stack_create(int length)
{
  STACK *stack = (STACK *) malloc(sizeof(STACK));
  stack->array = (int *) malloc(length * sizeof(int));
  stack->top = -1;

  return stack;
}

int stack_is_empty(STACK *stack)
{
  return stack->top == -1;
}

char stack_get(STACK *stack)
{
  return stack->array[stack->top];
}

void stack_push(STACK *stack, char op)
{
  stack->array[++stack->top] = op;
}

char stack_pop(STACK *stack)
{
  if (stack_is_empty(stack)) {
    return '\0';
  }
  return stack->array[stack->top--];
}

int stack_precedence(char ch)
{
  switch (ch) {
    case '+':
    case '-':
      return 1;

    case '*':
    case '/':
      return 2;

    case '^':
      return 3;

    case '$':
      return 4;

    default:
      return -1;
  }
}

int infix_to_postfix(char *infix, char *postfix)
{
  STACK *stack = stack_create(strlen(infix));
  int i, j;
  boolean unaryStart = *infix == '-' || *infix == '$';
  for (i = 0, j = 0; infix[i]; i++) {
    if (infix[i] == ' ') {
      continue;
    } else if (is_numeric(infix[i])) {
      do {
        postfix[j++] = infix[i++];
      } while (is_numeric(infix[i]));
      postfix[j++] = ' ';
      i--;
    } else if (infix[i] == '(') {
      stack_push(stack, infix[i]);
    } else if (infix[i] == ')') {
      while (!stack_is_empty(stack) && stack_get(stack) != '(') {
        postfix[j++] = stack_pop(stack);
        postfix[j++] = ' ';
      }
      if (!stack_is_empty(stack) && stack_get(stack) != '(')  {
        return -1;
      } else {
        stack_pop(stack);
      }
    } else {
      while (!stack_is_empty(stack) && stack_precedence(infix[i]) <= stack_precedence(stack_get(stack)))  {
        postfix[j++] = stack_pop(stack);
        postfix[j++] = ' ';
      }
      if (infix[i] == '-' || infix[i] == '$') {
        if (unaryStart) {
          unaryStart = false;
        } else {
          stack_push(stack, '+');
        }
      }
      stack_push(stack, infix[i]);
    }
  }
  while (!stack_is_empty(stack)) {
    postfix[j++] = stack_pop(stack);
    postfix[j++] = ' ';
  }
  postfix[--j] = '\0';
  return 0;
}
