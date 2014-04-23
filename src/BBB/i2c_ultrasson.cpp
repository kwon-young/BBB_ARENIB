
#include "i2c_ultrasson.hpp"

I2c_ultrasson::I2c_ultrasson(int bus, uint8_t slave_addr) :
I2c_interface(bus, slave_addr)
{}


I2c_ultrasson::~I2c_ultrasson() {

}


float I2c_ultrasson::get_distance() {
  uint8_t distance[10]={0};
  int r=i2c_read('r', distance, sizeof(distance));
  if (r==-1) {
    return 0.0;
  }
  int distance_int;
  for (unsigned int i=0; i<sizeof(distance); i++) {
    distance_int &= distance[i] << (i*8);
  }
  return (float)distance_int;
}

