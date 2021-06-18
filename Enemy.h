#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "raylib.h"
class Enemy : public BaseCharacter
{
public:
    Enemy();
    virtual void Tick(float deltaTime) override;
    void UpdateMovement() override;

private:
    Character* target;
    float damagePerSecond{20.f};
    float attackRange{};
    float agroRange{};
    bool agroed{};
public:
    void setTarget(Character* chr) { target = chr; }
    Character* getTarget() const { return target; }
    float getDamagePerSecond() const { return damagePerSecond; }
};

#endif