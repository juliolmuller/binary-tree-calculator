#include <stdio.h>
#include <stdlib.h>

typedef struct _treeNode {
  int value;
  struct _treeNode *left, *right;
} TREE_NODE;

TREE_NODE *tree_add_node(TREE_NODE *, TREE_NODE *);
TREE_NODE *tree_search_node(TREE_NODE *, int);
int tree_count_nodes(TREE_NODE *);
void tree_print(TREE_NODE *);

TREE_NODE *tree_create_node(int value)
{
  TREE_NODE *node = (TREE_NODE *) malloc(sizeof(TREE_NODE));
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  return node;
}

TREE_NODE *tree_add_node(TREE_NODE *root, TREE_NODE *node)
{
  if (root == NULL) {
    return node;
  }
  if (node->value < root->value) {
    root->left = tree_add_node(root->left, node);
  } else if (node->value > root->value) {
    root->right = tree_add_node(root->right, node);
  }
  return root;
}

TREE_NODE *tree_search_node(TREE_NODE *root, int value)
{
  if (root == NULL) {
    return NULL;
  }
  if (value < root->value) {
    return tree_search_node(root->left, value);
  }
  if (value > root->value) {
    return tree_search_node(root->right, value);
  }
  return root;
}

int tree_count_nodes(TREE_NODE *root)
{
  if (root == NULL) {
    return 0;
  }
  return 1 + tree_count_nodes(root->left) + tree_count_nodes(root->right);
}

void tree_print(TREE_NODE *root)
{
  if (root != NULL) {
    printf("%i", root->value);
    printf(" (");
    tree_print(root->left);
    tree_print(root->right);
    printf(") ");
  }
}
