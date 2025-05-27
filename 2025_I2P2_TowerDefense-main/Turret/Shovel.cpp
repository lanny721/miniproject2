#include <allegro5/base.h>
#include <cmath>
#include <string>
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"

const int Shovel::Price = 50;
Shovel::Shovel(float x, float y) : Turret("play/shovel-base.png","play/shovel.png",x,y,0,Price,INFINITY) {
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Shovel::Use() {
    int x=floor(Position.x / PlayScene::BlockSize);
    int y=floor(Position.y / PlayScene::BlockSize);

    PlayScene *scene = getPlayScene();
    scene->RemoveTurret(x, y);
    
}
