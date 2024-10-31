//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Jessie Zhou, Sept 22, 2024
#include "Player.h"
#include <iostream> 

Player::Player() {
    x = 0;
    y = 0;
    height = 1;
    width = 1;
}

double Player::getX(){
    return x;
}

double Player::getY(){
    return y;
}

int Player::getHeight(){
    return height;
}

int Player::getWidth(){
    return width;
}

void Player::decreaseHeight(int delta_to_decrease_by){
    if (height - delta_to_decrease_by > 3) {
        height = height - delta_to_decrease_by; ///minimum height is 3
    }
}

void Player::update(char c) {  //tbh idk if this is right
//paddle going up
    if (c == 'A') {
        y += 2;
        //checking to see if the paddle went over the ceiling
        if (y < 0 ) {
            y = 0; 
        }
    }
    //going down
    else if (c == 'B') {
        y -= 2;
        //check if paddle went below the screen
        if (y > HEIGHT - 1) {
            y = HEIGHT - 1;
        }
    }
}

void Player::draw(Screen& screen_to_draw_to) {
    int paddleH = height; 

    for (int i = 0; i < paddleH; ++i){
        screen_to_draw_to.addPixel(x, y + i, '#');
    }

}
