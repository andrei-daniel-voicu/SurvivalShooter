#include "object.h"

Object::Object()
    : Object(nullptr, nullptr){

      };

Object::Object(Mesh* mesh, Shader* shader) {
  this->mesh = mesh;
  this->shader = shader;

  toDestroy = false;
};

Object::~Object(){};

void Object::Update(float deltaTime) {}

void Object::Destroy() { toDestroy = true; }
