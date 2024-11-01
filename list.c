#include "list.h"
#include "component.h"
#include "stdio.h"
#include "stdlib.h"

node_t *newList(Point *headPoint) {
  node_t *head = NULL;
  head = (node_t *)malloc(sizeof(node_t));
  if (head == NULL) {
    return NULL;
  }

  head->val = headPoint;
  head->next = NULL;

  return head;
}

int pushBack(node_t *head, Point *value) {
  node_t *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = malloc(sizeof(node_t));

  current->next->val = value;
  current->next->next = NULL;

  return 0;
}

void iterate(node_t *head) {
  node_t *current = head;

  while (current != NULL) {
    printf("%s\n", current->val->label);
    current = current->next;
  }
}

node_t *getByIndex(node_t *head, int index) {
  node_t *current = head;

  if (index == 0) {
    return head;
  }

  for (int a = 0; a < index - 1; a++) {
    if (current->next == NULL) {
      return NULL;
    }
    current = current->next;
  }

  return current->next;
}
