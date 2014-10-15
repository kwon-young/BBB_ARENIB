
#include "motorisation.hpp"

#ifndef SIMULATION
_i2c_packet::_i2c_packet() :
  Type(0),
  X(0),
  Y(0),
  Theta(0)
{
}
#endif

_Commande::_Commande() :
  Type(0),
  X(0),
  Y(0),
  Theta(0)
{
}

_Commande::_Commande(uint8_t myType, double myX, double myY, double myTheta) :
  Type(myType),
  X(myX),
  Y(myY),
  Theta(myTheta)
{
}

Motorisation::Motorisation(unsigned int etat, double posX, double posY, double theta) :
#ifndef SIMULATION
  i2c_envoie(),
#endif
  etat_courant(etat, posX, posY, theta),
  avance(),
  tourne()
{
}

Motorisation::~Motorisation() {
}

int Motorisation::get_angle() {
  return 0;
}
int Motorisation::get_position() {
  return 0;
}

int Motorisation::envoie_ordre(){
  return 0;
}

void Motorisation::update() {
}

