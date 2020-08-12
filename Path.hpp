#ifndef PATH_H
#define PATH_H "PATH"
#include<vector>
#include"rsdl.hpp"
#include"Enemy.hpp"
#include"UpdatedPoint.hpp"
#define FIRST_BLOCK_INDEX 0
class Path{
public:
    Path(){};
    Point get_first_block(){ return path_blocks[FIRST_BLOCK_INDEX];}
    Point to_point(UpdatedPoint block);
    UpdatedPoint to_updated_point(Point block);
    int find_block(Point block);
    UpdatedPoint determine_direction_vector(int index);
    void move_enemy(Enemy* selected_enemy);
    Path(std::vector<Point> blocks){ path_blocks=blocks;}
    void draw(Window* game_window);
private:
    std::vector<Point> path_blocks;
};
#endif