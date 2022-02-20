#pragma once
#include "glm/glm.hpp"

class Transform {
 public:
  Transform() : position{0, 0, 0}, rotation{0, 0, 0}, scale{1, 1, 1} {};
  ~Transform();

 private:
  glm::vec3 position, rotation, scale;

 public:
  glm::vec3 getPosition() const;
  void setPosition(const glm::vec3&);
  virtual void setPosition(float, float);

  glm::vec3 getRotation() const;
  void setRotation(const glm::vec3&);
  virtual void setRotation(float);

  glm::vec3 getScale() const;
  void setScale(const glm::vec3&);
  virtual void setScale(float, float);
};