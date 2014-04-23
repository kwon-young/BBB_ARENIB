

///\file i2c_interface.cpp
///\author Kwon-Young Choi & Julien De Loor

#include "i2c_bus.hpp"
#ifdef SIMULATION

i2c_bus::i2c_bus(unsigned int udelay):
_udelay(udelay)
{
  snprintf(name, sizeof(name), "fake i2c system");
}

i2c_bus::~i2c_bus()
{
}

int i2c_bus::do_operation(unsigned int bytes)
{
  //TODO put proper sleep here in usec
  sf::sleep(sf::microseconds(bytes*_udelay));
  return bytes*_udelay;
}

#else

i2c_bus::i2c_bus(int id) {
  snprintf(name, sizeof(name), "/dev/i2c-%d", id);
  RESTART_SYSCALL(_fd, open(name, O_RDWR));
  if (_fd==-1) {
    printf("open %s", name);
    perror("");
  }
}

i2c_bus::~i2c_bus() {
  int r;
  RESTART_SYSCALL(r, close(_fd));
  if (r==-1) {
    printf("close %s", name);
    perror("");
  }
}

int i2c_bus::request() {
  int r;
  RESTART_SYSCALL(r, dup(_fd));
  if (r==-1) {
    printf("request %s", name);
    perror("");
  }
  return r;
}


#endif //SIMULATION


