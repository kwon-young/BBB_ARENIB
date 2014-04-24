
#ifndef I2C_LM75
#define I2C_LM75

#include "i2c_interface.hpp"

#define TEMPERATURE_ADDR 0x0
#define CONFIGURATION_ADDR 0x1
#define THYST_ADDR 0x2
#define TOS_ADDR 0x3

class I2c_LM75 : public I2c_interface {

  public:
    I2c_LM75(int bus, uint8_t slave_addr);
    virtual ~I2c_LM75();

    float temp_hextofloat(uint8_t * temp_hex);
    void temp_floattohex(uint8_t * temp_hex, float temp_float);

    float get_temp();
  private:
};

#endif

