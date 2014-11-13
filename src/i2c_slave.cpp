

///\file i2c_slave.cpp
///\author Julien De Loor

#include "i2c_bus.hpp"
#include "i2c_slave.hpp"

#ifdef SIMULATION
i2c_slave::i2c_slave(fake_i2c_bus& bus, uint8_t addr) :
_bus(&bus)
{
	(void) addr;
}

#else
i2c_slave::i2c_slave(i2c_bus& bus, uint8_t addr) :
_derivated_fd(-1),
_bus(&bus),
_addr(addr)
{
  set_bus(bus);
}
#endif
    
    
i2c_slave::~i2c_slave() {
  #ifndef SIMULATION
  if (_derivated_fd != -1)
  {
    int r;
    RESTART_SYSCALL(r, close(_fd));
    if (r==-1) {
      printf("close %s", bus->name);
      perror("");
    }
  }
  #endif
}

#ifndef SIMULATION  
int i2c_slave::set_bus(i2c_bus& bus)
{
  int r;
  if (_derivated_fd != -1)
  {
    RESTART_SYSCALL(r, close(_fd));
    if (r==-1) {
      printf("close %s", _bus->name);
      perror("");
      return r;
    }
  }
  
  _bus=&bus;
  _derivated_fd = bus.request();
  
  if (_derivated_fd == -1) return -1;
  
  RESTART_SYSCALL(r, ioctl(_derivated_fd, I2C_SLAVE, _addr));
  if (r==-1) {
    printf("ioctl %s", _bus->name);
    perror("");
  }
  return r;
}
#endif


int i2c_slave::write(const uint8_t *buffer, int length)
{
  #ifdef SIMULATION
    (void) buffer;
    _bus->do_operation(length+1);
    return length;

  #else
    int r;
    if (_derivated_fd == -1) return -1;

    RESTART_SYSCALL(r, write(_derivated_fd, buffer, length));
    if (r==-1) {
      perror("in i2c_slave write");
      return -1;
    }
    return r;

  #endif
}

int i2c_slave::fast_read(uint8_t cmd, uint8_t *buffer, int length)
{
#ifdef SIMULATION
  (void) buffer;
  (void) cmd;
  _bus->do_operation(2);
  _bus->do_operation(length+1);
  return length;
#else
  int r;
  if (_derivated_fd == -1) return -1;
  
  RESTART_SYSCALL(r, write(_derivated_fd, &cmd, 1));
  if (r==-1) {
    perror("in i2c_slave fast_read : write cmd");
    return -1;
  }
  RESTART_SYSCALL(r, read(_derivated_fd, buffer, length));
  if (r==-1) {
    perror("in i2c_slave fast_read : read data");
    return -1;
  }
  return r;
#endif
}  

int i2c_slave::write_read( const uint8_t *out, int lout, 
                           uint8_t *in, int lin)
{
#ifdef SIMULATION
  (void) in;
  (void) out;
  _bus->do_operation(lout+1);
  _bus->do_operation(lin+1);
  return lin;
#else
  int r;
  if (_derivated_fd == -1) return -1;
  
  RESTART_SYSCALL(r, write(_derivated_fd, out, lout));
  if (r==-1) {
    perror("in i2c_slave write_read : write cmd");
    return -1;
  }
  RESTART_SYSCALL(r, read(_derivated_fd, in, lin));
  if (r==-1) {
    perror("in i2c_slave write_read : read data");
    return -1;
  }
  return r;
#endif
}
