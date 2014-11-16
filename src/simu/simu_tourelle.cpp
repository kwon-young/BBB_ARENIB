
#include "simu_tourelle.hpp"


Simu_tourelle::Simu_tourelle(int     my_simu_nbr_mesures,
                             uint8_t my_simu_error, 
                             uint8_t my_simu_instruction, 
                             double  *my_simu_distances, 
                             double  *my_simu_angles) :
  simu_nbr_mesures(my_simu_nbr_mesures),
  simu_error(my_simu_error),
  simu_instruction(my_simu_instruction)
{
  if (!my_simu_distances) {
    simu_distances=(double*)malloc(sizeof(double)*simu_nbr_mesures);
  } else {
    simu_distances=my_simu_distances;
  }
  if (!my_simu_angles) {
    simu_angles=(double*)malloc(sizeof(double)*simu_nbr_mesures);
  } else {
    simu_angles=my_simu_angles;
  }
  for (int i=0; i<simu_nbr_mesures; i++) {
    simu_distances[i]=0;
    simu_angles[i]=0;
  }
}

Simu_tourelle::Simu_tourelle(const Simu_tourelle &my_simu_tourelle) :
  simu_nbr_mesures(my_simu_tourelle.simu_nbr_mesures),
  simu_error(my_simu_tourelle.simu_error),
  simu_instruction(my_simu_tourelle.simu_instruction),
  simu_distances(my_simu_tourelle.simu_distances),
  simu_angles(my_simu_tourelle.simu_angles)
{
}

Simu_tourelle::~Simu_tourelle() {
  free(simu_distances);
  free(simu_angles);
}

int Simu_tourelle::send_datas(double *distances, double *angles) const {
  for (int i=0; i<simu_nbr_mesures; i++) {
    distances[i]=simu_distances[i];
    angles[i]=simu_angles[i];
  }
  return 0;
}

int Simu_tourelle::send_error(uint8_t &error) const {
  error=simu_error;
  return 0;
}

int Simu_tourelle::recv_instruction(const uint8_t instruction) {
  simu_instruction=instruction;
  return 0;
}

int Simu_tourelle::update() {
  return 0;
}


