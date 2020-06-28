#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expression.h"
#include "strlist.h"
#include "bintree.h"

LIST_NODE *infixExpressions = NULL;
LIST_NODE *postfixExpressions = NULL;

int main()
{
  while (true) {
    char infix[MAX_STR], postfix[MAX_STR];
    printf("Digite a expressao aritmetica ('0' para encerrar): ");
    gets(infix);
    if (strcmp(infix, "0") == 0) {
      break;
    }
    infix_to_postfix(infix, postfix);
    list_push(&infixExpressions, infix);
    list_push(&postfixExpressions, postfix);
  }

  list_print(infixExpressions);
  list_print(postfixExpressions);
  return 0;
}
