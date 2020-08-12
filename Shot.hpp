#ifndef SHOT_H
#define SHOT_H "SHOT"
#include"rsdl.hpp"
#include"Enemy.hpp"
#include<vector>
#include"UpdatedPoint.hpp"
class Shot{
public:
    Shot(Point tower_block,std::string type,int shot_damage,Enemy* enemy);
    bool move();
    float compute_distance(UpdatedPoint enemy_block);
    void draw(Window* game_window);
    bool collide(const std::vector<Enemy*>& appeared_enemies);
    void find_enemies_in_range(const std::vector<Enemy*>& appeared_enemies);
private:
    UpdatedPoint block;
    std::string tower_type;
    int damage;
    std::vector<Enemy*> affected_enemies;
    bool collision_mode;    
};
#endif