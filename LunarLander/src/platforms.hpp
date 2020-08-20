//
//  platforms.hpp
//  testSFML
//
//  Created by Dalton Bennett on 9/19/19.
//
#pragma once
#ifndef platforms_hpp
#define platforms_hpp

#include <SFML/Graphics.hpp>
#include <stdio.h>

///Class for the Landing platforms
class Platform{
public:
    //constructor
    Platform();
    
    //member variables
    sf::RectangleShape shape;
    int pointVal;
    sf::FloatRect boundingBox;
};

#endif /* platforms_hpp */
