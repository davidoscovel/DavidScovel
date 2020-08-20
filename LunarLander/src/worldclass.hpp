//
//  worldclass.hpp
//  testSFML
//
//  Created by David Scovel on 9/17/19.
//
#pragma once
#ifndef worldclass_hpp
#define worldclass_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "spaceship.hpp"
#include "terrain.hpp"
#include "platforms.hpp"

///A class that contains all the elements of the game's "World"
class World{
    
public:
    Ship ship;
    sf::VertexArray terrain;
    float gravity;
    float x;
    float y;
    int fuelCount;
    int pointCount;
    Platform platform;
    sf::Text text;
    sf::Text crashedText;
    sf::Font font;
    std::vector<Platform> platforms;
    
    //Constructor
    World(){
        
        //Create the Lunar Rover/ship
        ship = Ship();
        
        //Build Terrain
        terrain = build_terrain();
        
        //Create landing platforms
        platforms = createPlatforms();
        
        //Initializing gravity and velocity
        gravity = .00003;
        x = 100;
        y = 200;
        
        //Initializing Text for fuel and point display
        fuelCount = ship.fuel;
        pointCount = 0;
        font.loadFromFile("Roboto-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::White);
        text.setPosition(1600, 75);
        
        //initializing test for crashing
        crashedText.setString("CRASHED! \n Press enter to restart.");
        crashedText.setFont(font);
        crashedText.setCharacterSize(36);
        crashedText.setFillColor(sf::Color::Red);
        crashedText.setPosition(600, 600);
        
    }
    
    //Methods
    //Draw
    void draw_world(sf::RenderWindow& window);
    
    //Update
    void update_world();
    
    //Keyboard Input
    void keyboard_input();
    
    //Collision
    bool contact(const Ship& ship, const sf::VertexArray& terrain);
    bool line_contact(const Ship& ship, const sf::Vector2f& a_p1, const sf::Vector2f& a_p2);
    bool contactLP(const Ship& ship);
    
    std::vector<Platform> createPlatforms();
    
    //Successful or Unsuccessful Landing
    //See if the ships landing is successful
    bool successful_landing(const Ship& ship);
    
    //Unsuccessful
    bool unsuccessful_landing(const Ship& ship);
    
    //Method that resets the ship
    void reset_world();

};







#endif /* worldclass_hpp */
