#ifndef LIST_H
#define LIST_H

// get rid of errors
typedef struct Point Point;

typedef struct node {
  // this would change to "Point"
  struct Point *val;
  struct node *next;
} node_t;

node_t *newList(Point *headPoint);
int pushBack(node_t *head, Point *value);
void printList(node_t *head);
node_t *getByIndex(node_t *head, int index);

#endif
