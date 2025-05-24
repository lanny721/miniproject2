#ifndef INVISIBLEENEMY_HPP
#define INVISIBLEENEMY_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class InvisibleEnemy : public Enemy {
private:
    float visibleTime = 0.0; //change to invisible when visibleTime is 5.0
    float invisibleTime = 0.0; //change to invisible when visibleTime is 3.5
    int visible = 1; // 1 is visible, 0 is invisible

public:
    InvisibleEnemy(int x, int y);
    void Draw() const override;
    void Update(float deltaTime) override;
    bool IsVisible() const { return visible; }
};
#endif   // INVISIBLEENEMY_HPP
