
#include "lm75.hpp"

#ifndef SIMULATION

LM75::LM75(i2c_bus& bus, uint8_t slave_addr) :
i2c_slave(bus, slave_addr)
{
}


LM75::~LM75() {

}

float LM75::get_temp() {
  uint8_t temp[2]={0};
  int r=fast_read(0x0, temp, 2);
  if (r==-1) {
    return 301.0; //not in temperature range
  }
  return temp_hextofloat(temp);
}

float LM75::temp_hextofloat(uint8_t * temp_hex) {
  int signe=((temp_hex[0]>>7)?-1:1);
  int partie_entiere=((temp_hex[0])&(~(1<<7)));
  float partie_decimale=(((temp_hex[1]>>7)?0.5:0));
  float temp_float=signe * (partie_entiere + partie_decimale);
  return temp_float;
}
void LM75::temp_floattohex(uint8_t * temp_hex, float temp_float) {
  int temp = (int)(temp_float*10);
  temp_hex[0]=(abs(temp/10)&(0xFF>>1));
  if (temp_float<0)
    temp_hex[0]|=(1<<7);
  else
    temp_hex[0]&=~(1<<7);
  temp_hex[1]=(uint8_t)((temp%10)>=5)?0x80:0;
}

#endif