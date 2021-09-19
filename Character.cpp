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
    worldPosLastFrame = worldPos;

    Vector2 direction{};
    if (IsKeyDown(KEY_A)) 
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) 
        direction.x += 1.0;
    if (IsKeyDown(KEY_W)) 
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) 
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    // Update Animation Frames
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    // Draw the character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRec() {
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}