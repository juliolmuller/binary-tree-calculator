#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
typedef int boolean;

boolean is_numeric(char);
int infix_to_postfix(char *);

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
    infix_to_postfix(exp);
    list_push(&expressions, exp);
  }

  list_print(expressions);
  return 0;
}

boolean is_numeric(char ch)
{
  return (ch >= '0' && ch <= '9');
}

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
    return '$';
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

    default:
      return -1;
  }
}

int infix_to_postfix(char *infix)
{
  STACK *stack = stack_create(strlen(infix));
  int i, j;
  for (i = 0, j = 0; infix[i]; i++) {
    if (is_numeric(infix[i])) {
      do {
        infix[j++] = infix[i++];
      } while (is_numeric(infix[i]));
      i--;
    } else if (infix[i] == '(') {
      stack_push(stack, infix[i]);
    } else if (infix[i] == ')') {
      while (!stack_is_empty(stack) && stack_get(stack) != '(') {
        infix[j++] = stack_pop(stack);
      }
      if (!stack_is_empty(stack) && stack_get(stack) != '(')  {
        return -1;
      } else {
        stack_pop(stack);
      }
    } else {
      while (!stack_is_empty(stack) && stack_precedence(infix[i]) <= stack_precedence(stack_get(stack)))  {
        infix[j++] = stack_pop(stack);
      }
      stack_push(stack, infix[i]);
    }
  }
  while (!stack_is_empty(stack)) {
    infix[j++] = stack_pop(stack);
  }
  infix[j] = '\0';
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
