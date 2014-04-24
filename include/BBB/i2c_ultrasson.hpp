
#ifndef I2C_ULTRASSON_HPP
#define I2C_ULTRASSON_HPP

#include "i2c_interface.hpp"

class I2c_ultrasson : public I2c_interface {

  public:
    I2c_ultrasson(int bus, uint8_t slave_addr);
    virtual ~I2c_ultrasson();

    float get_distance();
};


/*
#ifdef REEL
I2c_ultrasson ultrason(42,42);
#elif SIMU
Simu_ultrasson ultrason(fdhjidfshui);
#endif

ultrason.get_distance(); // marche directement
*/
#endif
