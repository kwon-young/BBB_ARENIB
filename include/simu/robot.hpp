
#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "utils.hpp"
#include <SFML/Graphics.hpp>

class Robot {

  public:
    Robot(float largeur, float hauteur, const sf::Color & my_couleur_robot, float pas_U, float pas_theta);
	~Robot();
	
	void set_pos(sf::Vector2f pos);
	
	void avance(sf::Vector2f pos, float angle);
	void tourne(float angle);
	
	int simu_tourne();
	int simu_avance();
	
	sf::RectangleShape surface_robot;
    sf::Vector2f obj_pos;
	float obj_angle;

  private:
	float _pas_U;
	float _pas_theta;
	
};


#endif

