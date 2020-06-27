#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100

typedef struct _listNode {
  char exp[MAX_STR];
  struct _listNode *next;
} LIST_NODE;

void list_push(LIST_NODE **, char []);
void list_print(LIST_NODE *);

typedef struct _treeNode {
  char value;
  struct _treeNode *left, *right;
} TREE_NODE;

TREE_NODE *tree_create_node(char value)
{
  TREE_NODE *node = (TREE_NODE *) malloc(sizeof(TREE_NODE));
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  return node;
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

TREE_NODE *tree_search_node2(TREE_NODE *root, char value, TREE_NODE **parent)
{
  TREE_NODE *current = root;
  *parent = NULL;
  while (current) {
    if (value == current->value) {
      return current;
    }
    *parent = current;
    if (value < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return NULL;
}

TREE_NODE *tree_remove_node(TREE_NODE *root, char value)
{
  TREE_NODE *parent, *node, *next, *aux;
  node = tree_search_node2(root, value, &parent);
  if (node == NULL) {
    return root;
  }
  if (!node->left || !node->right) {
    next = !node->left ? node->left : node->right;
  } else {
    aux = node;
    next = node->left;
    while (next->right) {
      aux = next;
      next = next->right;
    }
    if (aux != node) {
      aux->right = next->left;
      next->left = node->left;
    }
    next->right = node->right;
  }
  if (!parent) {
    free(node);
    return next;
  }
  if (value < parent->value) {
    parent->left = next;
  } else {
    parent->right = next;
  }
  free(node);
  return root;
}

int main()
{
  LIST_NODE *list = NULL;

  int i;
  for (i = 0; i < 3; i++) {
    char word[MAX_STR] = "\0";
    gets(word);
    list_push(&list, word);
  }

  list_print(list);
  return 0;
}

int main2()
{
  TREE_NODE *tree = NULL;

  while (1) {
    int option = 0;
    printf("\n");
    printf("O que deseja fazer com a ARVORE?\n" );
    printf(" 1 Implrimir elementos   ");
    printf(" 2 Buscar elemento   ");
    printf(" 3 Contar elementos   ");
    printf(" 4 Adicionar elementos   ");
    printf(" 5 Remover elementos   ");
    printf(" 0 [Sair]\n");

    while (option == 0) {
      printf( ">>> " );
      scanf("%d", &option);
      switch (option) {
        case 1:
          printf("\t");
          tree_print(tree);
          printf("\n");
          break;

        case 2:
          while (1) {
            char value;
            TREE_NODE *node = NULL;
            printf("\tBuscar elemento: ");
            scanf("%d", &value);
            if (value == 0) break;
            node = tree_search_node(tree, value);
            if (node == NULL) {
              printf("\t   Elemento nao encontrado =(\n" );
            } else {
              printf("\t   Elemento presente =)\n" );
            }
          }
          break;

        case 3:
          printf("\tQUantidade de elementos: %d\n", tree_count_nodes(tree));
          break;

        case 4:
          while (1) {
            char value;
            printf("\tNovo elemento: ");
            scanf("%d", &value);
            if (value == 0) break;
            TREE_NODE *node = tree_create_node(value);
            tree = tree_add_node(tree, node);
          }
          break;

        case 5:
          while (1) {
            char value;
            printf( "\tElemento a ser removido: " );
            scanf("%d", &value);
            if (value == 0) break;
            tree = tree_remove_node(tree, value);
          }
          break;

        case 0:
          return 0;

        default:
          option = 0;
      }
    }
  }
}

LIST_NODE *list_create_node(char word[])
{
  if (word == NULL) {
    return NULL;
  }

  LIST_NODE *newNode = (LIST_NODE *) malloc(sizeof(LIST_NODE));
  strcpy(newNode->exp, word);
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
    printf("    %s\n", list->exp);
    list = list->next;
  }
  printf("\n");
}
