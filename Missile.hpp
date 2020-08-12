#ifndef MISSILE_H
#define MISSILE_H "MISSILE"
#include"Tower.hpp"
#define MISSILE_INITIAL_PICTURE "missile"
#define MISSILE_SHOOT_RATE 3000
#define MISSILE_DAMAGE 75
#define MISSILE_DAMAGE_UPGRADE 75
#define MISSILE_UPGRADE_COST 60
class Missile : public Tower{
public:
    Missile(Point block) : Tower(block,MISSILE_INITIAL_PICTURE,MISSILE_SHOOT_RATE,MISSILE_UPGRADE_COST,MISSILE_DAMAGE_UPGRADE,MISSILE_DAMAGE){};
    void draw(Window* game_window);
};
#endif