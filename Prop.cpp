#include "raymath.h"
#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    // member initializer list (note the colon after the parameters above)
    worldPos(pos), texture(tex)
{
    // Assume something will be added here later
}

void Prop::Render(Vector2 knightPos) {
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos) {
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{ 
        screenPos.x, 
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}