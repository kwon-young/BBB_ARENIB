
#ifndef MOTORISATION_HPP
#define MOTORISATION_HPP

// Ce sont les différents états du robot
#define STOP_F          1
#define AVANCE          2
#define TOURNE          3
#define STOP            4
#define POSITION_W      5
#define AVANCE_Free     6
#define POSITION_R      7
#define BLOQUE          8
#define AVANCE_TOURNE   9
#define ORDRE_RECU_MAIS_PAS_ENCORE_TRAITE       20 //pour i2c

#include "utils.hpp"
#ifndef SIMULATION
#include "i2c_interface.hpp"
#endif

#ifndef SIMULATION
struct i2c_packet {
  uint8_t Type;
  uint8_t X[4];
  uint8_t Y[4];
  uint8_t Theta[4];
};

#endif

struct commande
{
  uint8_t Type ;
  double X ;
  double Y ;
  double Theta ;
};

class Motorisation {

  public:
    Motorisation(unsigned int etat, double posX, double posY, double theta);
    ~Motorisation();

    int set_position();
    int get_position();

    int avance(double obj_X, double obj_Y);
    int tourne(double obj_Theta);
    int avance_tourne(double obj_X, double obj_Y, double obj_Theta);

    int commandeToI2c_packet();
    int i2c_packetToEtat_courant();

    void update();

#ifndef SIMULATION
    I2c_interface my_i2c_interface;
#endif
    struct i2c_packet i2c_envoie;
    struct commande commande_etat_courant;
    struct commande commande_avance;
};

#endif
