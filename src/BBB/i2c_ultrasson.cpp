
#include "i2c_ultrasson.hpp"

I2c_ultrasson::I2c_ultrasson(int bus, char slave_addr) :
I2c_interface(bus, slave_addr)
{}


I2c_ultrasson::~I2c_ultrasson() {

}


float I2c_ultrasson::get_distance() {
  char distance[10];
  i2c_read('r', distance, sizeof(distance));
  int distance_int;
  printf("0x");
  for (int i=0; i<sizeof(distance); i++) {
    printf("%x ", distance[i]);
    distance_int &= distance[i] << (i*8);
  }
  printf("\n");
  return (float)distance_int;
}

