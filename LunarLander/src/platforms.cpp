//
//  platforms.cpp
//  testSFML
//
//  Created by Dalton Bennett on 9/19/19.
//

#include "platforms.hpp"

//Platform constructor
Platform::Platform(){
    shape.setSize(sf::Vector2f(0,0));
    shape.setPosition(0, 0);
    shape.setFillColor(sf::Color::White);
    pointVal = 0;
    boundingBox = sf::FloatRect(0,0,0,0);
}
