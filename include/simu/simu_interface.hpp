
#ifndef SIMU_INTERFACE
#define SIMU_INTERFACE

#include "utils.hpp"

class Simu_interface {

  public:
    Simu_interface();
    Simu_interface(const Simu_interface &my_simu_interface);
    virtual ~Simu_interface();

    void simu_write();
    void simu_read();
    
  protected:
    
};

#endif
