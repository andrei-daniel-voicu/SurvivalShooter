#include "lab_m1/tema1/tema1.h"

#include <iostream>
#include <vector>

#include "lab_m1/tema1/transform2D.h"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Tema1::Tema1() : player(){};

Tema1::~Tema1() {}

void Tema1::Init() {
  auto camera = GetSceneCamera();
  camera->SetPosition(glm::vec3(0, 0, 50));
  camera->SetRotation(glm::vec3(0, 0, 0));
  camera->Update();
  GetCameraInput()->SetActive(false);

  logicSpace.x = 0;        // logic x
  logicSpace.y = 0;        // logic y
  logicSpace.width = 20;   // logic width
  logicSpace.height = 20;  // logic height

  miniLogicSpace.width = 45;
  miniLogicSpace.height = 45;
  miniLogicSpace.x = -miniLogicSpace.width / 2;
  miniLogicSpace.y = -miniLogicSpace.height / 2;
  {
    Mesh* mesh = GenerateSquare("map", glm::vec3(131 / 255.f), 1, 0, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("mapBorder",
                                glm::vec3(59 / 255.f, 227 / 255.f, 107 / 255.f),
                                1, -0.1, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("obstacle",
                                glm::vec3(59 / 255.f, 227 / 255.f, 107 / 255.f),
                                1, 0.1, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("bullet", glm::vec3(0), 1, 0.1, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("bullet_enemy", glm::vec3(1), 1, 0.1, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare(
        "enemy", glm::vec3(187 / 255.f, 27 / 255.f, 67 / 255.f), 1, 0.2, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("pickup_fire_rate", glm::vec3(0.f, 0.f, 1.f), 1,
                                0.2, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh =
        GenerateSquare("pickup_size", glm::vec3(0.f, 1.f, 0.f), 1, 0.2, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("pickup_shotgun", glm::vec3(1.f, 1.f, 0.3f), 1,
                                0.2, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("enemy_outline", glm::vec3(0), 1, 0.15, true);
    AddMeshToList(mesh);
  }

  {
    Mesh* mesh = GenerateSquare("enemy_mini",
                                glm::vec3(187 / 255.f, 27 / 255.f, 67 / 255.f),
                                1, 0.4, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh =
        GenerateSquare("enemy_mini_outline", glm::vec3(0), 1, 0.3, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("enemy_advanced",
                                glm::vec3(35 / 255.f, 38 / 255.f, 211 / 255.f),
                                1, 0.2, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("enemy_advanced_mini",
                                glm::vec3(35 / 255.f, 38 / 255.f, 211 / 255.f),
                                1, 0.4, true);
    AddMeshToList(mesh);
  }

  {
    Mesh* mesh = GenerateCircle(
        "player", glm::vec3(243 / 255.f, 203 / 255.f, 107 / 255.f), 1, 30, 0.2,
        true);
    AddMeshToList(mesh);
  }

  {
    Mesh* mesh =
        GenerateCircle("player_outline", glm::vec3(0), 1, 30, 0.1, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateCircle(
        "player_mini", glm::vec3(243 / 255.f, 203 / 255.f, 107 / 255.f), 1, 30,
        0.4, true);
    AddMeshToList(mesh);
  }

  {
    Mesh* mesh =
        GenerateCircle("player_mini_outline", glm::vec3(0), 1, 30, 0.3, true);
    AddMeshToList(mesh);
  }

  {
    Mesh* mesh = GenerateSquare(
        "hp", glm::vec3(203 / 255.f, 3 / 255.f, 3 / 255.f), 1, 30, true);
    AddMeshToList(mesh);
  }
  {
    Mesh* mesh = GenerateSquare("hp_outline",
                                glm::vec3(203 / 255.f, 3 / 255.f, 3 / 255.f), 1,
                                30, false);
    AddMeshToList(mesh);
  }

  {
    map.setScale(3 * logicSpace.width, 2 * logicSpace.height);
    map.mesh = meshes["map"];
    map.shader = shaders["VertexColor"];

    mapBorder.mesh = meshes["mapBorder"];
    mapBorder.shader = shaders["VertexColor"];
    mapBorder.setScale(map.getScale().x + 1, map.getScale().y + 1);
    mapBorder.setPosition(map.getPosition());
  }
  {
    hp.setScale(logicSpace.width / 1.5f, logicSpace.height / 10);
    hp.setPosition(logicSpace.width,
                   logicSpace.height - hp.getScale().y / 2 - 0.5f);
    hp.mesh = meshes["hp"];
    hp.shader = shaders["VertexColor"];

    hpBorder.setScale(hp.getScale().x, hp.getScale().y);
    hpBorder.setPosition(logicSpace.width,
                         logicSpace.height - hp.getScale().y / 2 - 0.5f);
    hpBorder.mesh = meshes["hp_outline"];
    hpBorder.shader = shaders["VertexColor"];
    initialHpScale = hp.getScale().x;
  }
  {
    player.setPosition(logicSpace.width / 2, logicSpace.height / 2);
    player.mesh = meshes["player"];
    player.shader = shaders["VertexColor"];
    player.speed = 20.f;
    player.fireRate = 0.5f;
    player.hp = 10;
    player.initialHp = player.hp;

    player.bulletMesh = meshes["bullet"];
    player.bulletShader = shaders["VertexColor"];
    player.bulletSpeed = 40.f;
    player.travelDistance = 20.f;
  }
  {
    spawnRate = 4.f;
    spawnNr = 4;
    timeSinceSpawn = 0;
  }
  srand(time(NULL));
  GenerateScene();
}

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace,
                                       const ViewportSpace& viewSpace) {
  float sx, sy, tx, ty;
  sx = viewSpace.width / logicSpace.width;
  sy = viewSpace.height / logicSpace.height;
  tx = viewSpace.x - sx * logicSpace.x;
  ty = viewSpace.y - sy * logicSpace.y;

  return glm::transpose(
      glm::mat3(sx, 0.0f, tx, 0.0f, sy, ty, 0.0f, 0.0f, 1.0f));
}

// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace,
                                           const ViewportSpace& viewSpace) {
  float sx, sy, tx, ty, smin;
  sx = viewSpace.width / logicSpace.width;
  sy = viewSpace.height / logicSpace.height;
  if (sx < sy)
    smin = sx;
  else
    smin = sy;
  tx = viewSpace.x - smin * logicSpace.x +
       (viewSpace.width - smin * logicSpace.width) / 2;
  ty = viewSpace.y - smin * logicSpace.y +
       (viewSpace.height - smin * logicSpace.height) / 2;

  return glm::transpose(
      glm::mat3(smin, 0.0f, tx, 0.0f, smin, ty, 0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace,
                            glm::vec3 colorColor, bool clear) {
  glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

  glEnable(GL_SCISSOR_TEST);
  glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

  // Clears the color buffer (using the previously set color) and depth buffer
  glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_SCISSOR_TEST);

  GetSceneCamera()->SetOrthographic(
      (float)viewSpace.x, (float)(viewSpace.x + viewSpace.width),
      (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
  GetSceneCamera()->Update();
}

void Tema1::FrameStart() {
  // Clears the color buffer (using the previously set color) and depth buffer
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema1::Update(float deltaTimeSeconds) {
  if (player.hp <= 0) {
    window->Close();
  }

  glm::ivec2 resolution = window->GetResolution();

  viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
  SetViewportArea(viewSpace, glm::vec3{0.2f, 0.2f, 0.2f}, true);

  visMatrix = glm::mat3(1);
  visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

  timeSinceSpawn += deltaTimeSeconds;
  if (timeSinceSpawn >= spawnRate) {
    timeSinceSpawn = 0;
    SpawnEnemies();
    SpawnPickups();
  }

  // call updates
  player.Update(deltaTimeSeconds);
  std::for_each(enemies.begin(), enemies.end(), [&](Enemy& enemy) {
    enemy.Update(deltaTimeSeconds);
    enemy.Move(map, obstacles, player.getPosition(), deltaTimeSeconds);
  });

  // check collisions
  CheckCollisions();

  // remove entities
  enemies.remove_if([](const Enemy& enemy) { return enemy.toDestroy == true; });
  pickups.remove_if(
      [](const Pickup& pickup) { return pickup.toDestroy == true; });

  // draw scene
  DrawScene(visMatrix);

  viewSpace = ViewportSpace(resolution.x - resolution.x / 4, 0,
                            resolution.x / 4, resolution.y / 4);
  SetViewportArea(viewSpace, glm::vec3{0.2f, 0.2f, 0.2f}, true);
  visMatrix = glm::mat3(1);
  visMatrix *= VisualizationTransf2DUnif(miniLogicSpace, viewSpace);
  DrawMinimap(visMatrix);
}

void Tema1::FrameEnd() {}

void Tema1::DrawMinimap(const glm::mat3& visMatrix) {
  // draw map
  DrawMap(visMatrix);

  // draw player
  DrawPlayer(visMatrix);

  // draw enemies
  DrawEnemies(visMatrix);

  // draw pickups
  DrawPickups(visMatrix);
}

void Tema1::DrawScene(const glm::mat3& visMatrix) {
  // draw background + obstacles
  DrawMap(visMatrix);

  // draw player
  DrawPlayer(visMatrix);

  // draw enemies
  DrawEnemies(visMatrix);

  // draw bullets
  DrawBullets(visMatrix);

  // draw pickups
  DrawPickups(visMatrix);

  // draw hp
  DrawUI(visMatrix);
}

void m1::Tema1::DrawPlayer(const glm::mat3& visMatrix) {
  glm::mat3 center;

  modelMatrix = visMatrix;
  modelMatrix *=
      transform2D::Translate(player.getPosition().x, player.getPosition().y);
  modelMatrix *= transform2D::Rotate(player.getRotation().x);
  modelMatrix *= transform2D::Scale(player.getScale().x, player.getScale().y);
  center = modelMatrix;
  RenderMesh2D(player.mesh, player.shader, modelMatrix);
  modelMatrix *= transform2D::Scale(1.1f, 1.1f);
  RenderMesh2D(meshes["player_outline"], shaders["VertexColor"], modelMatrix);

  modelMatrix = center;
  modelMatrix *= transform2D::Translate(1.f, 0.5f);
  modelMatrix *= transform2D::Scale(0.3f, 0.3f);
  RenderMesh2D(meshes["player_mini"], shaders["VertexColor"], modelMatrix);
  modelMatrix *= transform2D::Scale(1.2f, 1.2f);
  RenderMesh2D(meshes["player_mini_outline"], shaders["VertexColor"],
               modelMatrix);

  modelMatrix = center;
  modelMatrix *= transform2D::Translate(1.f, -0.5f);
  modelMatrix *= transform2D::Scale(0.3f, 0.3f);
  RenderMesh2D(meshes["player_mini"], shaders["VertexColor"], modelMatrix);
  modelMatrix *= transform2D::Scale(1.2f, 1.2f);
  RenderMesh2D(meshes["player_mini_outline"], shaders["VertexColor"],
               modelMatrix);
}

void m1::Tema1::DrawEnemies(const glm::mat3& visMatrix) {
  glm::mat3 center;

  for (const Enemy& enemy : enemies) {
    modelMatrix = visMatrix;
    modelMatrix *=
        transform2D::Translate(enemy.getPosition().x, enemy.getPosition().y);
    modelMatrix *= transform2D::Rotate(enemy.getRotation().x);
    modelMatrix *= transform2D::Scale(enemy.getScale().x, enemy.getScale().y);
    center = modelMatrix;
    RenderMesh2D(enemy.mesh, enemy.shader, modelMatrix);
    modelMatrix *= transform2D::Scale(1.1f, 1.1f);
    RenderMesh2D(meshes["enemy_outline"], shaders["VertexColor"], modelMatrix);
    modelMatrix = center;
    modelMatrix *= transform2D::Translate(0.5f, 0.5f);
    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
    if (enemy.canShoot)
      RenderMesh2D(meshes["enemy_advanced_mini"], shaders["VertexColor"],
                   modelMatrix);
    else
      RenderMesh2D(meshes["enemy_mini"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(1.3f, 1.3f);
    RenderMesh2D(meshes["enemy_mini_outline"], shaders["VertexColor"],
                 modelMatrix);
    modelMatrix = center;
    modelMatrix *= transform2D::Translate(0.5f, -0.5f);
    modelMatrix *= transform2D::Scale(0.3f, 0.3f);
    if (enemy.canShoot)
      RenderMesh2D(meshes["enemy_advanced_mini"], shaders["VertexColor"],
                   modelMatrix);
    else
      RenderMesh2D(meshes["enemy_mini"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(1.3f, 1.3f);
    RenderMesh2D(meshes["enemy_mini_outline"], shaders["VertexColor"],
                 modelMatrix);
  }
}

void m1::Tema1::DrawUI(const glm::mat3& visMatrix) {
  modelMatrix = visMatrix;
  modelMatrix *= transform2D::Translate(hp.getPosition().x, hp.getPosition().y);
  modelMatrix *=
      transform2D::Translate((initialHpScale - hp.getScale().x) / 2, 0);
  modelMatrix *= transform2D::Scale(hp.getScale().x, hp.getScale().y);
  RenderMesh2D(hp.mesh, hp.shader, modelMatrix);

  modelMatrix = visMatrix;
  modelMatrix *= transform2D::Translate(hpBorder.getPosition().x,
                                        hpBorder.getPosition().y);
  modelMatrix *=
      transform2D::Scale(hpBorder.getScale().x, hpBorder.getScale().y);
  RenderMesh2D(hpBorder.mesh, hpBorder.shader, modelMatrix);
}

void m1::Tema1::DrawMap(const glm::mat3& visMatrix) {
  modelMatrix = visMatrix;
  modelMatrix *=
      transform2D::Translate(map.getPosition().x, map.getPosition().y);
  modelMatrix *= transform2D::Scale(map.getScale().x, map.getScale().y);
  RenderMesh2D(map.mesh, map.shader, modelMatrix);
  modelMatrix = visMatrix;
  modelMatrix *= transform2D::Translate(mapBorder.getPosition().x,
                                        mapBorder.getPosition().y);
  modelMatrix *=
      transform2D::Scale(mapBorder.getScale().x, mapBorder.getScale().y);
  RenderMesh2D(mapBorder.mesh, mapBorder.shader, modelMatrix);

  for (const Object& obj : obstacles) {
    modelMatrix = visMatrix;
    modelMatrix *=
        transform2D::Translate(obj.getPosition().x, obj.getPosition().y);
    modelMatrix *= transform2D::Scale(obj.getScale().x, obj.getScale().y);
    RenderMesh2D(obj.mesh, obj.shader, modelMatrix);
  }
}

void m1::Tema1::DrawBullets(const glm::mat3& visMatrix) {
  // draw player bullets
  for (const Bullet& bullet : player.bullets) {
    modelMatrix = visMatrix;
    modelMatrix *=
        transform2D::Translate(bullet.getPosition().x, bullet.getPosition().y);
    modelMatrix *= transform2D::Rotate(bullet.getRotation().x);
    modelMatrix *= transform2D::Scale(bullet.getScale().x, bullet.getScale().y);
    RenderMesh2D(bullet.mesh, bullet.shader, modelMatrix);
  }

  // draw enemy bullets
  for (const Enemy& enemy : enemies) {
    for (const Bullet& bullet : enemy.bullets) {
      modelMatrix = visMatrix;
      modelMatrix *= transform2D::Translate(bullet.getPosition().x,
                                            bullet.getPosition().y);
      modelMatrix *= transform2D::Rotate(bullet.getRotation().x);
      modelMatrix *=
          transform2D::Scale(bullet.getScale().x, bullet.getScale().y);
      RenderMesh2D(bullet.mesh, bullet.shader, modelMatrix);
    }
  }
}

void m1::Tema1::DrawPickups(const glm::mat3& visMatrix) {
  glm::mat3 center;

  for (const Pickup& pickup : pickups) {
    modelMatrix = visMatrix;
    modelMatrix *=
        transform2D::Translate(pickup.getPosition().x, pickup.getPosition().y);
    modelMatrix *= transform2D::Rotate(pickup.getRotation().x);
    center = modelMatrix;
    modelMatrix *=
        transform2D::Scale(pickup.getScale().x * 2, 0.5f * pickup.getScale().y);
    RenderMesh2D(pickup.mesh, pickup.shader, modelMatrix);
    modelMatrix = center * transform2D::Scale(0.5f * pickup.getScale().x,
                                              pickup.getScale().y * 2);
    RenderMesh2D(pickup.mesh, pickup.shader, modelMatrix);
  }
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Tema1::OnInputUpdate(float deltaTime, int mods) {
  if (deltaTime == INFINITY) return;

  glm::vec3 dir{0, 0, 0};
  glm::vec3 move{0, 0, 0};

  if (window->KeyHold(GLFW_KEY_W)) dir += glm::vec3_up;
  if (window->KeyHold(GLFW_KEY_S)) dir += glm::vec3_down;
  if (window->KeyHold(GLFW_KEY_A)) dir += glm::vec3_left;
  if (window->KeyHold(GLFW_KEY_D)) dir += glm::vec3_right;

  if (dir == glm::vec3{0, 0, 0}) return;
  dir = glm::normalize(dir);
  move = dir * player.speed * deltaTime;

  glm::vec3 newMove{0, 0, 0};
  newMove = player.Move(map, obstacles, move);
  if (newMove == glm::vec3{0, 0, 0}) return;
  logicSpace.x += newMove.x;
  logicSpace.y += newMove.y;
  hp.setPosition(hp.getPosition().x + newMove.x,
                 hp.getPosition().y + newMove.y);
  hpBorder.setPosition(hpBorder.getPosition().x + newMove.x,
                       hpBorder.getPosition().y + newMove.y);
}

void Tema1::SpawnEnemies() {
  for (int i = 0; i < spawnNr; i++) {
    float x = -map.getScale().x / 2 + rand() % ((int)map.getScale().x);
    float y = -map.getScale().y / 2 + rand() % ((int)map.getScale().y);

    bool canShoot = rand() % 2;
    if (canShoot) {
      Enemy enemy(meshes["enemy_advanced"], shaders["VertexColor"], canShoot);
      enemy.setPosition(x, y);
      enemy.bulletMesh = meshes["bullet_enemy"];
      enemy.bulletShader = shaders["VertexColor"];
      enemy.bulletSpeed = enemy.speed + 20.f +
                          static_cast<float>(rand()) /
                              (static_cast<float>(RAND_MAX / (30.f - 20.f)));
      enemy.fireRate =
          0.3f + static_cast<float>(rand()) /
                     (static_cast<float>(RAND_MAX / (0.6f - 0.3f)));
      enemies.push_back(enemy);
    } else {
      Enemy enemy(meshes["enemy"], shaders["VertexColor"], canShoot);
      enemy.setPosition(x, y);
      enemies.push_back(enemy);
    }
  }
}

void m1::Tema1::SpawnPickups() {
  for (int i = 0; i < 2; i++) {
    float x = -map.getScale().x / 2 + rand() % ((int)map.getScale().x);
    float y = -map.getScale().y / 2 + rand() % ((int)map.getScale().y);

    Pickup::Type type =
        static_cast<Pickup::Type>((rand() % ((int)Pickup::Type::SIZE + 1)));
    Pickup pickup(meshes["enemy"], shaders["VertexColor"], type);

    switch (type) {
      case Pickup::Type::FIRE_RATE:
        pickup.mesh = meshes["pickup_fire_rate"];
        pickup.duration = spawnRate + 4.f;
        break;
      case Pickup::Type::SHOTGUN:
        pickup.mesh = meshes["pickup_shotgun"];
        pickup.duration = spawnRate + 3.f;
        break;
      case Pickup::Type::SIZE:
        pickup.mesh = meshes["pickup_size"];
        pickup.duration = spawnRate + 6.f;
        break;
      default:
        break;
    }

    pickup.setPosition(x, y);
    pickups.push_back(pickup);
  }
}

void Tema1::GenerateScene() {
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(2, 2);
    obj.setScale(2, 8);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(-18, 5);
    obj.setScale(8, 5);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(-13, -10);
    obj.setScale(10, 2);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(-5, -15);
    obj.setScale(2, 10);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(-5, 15);
    obj.setScale(4, 10);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(10, -15);
    obj.setScale(2, 10);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(-5, -15);
    obj.setScale(2, 10);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(15, -15);
    obj.setScale(8, 1);
    obstacles.push_back(obj);
  }
  {
    Obstacle obj(meshes["obstacle"], shaders["VertexColor"]);
    obj.setPosition(30, -30);
    obj.setScale(8, 1);
    obstacles.push_back(obj);
  }
}

void Tema1::CheckCollisions() {
  glm::vec3 mapPos = map.getPosition();
  glm::vec3 mapScale = map.getScale();
  glm::vec3 playerPos = player.getColPosition();
  glm::vec3 playerScale = player.getColScale();

  // player bullet collisions
  for (Bullet& bullet : player.bullets) {
    glm::vec3 bulletPos = bullet.getColPosition();
    glm::vec3 bulletScale = bullet.getColScale();

    // bullet - map border
    if (bulletPos.x - bulletScale.x / 2 <= mapPos.x - mapScale.x / 2 + 0.5f) {
      bullet.Destroy();
      continue;
    }
    if (bulletPos.x + bulletScale.x / 2 >= mapPos.x + mapScale.x / 2 - 0.5f) {
      bullet.Destroy();
      continue;
    }
    if (bulletPos.y + bulletScale.y / 2 >= mapPos.y + mapScale.y / 2 - 0.5f) {
      bullet.Destroy();
      continue;
    }
    if (bulletPos.y - bulletScale.y / 2 <= mapPos.y - mapScale.y / 2 + 0.5f) {
      bullet.Destroy();
      continue;
    }

    // bullet - enemies
    bool ok = false;
    for (Enemy& enemy : enemies) {
      if (enemy.deathAnimation) continue;
      if (bullet.CheckCollision(bulletPos, bulletScale, enemy.getColPosition(),
                                enemy.getColScale())) {
        player.score++;
        std::cout << "\033[1;31m\nYOUR SCORE IS " << player.score
                  << ".\n\033[0m";
        enemy.OnCollisionEnter(bullet);
        bullet.OnCollisionEnter(enemy);
        ok = true;
        break;
      }
    }

    if (ok) continue;

    // bullet - obstacles
    for (Obstacle& obs : obstacles) {
      if (bullet.CheckCollision(obs.getColPosition(), obs.getColScale(),
                                bulletPos, bulletScale)) {
        obs.OnCollisionEnter(bullet);
        bullet.OnCollisionEnter(obs);
        break;
      }
    }
  }

  // enemy bullet collision
  for (Enemy& enemy : enemies) {
    for (Bullet& bullet : enemy.bullets) {
      glm::vec3 bulletPos = bullet.getColPosition();
      glm::vec3 bulletScale = bullet.getColScale();

      // bullet - map border
      if (bulletPos.x - bulletScale.x / 2 <= mapPos.x - mapScale.x / 2 + 0.5f) {
        bullet.Destroy();
        continue;
      }
      if (bulletPos.x + bulletScale.x / 2 >= mapPos.x + mapScale.x / 2 - 0.5f) {
        bullet.Destroy();
        continue;
      }
      if (bulletPos.y + bulletScale.y / 2 >= mapPos.y + mapScale.y / 2 - 0.5f) {
        bullet.Destroy();
        continue;
      }
      if (bulletPos.y - bulletScale.y / 2 <= mapPos.y - mapScale.y / 2 + 0.5f) {
        bullet.Destroy();
        continue;
      }

      // bullet - obstacles
      for (Obstacle& obs : obstacles) {
        if (bullet.CheckCollision(obs.getColPosition(), obs.getColScale(),
                                  bulletPos, bulletScale)) {
          obs.OnCollisionEnter(bullet);
          bullet.OnCollisionEnter(obs);
          break;
        }
      }

      // bullet - player
      if (bullet.CheckCollision(bullet.getColPosition(), bullet.getColScale(),
                                playerPos, playerScale)) {
        player.OnCollisionEnter(bullet);
        hp.setScale(player.hp * initialHpScale / player.initialHp,
                    hp.getScale().y);
        bullet.OnCollisionEnter(player);
      }
    }

    // enemy - player collision
    if (enemy.deathAnimation) continue;
    if (enemy.CheckCollision(playerPos, playerScale, enemy.getColPosition(),
                             enemy.getColScale())) {
      enemy.OnCollisionEnter(player);
      player.OnCollisionEnter(enemy);
      hp.setScale(player.hp * initialHpScale / player.initialHp,
                  hp.getScale().y);
      break;
    }
  }

  // player - pickups
  for (Pickup& pickup : pickups) {
    if (pickup.CheckCollision(pickup.getColPosition(), pickup.getColScale(),
                              playerPos, playerScale)) {
      pickup.OnCollisionEnter(player);
      player.OnCollisionEnter(pickup);
      hp.setScale(player.hp * initialHpScale / player.initialHp,
                  hp.getScale().y);
    }
  }
}

Mesh* Tema1::GenerateCircle(const std::string& name, const glm::vec3& color,
                            float r, int no_sides, float depth, bool fill) {
  vector<VertexFormat> vertices;
  vector<unsigned int> indices;

  vertices.push_back({glm::vec3(0, 0, depth), color, glm::vec3(0.2, 0.8, 0.6)});

  for (int i = 1; i < no_sides + 2; i++) {
    float x, y;
    x = r * cos(i * 2 * M_PI / no_sides + M_PI / 4);
    y = r * sin(i * 2 * M_PI / no_sides + M_PI / 4);

    vertices.push_back(
        {glm::vec3(x, y, depth), color, glm::vec3(0.2, 0.8, 0.6)});
  }
  for (int i = 0; i < vertices.size(); i++) {
    indices.push_back(i);
  }
  Mesh* circle = new Mesh(name);

  if (!fill) {
    vertices.erase(vertices.begin());
    indices.erase(indices.begin());
    vertices.push_back(*vertices.begin());
    indices.push_back(*indices.begin());
    circle->SetDrawMode(GL_LINE_LOOP);
  } else
    circle->SetDrawMode(GL_TRIANGLE_FAN);
  circle->InitFromData(vertices, indices);

  return circle;
}

Mesh* Tema1::GenerateSquare(const std::string& name, const glm::vec3& color,
                            float length, float depth, bool fill) {
  return GenerateCircle(name, color, length * sqrt(2) / 2, 4, depth, fill);
}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {
  // Add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
  // Add mouse move event
  glm::ivec2 resolution = window->GetResolution();

  float rotate = -atan2((float)mouseY - ((float)resolution.y / 2),
                        (float)mouseX - ((float)resolution.x / 2));
  player.setRotation(rotate);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
  player.SpawnBullet();
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
  // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}
