#ifndef BASE_CHARACTER_H // if not defined
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter {
    public:
        BaseCharacter();
        Vector2 getWorldPos() { return worldPos; }
        void undoMovement();
        Rectangle getCollisionRec();
        virtual void tick(float deltaTime);
        // = 0 makes it a "pure virtual function"
        // BaseCharacter is now an abstract class
        // Can't instantiate from; only derive from
        virtual Vector2 getScreenPos() = 0;
        bool getAlive() { return alive; };
        void setAlive(bool isAlive) { alive = isAlive; };

    protected: // can be accessed by children
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        float width{};
        float height{};
        float scale{4.0f};

        // 1 : facing right, -1 : facing left
        float rightLeft{1.f};

        // animation variables
        float runningTime{};
        int frame{};
        int maxFrames{6};
        float updateTime{1.f / 12.f};
        float speed{4.f};
        Vector2 velocity{};
    private:
        bool alive{true};
};

#endif