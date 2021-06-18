#include "Collidable.h"
#include "raylib.h"
#include "raymath.h"

Collidable::Collidable(Texture2D tex, Vector2 pos) :
    texture(tex),
    position(pos)
{
    drawScale = 4.f;
}

Rectangle Collidable::getCollisionRec(Vector2 worldOrigin)
{
    // return collision rec at global position
    return Rectangle{
        position.x + worldOrigin.x,
        position.y + worldOrigin.y,
        texture.width * drawScale,
        texture.height * drawScale
    };

}

void Collidable::setPosition(Vector2 pos)
{
    position = pos;
}

void Collidable::Render(Vector2 worldOrigin)
{
    DrawTextureEx(texture, Vector2Add(position, worldOrigin), 0.f, drawScale, WHITE);
}