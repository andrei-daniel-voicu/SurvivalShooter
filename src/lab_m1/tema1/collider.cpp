#include "collider.h"

Collider::Collider(const glm::vec3& center, float width, float height) {
  this->center = center;
  this->width = width;
  this->height = height;
}

bool Collider::CheckCollision(const glm::vec3& pos1, const glm::vec3& scale1,
                              const glm::vec3& pos2, const glm::vec3& scale2) {
  if (abs(pos1.x - pos2.x) > scale1.x / 2 + scale2.x / 2) return false;
  if (abs(pos1.y - pos2.y) > scale1.y / 2 + scale2.y / 2) return false;
  return true;
}

void Collider::OnCollisionEnter(const Collider&) {}

void Collider::setColPosition(float x, float y) {
  center.x = x;
  center.y = y;
}

void Collider::setColScale(float x, float y) {
  width = x;
  height = y;
}

glm::vec3 Collider::getColPosition() const { return center; }

glm::vec3 Collider::getColScale() const { return glm::vec3{width, height, 0}; }
