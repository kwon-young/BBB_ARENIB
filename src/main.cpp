
///\file main.cpp
///\brief Programme pour robot réele programmation sur cible BeagleBone Black
///\author Kwon-Young Choi
///\version 1
///\date 20/10/2014


#define LARGEUR_TABLE 600.0
#define HAUTEUR_TABLE 400.0
#define PAS_U 1.0
#define PAS_THETA 1.0

#include "i2c_slave.hpp"
//#include "i2c_LM75.hpp"


#include "utils.hpp"
#include "tourelle.hpp"
#include "ultrasson.hpp"
#include "simu_motorisation.hpp"


int main (int argc, char *argv[]) {
  for (int i=0; i<argc; i++) {
    if (i==1) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
    else if (i==2) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
  }

  return 0;

}


