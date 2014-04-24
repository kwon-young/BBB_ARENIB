
#ifndef I2C_INTERFACE
#define I2C_INTERFACE

#include "utils.hpp"

class I2c_interface {

  public:
    I2c_interface(int bus, char slave_addr);
    I2c_interface(const I2c_interface &my_i2c_interface);
    virtual ~I2c_interface();

    int i2c_write(uint8_t reg_addr, uint8_t *buffer=NULL, int length=0);
    int i2c_read(uint8_t reg_addr, uint8_t *buffer, int length);

    
  protected:
    int _bus;
    char _slave_addr;
    char _name_bus[42];
    int _fd;
};


#endif

