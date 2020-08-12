#ifndef SCRAMBLER_H
#define SCRAMBLER_H "SCRAMBLER"
#include"Enemy.hpp"
#define SCRAMBLER_SPEED 90
#define SCRAMBLER_INITIAL_HEALTH 100
#define SCRAMBLER_REDUCED_HEARTS 2
#define SCRAMBLER_DEATH_VALUE 4
#define SCRAMBLER_FRAME_NUMBERS 4
class Scrambler : public Enemy{
public:
    Scrambler(UpdatedPoint block,UpdatedPoint direction_vector) : Enemy(block,direction_vector,SCRAMBLER_SPEED,SCRAMBLER_INITIAL_HEALTH,SCRAMBLER_REDUCED_HEARTS,SCRAMBLER_DEATH_VALUE,SCRAMBLER_FRAME_NUMBERS){};
    std::string file_name_maker();
    void draw(Window* game_window);
};
#endif