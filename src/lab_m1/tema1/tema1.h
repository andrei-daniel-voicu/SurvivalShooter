#pragma once

#include "components/simple_scene.h"
#include "enemy.h"
#include "obstacle.h"
#include "pickup.h"
#include "player.h"

namespace m1 {
class Tema1 : public gfxc::SimpleScene {
 public:
  struct ViewportSpace {
    ViewportSpace() : x(0), y(0), width(1), height(1) {}
    ViewportSpace(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}
    int x;
    int y;
    int width;
    int height;
  };

  struct LogicSpace {
    LogicSpace() : x(0), y(0), width(1), height(1) {}
    LogicSpace(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}
    float x;
    float y;
    float width;
    float height;
  };

 public:
  Tema1();
  ~Tema1();

  void Init() override;

 private:
  void FrameStart() override;
  void Update(float deltaTimeSeconds) override;
  void FrameEnd() override;

  void DrawScene(const glm::mat3& visMatrix);
  void DrawMinimap(const glm::mat3& visMatrix);
  void DrawPlayer(const glm::mat3& visMatrix);
  void DrawEnemies(const glm::mat3& visMatrix);
  void DrawUI(const glm::mat3& visMatrix);
  void DrawMap(const glm::mat3& visMatrix);
  void DrawBullets(const glm::mat3& visMatrix);
  void DrawPickups(const glm::mat3& visMatrix);

  void OnInputUpdate(float deltaTime, int mods) override;
  void OnKeyPress(int key, int mods) override;
  void OnKeyRelease(int key, int mods) override;
  void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
  void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
  void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

  glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace,
                                  const ViewportSpace& viewSpace);
  glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace,
                                      const ViewportSpace& viewSpace);

  void SetViewportArea(const ViewportSpace& viewSpace,
                       glm::vec3 colorColor = glm::vec3(0), bool clear = true);

 protected:
  ViewportSpace viewSpace;
  LogicSpace logicSpace;
  LogicSpace miniLogicSpace;
  glm::mat3 modelMatrix, visMatrix;

 private:
  Player player;
  std::list<Enemy> enemies;
  Object map, mapBorder, hp, hpBorder;
  float initialHpScale;

  std::vector<Obstacle> obstacles;
  std::list<Pickup> pickups;

  float spawnRate;
  float timeSinceSpawn;
  float spawnNr;

  void SpawnEnemies();
  void SpawnPickups();
  void GenerateScene();
  void CheckCollisions();

  Mesh* GenerateCircle(const std::string&, const glm::vec3&, float, int, float,
                       bool);
  Mesh* GenerateSquare(const std::string&, const glm::vec3&, float, float,
                       bool);
};
}  // namespace m1
