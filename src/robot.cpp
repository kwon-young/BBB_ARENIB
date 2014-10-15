
#include "robot.hpp"

Robot::Robot(double l, double h) :
#ifdef SIMULATION
surface_robot(sf::Vector2f(l, h))
#else
largeur(l),
hauteur(h)
#endif
{
}

Robot::~Robot() {
}
    
#ifdef SIMULATION
void Robot::draw(sf::RenderWindow &window) {
  window.draw(surface_robot);
}
#endif

void Robot::update() {

}