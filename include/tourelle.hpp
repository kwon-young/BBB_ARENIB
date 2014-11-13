
#ifndef I2C_TOURELLE_HPP
#define I2C_TOURELLE_HPP

#include "utils.hpp"
#include "i2c_slave.hpp"


class Tourelle : public i2c_slave {

  public:
	typedef struct _i2c_packet{
	  uint8_t distance;
	  uint16_t angle;
	} i2c_packet;
  
    Tourelle(i2c_bus& bus, uint8_t slave_addr, int my_nbr_mesures);
    virtual ~Tourelle();

    int get_datas();
    int get_error();
    int set_instruction(uint8_t instruction);

    int nbr_mesures;
    i2c_packet *datas;
    double *distances;
    double *angles;
    uint8_t error;
};

#endif

