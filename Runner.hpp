#ifndef RUNNER_H
#define RUNNER_H "RUNNER"
#include"Enemy.hpp"
#define RUNNER_SPEED 50
#define RUNNER_INITIAL_HEALTH 250
#define RUNNER_REDUCED_HEARTS 1
#define RUNNER_DEATH_VALUE 6
#define RUNNER_FRAME_NUMBERS 12
class Runner : public Enemy{
public:
    Runner(UpdatedPoint block,UpdatedPoint direction_vector) : Enemy(block,direction_vector,RUNNER_SPEED,RUNNER_INITIAL_HEALTH,RUNNER_REDUCED_HEARTS,RUNNER_DEATH_VALUE,RUNNER_FRAME_NUMBERS){};
    void draw(Window* game_window);
    std::string file_name_maker();
};
#endif