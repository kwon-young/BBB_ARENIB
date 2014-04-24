
#ifndef I2C_TOURELLE_HPP
#define I2C_TOURELLE_HPP

#ifndef SIMULATION
#include "i2c_interface.hpp"
#endif

typedef struct _i2c_tourelle{
  uint8_t distance;
  uint16_t angle;
}I2c_tourelle;

#ifndef SIMULATION
class Tourelle : public I2c_interface {
#endif

  public:
    Tourelle(int bus, uint8_t slave_addr, int my_nbr_mesures);
    virtual ~Tourelle();

    int get_datas();
    int get_error();
    int set_instruction(uint8_t instruction);

    int nbr_mesures;
    I2c_tourelle *datas;
    double *distances;
    double *angles;
    uint8_t error;
};

#endif

