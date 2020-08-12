#include"SuperTrooper.hpp"
#include"functions.hpp"
#define SUPERTROOPER_INITIAL_PICTURE "heavyRunner"
#define MAIN_FOLDER "Assets"
#define ENEMY_FOLDER "enemies"
#define PICTURE_FORMAT ".png"
#define HEALTH_BAR_PICTURE "healthbar"
#define HEALTH_BAR_WIDTH 60
#define HEALTH_BAR_HIEGHT 20
#define BAR_TO_ENEMY_HEIGHT 50
#define SQUARE_LENGHT 60
using namespace std;
#include<sstream>
string SuperTrooper::file_name_maker(){
    stringstream file_name;
    file_name<<SUPERTROOPER_INITIAL_PICTURE<<'/'<<SUPERTROOPER_INITIAL_PICTURE<<direction<<to_string(frame_index);
    return file_name.str();
}
void SuperTrooper::draw(Window* game_window){
    if(is_available){
        game_window->draw_img(file_path_maker(MAIN_FOLDER,ENEMY_FOLDER,file_name_maker(),PICTURE_FORMAT),Rectangle(block.x - SQUARE_LENGHT/2,block.y - SQUARE_LENGHT/2,SQUARE_LENGHT,SQUARE_LENGHT),NULL_RECT,(0,0),flip_horizontal);
        game_window->draw_img(file_path_maker(MAIN_FOLDER,ENEMY_FOLDER,HEALTH_BAR_PICTURE,PICTURE_FORMAT),Rectangle(block.x - HEALTH_BAR_WIDTH/2,block.y - HEALTH_BAR_HIEGHT/2 - BAR_TO_ENEMY_HEIGHT,HEALTH_BAR_WIDTH * current_health/wave_health,HEALTH_BAR_HIEGHT));
    }
}