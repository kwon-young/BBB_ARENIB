

///\file i2c_interface.cpp
///\author Kwon-Young Choi & Julien De Loor

#include "i2c_bus.hpp"

#ifdef SIMULATION

fake_i2c_bus::fake_i2c_bus(unsigned int udelay):
_udelay(udelay)
{
  snprintf(name, sizeof(name), "fake i2c system");
}

fake_i2c_bus::~fake_i2c_bus()
{
}

int fake_i2c_bus::do_operation(unsigned int bytes)
{
  //TODO put proper sleep here in usec
  return bytes*_udelay;
}

#else

i2c_bus::i2c_bus(int id) {
  int r;
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


