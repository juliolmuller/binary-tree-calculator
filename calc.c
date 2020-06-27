#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int boolean;
typedef int TREE_TYPE; /* tipo do elemento a ser colocado na estrutura */
typedef struct _node {
  TREE_TYPE value;
  struct _node *left, *right;
} NODE;
typedef NODE *POINTER;

POINTER tree_init()
{
  return NULL;
}

POINTER tree_create_node(TREE_TYPE value)
{
  POINTER node = (POINTER) malloc(sizeof(NODE));
  node->value = value;
  node->right = NULL;
  node->left = NULL;
  return node;
}

void tree_print(POINTER root)
{
  if (root != NULL) {
    printf("%i", root->value);
    printf(" (");
    tree_print(root->left);
    tree_print(root->right);
    printf(") ");
  }
}

POINTER tree_search_node(POINTER root, TREE_TYPE value)
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

int tree_count_nodes(POINTER root)
{
  if (root == NULL) {
    return 0;
  }
  return 1 + tree_count_nodes(root->left) + tree_count_nodes(root->right);
}

POINTER tree_add_node(POINTER root, POINTER node)
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

POINTER tree_search_node2(POINTER root, TREE_TYPE value, POINTER *parent)
{
  POINTER current = root;
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

POINTER tree_remove_node(POINTER root, TREE_TYPE value)
{
  POINTER parent, node, next, aux;
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
  POINTER tree = tree_init();

  while (true) {
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
          while (true) {
            TREE_TYPE value;
            POINTER node = NULL;
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
          while (true) {
            TREE_TYPE value;
            printf("\tNovo elemento: ");
            scanf("%d", &value);
            if (value == 0) break;
            POINTER node = tree_create_node(value);
            tree = tree_add_node(tree, node);
          }
          break;

        case 5:
          while (true) {
            TREE_TYPE value;
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
