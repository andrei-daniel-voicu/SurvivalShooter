#pragma once
#include "bullet.h"
#include "collider.h"
#include "object.h"
#include "obstacle.h"

class Enemy : public Object, public Collider {
 public:
  Enemy(Mesh*, Shader*, bool);
  ~Enemy();
  void Update(float) override;
  void Move(const Transform&, const std::vector<Obstacle>&, const glm::vec3&,
            float);

  void OnCollisionEnter(const Collider&) override;
  void setPosition(float, float) override;
  void setScale(float, float) override;
  float speed;
  bool canShoot;
  float fireRate;
  float bulletSpeed;
  float travelDistance;
  bool deathAnimation;

  std::list<Bullet> bullets;
  Mesh* bulletMesh;
  Shader* bulletShader;

 private:
  float timeSinceFired;
};