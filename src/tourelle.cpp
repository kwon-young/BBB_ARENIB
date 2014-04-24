
#include "tourelle.hpp"

Tourelle::Tourelle(int bus, uint8_t slave_addr, int my_nbr_mesures) :
#ifndef SIMULATION
I2c_interface(bus, slave_addr),
#endif
nbr_mesures(my_nbr_mesures),
error(0)
{
  datas=(I2c_tourelle*)malloc(sizeof(I2c_tourelle)*nbr_mesures);
  distances=(double*)malloc(sizeof(double)*nbr_mesures);
  angles=(double*)malloc(sizeof(double)*nbr_mesures);
  for (int i=0; i<nbr_mesures; i++) {
    datas[i].distance=0;
    datas[i].angle=0;
    distances[i]=0;
    angles[i]=0;
  }
}

Tourelle::~Tourelle() {
  free(datas);
  free(distances);
  free(angles);
}

int Tourelle::get_datas() {
  int r=0;
#ifndef SIMULATION
  r=i2c_read('D', (uint8_t *)datas, sizeof(datas));
#endif
  if (r==-1) {
    return r;
  }
  for (int i=0; i<nbr_mesures; i++) {
    distances[i]=(double)(datas[i].distance);
    angles[i]=((double)(datas[i].angle))/10.0;
  }
  return 0;
}

int Tourelle::get_error() {
  uint8_t error=0;
  int r=0;
#ifndef SIMULATION
  r=i2c_read('E', &error, 1);
#endif
  if (r==-1) return r;
  return error;
}

int Tourelle::set_instruction(uint8_t instruction) {
  int r=0;
#ifndef SIMULATION
  r = i2c_write('I', &instruction, 1);
#endif
  return r;
}

