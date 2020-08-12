#include"Tower.hpp"
using namespace std;
#define SHOOT_RANGE_PIXEL 150
#define INITIAL_LEVEL 1
#define MAX_TOWER_LEVEL 3
void Tower::upgrade(int& total_money){
    if(level < MAX_TOWER_LEVEL){
        if(total_money >= upgrade_cost){
            total_money -= upgrade_cost;
            level++;
            damage += damage_upgrade;
        }
    }
}
void Tower::find_nearest_enemy(vector<Enemy*> appeared_enemies){
    nearest_enemy = NULL;
    for(int i=0;i<appeared_enemies.size();i++){
        if(appeared_enemies[i]->show_availability()){
            if(nearest_enemy==NULL){
                nearest_enemy = appeared_enemies[i];
            }
            else{
                if(compute_distance(appeared_enemies[i]) < compute_distance(nearest_enemy)){
                    nearest_enemy = appeared_enemies[i];
                }
            }
        }
    }
}
float Tower::compute_distance(Enemy* selected_enemy){
    UpdatedPoint enemy_block = selected_enemy->get_block();
    return sqrt((block.x - enemy_block.x)*(block.x - enemy_block.x) + (block.y - enemy_block.y)*(block.y - enemy_block.y));
}
Shot* Tower::shoot(){
    if(nearest_enemy){
        if(!ever_shooted){
            if(compute_distance(nearest_enemy) <= SHOOT_RANGE_PIXEL){
                last_shoot_time = chrono::high_resolution_clock::now();
                ever_shooted = true;
                return (new Shot(block,type,damage,nearest_enemy));
            }
        }
        else if(ever_shooted){
            auto current_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(current_time - last_shoot_time);
            if(compute_distance(nearest_enemy) <= SHOOT_RANGE_PIXEL && duration.count()>=shoot_rate){
                last_shoot_time = chrono::high_resolution_clock::now();
                return (new Shot(block,type,damage,nearest_enemy));
            }
        }
    }
    return NULL;
} 
Tower::Tower(Point tower_block,string tower_type,int tower_shoot_rate,int tower_upgrade_cost,int tower_damage_upgrade,int tower_damage){
    block = tower_block;
    type = tower_type;
    level = INITIAL_LEVEL;
    shoot_rate = tower_shoot_rate;
    upgrade_cost = tower_upgrade_cost;
    damage_upgrade = tower_upgrade_cost;
    damage = tower_damage;
    ever_shooted = false;
}
