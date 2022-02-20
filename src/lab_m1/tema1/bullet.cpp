#include "bullet.h"

#include <iostream>

Bullet::Bullet(const Transform& transform, float speed, Mesh* mesh,
               Shader* shader)
    : Object(mesh, shader) {
  this->setPosition(transform.getPosition().x, transform.getPosition().y);
  this->setRotation(transform.getRotation());
  this->speed = speed;
  this->distanceTraveled = 0;
  setScale(1.2f, 0.5f);
}

void Bullet::Update(float deltaTime) {
  glm::vec3 oldPos, newPos;

  oldPos = getPosition();
  float x = cos(getRotation().x) * speed * deltaTime;
  float y = sin(getRotation().x) * speed * deltaTime;

  newPos.x = oldPos.x + x;
  newPos.y = oldPos.y + y;
  newPos.z = 0;
  oldPos.z = 0;
  distanceTraveled += glm::length(newPos - oldPos);
  setPosition(newPos.x, newPos.y);
}

void Bullet::OnCollisionEnter(const Collider& col) { Destroy(); }

void Bullet::setPosition(float x, float y) {
  Transform::setPosition(x, y);
  setColPosition(x, y);
}

void Bullet::setScale(float x, float y) {
  Transform::setScale(x, y);
  setColScale(x, y);
}