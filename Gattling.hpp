#ifndef GATTLING_H
#define GATTLING_H "GATTLING"
#include"Tower.hpp"
#define GATLING_SHOOT_RATE 1000
#define GATLING_DAMAGE 35
#define GATLING_DAMAGE_UPGRADE 40
#define GATLING_UPGRADE_COST 40
#define GATLING_INITIAL_PICTURE "gattling"
class Gattling : public Tower{
public:
    Gattling(Point block) : Tower(block,GATLING_INITIAL_PICTURE,GATLING_SHOOT_RATE,GATLING_UPGRADE_COST,GATLING_DAMAGE_UPGRADE,GATLING_DAMAGE){};
    void draw(Window* game_window);
};
#endif