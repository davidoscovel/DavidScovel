//
//  terrain.cpp
//  testSFML
//
//  Created by David Scovel on 9/17/19.
//

#include "terrain.hpp"
#include "worldclass.hpp"
#include <SFML/Graphics.hpp>

//default constructor to build terrain for a 2000x1500 window

sf::VertexArray build_terrain(){
    sf::VertexArray terrain(sf::LineStrip, 40);
    terrain[0].position = sf::Vector2f(0.f, 1100.f);
    terrain[1].position = sf::Vector2f(40.f, 1125.f);
    terrain[2].position = sf::Vector2f(80.f, 1125.f);
    terrain[3].position = sf::Vector2f(100.f, 1160.f);
    terrain[4].position = sf::Vector2f(140.f, 1200.f);
    terrain[5].position = sf::Vector2f(200.f, 1200.f);
    terrain[6].position = sf::Vector2f(250.f, 1130.f);
    terrain[7].position = sf::Vector2f(275.f, 1125.f);
    terrain[8].position = sf::Vector2f(300.f, 1000.f);
    terrain[9].position = sf::Vector2f(350.f, 900.f);
    terrain[10].position = sf::Vector2f(400.f, 850.f);
    terrain[11].position = sf::Vector2f(450.f, 850.f);
    terrain[12].position = sf::Vector2f(500.f, 810.f);
    terrain[13].position = sf::Vector2f(525.f, 830.f);
    terrain[14].position = sf::Vector2f(570.f, 830.f);
    terrain[15].position = sf::Vector2f(600.f, 800.f);
    terrain[16].position = sf::Vector2f(625.f, 735.f);
    terrain[17].position = sf::Vector2f(650.f, 710.f);
    terrain[18].position = sf::Vector2f(680.f, 710.f);
    terrain[19].position = sf::Vector2f(700.f, 810.f);
    terrain[20].position = sf::Vector2f(750.f, 865.f);
    terrain[21].position = sf::Vector2f(800.f, 924.f);
    terrain[22].position = sf::Vector2f(900.f, 1100.f);
    terrain[23].position = sf::Vector2f(925.f, 1200.f);
    terrain[24].position = sf::Vector2f(1050.f, 1300.f);
    terrain[25].position = sf::Vector2f(1150.f, 1300.f);
    terrain[26].position = sf::Vector2f(1240.f, 1400.f);
    terrain[27].position = sf::Vector2f(1280.f, 1430.f);
    terrain[28].position = sf::Vector2f(1310.f, 1390.f);
    terrain[29].position = sf::Vector2f(1350.f, 1250.f);
    terrain[30].position = sf::Vector2f(1430.f, 1120.f);
    terrain[31].position = sf::Vector2f(1500.f, 1000.f);
    terrain[32].position = sf::Vector2f(1570.f, 1000.f);
    terrain[33].position = sf::Vector2f(1600.f, 1100.f);
    terrain[34].position = sf::Vector2f(1640.f, 1300.f);
    terrain[35].position = sf::Vector2f(1700.f, 1400.f);
    terrain[36].position = sf::Vector2f(1800.f, 1400.f);
    terrain[37].position = sf::Vector2f(1870.f, 1320.f);
    terrain[38].position = sf::Vector2f(1940.f, 1300.f);
    terrain[39].position = sf::Vector2f(2000.f, 1300.f);
    
    return terrain;
}


