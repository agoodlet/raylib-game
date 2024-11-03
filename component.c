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

const int screenWidth = 800;
const int screenHeight = 450;
const int numPoints = 3;
// should theses be moved to the point struct?
Point *target = NULL;
Point *start = NULL;

void registerPoint(Component *component, Vector2 pos, int labelSize,
                   char *label, PointType type) {
  Point *point;
  point = malloc(sizeof(Point));

  point->pos = pos;
  // do some computing to make sure label is = labelSize
  point->label = malloc(labelSize * sizeof(char));
  point->label = label;
  point->isConnected = malloc(sizeof(bool));
  point->isConnected = false;
  point->isConnecting = malloc(sizeof(bool));
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

int render(Component *component) {

  Vector2 mouse = GetMousePosition();

  // there's probably a way to iterate through the linked list that saves me
  // from having to uses the getByIndex function I can probably do this the
  // exact same way i'm doign it in the link file
  for (int a = 0; a < component->numPoints; a++) {
    Point *point = getByIndex(component->points, a)->val;

    // draw existing connections
    if (point->isConnected) {
      DrawLineBezier(point->pos, point->connectedPoint->pos, 4.0f, GREEN);
    }

    DrawCircleV(point->pos,
                CheckCollisionPointCircle(mouse, point->pos, 10.0f) ? 14.0f
                                                                    : 8.0f,
                point->isConnecting ? RED : BLUE);

    // if I'm currently moused over a START node
    // AND I'm holding the mouse down
    // I want to draw a bezier curve between my mouse and that node
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointCircle(mouse, point->pos, 10.0f) &&
        point->type == START) {
      point->isConnecting = true;
      point->isConnected = false;
      start = point;
    }

    if (CheckCollisionPointCircle(mouse, point->pos, 10.0f) &&
        IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && point->type == END) {
      target = point;
    }

    if (point->isConnecting) {
      DrawLineBezier(mouse, point->pos, 4.0f, BLUE);
    }

    // make a renderHelper.h so I can add my draw text bounds detection to
    // that I guess
    Vector2 labelDimensions;
    labelDimensions = MeasureTextEx(GetFontDefault(), point->label, 20, 1);

    if (point->pos.y > screenHeight / 2.0f) {
      // I don't fucking understand why this is -2 instead of -1
      labelDimensions.y *= -2;
    }

    DrawText(point->label, point->pos.x - labelDimensions.x,
             point->pos.y + labelDimensions.y, 20, BLACK);

    DrawCircleV(point->pos,
                CheckCollisionPointCircle(mouse, point->pos, 10.0f) ? 14.0f
                                                                    : 8.0f,
                point->isConnecting ? RED : BLUE);
  }

  // tto be honest I can probably move most more of the logic out here and just
  // uses the start and target values instead of the point iterator
  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    if (start != NULL && target != NULL) {
      start->isConnected = true;
      start->connectedPoint = target;
      start->isConnecting = false;
    } else if (start != NULL && target == NULL) {
      start->isConnecting = false;
    }
    start = NULL;
    target = NULL;
  }

  return 0;
}
