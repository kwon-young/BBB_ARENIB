
#include "robot.hpp"

Robot::Robot(float largeur, float hauteur, const sf::Color & my_couleur_robot, float pas_U, float pas_theta):
surface_robot(sf::Vector2f(largeur, hauteur)),
obj_pos(0.0,0.0),
obj_angle(0.0),
_pas_U(pas_U),
_pas_theta(pas_theta)
{
  surface_robot.setFillColor(my_couleur_robot);
  surface_robot.setPosition(0,0);
  surface_robot.setOrigin(sf::Vector2f((surface_robot.getSize().x)/2.0, (surface_robot.getSize().y)/2.0));
}

Robot::~Robot()
{}

void Robot::set_pos(sf::Vector2f pos) {
  surface_robot.setPosition(pos);
  obj_pos.x=pos.x;
  obj_pos.y=pos.y;
}

void Robot::avance(sf::Vector2f pos, float angle) {
  obj_pos.x=pos.x;
  obj_pos.y=pos.y;
  obj_angle=angle;
}

void Robot::tourne(float angle) {
  obj_angle=angle;
}

int Robot::simu_tourne() {
  if (fabs(fmod(obj_angle-surface_robot.getRotation(), 360.0)) >=_pas_theta) {
    if (obj_angle > surface_robot.getRotation()) {
	  surface_robot.setRotation(surface_robot.getRotation()+_pas_theta);
	} else {
	  surface_robot.setRotation(surface_robot.getRotation()-_pas_theta);
	}
	return 1;
  } else {
    surface_robot.setRotation(obj_angle);
	return 0;
  }
}

int Robot::simu_avance() {
  float distance=(obj_pos-surface.getPosition()).x * (obj_pos-surface.getPosition()).x + 
                 (obj_pos-surface.getPosition()).y * (obj_pos-surface.getPosition()).y;
  if (!simu_tourne()) {
    if (distance >= _pas_U) {
	  
    }
  }
}




























