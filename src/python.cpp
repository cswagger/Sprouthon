#include "setting.hpp"

void init_python() {
    extern Python python ;
    python.length = 1 ;
    python.direction[0] = 0 ;
    python.x[0] = python_init_x ;
    python.y[0] = python_init_y ;

    for (int i = 0; i < col_num; i++) {
        for (int j = 0; j < row_num; j++) {
            python.board_occupied[i][j] = false ;
        }
    }
    python.board_occupied[python_init_x][python_init_y] = true ;

    //load images
    python.head.loadFromFile("../images/head.png") ;
    python.body_images[0].loadFromFile("../images/body_red.png") ;
    python.body_images[1].loadFromFile("../images/body_orange.png") ;
    python.body_images[2].loadFromFile("../images/body_yellow.png") ;
}

void update_python() {
    extern Python python ;
    extern int current_direction ;
    extern bool game_running ;
    extern Apple apple ;
    extern bool win_game ;

    // TODO 4: You might need to store information about the last segment of python's body for later use.
    int last_x = python.x[python.length - 1], last_y = python.y[python.length - 1], last_direction = python.direction[python.length - 1] ;
    
    // TODO 1: Update the positions for python's body by copying the direction, x-axis, and y-axis from the i-th segment to the (i+1)-th segment.
    // TODO 1: Also, you should update python.board_occupied
    python.board_occupied[python.x[python.length - 1]][python.y[python.length - 1]] = false ;
    for (int i = python.length - 1; i > 0; i--) {
        python.direction[i] = python.direction[i - 1] ;
        python.x[i] = python.x[i - 1] ;
        python.y[i] = python.y[i - 1] ;
    }

    // TODO 2: Handle situations where python can't directly turn around.
if(python.length == 1) {
        if (current_direction == 0) {
            python.x[0] -= 1 ;
        } else if (current_direction == 1) {
            python.y[0] -= 1 ;
        } else if (current_direction == 2) {
            python.x[0] += 1 ;
        } else if (current_direction == 3) {
            python.y[0] += 1 ;
        }
    } else if(python.length > 1) {
        if(python.direction[0] == 0 && current_direction == 2) {
            python.x[0] -= 1;
            current_direction = 0;
        }
        else if(python.direction[0] == 1 && current_direction == 3) {
            python.y[0] -= 1;
            current_direction = 1;
        }
        else if(python.direction[0] == 2 && current_direction == 0) {
            python.x[0] += 1;
            current_direction = 2;
        }
        else if(python.direction[0] == 3 && current_direction == 1) {
            python.y[0] += 1;
            current_direction = 3;
        }
        else {
            if (current_direction == 0) {
                python.x[0] -= 1 ;
            } else if (current_direction == 1) {
                python.y[0] -= 1 ;
            } else if (current_direction == 2) {
                python.x[0] += 1 ;
            } else if (current_direction == 3) {
                python.y[0] += 1 ;
            }
        }
    }

    //python.direction[0] = current_direction ;

    // TODO 3: Check if the game is over. If not, update python.board_occupied.
    if (python.board_occupied[python.x[0]][python.y[0]] != false || python.x[0] < 0 || python.x[0] >= col_num || python.y[0] < 0 || python.y[0] >= row_num) {
        game_running = false ;
    } else {
        python.board_occupied[python.x[0]][python.y[0]] = true ;
    }

    // TODO 4: Add a new body part to python if python's head is at the same position as the apple. 
    // TODO 4: Remember to set the position, direction, and color for the new body part. 
    // TODO 4: Also, remember to update python.length and python.board_occupied.
    if (apple.x == python.x[0] && apple.y == python.y[0]) {
        python.length++ ;
        python.x[python.length - 1] = last_x ;
        python.y[python.length - 1] = last_y ;
        python.direction[python.length - 1] = last_direction ;
        python.colors[python.length - 1] = apple.color ;
        python.board_occupied[python.x[python.length - 1]][python.y[python.length - 1]] = python.length - 1 ;
    }

    // check python.length
    if (python.length == row_num * col_num) {
        game_running = false ;
        win_game = true ;
    }
}


void draw_python() {
    extern Python python ;
    extern sf::RenderWindow window ;

    // set head
    python.sprites[0].setTexture(python.head) ;
    python.sprites[0].setOrigin(python.sprites[0].getLocalBounds().width / 2, python.sprites[0].getLocalBounds().height / 2) ;
    python.sprites[0].setRotation(90.0f * python.direction[0]) ;
    python.sprites[0].setPosition(python.x[0] * grid_length + board_left + grid_length / 2, python.y[0] * grid_length + board_top + grid_length / 2) ;
    // set body
    for (int i = 1; i < python.length; i++) {
        python.sprites[i].setTexture(python.body_images[python.colors[i]]) ;
        python.sprites[i].setOrigin(python.sprites[i].getLocalBounds().width / 2, python.sprites[i].getLocalBounds().height / 2) ;
        python.sprites[i].setRotation(90.0f * python.direction[i]) ;
        python.sprites[i].setPosition(python.x[i] * grid_length + board_left + grid_length / 2, python.y[i] * grid_length + board_top + grid_length / 2) ;
    }

    // display all
    for (int i = 0; i < python.length; i++) {
        window.draw(python.sprites[i]) ;
    }
}

void auto_mode() {
    extern Python python ;
    extern int current_direction ;

    // TODO: Set current_direction for auto mode. The direction you set will change python's position in the next frame.
    // TODO: For example, suppose Python is currently positioned at (x, y), and you set current_direction to 0. Then, in the next frame, Python will move to (x - 1, y).
    if (python.y[0] == row_num - 1 && python.x[0] != 0) {
        current_direction = 0 ;
    } else if (python.x[0] % 2 == 0) {
        if (python.y[0] != 0) {
            current_direction = 1 ;
        } else {
            current_direction = 2 ;
        }
    } else if (python.x[0] % 2 == 1) {
        if (python.y[0] < row_num - 2 || python.x[0] == col_num - 1) {
            current_direction = 3 ;
        } else {
            current_direction = 2 ;
        }
    }
}