
#include "i2c_interface.hpp"

I2c_interface::I2c_interface(int bus, uint8_t slave_addr) :
_bus(bus),
_slave_addr(slave_addr)
{
  int r;

  snprintf(_name_bus, sizeof(_name_bus), "/dev/i2c-%d", _bus);
  
  RESTART_SYSCALL(_fd, open(_name_bus, O_RDWR));
  if (_fd==-1) {
    printf("open %s", _name_bus);
    perror("");
  }
  
  RESTART_SYSCALL(r, ioctl(_fd, I2C_SLAVE, _slave_addr));
  if (r==-1) {
    printf("ioctl %s", _name_bus);
    perror("");
  }
}

I2c_interface::I2c_interface(const I2c_interface &my_i2c_interface) :
_bus(my_i2c_interface._bus),
_slave_addr(my_i2c_interface._slave_addr)
{
  int r;

  snprintf(_name_bus, sizeof(_name_bus), "/dev/i2c-%d", _bus);
  
  RESTART_SYSCALL(_fd, open(_name_bus, O_RDWR));
  if (_fd==-1) {
    printf("open %s", _name_bus);
    perror("");
  }
  
  RESTART_SYSCALL(r, ioctl(_fd, I2C_SLAVE, _slave_addr));
  if (r==-1) {
    printf("ioctl %s", _name_bus);
    perror("");
  }
}

I2c_interface::~I2c_interface() {
  int r;
  RESTART_SYSCALL(r, close(_fd));
  if (r==-1) {
    printf("close %s", _name_bus);
    perror("");
  }
}

int I2c_interface::i2c_read(uint8_t reg_addr, uint8_t * buffer, int length) {
  int r;

  r=i2c_write(reg_addr);
  if (r==-1) {
    return -1;
  }
  RESTART_SYSCALL(r, read(_fd, buffer, length));
  if (r==-1) {
    perror("in i2c_interface read : read data");
    return -1;
  }
  return 0;
}

int I2c_interface::i2c_write(uint8_t reg_addr, uint8_t *buffer, int length) {
  
  uint8_t *wr_buf = (uint8_t *)malloc(sizeof(uint8_t)*(length+1));
  int r;
  wr_buf[0]=reg_addr;

  if (length > 0) {
    for (int i=0; i<length; i++) {
      wr_buf[i+1]=*buffer;
      buffer++;
    }
  }
  length++;
  RESTART_SYSCALL(r, write(_fd, wr_buf, length));
  if (r==-1) {
    perror("in i2c_interface write");
    free(wr_buf);
    return -1;
  }
  free(wr_buf);
  return 0;
}
