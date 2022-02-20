#pragma once
#include "bullet.h"
#include "enemy.h"
#include "obstacle.h"
#include "pickup.h"

class Player : public Object, public Collider {
 public:
  Player() : Player(nullptr, nullptr, nullptr, nullptr, 0, 0, 0, 0){};
  Player(Mesh*, Shader*, Mesh*, Shader*, float, float, float, float);
  ~Player();
  void Update(float) override;
  void OnCollisionEnter(const Collider&) override;
  glm::vec3 Move(const Transform&, const std::vector<Obstacle>&,
                 const glm::vec3&);
  void SpawnBullet();

  void setPosition(float, float) override;
  void setScale(float, float) override;

  std::list<Bullet> bullets;
  Mesh* bulletMesh;
  Shader* bulletShader;

  int hp;
  int initialHp;
  int score;
  float fireRate;
  float speed;
  float bulletSpeed;
  float travelDistance;

  float durations[3]{0, 0, 0};
  float sizeDuration;
  float shotgunDuration;
  float fireRateDuration;

 private:
  float timeSinceFired = fireRate;
};
