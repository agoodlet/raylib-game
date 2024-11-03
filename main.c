#include "component.h"
#include <raylib.h>
#include <stdlib.h>

typedef enum Scene { TITLE, COMPONENT, GAME } scene_t;

int main() {
  Component *component = newComponent(3);

  registerPoint(component, (Vector2){30, 30}, 5, "input", START);
  registerPoint(component, (Vector2){800 - 30, 450 - 30}, 9, "+1 damage", END);
  registerPoint(component, (Vector2){800 - 30, 30}, 13, "+1 projectile", END);

  Component *component2 = newComponent(4);

  registerPoint(component2, (Vector2){30, 30}, 5, "input", START);
  registerPoint(component2, (Vector2){800 - 30, 450 - 30}, 9, "+1 damage", END);
  registerPoint(component2, (Vector2){800 - 30, 30}, 13, "+1 projectile", END);
  registerPoint(component2, (Vector2){800 - 30, 450.0f / 2}, 27,
                "+10% critical strike chance", END);

  int screenWidth = 800;
  int screenHeight = 450;
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "bezier");
  scene_t currentScene = TITLE;

  // need to find map a "value" to a button
  // or maybe a callback? then I can define
  // a function that returns the right component
  Rectangle btn1Bounds = {50, 50, 100, 50};
  int btn1State = 0;

  Rectangle btn2Bounds = {50, 150, 100, 50};
  int btn2State = 0;

  Component *current = NULL;

  while (!WindowShouldClose()) {
    switch (currentScene) {
    case TITLE: {
      // do stuff
      Vector2 mouse = GetMousePosition();
      if (CheckCollisionPointRec(mouse, btn1Bounds)) {
        btn1State = 1;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          current = component;
          currentScene = COMPONENT;
        }
      } else {
        btn1State = 0;
      }

      if (CheckCollisionPointRec(mouse, btn2Bounds)) {
        btn2State = 1;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
          current = component2;
          currentScene = COMPONENT;
        }
      } else {
        btn2State = 0;
      }
    } break;
    case COMPONENT: {
      // do stuff
    } break;
    case GAME: {
      // do stuff
    } break;
    }
    BeginDrawing();
    switch (currentScene) {
    case TITLE: {
      // do stuff
      ClearBackground(GREEN);
      DrawRectangle(btn1Bounds.x, btn1Bounds.y, btn1Bounds.width,
                    btn1Bounds.height, btn1State == 1 ? DARKGREEN : LIME);
      DrawText("Component 1", btn1Bounds.x + 5, btn1Bounds.y + 25, 15,
               DARKGRAY);

      DrawRectangle(btn2Bounds.x, btn2Bounds.y, btn2Bounds.width,
                    btn2Bounds.height, btn2State == 1 ? DARKGREEN : LIME);
      DrawText("Component 2", btn2Bounds.x + 5, btn2Bounds.y + 25, 15,
               DARKGRAY);
    } break;
    case COMPONENT: {
      ClearBackground(RAYWHITE);

      if (IsKeyPressed(KEY_BACKSPACE)) {
        currentScene = TITLE;
      }

      render(current);
    } break;
    case GAME: {
      // do stuff
    } break;
    }

    EndDrawing();
  }
  /* yeet(component); */
  CloseWindow();

  return 0;
}
