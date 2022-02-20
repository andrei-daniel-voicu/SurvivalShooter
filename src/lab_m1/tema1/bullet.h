#pragma once
#include "collider.h"
#include "object.h"

class Bullet : public Object, public Collider {
 public:
  Bullet(const Transform&, float, Mesh*, Shader*);
  void Update(float) override;
  float speed;
  float distanceTraveled;

  void OnCollisionEnter(const Collider&) override;
  void setPosition(float, float) override;
  void setScale(float, float) override;
};