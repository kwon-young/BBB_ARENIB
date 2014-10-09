
#ifndef I2C_INTERFACE
#define I2C_INTERFACE

#include "utils.hpp"

class I2c_interface {

  public:
    I2c_interface(int bus, char slave_addr);
    I2c_interface(I2c_interface &my_i2c_interface);
    ~I2c_interface();

    void i2c_write(char reg_addr, char *buffer=NULL, int length=0);
    void i2c_read(char reg_addr, char *buffer, int length);

    
  protected:
    int _bus;
    char _slave_addr;
    char _name_bus[42];
    int _fd;
};


#endif

