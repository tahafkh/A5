#ifndef FIELDRUNNER_H
#define FIELDRUNNER_H "FIELDRUNNER"
#include<vector>
#include"Tower.hpp"
#include"Path.hpp"
#include"Enemy.hpp"
#include<chrono>
#define WINDOW_WIDTH 1365
#define WINDOW_HEIGHT 1024
#define GAME_NAME "FieldRunner"
class FieldRunner{
public:
    FieldRunner(int initial_total_money,int initial_total_hearts);
    void play_game();
    int convert_pixels_to_index(int pixel,int origin_pixel);
    void prepare_enemies_for_appearance();
    void determine_game_path();
    void draw_towers();
    void draw_shots();
    void draw_enemies();
    void draw_background(int wave_number);
    void check_death();
    void check_end_of_path();
    Tower* find_tower(Point selected_block);
    void generate_total_enemies_for_each_wave(int wave_number);
    bool is_occupied(Point block);
    void occupy_block(int x,int y){ blocks[x][y]=true;}
    void initialize_occupations();
    void move_enemies();
    void shoot();
    void prepare_towers_to_shoot();
    void move_shots();
    void check_collisions();
    void make_window() { game_window= new Window(WINDOW_WIDTH,WINDOW_HEIGHT,GAME_NAME);}
    void determine_blocks_between_two_blocks(std::vector<Point>& game_path,Point new_block);
    void determine_total_enemies();
    bool is_appeared(int enemy_index);
    std::vector<int> determine_enemies_for_each_wave(std::string enemies);
    void draw_game_screen(int wave_number);
    void update_enemies_health(int wave_number);
    void update_game_events();
    void handle_tower_events(char pressed_key);
    void handle_game_events();
    bool check_whether_enemies_are_available();
    void remove_all_enemies();
    void remove_everything();
    void check_winning_or_losing(int wave_number);
    void delete_window(){ delete game_window;}
private:
    std::chrono::_V2::system_clock::time_point last_enemy_appearance_time;
    std::vector<std::vector<bool>> blocks;
    Path game_path;
    Point tower_point;
    Window* game_window;
    int total_money;
    int total_hearts;
    std::vector<std::vector<int>> total_enemies;
    std::vector<Tower*> game_towers;
    std::vector<Enemy*> total_enemies_for_each_wave;
    std::vector<int> appeared_enemies_indexs;
    std::vector<Shot*> available_shots;
    std::vector<Enemy*> appeared_enemies_for_each_wave;
};
#endif