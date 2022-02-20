#pragma once

#include "collider.h"
#include "object.h"

class Pickup : public Object, public Collider {
 public:
  enum class Type { HEAL, FIRE_RATE, SHOTGUN, SIZE };
  Type type;
  float duration;
  Pickup(Mesh* mesh, Shader* shader, Type type) : Object(mesh, shader) {
    this->type = type;
    setScale(1, 1);
  };
  void OnCollisionEnter(const Collider&) override;

  void setPosition(float, float) override;
  void setScale(float, float) override;
};