#include "raylib.h"
#include "Character.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter {
    public:
        Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
        virtual void tick(float deltaTime) override;
        void setTarget(Character* character) { target = character; };
        virtual Vector2 getScreenPos() override;
    private:
        Character* target{}; // pointer-to-character
        float damagePerSec{10.f};
};