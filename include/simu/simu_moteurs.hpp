

#ifndef SIMU_MOTEURS____
#define SIMU_MOTEURS____

#include "utils.hpp"

class Simu_moteurs
{
  public:
    Simu_moteurs(float voltage=21.0);
    
    float pwmR; //-1.0 to 1.0;
    float pwmL; 
    
    void update(float dt);
    
    inline float getSpeedR() { // rad/sec
      return _speedR;
    }
    
    inline float getSpeedL() {
      return _speedL;
    }
  
  private:
    float _speedL;
    float _speedR;
    float _alim;
    
};

#endif
