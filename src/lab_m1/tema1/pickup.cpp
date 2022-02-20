#include "pickup.h"

void Pickup::OnCollisionEnter(const Collider& col) { Destroy(); }

void Pickup::setPosition(float x, float y) {
  Transform::setPosition(x, y);
  setColPosition(x, y);
}

void Pickup::setScale(float x, float y) {
  Transform::setScale(x, y);
  setColScale(x + 1.f, y + 1.f);
}
