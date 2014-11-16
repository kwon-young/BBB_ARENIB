
#ifndef SIMU_TOURELLE_HPP
#define SIMU_TOURELLE_HPP

#include "utils.hpp"
#include "tourelle.hpp"

class Simu_tourelle {

  public:
    Simu_tourelle(int     my_simu_nbr_mesures,
                  uint8_t my_simu_error, 
                  uint8_t my_simu_instruction, 
                  double  *my_simu_distances, 
                  double  *my_simu_angles); 
                  

    virtual ~Simu_tourelle();

    int send_datas(double *distances, double *angles) const;
    int send_error(uint8_t &error) const;
    int recv_instruction(const uint8_t instruction);

    int update();

  protected:
    int     simu_nbr_mesures;
    uint8_t simu_error;
    uint8_t simu_instruction;
    double  *simu_distances;
    double  *simu_angles;

};


#endif


