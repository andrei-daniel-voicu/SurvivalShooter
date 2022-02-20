#include "obstacle.h"

void Obstacle::OnCollisionEnter(const Collider&) {}

void Obstacle::setPosition(float x, float y) {
  Transform::setPosition(x, y);
  setColPosition(x, y);
}

void Obstacle::setScale(float x, float y) {
  Transform::setScale(x, y);
  setColScale(x + 1.f, y + 1.f);
}
