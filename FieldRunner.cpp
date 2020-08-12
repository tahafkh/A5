#include"FieldRunner.hpp"
using namespace std;
#include"functions.hpp"
#include"Gattling.hpp"
#include"Tesla.hpp"
#include"Missile.hpp"
#include"StubbornRunner.hpp"
#include"Runner.hpp"
#include"Scrambler.hpp"
#include"SuperTrooper.hpp"
#include<sstream>
#define MIN_HEALTH 0
#define UP_RIGHT_X 150
#define UP_RIGHT_Y 205
#define MAX_X 19
#define MAX_Y 11
#define HEART_TEXT_X 190
#define HEART_TEXT_Y 90
#define GOLD_TEXT_X 370
#define GOLD_TEXT_Y 90
#define DELAY_MILLISECONDS 25
#define END_GAME_DELAY_MILLISECONDS 4500
#define ENEMY_APPEARANCE_DELAY_MILLISECONDS 5000
#define WAVE_DELAY_MILLISECONDS 3000
#define HEART_X 150
#define HEART_Y 100
#define GOLD_X 330
#define GOLD_Y 100
#define QUANTITIES_TEXT_SIZE 24
#define FIRST_BLOCK_INDEX 0
#define ENEMY_TYPES 4
#define RUNNER_INDEX 0
#define STUBBORN_INDEX 1
#define SUPERTROOPER_INDEX 2
#define SCRAMBLER_INDEX 3
#define GATTLING_KEY 'g'
#define MISSILE_KEY 'm'
#define TESLA_KEY 't'
#define UPDATE_KEY 'u'
#define WAVE_TEXT "Wave"
#define WAVE_TEXT_X 510
#define WAVE_TEXT_Y 90
#define WIN_TEXT "You Win!"
#define LOSE_TEXT "You Lose!"
#define FINAL_TEXT_X 150
#define FINAL_TEXT_Y 300
#define FINAL_TEXT_SIZE 250 
#define VICTORY_SOUND_NAME "victory"
#define LOSE_SOUND_NAME "lose"
#define SOUND_FORMAT ".mp3"
#define MAIN_FOLDER "Assets"
#define BACKGROUND_FOLDER "background"
#define FONT_NAME "OpenSans"
#define FONT_FORMAT ".ttf"
#define SPACE_SEPERATOR ' '
#define GOLD_PICTURE "gold"
#define HEART_PICTURE "heart"
#define PICTURE_FORMAT ".png"
#define GATLING_BUILD_COST 55
#define SQUARE_LENGHT 60
#define MISSILE_BUILD_COST 70
#define TESLA_BUILD_COST 120
#define BACKGROUND_PICTURE "background"
void FieldRunner::check_winning_or_losing(int wave_number){
    game_window->clear();
    draw_background(wave_number);
    if(total_hearts > MIN_HEALTH){
        game_window->show_text(WIN_TEXT,Point(FINAL_TEXT_X,FINAL_TEXT_Y),WHITE,file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,FONT_NAME,FONT_FORMAT),FINAL_TEXT_SIZE);
        game_window->play_music(file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,VICTORY_SOUND_NAME,SOUND_FORMAT));
    }
    else{
       game_window->show_text(LOSE_TEXT,Point(FINAL_TEXT_X,FINAL_TEXT_Y),BLACK,file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,FONT_NAME,FONT_FORMAT),FINAL_TEXT_SIZE);
       game_window->play_music(file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,LOSE_SOUND_NAME,SOUND_FORMAT)); 
    }
    remove_everything();
    game_window->update_screen();
}
void FieldRunner::remove_everything(){
    remove_all_enemies();
    for(int i=0;i<available_shots.size();i++){
        delete available_shots[i];
    }
    available_shots.clear();
    for(int i=0;i<game_towers.size();i++){
        delete game_towers[i];
    }
    game_towers.clear();
}
void FieldRunner::handle_game_events(){
    while(game_window->has_pending_event()){
        Event new_event = game_window->poll_for_event();
        switch (new_event.get_type()){
            case Event::EventType::QUIT:
                remove_everything();
                delete_window();
                exit(0);
                break;
            case Event::EventType::LCLICK:
                tower_point=standardize_block(new_event.get_mouse_position());
                break;
            case Event::EventType::KEY_PRESS:
                handle_tower_events(new_event.get_pressed_key());
                break;
        }
    }
}
void FieldRunner::remove_all_enemies(){
    for(int i=0;i<total_enemies_for_each_wave.size();i++){
        delete total_enemies_for_each_wave[i];
    }
    total_enemies_for_each_wave.clear();
    appeared_enemies_for_each_wave.clear();
    appeared_enemies_indexs.clear();
}
bool FieldRunner::check_whether_enemies_are_available(){
    for(int i=0;i<total_enemies_for_each_wave.size();i++){
        if(total_enemies_for_each_wave[i]->show_availability()){
            return true;
        }
    }
    return false;
}
void FieldRunner::handle_tower_events(char pressed_key){
    switch(pressed_key){
        case GATTLING_KEY:
            if(!is_occupied(tower_point) && total_money>= GATLING_BUILD_COST){
                game_towers.push_back(new Gattling(tower_point));
                occupy_block(convert_pixels_to_index(tower_point.x,UP_RIGHT_X),convert_pixels_to_index(tower_point.y,UP_RIGHT_Y));
                total_money -= GATLING_BUILD_COST;
            }
            break;
        case MISSILE_KEY:
            if(!is_occupied(tower_point) && total_money>=MISSILE_BUILD_COST){
                game_towers.push_back(new Missile(tower_point));
                occupy_block(convert_pixels_to_index(tower_point.x,UP_RIGHT_X),convert_pixels_to_index(tower_point.y,UP_RIGHT_Y));
                total_money -= MISSILE_BUILD_COST;                        
            }
            break;
        case TESLA_KEY:
            if(!is_occupied(tower_point) && total_money>= TESLA_BUILD_COST){
                game_towers.push_back(new Tesla(tower_point));
                occupy_block(convert_pixels_to_index(tower_point.x,UP_RIGHT_X),convert_pixels_to_index(tower_point.y,UP_RIGHT_Y));
                total_money -= TESLA_BUILD_COST;
            }
            break;
        case UPDATE_KEY:
            Tower* selected_tower = find_tower(tower_point);
            if(selected_tower!= NULL){
                selected_tower->upgrade(total_money);
            }
            break;
    }
}
void FieldRunner::check_end_of_path(){
    for(int i=0;i<appeared_enemies_for_each_wave.size();i++){
        appeared_enemies_for_each_wave[i]->is_end_of_path(total_hearts);
    }
}
void FieldRunner::check_death(){
    for(int i=0;i<appeared_enemies_for_each_wave.size();i++){
        appeared_enemies_for_each_wave[i]->is_dead(total_money);
    }
}
void FieldRunner::update_enemies_health(int wave_number){
    for(int i=0;i<total_enemies_for_each_wave.size();i++){
        total_enemies_for_each_wave[i]->update_health(wave_number);
    }
}
void FieldRunner::draw_background(int wave_number){
    game_window->draw_img(file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,BACKGROUND_PICTURE,PICTURE_FORMAT),Rectangle(0,0,WINDOW_WIDTH,WINDOW_HEIGHT));
    game_window->draw_img(file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,GOLD_PICTURE,PICTURE_FORMAT),Rectangle(GOLD_X - SQUARE_LENGHT/2,GOLD_Y - SQUARE_LENGHT/2,SQUARE_LENGHT,SQUARE_LENGHT));
    game_window->show_text(to_string(total_money),Point(GOLD_TEXT_X,GOLD_TEXT_Y),YELLOW,file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,FONT_NAME,FONT_FORMAT),QUANTITIES_TEXT_SIZE);
    game_window->draw_img(file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,HEART_PICTURE,PICTURE_FORMAT),Rectangle(HEART_X - SQUARE_LENGHT/2,HEART_Y - SQUARE_LENGHT/2,SQUARE_LENGHT,SQUARE_LENGHT));
    game_window->show_text(to_string(total_hearts),Point(HEART_TEXT_X,HEART_TEXT_Y),RED,file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,FONT_NAME,FONT_FORMAT),QUANTITIES_TEXT_SIZE);
    stringstream wave;
    wave<<WAVE_TEXT<<SPACE_SEPERATOR<<to_string(wave_number);
    game_window->show_text(wave.str(),Point(WAVE_TEXT_X,WAVE_TEXT_Y),WHITE,file_path_maker(MAIN_FOLDER,BACKGROUND_FOLDER,FONT_NAME,FONT_FORMAT),QUANTITIES_TEXT_SIZE);
}
FieldRunner::FieldRunner(int initial_total_money,int initial_total_heart){
    total_money = initial_total_money;
    total_hearts = initial_total_heart;
}
Tower* FieldRunner::find_tower(Point selected_block){
    for(int i=0;i<game_towers.size();i++){
        Point tower_block = game_towers[i]->get_block();
        if(selected_block.x == tower_block.x && selected_block.y == tower_block.y){
            return game_towers[i];
        }
    }
    return NULL;
}
void FieldRunner::check_collisions(){
    for(int i=0;i<available_shots.size();i++){
        if(available_shots[i]->collide(appeared_enemies_for_each_wave)){
            delete available_shots[i];
            available_shots.erase(available_shots.begin() + i);
            i--;
        }
    }
}
void FieldRunner::prepare_towers_to_shoot(){
    for(int i=0;i<game_towers.size();i++){
        game_towers[i]->find_nearest_enemy(appeared_enemies_for_each_wave);
    }
}
void FieldRunner::shoot(){
    for(int i=0;i<game_towers.size();i++){
        Shot* new_shot=game_towers[i]->shoot();
        if(new_shot != NULL){
            available_shots.push_back(new_shot);
        }
    }
}
void FieldRunner::move_shots(){
    for(int i=0;i<available_shots.size();i++){
        if(!available_shots[i]->move()){
            delete available_shots[i];
            available_shots.erase(available_shots.begin() + i);
            i--;
        }
    }
}
void FieldRunner::draw_shots(){
    for(int i=0;i<available_shots.size();i++){
        available_shots[i]->draw(game_window);
    }
}
void FieldRunner::draw_enemies(){
    for(int i=0;i<appeared_enemies_for_each_wave.size();i++){
        appeared_enemies_for_each_wave[i]->draw(game_window);
    }
}
bool FieldRunner::is_appeared(int enemy_index){
    for(int i=0;i<appeared_enemies_indexs.size();i++){
        if(enemy_index == appeared_enemies_indexs[i]){
            return true;
        }
    }
    return false;
}
void FieldRunner::prepare_enemies_for_appearance(){
    if(appeared_enemies_for_each_wave.size()<total_enemies_for_each_wave.size()){
        srand(time(0));
        if(appeared_enemies_for_each_wave.size()==0){
            int first_appeared_enemy_index = rand()%total_enemies_for_each_wave.size();
            appeared_enemies_indexs.push_back(first_appeared_enemy_index);
            appeared_enemies_for_each_wave.push_back(total_enemies_for_each_wave[first_appeared_enemy_index]);
            last_enemy_appearance_time = chrono::high_resolution_clock::now();
        }
        else{
            auto current_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds> (current_time - last_enemy_appearance_time);
            if(duration.count() >= ENEMY_APPEARANCE_DELAY_MILLISECONDS){
                int selected_enemy_index = rand()%total_enemies_for_each_wave.size();
                while(is_appeared(selected_enemy_index)){
                    selected_enemy_index = rand()%total_enemies_for_each_wave.size();
                }
                appeared_enemies_indexs.push_back(selected_enemy_index);
                appeared_enemies_for_each_wave.push_back(total_enemies_for_each_wave[selected_enemy_index]);
                last_enemy_appearance_time = chrono::high_resolution_clock::now();
            }
        }
    }
}
void FieldRunner::generate_total_enemies_for_each_wave(int wave_number){
    for(int i=0;i<ENEMY_TYPES;i++){
        for(int j=0; j<total_enemies[wave_number - 1][i];j++){
            switch(i){
                case RUNNER_INDEX:
                    total_enemies_for_each_wave.push_back(new Runner(game_path.to_updated_point(game_path.get_first_block()),game_path.determine_direction_vector(FIRST_BLOCK_INDEX)));
                    break;
                case STUBBORN_INDEX:
                    total_enemies_for_each_wave.push_back(new StubbornRunner(game_path.to_updated_point(game_path.get_first_block()),game_path.determine_direction_vector(FIRST_BLOCK_INDEX)));
                    break;
                case SUPERTROOPER_INDEX:
                    total_enemies_for_each_wave.push_back(new SuperTrooper(game_path.to_updated_point(game_path.get_first_block()),game_path.determine_direction_vector(FIRST_BLOCK_INDEX)));
                    break;
                case SCRAMBLER_INDEX:
                    total_enemies_for_each_wave.push_back(new Scrambler(game_path.to_updated_point(game_path.get_first_block()),game_path.determine_direction_vector(FIRST_BLOCK_INDEX)));
                    break;
            }
        }
    }
    update_enemies_health(wave_number);
}
void FieldRunner::move_enemies(){
    for(int i=0;i<appeared_enemies_for_each_wave.size();i++){
        game_path.move_enemy(appeared_enemies_for_each_wave[i]);
    }
}
int FieldRunner::convert_pixels_to_index(int pixel,int origin_pixel){
    return (pixel - origin_pixel)/SQUARE_LENGHT;
}
bool FieldRunner::is_occupied(Point block){
    return blocks[convert_pixels_to_index(block.x,UP_RIGHT_X)][convert_pixels_to_index(block.y,UP_RIGHT_Y)];
}
void FieldRunner::draw_towers(){
    for(int i=0;i<game_towers.size();i++){
        game_towers[i]->draw(game_window);
    }
}
void FieldRunner::update_game_events(){
    prepare_enemies_for_appearance();
    handle_game_events();
    move_enemies();
    prepare_towers_to_shoot();
    shoot();
    move_shots();
    check_collisions();
    check_death();
    check_end_of_path();
}
void FieldRunner::initialize_occupations(){
    vector<bool> column_blocks;
    for(int i=0;i<MAX_X;i++){
        for(int j=0;j<MAX_Y;j++){
            column_blocks.push_back(false);
        }
        blocks.push_back(column_blocks);
        column_blocks.clear();
    }
}
vector<int> FieldRunner::determine_enemies_for_each_wave(string enemies){
    stringstream all_enemies(enemies);
    string enemy;
    vector<int> enemies_for_this_wave;
    while(getline(all_enemies,enemy,SPACE_SEPERATOR)){
        enemies_for_this_wave.push_back(stoi(enemy));
    }
    return enemies_for_this_wave;
}
void FieldRunner::determine_total_enemies(){
    string enemies;
    while(getline(cin,enemies)){
        total_enemies.push_back(determine_enemies_for_each_wave(enemies));
    }
}
void FieldRunner::draw_game_screen(int wave_number){
    game_window->clear();
    draw_background(wave_number);
    game_path.draw(game_window);
    draw_towers();
    draw_shots();
    draw_enemies();
    game_window->update_screen();
}
void FieldRunner::determine_blocks_between_two_blocks(vector<Point>& game_path,Point new_block){
    if(game_path.size()){
        int dx=(new_block.x - game_path.back().x)?((new_block.x - game_path.back().x)/abs((new_block.x - game_path.back().x)))*SQUARE_LENGHT : 0;
        int dy = (new_block.y - game_path.back().y)?((new_block.y - game_path.back().y)/abs((new_block.y - game_path.back().y)))*SQUARE_LENGHT : 0;
        int new_x = game_path.back().x + dx,new_y = game_path.back().y + dy;
        while( new_x!= new_block.x || new_y!= new_block.y ){
            Point new_point(new_x,new_y);
            occupy_block((new_x-UP_RIGHT_X)/SQUARE_LENGHT,(new_y-UP_RIGHT_Y)/SQUARE_LENGHT);
            game_path.push_back(new_point);
            new_x += dx;
            new_y += dy;
        } 
    }
}
void FieldRunner::determine_game_path(){
    string path_blocks,x_block,y_block;
    getline(cin,path_blocks);
    vector<Point> points;
    stringstream path_points(path_blocks);
    while(getline(path_points,x_block,SPACE_SEPERATOR)){
        getline(path_points,y_block,SPACE_SEPERATOR);
        Point new_point(stoi(x_block)*SQUARE_LENGHT + UP_RIGHT_X,stoi(y_block)*SQUARE_LENGHT + UP_RIGHT_Y);
        determine_blocks_between_two_blocks(points,new_point);
        occupy_block(stoi(x_block),stoi(y_block));
        points.push_back(new_point);
    }
    Path path(points);
    game_path=path;
}
void FieldRunner::play_game(){
    int wave_number = 1;
    while(wave_number <= total_enemies.size() && total_hearts > MIN_HEALTH){
        generate_total_enemies_for_each_wave(wave_number);
        while(check_whether_enemies_are_available() && total_hearts > MIN_HEALTH){
            update_game_events();
            draw_game_screen(wave_number);
            delay(DELAY_MILLISECONDS);
        }
        remove_all_enemies();
        for(int wave_delay = 0;wave_delay <= WAVE_DELAY_MILLISECONDS && total_hearts > MIN_HEALTH; wave_delay += DELAY_MILLISECONDS){
            handle_game_events();
            draw_game_screen(wave_number);
            delay(DELAY_MILLISECONDS);
        }
        wave_number++;
    }
    check_winning_or_losing(wave_number-1);
    delay(END_GAME_DELAY_MILLISECONDS);
}