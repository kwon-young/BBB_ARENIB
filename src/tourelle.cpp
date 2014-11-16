
#include "tourelle.hpp"

Tourelle::Tourelle(i2c_bus& bus, 
#ifdef SIMULATION
                   Simu_tourelle &my_simu_tourelle,
#endif
                   uint8_t slave_addr, 
                   int my_nbr_mesures) :
  i2c_slave(bus, slave_addr),
  nbr_mesures(my_nbr_mesures),
  error(0)
#ifdef SIMULATION
  ,simu_tourelle(&my_simu_tourelle)
#endif

{
  distances=(double*)malloc(sizeof(double)*nbr_mesures);
  angles=(double*)malloc(sizeof(double)*nbr_mesures);
}

Tourelle::~Tourelle() {
  free(distances);
  free(angles);
}

int Tourelle::get_datas() {
  i2c_packet *datas=(i2c_packet*)malloc(sizeof(i2c_packet)*nbr_mesures);
  for (int i=0; i<nbr_mesures; i++) {
    datas[i].distance=0;
    datas[i].angle=0;
    distances[i]=0;
    angles[i]=0;
  }
  int r=0;
  r=fast_read('D', (uint8_t *)datas, sizeof(datas));
  if (r==-1) {
    return r;
  }
  for (int i=0; i<nbr_mesures; i++) {
    distances[i]=(double)(datas[i].distance);
    angles[i]=((double)(datas[i].angle))/10.0;
  }
  free(datas);

#ifdef SIMULATION
  simu_tourelle->send_datas(distances, angles);
#endif
  return 0;
}

int Tourelle::get_error() {
  uint8_t error=0;
  int r=0;
  r=fast_read('E', &error, 1);
  if (r==-1) return r;
#ifdef SIMULATION
  simu_tourelle->send_error(error);
#endif
  return error;
}

int Tourelle::set_instruction(uint8_t instruction) {
  int r=0;
  uint8_t cmd[2];
  cmd[0] = 'I';
  cmd[1] = instruction;
  r = write(cmd, 2);
#ifdef SIMULATION
  simu_tourelle->recv_instruction(instruction);
#endif
  return r;
}

