//
//  worldclass.cpp
//  testSFML
//
//  Created by David Scovel on 9/18/19.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "worldclass.hpp"

//Methods
//Draw the ship and terrain onto the window
void World::draw_world(sf::RenderWindow& window){
    window.draw(terrain);
    window.draw(ship.shape);
    window.draw(text);
    //draw landing platforms
    for(Platform p : platforms){
        window.draw(p.shape);
    }
}

//Updates the world at the end of each frame
void World::update_world(){
    ship.yVelocity += gravity;
    y += ship.yVelocity;
    x += ship.xVelocity;
    ship.shape.setPosition(x, y);
    fuelCount = ship.fuel;
    std::string string = std::to_string(fuelCount/100);
    std::string XVstring = std::to_string(int(ship.xVelocity*300));
    std::string YVstring = std::to_string(int(ship.yVelocity*300));
    std::string pointString = std::to_string(pointCount);
    text.setString("Points: " +pointString + "\nFuel remaining: " + string +"\nX Vel: " + XVstring + "\nY Vel: " + YVstring);
    //ship.boundingBox = ship.shape.getGlobalBounds();
}

//Rotate or propel the ship based on user input
void World::keyboard_input(){
    //rotate the ship based on user interaction
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        ship.leftPressed();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        ship.rightPressed();
    }
    //if there is still fuel and space is pressed, propulsion
    if(fuelCount > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        ship.spacePressed();
    }
}

//See if the ship has made contact with the terrain
bool World::contact(const Ship& ship, const sf::VertexArray& terrain){
    for(int i = 0; i < terrain.getVertexCount() -1; i++){
        sf::Vector2f point1 = terrain[i].position;
        sf::Vector2f point2 = terrain[i + 1].position;
        if(line_contact(ship, point1, point2)){
            return true;
        }
        if(ship.shape.getGlobalBounds().contains(terrain[i].position)){
            return true;
            }
        }
    if(contactLP(ship)){
        return true;
    }
    //if statement velocity, location, angle
    return false;
}

//See if the ship has made contact with the lines between points in terrain
bool World::line_contact(const Ship& ship, const sf::Vector2f& point1, const sf::Vector2f& point2){
    float x = point1.x;
    float y = point1.y;
    float x_slope = (point2.x - point1.x)/100;
    float y_slope = (point2.y - point1.y)/100;
    if(x > point2.x){
        while(int(x) > int(point2.x)){
            if(ship.shape.getGlobalBounds().contains(x,y)){
                return true;
            }
            x += x_slope;
            y += y_slope;
        }
    }
    if(x < point2.x){
        while(int(x) < int(point2.x)){
            if(ship.shape.getGlobalBounds().contains(x,y)){
                return true;
            }
            x += x_slope;
            y += y_slope;
        }
    }
    return false;
}

//See if ship has made contact with landing pads
bool World::contactLP(const Ship& ship){
    for(Platform p: platforms){
        if(ship.shape.getGlobalBounds().intersects(p.boundingBox)){
            return true;
        }
    }
    return false;
}

//See if the ships landing is successful
bool World::successful_landing(const Ship& ship){
    //if statement based on if ship is contacting landing pad, x and y velocity, and angle at touchdown
    if(contactLP(ship) && ((ship.xVelocity < 0.018) && (ship.xVelocity > -0.018)) && ((ship.yVelocity < 0.04) && (ship.yVelocity >= 0)) && ((ship.shape.getRotation() > 340) || (ship.shape.getRotation() < 20))){
        for(Platform p: platforms){
            if(ship.shape.getGlobalBounds().intersects(p.boundingBox)){
                pointCount += p.pointVal;
            }
        }
        return true;
    }
    return false;
}

//tests to see if ship unsuccessfully landed on a landing platform or if it contacted the terrain
bool World::unsuccessful_landing(const Ship& ship){
    if(!successful_landing(ship) && contact(ship, terrain)){
        return true;
    }
    return false;
}

//initialize and store all landing platforms in a vector of platforms for drawing in draw_world function
std::vector<Platform> World::createPlatforms(){
    std::vector<Platform> platforms;
    Platform platform1;
    platform1.shape.setSize(sf::Vector2f(60.f, 10.f));
    platform1.shape.setPosition(sf::Vector2f(140.f, 1190.f));
    platform1.shape.setFillColor(sf::Color::Red);
    platform1.boundingBox = sf::FloatRect(140.f, 1190.f, 60.f, 10.f);
    platform1.pointVal = 100;
    platforms.push_back(platform1);
    
    Platform platform2;
    platform2.shape.setSize(sf::Vector2f(50.f, 10.f));
    platform2.shape.setPosition(sf::Vector2f(400.f, 840.f));
    platform2.shape.setFillColor(sf::Color::Blue);
    platform2.boundingBox = sf::FloatRect(400.f, 840.f, 50.f, 10.f);
    platform2.pointVal = 250;
    platforms.push_back(platform2);
    
    Platform platform3;
    platform3.shape.setSize(sf::Vector2f(50.f, 10.f));
    platform3.shape.setPosition(sf::Vector2f(525.f, 820.f));
    platform3.shape.setFillColor(sf::Color::Blue);
    platform3.boundingBox = sf::FloatRect(525.f, 820.f, 50.f, 10.f);
    platform3.pointVal = 250;
    platforms.push_back(platform3);
    
    Platform platform4;
    platform4.shape.setSize(sf::Vector2f(30.f, 10.f));
    platform4.shape.setPosition(sf::Vector2f(650.f, 700.f));
    platform4.shape.setFillColor(sf::Color(255,215,0));
    platform4.boundingBox = sf::FloatRect(650.f, 700.f, 30.f, 10.f);
    platform4.pointVal = 500;
    platforms.push_back(platform4);
    
    Platform platform5;
    platform5.shape.setSize(sf::Vector2f(100.f, 10.f));
    platform5.shape.setPosition(sf::Vector2f(1050.f, 1290.f));
    platform5.shape.setFillColor(sf::Color::Red);
    platform5.boundingBox = sf::FloatRect(1050.f, 1290.f, 100.f, 10.f);
    platform5.pointVal = 100;
    platforms.push_back(platform5);
    
    Platform platform6;
    platform6.shape.setSize(sf::Vector2f(70.f, 10.f));
    platform6.shape.setPosition(sf::Vector2f(1500.f, 990.f));
    platform6.shape.setFillColor(sf::Color::Blue);
    platform6.boundingBox = sf::FloatRect(1500.f, 990.f, 70.f, 10.f);
    platform6.pointVal = 250;
    platforms.push_back(platform6);
    
    Platform platform7;
    platform7.shape.setSize(sf::Vector2f(100.f, 10.f));
    platform7.shape.setPosition(sf::Vector2f(1700.f, 1390.f));
    platform7.shape.setFillColor(sf::Color::Red);
    platform7.boundingBox = sf::FloatRect(1700.f, 1390.f, 100.f, 10.f);
    platform7.pointVal = 100;
    platforms.push_back(platform7);
    return platforms;
}

//Reset the world
void World::reset_world(){
    ship.shape.setPosition(100.f, 200.f);
    ship.xVelocity = 0.05;
    ship.yVelocity = 0;
    gravity = .00003;
    x = 100;
    y = 200;
    ship.shape.setRotation(0);
}
