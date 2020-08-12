#ifndef STUBBORNRUNNER_H
#define STUBBORNRUNNER_H "STUBBORNRUNNER"
#define STUBBORN_RUNNER_SPEED 30
#define STUBBORN_RUNNER_INITIAL_HEALTH 400
#define STUBBORN_RUNNER_REDUCED_HEARTS 4
#define STUBBORN_RUNNER_DEATH_VALUE 10
#define STUBBORN_RUNNER_FRAME_NUMBERS 15
#include"Enemy.hpp"
class StubbornRunner : public Enemy{
public:
    StubbornRunner(UpdatedPoint block,UpdatedPoint direction_vector) : Enemy(block,direction_vector,STUBBORN_RUNNER_SPEED,STUBBORN_RUNNER_INITIAL_HEALTH,STUBBORN_RUNNER_REDUCED_HEARTS,STUBBORN_RUNNER_DEATH_VALUE,STUBBORN_RUNNER_FRAME_NUMBERS){};
    void draw(Window* game_window);
    std::string file_name_maker();
    void get_hurt(int damage,std::string tower_type); 
};
#endif