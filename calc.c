#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

typedef struct _listNode {
  char string[MAX_STR];
  struct _listNode *next;
} LIST_NODE;

void list_push(LIST_NODE **, char []);
void list_print(LIST_NODE *);

typedef struct _treeNode {
  char value;
  struct _treeNode *left, *right;
} TREE_NODE;

TREE_NODE *tree_add_node(TREE_NODE *, TREE_NODE *);
TREE_NODE *tree_search_node(TREE_NODE *, char);
int tree_count_nodes(TREE_NODE *);
void tree_print(TREE_NODE *);

int main()
{
  LIST_NODE *expressions = NULL;
  while (1) {
    char exp[MAX_STR] = "\0";
    printf("Digite a expressao aritmetica ('0' para encerrar): ");
    gets(exp);
    if (strcmp(exp, "0") == 0) {
      break;
    }
    list_push(&expressions, exp);
  }

  list_print(expressions);
  return 0;
}

LIST_NODE *list_create_node(char word[])
{
  if (word == NULL) {
    return NULL;
  }

  LIST_NODE *newNode = (LIST_NODE *) malloc(sizeof(LIST_NODE));
  strcpy(newNode->string, word);
  newNode->next = NULL;

  return newNode;
}

void list_push(LIST_NODE **list, char word[])
{
  LIST_NODE *newNode = list_create_node(word);
  LIST_NODE *currentNode = *list;

  if (*list == NULL) {
    *list = newNode;
    return;
  }

  while (currentNode->next != NULL) {
    currentNode = currentNode->next;
  }
  currentNode->next = newNode;
}

void list_print(LIST_NODE *list)
{
  if (list == NULL) {
    printf("A lista esta vazia\n\n");
  }
  printf("Itens da lista:\n");
  while (list != NULL) {
    printf("    %s\n", list->string);
    list = list->next;
  }
  printf("\n");
}

TREE_NODE *tree_create_node(char value)
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

TREE_NODE *tree_search_node(TREE_NODE *root, char value)
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
