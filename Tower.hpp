#ifndef TOWER_H
#define TOWER_H "TOWER"
#include<chrono>
#include"rsdl.hpp"
#include"Enemy.hpp"
#include"Shot.hpp"
class Tower{
public:
    Tower(Point tower_block,std::string tower_type,int tower_shoot_rate,int tower_upgrade_cost,int tower_damage_upgrade,int tower_damage);
    virtual void draw(Window *game_window) = 0;
    Shot* shoot();
    void upgrade(int& total_money);
    Point get_block(){ return block;}
    void find_nearest_enemy(std::vector<Enemy*> appeared_enemies);
    float compute_distance(Enemy* selected_enemy);
protected:
    std::chrono::_V2::system_clock::time_point last_shoot_time;
    Point block;
    std::string type;
    int level;
    int shoot_rate;
    int upgrade_cost;
    int damage_upgrade;
    int damage;
    bool ever_shooted;
    Enemy* nearest_enemy;
};
#endif