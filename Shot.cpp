#include"Shot.hpp"
#include"functions.hpp"
#include<sstream>
#define SHOT_AFFECTED_RANGE 50
#define SHOT_SQUARE_LENGHT 20
#define COLLISION_RADIUS_PIXEL 10
#define SHOT_INITIAL_PICTURE "shot"
#define MISSILE_INITIAL_PICTURE "missile"
#define MAIN_FOLDER "Assets"
#define SHOTS_FOLDER "shots"
#define PICTURE_FORMAT ".png"
using namespace std;
void Shot::find_enemies_in_range(const vector<Enemy*>& appeared_enemies){
    for(int i=0;i< appeared_enemies.size();i++){
        float distance = compute_distance(appeared_enemies[i]->get_block());
        if(appeared_enemies[i]->show_availability() && distance <= SHOT_AFFECTED_RANGE && distance != (float)0){
            affected_enemies.push_back(appeared_enemies[i]);
        }
    }
}
bool Shot::collide(const vector<Enemy*>& appeared_enemies){
    if(collision_mode){
        if(tower_type == MISSILE_INITIAL_PICTURE){
            find_enemies_in_range(appeared_enemies);
        }
        for(int i=0;i<affected_enemies.size();i++){
            affected_enemies[i]->get_hurt(damage,tower_type);
        }
    }
    return collision_mode;
}
void Shot::draw(Window* game_window){
    stringstream shot_picture_name;
    shot_picture_name<<tower_type<<SHOT_INITIAL_PICTURE;
    game_window->draw_img(file_path_maker(MAIN_FOLDER,SHOTS_FOLDER,shot_picture_name.str(),PICTURE_FORMAT),Rectangle(block.x - SHOT_SQUARE_LENGHT/2,block.y - SHOT_SQUARE_LENGHT/2,SHOT_SQUARE_LENGHT,SHOT_SQUARE_LENGHT));
}
Shot::Shot(Point tower_block,string type,int shot_damage,Enemy* enemy){
    block.x = (float)tower_block.x;
    block.y = (float)tower_block.y; 
    tower_type = type;
    damage = shot_damage;
    affected_enemies.push_back(enemy);
    collision_mode = false;
}
float Shot::compute_distance(UpdatedPoint enemy_block){
    return sqrt((block.x - enemy_block.x)*(block.x - enemy_block.x) + (block.y - enemy_block.y)*(block.y - enemy_block.y));
}
bool Shot::move(){
    if(affected_enemies[0]->show_availability()){
        UpdatedPoint enemy_current_block = affected_enemies[0]->get_block();
        block.x = (block.x + enemy_current_block.x)/2;
        block.y = (block.y + enemy_current_block.y)/2;
        if(compute_distance(enemy_current_block) <= COLLISION_RADIUS_PIXEL){
            block.x = enemy_current_block.x;
            block.y = enemy_current_block.y;
            collision_mode = true;
        }
    }
    return affected_enemies[0]->show_availability();
}