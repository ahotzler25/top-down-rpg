#include "raymath.h"
#include "Character.h"

// adding Character::function name is "fully qualifying the function name"
// :: scope resolution operator
Character::Character(int winWidth, int winHeight) {
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {
        // C style cast = (float)winWidth (this does not check types to or from cast)
        // Static cast = static_cast<float>(winWidth) (checks to make sure conversion types are compatible)(type-checking)
        screenPos.x = static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width), 
        screenPos.y = static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);

    Vector2 direction{};
    if (IsKeyDown(KEY_A)) 
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) 
        direction.x += 1.0;
    if (IsKeyDown(KEY_W)) 
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) 
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0) {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    } else {
        texture = idle;
    }
}