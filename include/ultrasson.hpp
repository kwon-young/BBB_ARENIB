
#ifndef ULTRASSON_HPP
#define ULTRASSON_HPP

#include "utils.hpp"
#ifndef SIMULATION
#include "i2c_interface.hpp"
#endif

#ifndef SIMULATION
class Ultrasson : public I2c_interface {
#else
class Ultrasson {
#endif

  public:
    Ultrasson(int bus, uint8_t slave_addr, int my_nbr_ultrassons);
    virtual ~Ultrasson();

    int get_distances();
    int nbr_ultrassons;
    double * distances;
};

#endif
