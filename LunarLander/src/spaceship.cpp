//
//  spaceship.cpp
//  testSFML
//
//  Created by Dalton Bennett on 9/17/19.
//

#include "spaceship.hpp"
#include "worldclass.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

//Ship default constructor
//sets size, color, initial position, velocities, and fuel amount
Ship::Ship(){
    shape.setSize(sf::Vector2f(20.f, 40.f));
    shape.setFillColor(sf::Color(105,105,105));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);
    shape.setPosition(100.f, 200.f);
    shape.setOrigin(10.f, 30.f);
    xVelocity = 0.05;
    yVelocity = 0;
    fuel = 20000;
}

//function to see if space bar is pressed
//this function calculates new velocities based on the ship's rotation and angular acceleration and subtracts fuel from the fuel total
bool Ship::spacePressed(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        yVelocity -= 0.0001 * sin((shape.getRotation()+90)*float(3.14159265)/180);
        xVelocity -= 0.0001 * cos((shape.getRotation()+90)*float(3.14159265)/180);
        fuel -= 1;
    }
};

//function to change ship's rotation to the left if the left arrow is pressed
bool Ship::leftPressed(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        shape.rotate(-0.08);
    }
};

//function to change ship's rotation to the right if the right arrow is pressed
bool Ship::rightPressed(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        shape.rotate(0.08);
    }
};
