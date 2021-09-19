#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    // const int windowWidth{780};
    // const int windowHeight{780};
    InitWindow(windowWidth, windowHeight, "RPG");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};

    // Render Instances of Props
    Prop props[]{
        Prop{Vector2{600.f, 400.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")},
        Prop{Vector2{780.f, 800.f}, LoadTexture("nature_tileset/Sign.png")}
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        // draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        
        // Draw the props
        for (auto prop : props) {
            prop.Render(knight.getWorldPos());
        }
        
        knight.tick(GetFrameTime());
        
        // Check Map Bounds
        if (knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale) 
        {
            knight.undoMovement();
        }

        // range-based for loop
        // Check Prop collisions
        for (auto prop : props) 
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) 
            {
                knight.undoMovement();
            }
        }
        EndDrawing();
    }
    CloseWindow();
}