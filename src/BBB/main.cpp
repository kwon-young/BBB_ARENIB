
///\file main.cpp
///\brief Programme pour robot réele programmation sur cible BeagleBone Black
///\author Kwon-Young Choi
///\version 1
///\date 20/10/2014


#define LARGEUR_TABLE 600.0
#define HAUTEUR_TABLE 400.0
#define PAS_U 1.0
#define PAS_THETA 1.0

#include "i2c_interface.hpp"
#include "i2c_LM75.hpp"


#include "utils.hpp"
#include "robot.hpp"
#include "tourelle.hpp"
#include "ultrasson.hpp"

int main (int argc, char *argv[]) {
  for (int i=0; i<argc; i++) {
    if (i==1) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
    else if (i==2) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
  }
  Robot mon_robot(100.0, 50.0, 1, 0x30);
  //mon_robot.asserv.set_position(0, 0, 0);
  mon_robot.asserv.avance(0, 200, -PI/2.0);
  sleep(1);
  mon_robot.asserv.avance(200, 200, -2.0*PI/2.0);
  sleep(1);
  mon_robot.asserv.avance(200, 0, PI/2.0);
  sleep(1);
  mon_robot.asserv.avance(0, 0, 0.0);
  sleep(1);

  while(mon_robot.asserv.status_robot()!=STOP) {
  sleep(1);
  }
  mon_robot.asserv.get_position();
  mon_robot.asserv.avance(0, 200, -PI/2.0);
  sleep(1);
  while(mon_robot.asserv.status_robot()!=STOP) {
  sleep(1);
  }
  mon_robot.asserv.get_position();
  while(mon_robot.asserv.status_robot()!=STOP) {
  sleep(1);
  }
  mon_robot.asserv.get_position();
  /*
     Tourelle mytourelle(1, 0x45, 6);
     printf("%c\n", mytourelle.get_error());
     mytourelle.get_datas();
   */

  /*
     I2c_LM75 * myLM75 = new I2c_LM75(1, 0x48);
     uint8_t temp_hex[2];
     myLM75->temp_floattohex(temp_hex, 25.5);

     printf("%x %x\n", temp_hex[0], temp_hex[1]);
     printf("%f\n", myLM75->temp_hextofloat(temp_hex));

     printf("%.1f\n", myLM75->get_temp());

     Ultrasson * myUltrasson= new Ultrasson(1, 0x10, 2);
     while(1) {
     myUltrasson->get_distances();
     usleep(5000);
     usleep(5000);
     usleep(5000);
     }
   */
  return 0;

}


