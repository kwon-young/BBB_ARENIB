
#include "robot.hpp"

Robot::Robot(double l, double h, int i2c_bus, uint8_t asserv_addr) :
#ifdef SIMULATION
surface_robot(sf::Vector2f(l, h)),
#else
largeur(l),
hauteur(h),
#endif
asserv(i2c_bus, asserv_addr, STOP, 0.0, 0.0, 0.0)
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
