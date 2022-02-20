#pragma once
#include "components/simple_scene.h"
#include "core/gpu/mesh.h"
#include "core/gpu/shader.h"
#include "transform.h";

class Object : public Transform {
 public:
  Object();
  Object(Mesh* mesh, Shader* shader);
  ~Object();

  Mesh* mesh;
  Shader* shader;
  virtual void Update(float);
  void Destroy();
  bool toDestroy;
};