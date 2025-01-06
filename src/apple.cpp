#include "setting.hpp"

void spawn_apple() {
    extern Apple apple ;
    extern Python python ;

    apple.life_time = 0 ;
    apple.color = 0 ;

    // set random position
    std::random_device dev ;
    std::mt19937 rng(dev()) ; // Mersenne Twister engine
    std::uniform_int_distribution<int> dist6(1, col_num * row_num - python.length) ;
    int random_num = dist6(rng) ;
    // TODO: Update apple.x and apple.y according to random_num.
    int picked_x, picked_y ;
    bool is_finished = false ;
    for (int i = 0; i < col_num && !is_finished; i++) {
        for (int j = 0; j < row_num && !is_finished; j++) {
            if (python.board_occupied[i][j] == false) {
                random_num-- ;
                if (random_num <= 0) {
                    picked_x = i ;
                    picked_y = j ;
                    is_finished = true ;
                }
            } 
        }
    }
    apple.x = picked_x ;
    apple.y = picked_y ;

    // load images
    apple.images[0].loadFromFile("../images/apple_red.png") ;
    apple.images[1].loadFromFile("../images/apple_orange.png") ;
    apple.images[2].loadFromFile("../images/apple_yellow.png") ;
    apple.sprite.setTexture(apple.images[0]) ;
    apple.sprite.setPosition(apple.x * grid_length + board_left, apple.y * grid_length + board_top) ;
}

void draw_apple() {
    extern Apple apple ;
    extern sf::RenderWindow window ;

    apple.sprite.setPosition(apple.x * grid_length + board_left, apple.y * grid_length + board_top) ;
    if (apple.life_time < red_duration) {
        apple.sprite.setTexture(apple.images[0]) ;
        apple.color = 0 ;
    } else if (apple.life_time < orange_duration) {
        apple.sprite.setTexture(apple.images[1]) ;
        apple.color = 1 ;
    } else {
        apple.sprite.setTexture(apple.images[2]) ;
        apple.color = 2 ;
    }
    window.draw(apple.sprite) ;
}