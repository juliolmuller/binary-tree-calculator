#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"

typedef struct _treeNode {
  int value;
  boolean isNumber;
  struct _treeNode *left, *right;
} TREE_NODE;

TREE_NODE *tree_insert(TREE_NODE *, int, boolean);
void tree_print(TREE_NODE *);
double tree_calculate(TREE_NODE *);

TREE_NODE *tree_create_node(int value, boolean isNumber)
{
  TREE_NODE *node = (TREE_NODE *) malloc(sizeof(TREE_NODE));
  node->isNumber = isNumber;
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  return node;
}

TREE_NODE *tree_insert(TREE_NODE *root, int newValue, boolean isNumber)
{
  if (root == NULL) {
    return tree_create_node(newValue, isNumber);
  }
  if (root->right == NULL || !root->right->isNumber) {
    TREE_NODE *attempt = tree_insert(root->right, newValue, isNumber);
    if (attempt != NULL) {
      root->right = attempt;
      return root;
    }
  }
  if (root->value != '-' && root->value != '$' && (root->left == NULL || !root->left->isNumber)) {
    TREE_NODE *attempt = tree_insert(root->left, newValue, isNumber);
    if (attempt != NULL) {
      root->left = attempt;
      return root;
    }
  }
  return NULL;
}

void tree_print(TREE_NODE *root)
{
  if (root != NULL) {
    if (root->isNumber) {
      printf("%i", root->value);
    } else {
      printf("%c", root->value);
    }
    printf(" (");
    tree_print(root->left);
    tree_print(root->right);
    printf(") ");
  }
}

double tree_calculate(TREE_NODE *root)
{
  if (root->isNumber) {
    return root->value;
  }
  double rightOp = tree_calculate(root->right);
  if (root->value == '-') {
    return rightOp * -1;
  }
  if (root->value == '$') {
    return sqrt(rightOp);
  }
  double leftOp = tree_calculate(root->left);
  switch (root->value) {
    case '+':
      return leftOp + rightOp;

    case '*':
      return leftOp * rightOp;

    case '/':
      return leftOp / rightOp;

    case '^':
      return pow(leftOp, rightOp);
  }
}
