#include"functions.hpp"
#include<sstream>
using namespace std;
#define UP_RIGHT_X 150
#define UP_RIGHT_Y 205
#define SQUARE_LENGHT 60
string file_path_maker(string main_folder_name,string minor_folder_name,string file_name,string format){
    stringstream file_path;
    file_path<<main_folder_name<<"/"<<minor_folder_name<<"/"<<file_name<<format;
    return file_path.str();
}
Point standardize_block(Point block){
    Point standard_block;
    standard_block.x=((block.x - UP_RIGHT_X + SQUARE_LENGHT/2)/SQUARE_LENGHT)*SQUARE_LENGHT + UP_RIGHT_X ;
    standard_block.y=((block.y - UP_RIGHT_Y + SQUARE_LENGHT/2)/SQUARE_LENGHT)*SQUARE_LENGHT + UP_RIGHT_Y ;
    return standard_block;
}