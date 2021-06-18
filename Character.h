#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character() = default;
    Character(Vector2 screen);
    virtual void Tick(float deltaTime) override;
    virtual void UpdateMovement() override;
    void DrawWeapon();
    virtual void DrawCharacter() override;
    virtual Rectangle getCollision();
    virtual Vector2 getCenter();
protected:
    void setRightLeft(float rl) override;

private:
    Vector2 windowDimensions{};
    Vector2 positionOnScreen{};
    Rectangle weaponCollisionRec{};
    Texture2D weapon;
    float weaponDrawScale{4.f};
    float reach{30.f};
    float weaponRot{-75.f};
    float rightWeaponRot{-75.f};
    float lefttWeaponRot{90.f + 75.f};
    float swingRot{30.f};
    float attackTime{};
    float attackDuration{.2f};
    bool attacking{false};
    void Attack();
    void EndAttack();
public:
    float getWeaponDrawScale() { return weaponDrawScale;}
    inline float getWeaponRot() const { return weaponRot; }
    inline float getReach() const { return reach; }
    inline void setReach(float rch) { reach = rch; }
    inline Texture2D getWeapon() const { return weapon; }
    Rectangle getWeaponCollisionRec();
    inline void setWeaponCollisionRec(Rectangle wrec) { weaponCollisionRec = wrec; }
};

#endif