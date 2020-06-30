#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expression.h"
#include "bintree.h"

LIST_NODE *infixExpressions = NULL;
LIST_NODE *prefixExpressions = NULL;

TREE_NODE *build_tree(char *);

int main()
{
  int i, counter = 0;
  while (true) {
    char infix[MAX_STR], prefix[MAX_STR], postfix[MAX_STR];
    printf("Digite a expressao aritmetica ('0' para encerrar): ");
    gets(infix);
    if (strcmp(infix, "0") == 0) {
      break;
    }
    counter++;
    infix_to_prefix(infix, prefix);
    list_push(&infixExpressions, infix);
    list_push(&prefixExpressions, prefix);
  }

  for (i = 0; i < counter; i++) {
    printf("\nExpression #%i\n", i + 1);
    printf("    Infix:  %s\n", infixExpressions->string);
    printf("    Prefix: %s\n", prefixExpressions->string);
    printf("    Tree:   ");
    TREE_NODE *tree = build_tree(prefixExpressions->string);
    tree_print(tree);
    printf("\n    Result: %.2f\n", tree_calculate(tree));

    infixExpressions = infixExpressions->next;
    prefixExpressions = prefixExpressions->next;
  }
  printf("\n");

  return 0;
}

TREE_NODE *build_tree(char *exp)
{
  TREE_NODE *tree = NULL;
  int i, len = strlen(exp);
  for (i = 0; i < len; i++) {
    if (exp[i] == ' ') {
      continue;
    }
    if (is_numeric(exp[i])) {
      char number[MAX_STR];
      int index = 0;
      do {
        number[index++] = exp[i++];
      } while (is_numeric(exp[i]));
      number[index] = '\0';
      tree = tree_insert(tree, atoi(number), true);
    } else {
      tree = tree_insert(tree, exp[i], false);
    }
  }
  return tree;
}
