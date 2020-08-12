#ifndef SUPERTROOPER_H
#define SUPERTROOPER_H "SUPERTROOPER"
#include"Enemy.hpp"
#define SUPERTROOPER_SPEED 25
#define SUPERTROOPER_INITIAL_HEALTH 500
#define SUPERTROOPER_REDUCED_HEARTS 4
#define SUPERTROOPER_DEATH_VALUE 8
#define SUPERTROOPER_FRAME_NUMBERS 15
class SuperTrooper : public Enemy{
public:
    SuperTrooper(UpdatedPoint block,UpdatedPoint direction_vector) : Enemy(block,direction_vector,SUPERTROOPER_SPEED,SUPERTROOPER_INITIAL_HEALTH,SUPERTROOPER_REDUCED_HEARTS,SUPERTROOPER_DEATH_VALUE,SUPERTROOPER_FRAME_NUMBERS){};
    void draw(Window* game_window);
    std::string file_name_maker();
};
#endif