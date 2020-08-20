#include <SFML/Graphics.hpp>
#include "spaceship.hpp"
#include "terrain.hpp"
#include <string>
#include "worldclass.hpp"
#include <iostream>
///Lunar lander game
int main()
{
    
    //World default constructor to construct the game world: terrain, landing platforms, ship
    World world = World();

    sf::RenderWindow window(sf::VideoMode(2000, 1500), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
       
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // clear the window with grey color
        window.clear(sf::Color(105, 105, 105));
        
        //reads keyboard input from user to manipulate ship
        world.keyboard_input();
        
        //draws elements of world to the window
        world.draw_world(window);
       
        //Updating the world each frame
        world.update_world();
        
        //checks to see if ship lands successfully on landing platform. Sets gravity and velocities to 0 and resets ship position for next round
        if(world.successful_landing(world.ship)){
            std::cout << "successful\n";
            world.gravity = 0;
            world.ship.xVelocity = 0;
            world.ship.yVelocity = 0;
            if(world.ship.fuel > 0){
            world.reset_world();
            }
        }
        
        //Resets ship position for next round when ship crashes into terrain or unsuccessfully lands on landing platform
        if(world.unsuccessful_landing(world.ship)){
            std::cout << "CRASHED!\n";
            if(world.ship.fuel > 0){
            world.reset_world();
            }
        }
        
        // end the current frame
        window.display();
        
    }
    return 0;
}
