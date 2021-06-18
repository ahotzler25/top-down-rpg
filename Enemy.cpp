#include "Enemy.h"
#include "raylib.h"
#include "raymath.h"

Enemy::Enemy()
{
    setSpeed(2.f);
    drawScale = 3.f;
    attackRange = 25.f;
    agroRange = 100.f;
    agroed = false;
}

void Enemy::Tick(float deltaTime)
{
    if (getHealth() <= 0.f) return;
    BaseCharacter::Tick(deltaTime);
    if (target)
    {
        Vector2 toTarget = Vector2Subtract(target->getCenter(), getCenter());
        float distance = Vector2Length(toTarget);
        if (distance < agroRange) agroed = true;
        if (!agroed) return;
        if (distance < attackRange)
            setDirection(Vector2{0.f, 0.f});
        else
            setDirection(toTarget);

        // deal damage
        if (CheckCollisionRecs(getCollision(), target->getCollision()))
        {
            const float newHealth{target->getHealth() - getDamagePerSecond() * GetFrameTime()};
            target->setHealth(newHealth);
        }
        DrawRectangleLines(
            getCollision().x,
            getCollision().y,
            getCollision().width,
            getCollision().height,
            PURPLE
        );
    }
    // check for collisions
    if (isCollidingWithProp())
    {
        UndoMovement();
    }
}

void Enemy::UpdateMovement()
{
    rightLeftLastFrame = rightLeft;
    if (Vector2Length(direction) != 0.f)
    {
        texture = runSheet;
        if (direction.x < 0.f) setRightLeft(-1.f);
        else setRightLeft(1.f);
        posLastFrame = position;
        position = Vector2Add(position, Vector2Scale(Vector2Normalize(direction), speed));
        direction = Vector2{0.f, 0.f};
    }
    else
        texture = idleSheet;
}

