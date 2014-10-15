
#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "utils.hpp"


class Robot {
  public:
    Robot(double l, double h);
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
};

#endif
