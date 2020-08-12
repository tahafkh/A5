#ifndef TESLA_H
#define TESLA_H "TESLA"
#include "Tower.hpp"
#define TESLA_INITIAL_PICTURE "tesla"
#define TESLA_SHOOT_RATE 1500
#define TESLA_DAMAGE 700
#define TESLA_DAMAGE_UPGRADE 1000
#define TESLA_UPGRADE_COST 100
class Tesla : public Tower{
public:
    Tesla(Point block) : Tower(block,TESLA_INITIAL_PICTURE,TESLA_SHOOT_RATE,TESLA_UPGRADE_COST,TESLA_DAMAGE_UPGRADE,TESLA_DAMAGE){};
    void draw(Window* game_window);
};
#endif