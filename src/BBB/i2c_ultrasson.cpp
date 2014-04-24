
#include "i2c_ultrasson.hpp"

I2c_ultrasson::I2c_ultrasson(int bus, uint8_t slave_addr) :
I2c_interface(bus, slave_addr)
{}


I2c_ultrasson::~I2c_ultrasson() {

}


double I2c_ultrasson::get_distance() {
  uint8_t distance[10]={0};
  int r=i2c_read('r', distance, sizeof(distance));
  if (r==-1) {
    return -1;
  }
  int distance_int;

  distance_int = (distance[1] << 8) | distance[0];
  distance_int += (distance[5] << 8) | distance[4];
  double distance_double=(double)distance_int;
  distance_double *=(5.0/(1024.0*2.0));
  printf("%1.2lf\n", distance_double);
  return (double)distance_int;
}

