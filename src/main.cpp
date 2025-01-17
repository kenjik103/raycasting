#include "raylib.h"
#include "textures.h"

#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "raylib.h"

constexpr size_t mapWidth{24};
constexpr size_t mapHeight{24};
constexpr int texWidth{64};
constexpr int texHeight{64};
constexpr int screenWidth{640};
constexpr int screenHeight{480};

constexpr float speedModifier{0.04f};
constexpr float rotationModifier{0.009f};

constexpr std::array<std::array<int, mapWidth>, mapHeight> worldMap = {
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}};

struct Player {
  Vector2 pos;
  Vector2 dir;
  Vector2 plane;
};

const char *textureFiles[]{
    "textures/eagle.png",       "textures/redbrick.png",
    "textures/purplestone.png", "textures/greystone.png",
    "textures/bluestone.png",   "textures/mossy.png",
    "textures/wood.png",        "textures/colorstone.png",
};

void rotateVector(Vector2 &v, float theta) {
  v.x = cos(theta) * v.x - sin(theta) * v.y;
  v.y = sin(theta) * v.x + cos(theta) * v.y;
}

int main(void) {
  InitWindow(screenWidth, screenHeight, "Raycast");
  Player player{{22, 12}, {-1, 0}, {0, 0.66}};
  // intitialize textures
  Textures textures;
  size_t numTextures = sizeof(textureFiles) / sizeof(textureFiles[0]);
  textures.initialize(textureFiles, numTextures);

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  BeginDrawing();
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    for (int x{}; x < screenWidth; ++x) {
      float cameraX{
          // a range [-1,1] representing where on our camera plane we are
          2 * x / static_cast<float>(screenWidth) - 1};
      Vector2 rayDir{player.dir.x + player.plane.x * cameraX,
                     player.dir.y + player.plane.y * cameraX};

      // ++++++++++++++++++++++++++ DDA ALGORITHM ++++++++++++++++++++++++++++
      // the final length of our ray
      Vector2 rayMagnitude{};

      // given a ray, for every 1 step on y, x steps rayDir.x and vice virsa
      Vector2 stepSize{// avoid 0 division issues
                       (rayDir.x == 0) ? (1e30f) : std::abs(1 / rayDir.x),
                       (rayDir.y == 0) ? (1e30f) : std::abs(1 / rayDir.y)};

      // player pos -> map index
      assert(player.pos.x >= 0 && player.pos.y >= 0);
      size_t mapX = static_cast<size_t>(player.pos.x);
      size_t mapY = static_cast<size_t>(player.pos.y);

      // steps will be 1, -1, or 0 depending on players look direction.
      int stepX{};
      int stepY{};

      // have we hit a wall
      bool hit{false};

      int side{};

      // initial side distance
      if (rayDir.x < 0) {
        stepX = -1;
        rayMagnitude.x = (player.pos.x - mapX) * stepSize.x;
      } else {
        stepX = 1;
        rayMagnitude.x = (1.f + mapX - player.pos.x) * stepSize.x;
      }
      if (rayDir.y < 0) {
        stepY = -1;
        rayMagnitude.y = (player.pos.y - mapY) * stepSize.y;
      } else {
        stepY = 1;
        rayMagnitude.y = (1.f + mapY - player.pos.y) * stepSize.y;
      }

      while (!hit) {
        if (rayMagnitude.x < rayMagnitude.y) {
          rayMagnitude.x += stepSize.x;
          mapX += static_cast<size_t>(stepX);
          side = 0;
        } else {
          rayMagnitude.y += stepSize.y;
          mapY += static_cast<size_t>(stepY);
          side = 1;
        }
        if (worldMap[mapY][mapX] > 0) {
          hit = true;
        }
      }

      //++++++++++++++++++++++++++DRAWING+++++++++++++++++++++++++++++++++++

      // get fisheye corrected wall distance
      float camToWallDist{(side == 0) ? (rayMagnitude.x - stepSize.x)
                                      : (rayMagnitude.y - stepSize.y)};
      // get wall height
      int wallHeight = static_cast<int>(screenHeight / camToWallDist);

      // calculate bottom and top of wall
      int wallTop{(screenHeight / 2) - (wallHeight / 2)};
      if (wallTop < 0) {
        wallTop = 0;
      }

      int wallBottom{(screenHeight / 2) + (wallHeight / 2)};
      if (wallBottom >= screenHeight) {
        wallBottom = screenHeight - 1;
      }
      [[maybe_unused]] size_t texCoord{static_cast<size_t>(worldMap[mapY][mapX] - 1)};

      // calculate ray position on wall
      double wallX{};
      if (side == 0) {
        wallX = player.pos.x + rayDir.x * camToWallDist;
      } else {
        wallX = player.pos.y + rayDir.y * camToWallDist;
      }
      wallX -= std::floor(wallX); // extract the frational bit

      // convert wall position to texture
      [[maybe_unused]] int texX{static_cast<int>(texWidth * wallX)};
      if (side == 0 && rayDir.x > 0) {
        texX = texWidth - texX - 1; // flip
      }
      if (side == 1 && rayDir.y < 0) {
        texX = texWidth - texX - 1; // flip
      }

      double step{1.0 * texHeight / wallHeight};
      double texPos{(wallTop - screenHeight / 2.0 + wallHeight / 2.0) * step};
      for (int y{wallTop}; y < wallBottom; ++y) {
        [[maybe_unused]] int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        // get texture color here
        DrawPixel(x, y,
                  WHITE);
//textures.textures[texCoord][static_cast<size_t>(
 //                     (texY * texHeight) + texX)]
      }
    }

    // +++++++++++ CONTROLS ++++++++++++++++++++++++++++++++++++++++++++++++
    if (IsKeyDown(KEY_UP)) {
      if (worldMap[player.pos.y][static_cast<size_t>(
              player.pos.x + player.dir.x * speedModifier)] == 0) {
        player.pos.x += player.dir.x * speedModifier;
      }
      if (worldMap[static_cast<size_t>(
              player.pos.y + player.dir.y * speedModifier)][player.pos.x] ==
          0) {
        player.pos.y += player.dir.y * speedModifier;
      }
    }
    if (IsKeyDown(KEY_DOWN)) {
      if (worldMap[player.pos.y][static_cast<size_t>(
              player.pos.x - player.pos.x * speedModifier)] == 0) {
        player.pos.x -= player.dir.x * speedModifier;
      }
      if (worldMap[static_cast<size_t>(
              player.pos.y - player.pos.y * speedModifier)][player.pos.x] ==
          0) {
        player.pos.y -= player.dir.y * speedModifier;
      }
    }
    if (IsKeyDown(KEY_RIGHT)) {
      rotateVector(player.dir, -rotationModifier);
      rotateVector(player.plane, -rotationModifier);
    }
    if (IsKeyDown(KEY_LEFT)) {
      rotateVector(player.dir, rotationModifier);
      rotateVector(player.plane, rotationModifier);
    }

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
