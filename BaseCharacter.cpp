#include "BaseCharacter.h"
#include "GameplayManager.h"
#include "raylib.h"
#include "raymath.h"

void BaseCharacter::Tick(float deltaTime)
{
    UpdateAnimFrame(GetFrameTime());
    UpdateMovement();
    DrawCharacter();
}

bool BaseCharacter::isCollidingWithProp()
{
    if (manager == nullptr) return false;
    Vector2 worldOrigin{Vector2Scale(manager->getScreenPosition(), -1.f)};
    for (auto prop : manager->getProps())
    {
        if (CheckCollisionRecs(getCollision(), prop->getCollisionRec(worldOrigin))) return true;
    }
    return false;
}

void BaseCharacter::UpdateMovement()
{
    rightLeftLastFrame = rightLeft;
    if (Vector2Length(direction) != 0.f)
    {
        texture = runSheet;
        if (direction.x < 0.f) setRightLeft(-1.f);
        else setRightLeft(1.f);
        Vector2 input{Vector2Scale(Vector2Normalize(direction), speed)};
        if (manager) manager->ApplyMovement(input);
        direction = Vector2{0.f, 0.f};
    }
    else texture = idleSheet;
}

void BaseCharacter::setRightLeft(float rl)
{
    rightLeft = rl;
}

void BaseCharacter::UpdateAnimFrame(float deltaTime)
{
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > spriteSheetFrames) frame = 0;
    }
    rec.x = frame * rec.width;
}

Vector2 BaseCharacter::getCenter()
{
    Vector2 worldOrigin{Vector2Scale(manager->getScreenPosition(), -1.f)};
    return Vector2{
        position.x + rec.width/2.f + worldOrigin.x,
        position.y + rec.height/2.f + worldOrigin.y
    };
}

void BaseCharacter::setIdleSheet(Texture2D sheet)
{
    idleSheet = sheet;
    rec.width = sheet.width/spriteSheetFrames;
    rec.height = sheet.height;
}

void BaseCharacter::setRunSheet(Texture2D sheet) 
{ 
    runSheet = sheet;
    rec.width = sheet.width/spriteSheetFrames;
    rec.height = sheet.height;
}

Rectangle BaseCharacter::getCollision()
{
    Vector2 worldOrigin{Vector2Scale(manager->getScreenPosition(), -1.f)};
    return Rectangle{
        position.x + worldOrigin.x,
        position.y + worldOrigin.y,
        rec.width * drawScale,
        rec.height * drawScale
    };
}

void BaseCharacter::DrawCharacter()
{
    if (manager)
    {
        Vector2 worldOrigin{Vector2Scale(manager->getScreenPosition(), -1.f)};

        Rectangle sourceRec{getRec().x, 0.f,getRec().width * getRightLeft(), getRec().height};
        Rectangle destRec{getPosition().x + worldOrigin.x, getPosition().y + worldOrigin.y, getDrawScale()*getRec().width, getDrawScale()*getRec().height};
        Vector2 origin{0.f, 0.f};
        DrawTexturePro(getTexture(),sourceRec, destRec, origin, 0.f, WHITE);
    }
}

void BaseCharacter::UndoMovement()
{
    position = posLastFrame;
}