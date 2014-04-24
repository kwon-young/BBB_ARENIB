
#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "utils.hpp"
#include "motorisation.hpp"

class Robot {
  public:
    Robot(double l, double h, int i2c_bus, uint8_t asserv_addr);
    ~Robot();
    
#ifdef SIMULATION
    void draw(sf::RenderWindow &window);
#endif
    void update();

#ifdef SIMULATION
    sf::RectangleShape surface_robot;
#else
    double largeur;
    double hauteur;
#endif
    Motorisation asserv;
};

#endif
