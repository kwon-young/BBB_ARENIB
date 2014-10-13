
#ifndef I2C_ULTRASSON_HPP
#define I2C_ULTRASSON_HPP

#include "i2c_interface.hpp"

class I2c_ultrasson : public I2c_interface {

  public:
    I2c_ultrasson(int bus, char slave_addr);
    virtual ~I2c_ultrasson();

    float get_distance();
};

#endif
