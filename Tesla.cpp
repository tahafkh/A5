#include"Tesla.hpp"
#include"functions.hpp"
#include<sstream>
#define MAIN_FOLDER "Assets"
#define TOWER_FOLDER "towers"
#define PICTURE_FORMAT ".png"
#define SQUARE_LENGHT 60
using namespace std;
void Tesla::draw(Window* game_window){
    stringstream file_name;
    file_name<<TESLA_INITIAL_PICTURE<<to_string(level);
    game_window->draw_img(file_path_maker(MAIN_FOLDER,TOWER_FOLDER,file_name.str(),PICTURE_FORMAT),Rectangle(block.x-SQUARE_LENGHT/2,block.y-SQUARE_LENGHT/2,SQUARE_LENGHT,SQUARE_LENGHT));
}