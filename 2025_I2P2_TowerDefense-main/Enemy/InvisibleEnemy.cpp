#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "InvisibleEnemy.hpp"

InvisibleEnemy::InvisibleEnemy(int x, int y)
    : Enemy("play/enemy-4.png", x, y, 20, 20, 12, 50) {
}
void InvisibleEnemy::Draw() const {
    Enemy::Draw();
}
void InvisibleEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    if(visible){
        visibleTime += deltaTime;
        if(visibleTime >= 5.0){
            visible = 0;
            visibleTime = 0;
            invisibleTime = 0;
            Tint = al_map_rgba(255, 255, 255, 50);
        }
    } else if(!visible){
        invisibleTime += deltaTime;
        if(invisibleTime >= 3.5){
            visible = 1;
            Tint = al_map_rgba(255, 255, 255, 255);
            visibleTime = 0;
            invisibleTime = 0;
        }
    }
}
