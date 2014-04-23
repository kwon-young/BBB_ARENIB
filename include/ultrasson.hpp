
#ifndef ULTRASSON_HPP
#define ULTRASSON_HPP

//#include "utils.hpp"
#include "i2c_slave.hpp"


class Ultrasson : public i2c_slave{

  public:
    Ultrasson(i2c_bus& bus, uint8_t slave_addr, int my_nbr_ultrassons);
    virtual ~Ultrasson();

    int get_distances();
    int nbr_ultrassons;
    double * distances;
};

#endif
