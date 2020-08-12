#include"Path.hpp"
#include"functions.hpp"
#define MAIN_FOLDER "Assets"
#define BACKGROUND_FOLDER "background"
#define CROSS_PICTURE "square"
#define SQUARE_LENGHT 60
#define PICTURE_FORMAT ".png"
using namespace std;
UpdatedPoint Path::to_updated_point(Point block){
    UpdatedPoint new_block;
    new_block.x=(float)block.x;
    new_block.y=(float)block.y;
    return new_block;
}
Point Path::to_point(UpdatedPoint block){
    Point new_block;
    new_block.x=(int)block.x;
    new_block.y=(int)block.y;
    return new_block;
}
UpdatedPoint Path::determine_direction_vector(int index){
    UpdatedPoint direction_vector;
    direction_vector.x = (float)(path_blocks[index+1].x - path_blocks[index].x)?((path_blocks[index+1].x - path_blocks[index].x)/abs((path_blocks[index+1].x - path_blocks[index].x))) : 0;
    direction_vector.y = (float)(path_blocks[index+1].y - path_blocks[index].y)?((path_blocks[index+1].y - path_blocks[index].y)/abs((path_blocks[index+1].y - path_blocks[index].y))) : 0;
    return direction_vector;
}
int Path::find_block(Point block){
    for(int i=0;i<path_blocks.size();i++){
        if(path_blocks[i].x == block.x && path_blocks[i].y == block.y){
            return i;
        }
    }
}
void Path::move_enemy(Enemy* selected_enemy){
    UpdatedPoint enemy_block=selected_enemy->get_block();
    Point standard_block=standardize_block(to_point(enemy_block));
    int index = find_block(standard_block);
    if(index != path_blocks.size()-1){
        selected_enemy->move(determine_direction_vector(index),standard_block,false);
    }
    else{
        selected_enemy->move(determine_direction_vector(index - 1),standard_block,true);
    }
}
void Path::draw(Window* game_window){
    for(int i=0;i<path_blocks.size();i++){
        game_window->draw_img(file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,CROSS_PICTURE,PICTURE_FORMAT),Rectangle(path_blocks[i].x-SQUARE_LENGHT/2,path_blocks[i].y-SQUARE_LENGHT/2,SQUARE_LENGHT,SQUARE_LENGHT));
    }
}