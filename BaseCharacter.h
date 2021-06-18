#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "Collidable.h"
#include <vector>
class BaseCharacter : public Collidable
{
public:
    BaseCharacter() = default;
    virtual void Tick(float deltaTime);
    virtual void UpdateMovement();
    void UpdateAnimFrame(float deltaTime);
    virtual Rectangle getCollision();
    virtual void DrawCharacter();
    void UndoMovement();
    bool isCollidingWithProp();
protected:
    Vector2 posLastFrame;
    Vector2 direction{};
    float rightLeft{1.f};
    float rightLeftLastFrame;
    Texture2D idleSheet;
    Texture2D runSheet;

    virtual void setRightLeft(float rl);
    float speed;

    class GameplayManager* manager;
    Rectangle rec{};
    int spriteSheetFrames{6};
private:

    float runningTime{};
    float updateTime{1.f/12.f};
    int frame{};

    float health = 100.f;

public:
    void setManager(GameplayManager* mgr) { manager = mgr; }
    Rectangle getRec() const { return rec;}
    void setSpeed(float spd) { speed = spd; }
    virtual Vector2 getCenter();
    void setPos(Vector2 pos) { position = pos; }
    void setDirection(Vector2 dir) { direction = dir; }
    float getRightLeft() const { return rightLeft; }
    void setIdleSheet(Texture2D sheet);
    void setRunSheet(Texture2D sheet);
    void setSpriteSheetFrames(int numFrames) { spriteSheetFrames = numFrames;}
    float getHealth() const { return health;}
    void setHealth(float amount) { health = amount; }
    Vector2 getPosLastFrame() const { return posLastFrame; }
    void setPosLastFrame(Vector2 pos) { posLastFrame = pos; }
};

#endif