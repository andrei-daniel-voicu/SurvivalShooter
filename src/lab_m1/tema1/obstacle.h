#pragma once
#include "collider.h"
#include "object.h"

class Obstacle : public Object, public Collider {
 public:
  Obstacle(Mesh* mesh, Shader* shader) : Object(mesh, shader){};
  void OnCollisionEnter(const Collider&) override;

  void setPosition(float, float) override;
  void setScale(float, float) override;
};