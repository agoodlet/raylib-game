#include "raylib.h"

#ifndef COMPONENT_H
#define COMPONENT_H

// get rid of errors
typedef struct node node_t;

typedef enum { START, END } PointType;

typedef struct Point Point;
struct Point {
  Vector2 pos;
  char *label;
  bool isConnected;
  bool isConnecting;
  bool selected;
  PointType type;
  Point *connectedPoint;
};

// do I need a seperate field to track the number of points?
typedef struct {
  int numPoints;
  node_t *points;
} Component;

Component *newComponent();
void registerPoint(Component *component, Vector2 pos, int labelSize,
                   char *label, PointType type);
int render(Component *component);
int render2(Component *component);
void yeet(Component *component);

#endif
