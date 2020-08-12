#include"Enemy.hpp"
using namespace std;
#define UP "Up"
#define DOWN "Down"
#define RIGHT "Right"
#define MIN_HEALTH 0
#define DELAY_MILLISECONDS 25
void Enemy::update_index(){
    frame_index = (frame_index + 2 - frame_numbers) ? (frame_index + 1) : 1;
}
void Enemy::update_direction(){
    if(direction_vector.x > 0){
        direction = RIGHT;
        flip_horizontal = false;
    }
    else if(direction_vector.x < 0){
        direction = RIGHT;
        flip_horizontal = true;
    }
    else if(direction_vector.y > 0){
        direction = DOWN;
        flip_horizontal = false;
    }
    else if(direction_vector.y < 0){
        direction = UP;
        flip_horizontal = false;
    }
    update_index();
}
void Enemy::is_end_of_path(int& total_hearts){
    if(!is_available && current_health > MIN_HEALTH){
        if(total_hearts > MIN_HEALTH){
            total_hearts -= reduced_hearts;
            current_health = MIN_HEALTH;
        }
        if (total_hearts < MIN_HEALTH){
            total_hearts = MIN_HEALTH;
        }
    }
}
void Enemy::is_dead(int& total_money){
    if(is_available){
        if(current_health <= MIN_HEALTH){
            is_available = false;
            total_money += death_value;
        }
    }
}
void Enemy::update_health(int wave_number){
    wave_health = (0.9 + 0.1*wave_number) * initial_health;
    current_health = wave_health;
}
int Enemy::move_in_last_block(Point last_block){
    int regular_move = 1;
    if(direction_vector.x > 0){
        if((block.x + speed*DELAY_MILLISECONDS/1000) > last_block.x){
            regular_move = 0;
        }
    }
    else if(direction_vector.x < 0){
        if((block.x - speed*DELAY_MILLISECONDS/1000) < last_block.x){
            regular_move = 0;
        }
    }
    else if(direction_vector.y > 0){
        if((block.y + speed*DELAY_MILLISECONDS/1000) > last_block.y){
            regular_move = 0;
        }
    }
    else if(direction_vector.y < 0){
        if((block.y - speed*DELAY_MILLISECONDS/1000) < last_block.y){
            regular_move = 0;
        }
    }
    if(!regular_move){
        is_available = false;
    }
    return regular_move;
}
Enemy::Enemy(UpdatedPoint enemy_block,UpdatedPoint enemy_direction_vector,int enemy_speed,double enemy_initial_health,int enemy_reduced_hearts,int enemy_death_value,int frames){
    block=enemy_block;
    direction_vector=enemy_direction_vector ;
    speed=enemy_speed;
    initial_health=enemy_initial_health;
    reduced_hearts=enemy_reduced_hearts;
    death_value=enemy_death_value;
    is_available=true;
    frame_index = 0;
    frame_numbers = frames;
}
void Enemy::move(UpdatedPoint new_direction_vector,Point standard_block,bool is_end_of_path){
    int regular_move = 1;
    if(!is_end_of_path && is_available){
        if((new_direction_vector.x != direction_vector.x && new_direction_vector.y != direction_vector.y) || (is_end_of_path)){
            if(direction_vector.x > 0){
                if((block.x + speed*DELAY_MILLISECONDS/1000) > standard_block.x){
                    block.y = block.y + new_direction_vector.y*(speed*DELAY_MILLISECONDS/1000 - (standard_block.x - block.x));
                    block.x = standard_block.x;
                    regular_move = 0;
                }
            }
            else if(direction_vector.x < 0){
                if((block.x - speed*DELAY_MILLISECONDS/1000) < standard_block.x){
                    block.y = block.y + new_direction_vector.y*(speed*DELAY_MILLISECONDS/1000 - (block.x - standard_block.x));
                    block.x = standard_block.x;
                    regular_move = 0;
                }
            }
            else if(direction_vector.y > 0){
                if((block.y + speed*DELAY_MILLISECONDS/1000) > standard_block.y){
                    block.x = block.x + new_direction_vector.x*(speed*DELAY_MILLISECONDS/1000 - (standard_block.y - block.y));
                    block.y = standard_block.y;
                    regular_move = 0;
                }
            }
            else if(direction_vector.y < 0){
                if((block.y - speed*DELAY_MILLISECONDS/1000) < standard_block.y){
                    block.x = block.x + new_direction_vector.x*(speed*DELAY_MILLISECONDS/1000 - (block.y - standard_block.y));
                    block.y = standard_block.y;
                    regular_move = 0;
                }
            }
            if(!regular_move){
                direction_vector=new_direction_vector;
            }
        }
    }
    else{
        regular_move=move_in_last_block(standard_block);
    }
    if(regular_move){
        block.x += direction_vector.x*speed*DELAY_MILLISECONDS/1000;
        block.y += direction_vector.y*speed*DELAY_MILLISECONDS/1000;
    }
    update_direction();
}