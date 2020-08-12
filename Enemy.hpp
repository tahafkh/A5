#ifndef ENEMY_H
#define ENEMY_H "ENEMY"
#include"UpdatedPoint.hpp"
#include"rsdl.hpp"
class Enemy{
public:
    UpdatedPoint get_block(){ return block; }
    void is_dead(int& total_money);
    bool show_availability(){ return is_available;}
    Enemy(UpdatedPoint enemy_block,UpdatedPoint enemy_direction_vector,int enemy_speed,double enemy_initial_health,int enemy_reduced_hearts,int enemy_death_value,int frames);
    virtual void draw(Window* game_window) = 0;
    void move(UpdatedPoint new_direction_vector,Point standard_block,bool is_end_of_path);
    int move_in_last_block(Point last_block);
    void is_end_of_path(int& total_hearts);
    virtual void get_hurt(int damage,std::string tower_type){ current_health -= damage;}
    void update_health(int wave_number);
    void update_direction();
    void update_index();
    virtual std::string file_name_maker() = 0;
protected:
    UpdatedPoint block;
    UpdatedPoint direction_vector;
    int speed;
    double wave_health;
    double current_health;
    double initial_health;
    int reduced_hearts;
    int frame_index;
    int death_value;
    std::string direction;
    bool is_available;
    bool flip_horizontal;
    int frame_numbers;
};
#endif