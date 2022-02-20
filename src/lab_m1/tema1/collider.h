#pragma once
#include "transform.h"

class Collider {
 public:
  Collider() : Collider(glm::vec3{0, 0, 0}, 0, 0){};
  Collider(const glm::vec3&, float, float);
  bool CheckCollision(const glm::vec3&, const glm::vec3&, const glm::vec3&,
                      const glm::vec3&);
  virtual void OnCollisionEnter(const Collider&);

  void setColPosition(float, float);
  void setColScale(float, float);

  glm::vec3 getColPosition() const;
  glm::vec3 getColScale() const;

 private:
  glm::vec3 center;
  float width, height;
};