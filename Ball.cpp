//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Jessie Zhou, Sept 22, 2024
#include "Ball.h"
#include <iostream>

Ball::Ball() : x(0), y(0), velocity_x(0), velocity_y(0), id(0), width(1), height(1) {}

Ball::Ball(double x, double y, double velocity_x, double velocity_y, int id) 
    : x(x), y(y), velocity_x(velocity_x), velocity_y(velocity_y), id(id), width(1), height(1) {}

double Ball::getX() {
    return x;
}

int Ball::getID() {
    return id;
}

void Ball::update() {
    //accounting for the change in velocity from gravity 
    velocity_y -= timeStep * 0.02;
    
    //updates the x, y coordinates of the ping-pong ball
    x += velocity_x * timeStep;
    y += velocity_y * timeStep;
}

int Ball::overlap(Ball& b) {
    // ball
    double bLB1x = x; // bottom left x
    double bLB1y = y; // bottom left y
    double bRB1x = x + width; // bottom right x
    double tLB1x = x; // top left x
    double tLB1y = y + height; // top left y
    double tRB1x = x + width; // top right x
    double tRB1y = y + height; // top right y

    // ball b 
    double bLBBx = b.x; // bottom left x
    double bLBBy = b.y; // bottom left y
    double bRBBx = b.x + b.width; // bottom right x
    double tLBBx = b.x; // top left x
    double tLBBy = b.y + b.height; // top left y
    double tRBBx = b.x + b.width; // top right x
    double tRBBy = b.y + b.height; // top right y

    bool horizontalOverlap = (std::abs(bRB1x - bLBBx) <= std::abs(bRBBx - bLB1x));
    bool verticalOverlap = (std::abs(tLB1y - bLBBy) <= std::abs(tRBBy - bLB1y));

    if (horizontalOverlap && verticalOverlap) {
        if ((bRB1x - bLBBx) < (tLB1y - bLBBy)) {
            return VERTICAL_OVERLAP;
        } else {
            return HORIZONTAL_OVERLAP;
        }
    } else if (horizontalOverlap) {
        return HORIZONTAL_OVERLAP;
    } else if (verticalOverlap) {
        return VERTICAL_OVERLAP;
    } else {
        return NO_OVERLAP;
    }
}

int Ball::overlap(Player& p) {
    double bLB1x = x; // bottom left x
    double bLB1y = y; // bottom left y
    double bRB1x = x + width; // bottom right x
    double tLB1y = y + height; // top left y

    // player p 
    double bLPPx = p.getX(); // bottom left x
    double bLPPy = p.getY(); // bottom left y
    double bRPPx = p.getX() + p.getWidth(); // bottom right x
    double tLPPy = p.getY() + p.getHeight(); // top left y

    bool horizontalOverlap = (std::abs(bRB1x >= bLPPx)) && std::abs((bLB1x <= bRPPx));
    bool verticalOverlap = (std::abs(tLB1y >= bLPPy)) && std::abs((bLB1y <= tLPPy));

    if (horizontalOverlap && verticalOverlap) {
        if ((tLB1y - bLPPy) < (bRB1x - bLPPx)) {
            return VERTICAL_OVERLAP;
        } else {
            return HORIZONTAL_OVERLAP;
        }
    } else if (horizontalOverlap) {
        return HORIZONTAL_OVERLAP;
    } else if (verticalOverlap) {
        return VERTICAL_OVERLAP;
    } else {
        return NO_OVERLAP;
    }
}
 
void Ball::bounce(Ball arr[], int ballCount, Player player) {
    for (int i = 0; i < ballCount; i++) {
        if (overlap(arr[i]) == VERTICAL_OVERLAP) {
            velocity_x = -velocity_x;
        }
        else if (overlap(arr[i]) == HORIZONTAL_OVERLAP) {
            velocity_y = -velocity_y;
        }
    }

    if (overlap(player) == VERTICAL_OVERLAP) {
        velocity_x = -velocity_x;
    }
    else if (overlap(player) == HORIZONTAL_OVERLAP) {
        velocity_y = -velocity_y;
    }
}   

void Ball::draw(Screen& screen_to_draw_to) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            screen_to_draw_to.addPixel(x + i, y + j, 'o');
        }
    }
}


