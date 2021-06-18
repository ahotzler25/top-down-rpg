#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include "raylib.h"

class Collidable
{
public:
    Collidable() = default;
    Collidable(Texture2D tex, Vector2 pos);

    Texture2D getTexture() const { return texture; }
    Vector2 getPosition() const { return position; }
    virtual void setPosition(Vector2 pos);
    float getDrawScale() const { return drawScale; }
    virtual Rectangle getCollisionRec(Vector2 worldOrigin);

    void Render(Vector2 worldOrigin);
protected:
    Texture2D texture{};
    Vector2 position{}; // local position (map space)
    float drawScale{};
private:
    Rectangle collisionRec();
};

#endif