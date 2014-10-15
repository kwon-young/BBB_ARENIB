
#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "utils.hpp"

class Robot {

  public:
    Robot(float largeur, float hauteur);
	~Robot();
	
	avance(float distance, float angle);
	tourne(float angle);
	
	sf::RectangleShape surface_robot;
	
  private:
    sf::Vector2f obj;
};


#endif

