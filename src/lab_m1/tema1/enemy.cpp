#include "enemy.h"

Enemy::Enemy(Mesh* mesh, Shader* shader, bool canShoot) : Object(mesh, shader) {
  if (canShoot)
    speed = 10 + rand() % (15 - 10);
  else
    speed = 15 + rand() % (20 - 15);
  setScale(1.5f, 1.5f);
  this->canShoot = canShoot;
  timeSinceFired = 0;
  bulletSpeed = 2 * speed;
  travelDistance = 40.f;
  deathAnimation = false;
};

void Enemy::Update(float deltaTime) {
  if (deathAnimation) {
    float rotate = getRotation().x + 17.f * deltaTime;
    float scale = getScale().x - 2 * deltaTime;
    setRotation(rotate);
    setScale(scale, scale);
    if (scale <= 0.1) Destroy();
    return;
  }
  if (canShoot) {
    timeSinceFired += deltaTime;

    bullets.remove_if(
        [](const Bullet& bullet) { return bullet.toDestroy == true; });

    for (Bullet& bullet : bullets) {
      bullet.Update(deltaTime);
      if (bullet.distanceTraveled >= travelDistance) {
        bullet.Destroy();
      }
    }

    if (timeSinceFired >= fireRate) {
      bullets.push_back(Bullet(*this, bulletSpeed, bulletMesh, bulletShader));
      timeSinceFired = 0;
    }
  }
}

void Enemy::Move(const Transform& map, const std::vector<Obstacle>& obstacles,
                 const glm::vec3& playerPos, float deltaTime) {
  if (deathAnimation) return;
  glm::vec3 pos = getPosition();
  glm::vec3 mapPos = map.getPosition();
  glm::vec3 mapScale = map.getScale();
  glm::vec3 colScale = getColScale();

  float rotate = atan2(playerPos.y - pos.y, playerPos.x - pos.x);
  setRotation(rotate);
  float x = speed * deltaTime * cos(rotate);
  float y = speed * deltaTime * sin(rotate);
  glm::vec3 newPos{getColPosition().x + x, getColPosition().y + y, 0};

  if (newPos.x - colScale.x / 2 <= mapPos.x - mapScale.x / 2 + 0.5f) {
    newPos.x -= x;
    x = 0;
  }
  if (newPos.x + colScale.x / 2 >= mapPos.x + mapScale.x / 2 - 0.5f) {
    newPos.x -= x;
    x = 0;
  }
  if (newPos.y + colScale.y / 2 >= mapPos.y + mapScale.y / 2 - 0.5f) {
    newPos.y -= y;
    y = 0;
  }
  if (newPos.y - colScale.y / 2 <= mapPos.y - mapScale.y / 2 + 0.5f) {
    newPos.y -= y;
    y = 0;
  }
  setPosition(pos.x + x, pos.y + y);
}

void Enemy::OnCollisionEnter(const Collider& col) {
  if (!deathAnimation) {
    bullets.clear();
    deathAnimation = true;
  }
}

void Enemy::setPosition(float x, float y) {
  Transform::setPosition(x, y);
  setColPosition(x, y);
}

void Enemy::setScale(float x, float y) {
  Transform::setScale(x, y);
  setColScale(x + 0.5f, y + 0.5f);
}

Enemy::~Enemy(){};