
#include "ultrasson.hpp"

Ultrasson::Ultrasson(i2c_bus& bus, uint8_t slave_addr, int my_nbr_ultrassons) :
i2c_slave(bus, slave_addr),
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
  r=fast_read('r', distance_uint8, sizeof(distance_uint8));
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

