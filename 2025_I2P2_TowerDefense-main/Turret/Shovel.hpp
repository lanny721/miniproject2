#ifndef SHOVEL_HPP
#define SHOVEL_HPP
#include "Turret.hpp"

class Shovel : public Turret {
public:
    static const int Price;
    Shovel(float x, float y);
    void Use();
    void CreateBullet() override {};
};
#endif   // Shovel_HPP
