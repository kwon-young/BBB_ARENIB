
#ifndef I2C_LM75
#define I2C_LM75

#include "i2c_slave.hpp"

#define TEMPERATURE_ADDR 0x0
#define CONFIGURATION_ADDR 0x1
#define THYST_ADDR 0x2
#define TOS_ADDR 0x3

#ifndef SIMULATION

class LM75 : public i2c_slave {

  public:
    LM75(i2c_bus& bus, uint8_t addr);
    virtual ~LM75();

    float temp_hextofloat(uint8_t * temp_hex);
    void temp_floattohex(uint8_t * temp_hex, float temp_float);

    float get_temp();
  private:
};

#endif //SIMULATION
#endif //HEADER

