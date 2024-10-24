#include "component.h"
/* #include "raylib.h" */
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
  // make a linked list so I can add to the end of the list every time without
  // array fuckery
  component->points[0].pos = pos;
  // do some computing to make sure label is = labelSize
  component->points[0].label = malloc(labelSize * sizeof(char));
  component->points[0].label = label;
  component->points[0].isConnected = false;
  component->points[0].isConnecting = false;
  component->points[0].selected = false;
  component->points[0].connectedPoint = malloc(sizeof(Point));
  component->points[0].type = type;
}

Component *newComponent() {
  Point *Points = malloc(numPoints * sizeof(Point));

  Component *newComponent;
  newComponent = (Component *)malloc(sizeof(Component));

  newComponent->numPoints = numPoints;

  newComponent->points = malloc(newComponent->numPoints * sizeof(Point));

  newComponent->points = Points;

  return newComponent;
}

void yeet(Component *component) {
  for (int a = 0; a < component->numPoints; a++) {
    // idk why but this breaks so we don't need it for now
    /* free(component->points[a].label); */
    free(component->points[a].connectedPoint);
  }
  free(component->points);
  free(component);
}

int render2(Component *component) {
  printf("num Points: %d\n", component->numPoints);

  for (int a = 0; a < component->numPoints; a++) {
    printf("%d\n", component->points[a].isConnected);
  }

  return 0;
}

// render should take in a pointer to a component and render that component
int render(Component *component) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "bezier");

  Point Points[numPoints];

  Point *start = NULL;
  Point *end = NULL;

  while (!WindowShouldClose()) {
    DrawFPS(50, 50);

    Vector2 mouse = GetMousePosition();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int a = 0; a < component->numPoints; a++) {
      // draw any connections we might have

      if (component->points[a].isConnected) {
        DrawLineBezier(component->points[a].pos,
                       component->points[a].connectedPoint->pos, 4.0f, GREEN);
      }

      if (component->points[a].type == START) {
        if (CheckCollisionPointCircle(mouse, component->points[a].pos, 10.0f) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          start = &component->points[a];
          start->label = "onput";
          printf("%s", component->points[a].label);
        }
      }

      if (component->points[a].type == END) {
        // set the end point if we mouse over a point while holding the
        // mouse
        // down
        if (CheckCollisionPointCircle(mouse, component->points[a].pos, 10.0f) &&
            IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
          end = &component->points[a];
        }
      }

      // make a renderHelper.h so I can add my draw text bounds detection to
      // that I guess
      Vector2 labelDimensions;
      labelDimensions =
          MeasureTextEx(GetFontDefault(), component->points[a].label, 20, 1);

      if (component->points[a].pos.y > screenHeight / 2.0f) {
        // I don't fucking understand why this is -2 instead of -1
        labelDimensions.y *= -2;
      }

      DrawText(component->points[a].label,
               component->points[a].pos.x - labelDimensions.x,
               component->points[a].pos.y + labelDimensions.y, 20, BLACK);

      DrawCircleV(
          component->points[a].pos,
          CheckCollisionPointCircle(mouse, component->points[a].pos, 10.0f)
              ? 14.0f
              : 8.0f,
          component->points[a].isConnecting ? RED : BLUE);
    }

    EndDrawing();

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
  }

  CloseWindow();

  return 0;
}
