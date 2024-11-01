#include "component.h"
#include "list.h"
/* #include <raylib.h> */
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

// what is the plan?
// input node connects to output nodes
// depending on which output nodes are "active" depends on the resulting stat
// increases

// What do I need to track for points?
// - xpos
// - ypos
// - isConnected
//    - is there an established connection?
// - isConnecting
//    - is the user currently manipulating the connection
// - connectedPoint
//    - what point is the current point connected to

// what do I need to track for the component?
//  - which output nodes are active

// need a function to:
// create random points on a component
//

const int screenWidth = 800;
const int screenHeight = 450;
const int numPoints = 3;

// take in a pos, label, label size, type
// in the future I should set up and register some structs that are "modifiers"
// so I can have a modifier that is for projectiles and a value of 2 for + 2
// projectiles and then I can derive the label from that
void registerPoint(Component *component, Vector2 pos, int labelSize,
                   char *label, PointType type) {
  Point *point;
  point = malloc(sizeof(Point));

  point->pos = pos;
  // do some computing to make sure label is = labelSize
  point->label = malloc(labelSize * sizeof(char));
  point->label = label;
  point->isConnected = false;
  point->isConnecting = false;
  point->selected = false;
  point->connectedPoint = malloc(sizeof(Point));
  point->type = type;
  if (component->points == NULL) {
    // this should now be the head node for the points linked list
    component->points = newList(point);
  } else {
    pushBack(component->points, point);
  }

  // make a linked list so I can add to the end of the list every time without
  // array fuckery
}

Component *newComponent() {
  /* Point *Points = malloc(numPoints * sizeof(Point)); */

  Component *newComponent;
  newComponent = (Component *)malloc(sizeof(Component));

  newComponent->numPoints = numPoints;

  newComponent->points = malloc(newComponent->numPoints * sizeof(Point));

  newComponent->points = NULL;

  return newComponent;
}

void yeet(Component *component) {
  for (int a = 0; a < component->numPoints; a++) {
    // idk why but this breaks so we don't need it for now
    /* free(component->points[a].label); */
    /* free(component->points[a].connectedPoint); */
  }
  /* free(component->points); */
  /* free(component); */
}

int render2(Component *component) {

  for (int a = 0; a < component->numPoints; a++) {
    Point point = *getByIndex(component->points, a)->val;
    DrawText(point.label, 50, 50 * a, 20, BLACK);
  }

  return 0;
}

// render should take in a pointer to a component and render that component
int render(Component *component) {
  Point *start = NULL;
  Point *end = NULL;

  Vector2 mouse = GetMousePosition();

  for (int a = 0; a < component->numPoints; a++) {
    // draw any connections we might have

    Point point = *getByIndex(component->points, a)->val;

    if (point.isConnected) {
      DrawLineBezier(point.pos, point.connectedPoint->pos, 4.0f, GREEN);
    }

    if (point.type == START) {
      if (CheckCollisionPointCircle(mouse, point.pos, 10.0f) &&
          IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        start = &point;
        start->label = "onput";
        printf("%s", point.label);
      }
    }

    if (point.type == END) {
      // set the end point if we mouse over a point while holding the
      // mouse
      // down
      if (CheckCollisionPointCircle(mouse, point.pos, 10.0f) &&
          IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        end = &point;
      }
    }

    // make a renderHelper.h so I can add my draw text bounds detection to
    // that I guess
    Vector2 labelDimensions;
    labelDimensions = MeasureTextEx(GetFontDefault(), point.label, 20, 1);

    if (point.pos.y > screenHeight / 2.0f) {
      // I don't fucking understand why this is -2 instead of -1
      labelDimensions.y *= -2;
    }

    DrawText(point.label, point.pos.x - labelDimensions.x,
             point.pos.y + labelDimensions.y, 20, BLACK);

    DrawCircleV(point.pos,
                CheckCollisionPointCircle(mouse, point.pos, 10.0f) ? 14.0f
                                                                   : 8.0f,
                point.isConnecting ? RED : BLUE);
  }

  // if we release the mouse button and we have an end point, we want to
  // connect to it then we want to wipe our start and end points
  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    if (start != NULL && end != NULL) {
      start->connectedPoint = end;
      start->isConnected = true;
      start->isConnecting = false;
    }
    start = NULL;
    end = NULL;
  }

  // if we are holding the mouse down and we have a start point we know we
  // want to be drawing a bezier curve
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && start != NULL) {
    start->isConnecting = true;
    start->isConnected = false;

    DrawLineBezier(start->pos, mouse, 4.0f, BLUE);
  }

  return 0;
}
