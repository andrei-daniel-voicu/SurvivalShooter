#include "player.h"

#include <iostream>

Player::Player(Mesh* mesh, Shader* shader, Mesh* bulletMesh,
               Shader* bulletShader, float speed, float travelDistance,
               float fireRate, float bulletSpeed)
    : Object(mesh, shader) {
  this->speed = speed;
  this->fireRate = fireRate;
  this->bulletSpeed = bulletSpeed;
  this->fireRate = fireRate;
  this->bulletMesh = bulletMesh;
  this->bulletShader = bulletShader;
  this->travelDistance = travelDistance;
  timeSinceFired = fireRate;
  score = 0;
  this->initialHp = hp;
  setScale(1, 1);
};

void Player::Update(float deltaTime) {
  for (int i = 0; i < 3; i++) {
    durations[i] -= deltaTime;
    if (durations[i] < 0.f) {
      durations[i] = 0;
    }
  }
  timeSinceFired += deltaTime;

  bullets.remove_if(
      [](const Bullet& bullet) { return bullet.toDestroy == true; });

  for (Bullet& bullet : bullets) {
    bullet.Update(deltaTime);
    if (bullet.distanceTraveled >= travelDistance) {
      bullet.Destroy();
    }
  }
}

void Player::SpawnBullet() {
  float fire = durations[static_cast<int>(Pickup::Type::FIRE_RATE) - 1] > 0.f
                   ? 0.2f
                   : fireRate;

  if (timeSinceFired >= fire) {
    timeSinceFired = 0;
    Bullet bullet = Bullet(*this, bulletSpeed, bulletMesh, bulletShader);
    if (durations[static_cast<int>(Pickup::Type::SIZE) - 1] > 0.f) {
      bullet.setScale(2 * bullet.getScale().x, 2 * bullet.getScale().y);
    }
    bullets.push_back(bullet);
    if (durations[static_cast<int>(Pickup::Type::SHOTGUN) - 1]) {
      float rot = bullet.getRotation().x;
      bullet.setPosition(bullet.getPosition().x + 0.5f, bullet.getPosition().y);
      bullet.setRotation(rot - RADIANS(45 / 2.f));
      bullets.push_back(bullet);
      bullet.setPosition(bullet.getPosition().x - 1.f, bullet.getPosition().y);
      bullet.setRotation(rot + RADIANS(45 / 2.f));
      bullets.push_back(bullet);
    }
  }
}

glm::vec3 Player::Move(const Transform& map,
                       const std::vector<Obstacle>& obstacles,
                       const glm::vec3& dir) {
  glm::vec3 newPos = getColPosition() + dir;
  glm::vec3 mapPos = map.getPosition();
  glm::vec3 mapScale = map.getScale();
  glm::vec3 newDir = dir;
  glm::vec3 colScale = getColScale();

  if (newPos.x - colScale.x / 2 <= mapPos.x - mapScale.x / 2 + 0.5f) {
    newPos.x -= dir.x;
    newDir.x = 0;
  }
  if (newPos.x + colScale.x / 2 >= mapPos.x + mapScale.x / 2 - 0.5f) {
    newPos.x -= dir.x;
    newDir.x = 0;
  }
  if (newPos.y + colScale.y / 2 >= mapPos.y + mapScale.y / 2 - 0.5f) {
    newPos.y -= dir.y;
    newDir.y = 0;
  }
  if (newPos.y - colScale.y / 2 <= mapPos.y - mapScale.y / 2 + 0.5f) {
    newPos.y -= dir.y;
    newDir.y = 0;
  }
  for (const Obstacle& obs : obstacles) {
    if (CheckCollision(obs.getColPosition(), obs.getColScale(), newPos,
                       colScale)) {
      glm::vec3 obsPos = obs.getColPosition();
      glm::vec3 obsScale = obs.getColScale();
      if (newPos.x - colScale.x / 2 <= obsPos.x - obsScale.x / 2) {
        newPos.x -= dir.x;
        newDir.x = 0;
      }
      if (newPos.x + colScale.x / 2 >= obsPos.x + obsScale.x / 2) {
        newPos.x -= dir.x;
        newDir.x = 0;
      }
      if (newPos.y + colScale.y / 2 >= obsPos.y + obsScale.y / 2) {
        newPos.y -= dir.y;
        newDir.y = 0;
      }
      if (newPos.y - colScale.y / 2 <= obsPos.y + obsScale.y / 2) {
        newPos.y -= dir.y;
        newDir.y = 0;
      }
    }
  }
  setPosition(getPosition().x + newDir.x, getPosition().y + newDir.y);
  return newDir;
}

void Player::OnCollisionEnter(const Collider& col) {
  if (dynamic_cast<const Enemy*>(&col) != nullptr) {
    hp--;
  } else if (dynamic_cast<const Pickup*>(&col) != nullptr) {
    const Pickup* pickup = dynamic_cast<const Pickup*>(&col);
    switch (pickup->type) {
      case Pickup::Type::HEAL:
        hp++;
        break;
      default:
        durations[static_cast<int>(pickup->type) - 1] = pickup->duration;
        break;
    }

  } else if (dynamic_cast<const Bullet*>(&col) != nullptr) {
    hp--;
  }
}

void Player::setPosition(float x, float y) {
  Transform::setPosition(x, y);
  setColPosition(x, y);
}

void Player::setScale(float x, float y) {
  Transform::setScale(x, y);
  setColScale(x + 0.5f, y + 0.5f);
}

Player::~Player(){};