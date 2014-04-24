
#include "ultrasson.hpp"

Ultrasson::Ultrasson(int bus, uint8_t slave_addr, int my_nbr_ultrassons) :
#ifndef SIMULATION
I2c_interface(bus, slave_addr),
#endif
nbr_ultrassons(my_nbr_ultrassons)
{
  distances=(double*)malloc(sizeof(double)*nbr_ultrassons);
  for (int i=0; i<nbr_ultrassons; i++) {
    distances[i]=0;
  }
}

Ultrasson::~Ultrasson() {
  free(distances);
}

int Ultrasson::get_distances() {
  uint8_t distance_uint8[10]={0};
  int r=0;
#ifndef SIMULATION
  r=i2c_read('r', distance_uint8, sizeof(distance_uint8));
#endif
  if (r==-1) {
    return r;
  }

  for (int i=0; i<nbr_ultrassons; i++) {
    distances[i] = (double)((distance_uint8[1] << 8) | distance_uint8[0]);
    distances[i]*=(5.0/(1024.0));
    printf("%1.2lf\n", distances[i]);
  }
  return r;
}

