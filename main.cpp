#include"FieldRunner.hpp"
#define INITIAL_TOTAL_COINS 200
#define INITIAL_TOTAL_HEARTS 20
int main(){
    FieldRunner fieldrunner(INITIAL_TOTAL_COINS,INITIAL_TOTAL_HEARTS);
    fieldrunner.initialize_occupations();
    fieldrunner.determine_game_path();
    fieldrunner.determine_total_enemies();
    fieldrunner.make_window();
    fieldrunner.play_game();
    fieldrunner.delete_window();
    return 0;
}