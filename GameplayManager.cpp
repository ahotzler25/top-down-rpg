#include "GameplayManager.h"
#include "Enemy.h"
#include <limits>
#include <vector>
#include "Character.h"
#include "BaseCharacter.h"
#include "raymath.h"

GameplayManager::GameplayManager(int winWidth, int winHeight)
{
    windowDimensions[0] = winWidth;
    windowDimensions[1] = winHeight;
    map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    mapScale = 4.f;
}

 void GameplayManager::AddEnemy(Enemy* enemy)
 {
     enemy->setManager(this);
     enemies.push_back(enemy);
 }

void GameplayManager::Update()
{
    Vector2 worldOrigin{Vector2Scale(mainCharacter->getPosition(), -1.f)};
    // draw map and props
    DrawTextureEx(map, worldOrigin, 0.f, 4.f, WHITE);
    for (auto prop : props)
    {
        prop->Render(worldOrigin);
    }
    mainCharacter->Tick(GetFrameTime());
    for (auto enemy : enemies)
    {
        enemy->Tick(GetFrameTime());
    }
    // draw map, then props, then character, then enemies (z-order)
}

void GameplayManager::registerMainCharacter(Character& chr)
{
    mainCharacter = &chr;
    mainCharacter->setManager(this);
}

bool GameplayManager::HittingMapBounds()
{
    return (mainCharacter->getPosition().x < 0.f ||
            mainCharacter->getPosition().x + (float)windowDimensions[0] > map.width * mapScale ||
            mainCharacter->getPosition().y < 0.f ||
            mainCharacter->getPosition().y + (float)windowDimensions[1] > map.height * mapScale);
}


void GameplayManager::ApplyMovement(Vector2 input)
{
    // Move the character's position
    mainCharacter->setPosLastFrame(mainCharacter->getPosition());
    mainCharacter->setPosition(Vector2{mainCharacter->getPosition().x + input.x, mainCharacter->getPosition().y + input.y});

    if (HittingMapBounds() || mainCharacter->isCollidingWithProp())
    {
        mainCharacter->setPosition(mainCharacter->getPosLastFrame());
    }
    movementInput = Vector2{}; // zero out movementInput
}

Vector2 GameplayManager::getScreenPosition()
{
    return mainCharacter->getPosition();
}