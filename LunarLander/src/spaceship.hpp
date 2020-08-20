//
//  spaceship.hpp
//  testSFML
//
//  Created by Dalton Bennett on 9/17/19.
//
#pragma once
#ifndef spaceship_hpp
#define spaceship_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

///Class for the vessel that the user will pilot
class Ship{
public:
    Ship();
    
    sf::RectangleShape shape;
    
    bool spacePressed();
    bool leftPressed();
    bool rightPressed();
    
    double xVelocity;
    double yVelocity;
    int fuel;
    
    sf::FloatRect boundingBox;
    
    
};



#endif /* spaceship_hpp */
