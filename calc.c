#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expression.h"
#include "bintree.h"

LIST_NODE *infixExpressions = NULL;
LIST_NODE *postfixExpressions = NULL;

TREE_NODE *build_tree(char *);

int main()
{
  int i, counter = 0;
  while (true) {
    char infix[MAX_STR], prefix[MAX_STR], postfix[MAX_STR];
    printf("Type an arithmetic expression ('0' to stop): ");
    gets(infix);
    if (strcmp(infix, "0") == 0) {
      break;
    }
    counter++;
    infix_to_postfix(infix, prefix);
    list_push(&infixExpressions, infix);
    list_push(&postfixExpressions, prefix);
  }

  for (i = 0; i < counter; i++) {
    printf("\nExpression #%i\n", i + 1);
    printf("    Infix:   %s\n", infixExpressions->string);
    printf("    Postfix: %s\n", postfixExpressions->string);
    printf("    Tree:    ");
    TREE_NODE *tree = build_tree(postfixExpressions->string);
    tree_print(tree);
    printf("\n    Result:  %.2f\n", tree_calculate(tree));

    infixExpressions = infixExpressions->next;
    postfixExpressions = postfixExpressions->next;
  }
  printf("\n");

  return 0;
}

TREE_NODE *build_tree(char *exp)
{
  TREE_NODE *tree = NULL;
  int i, len = strlen(exp);
  for (i = len - 1; i>= 0; i--) {
    if (exp[i] == ' ') {
      continue;
    }
    if (is_numeric(exp[i])) {
      char number[MAX_STR];
      int index = 0;
      do {
        number[index++] = exp[i--];
      } while (i >= 0 && is_numeric(exp[i]));
      number[index] = '\0';
      tree = tree_insert(tree, atoi(strrev(number)), true);
    } else {
      tree = tree_insert(tree, exp[i], false);
    }
  }
  return tree;
}
