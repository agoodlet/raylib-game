#include "component.h"

int main() {
  Component *component = newComponent();

  registerPoint(component, (Vector2){30, 30}, 5, "input", START);
  registerPoint(component, (Vector2){800 - 30, 450 - 30}, 9, "+1 damage", END);
  registerPoint(component, (Vector2){800 - 30, 30}, 13, "+1 projectile", END);

  int screenWidth = 800;
  int screenHeight = 450;
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "bezier");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    render(component);

    EndDrawing();
  }
  /* yeet(component); */
  CloseWindow();

  return 0;
}
