
#ifndef ULTRASSON_HPP
#define ULTRASSON_HPP

#ifndef SIMULATION
#include "i2c_interface.hpp"
#endif

#ifndef SIMULATION
class Ultrasson : public I2c_interface {
#endif

  public:
    Ultrasson(int bus, uint8_t slave_addr, int my_nbr_ultrassons);
    virtual ~Ultrasson();

    int get_distances();
    int nbr_ultrassons;
    double * distances;
};


/*
#ifdef REEL
I2c_ultrasson ultrason(42,42);
#elif SIMU
Simu_ultrasson ultrason(fdhjidfshui);
#endif

ultrason.get_distance(); // marche directement
 */
#endif
