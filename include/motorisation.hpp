
#ifndef MOTORISATION_HPP
#define MOTORISATION_HPP

#include "utils.hpp"

#ifndef SIMULATION
struct _i2c_packet {
  uint16_t Type;
  int16_t X;
  int16_t Y;
  int16_t Theta;
  _i2c_packet();
};

#endif

struct _Commande
{
  uint8_t Type ;
  double X ;
  double Y ;
  double Theta ;
  _Commande();
  _Commande(uint8_t myType, double myX, double myY, double myTheta);
};

class Motorisation {

  public:
    Motorisation(unsigned int etat, double posX, double posY, double theta);
    ~Motorisation();

    int get_angle();
    int get_position();

    int envoie_ordre();

    void update();
    
#ifndef SIMULATION
    struct _i2c_packet i2c_envoie;
#endif
    struct _Commande etat_courant;
    struct _Commande avance;
    struct _Commande tourne;
};

#endif
