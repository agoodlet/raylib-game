#include "component.h"

int main() {
  Component *component = newComponent();
  registerPoint(component, (Vector2){30, 30}, 5, "input", START);
  registerPoint(component, (Vector2){800 - 30, 450 - 30}, 5, "input", START);
  registerPoint(component, (Vector2){800 - 30, 30}, 5, "input", START);
  render(component);
  yeet(component);

  return 0;
}
