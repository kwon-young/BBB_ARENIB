
///\file main.cpp
///\brief Programme pour robot réele programmation sur cible BeagleBone Black
///\author Kwon-Young Choi
///\version 1
///\date 20/10/2014


#include "i2c_slave.hpp"
#include "utils.hpp"
#include "tourelle.hpp"
#include "ultrasson.hpp"
#ifdef SIMULATION
#include "simu_motorisation.hpp"
#endif
#include "motorisation.hpp"
#include <csignal>
#include <iostream>
#include <cstdlib>
#include <time.h>
#define NEXT_IP 1
#define NEXT_ROBOTNAME 2

int ActionLaPlusRentable(double &objX, double &objY, double &objTheta);

bool ragequit=false; //:D

void handle_sigint(int parameter)
{
  ragequit=true;
}

void print_help() {
  printf("olol.help\n");
}

int main (int argc, char *argv[]) {
  srand(time(NULL));

  ///Interrupts
  signal (SIGINT, handle_sigint);

  ///Communication
  //Network
  std::string interface_ip="127.0.0.1";
  std::string robot_name="EchecCritique"; 

  int next_for=0;
  for (int i=1; i<argc ; i++)
  {
    if (argv[i][0] == '-' && strlen(argv[i]) >= 2)
    {
      if (argv[i][1] == 'h' && argv[i][2] == 'e')
        print_help();
      else if (argv[i][1] == 'i')
        next_for = NEXT_IP;
      else if (argv[i][1] == 'n')
        next_for = NEXT_ROBOTNAME;
      else
      {
        printf("Warning");printf(" : Unknown option : %s\n",argv[i]);
      }
    }
    else if (next_for == NEXT_IP)
    {
      interface_ip=argv[i];
    }
    else if (next_for == NEXT_ROBOTNAME)
    {
      robot_name=argv[i];     
    }
    else 
    {
      printf("Useless %s: ",argv[i]);
    }
  }
  sf::UdpSocket socket;
  sf::Packet packet;
  socket.setBlocking(false);

  //i2c 
#ifdef SIMULATION
  i2c_bus communication_bus(4.7*8); //4.7usec/bit selon wikipedia
#else
  i2c_bus communication_bus(1); //Bus 1 on debian BBB
#endif

  ///Variable d'etat
  sf::Uint8 etat=0;
  sf::Int16 position_x=(rand()%2500)-1250; //mm
  sf::Int16 position_y=(rand()%1500)-750; //mm
  sf::Int16 theta=rand()%3600;      //degrees*10 [0, 3600]
  /*
     sf::Int16 position_x=0; //mm
     sf::Int16 position_y=0; //mm
     sf::Int16 theta=0;      //degrees*10 [0, 3600]
     */
  sf::Uint8 color_r=255;
  sf::Uint8 color_g=0;
  sf::Uint8 color_b=0;

  std::cout << position_x << " | " << position_y << " | " << theta<< std::endl;
  ///Simulation
  //Motorisation
#ifdef SIMULATION
  Simu_motorisation simu_motorisation(STOP,
      position_x,
      position_y,
      (theta/10.0)*PI/180.0);
#endif

  ///Periphériques
  //Motorisation
#ifdef SIMULATION
  Motorisation motorisation(communication_bus, 
      0x42, //je sait plus
      simu_motorisation,
      etat, 
      position_x, 
      position_y, 
      (theta/10.0)*PI/180.0);
#else 
  Motorisation motorisation(communication_bus, 
      0x42, //je sait plus
      etat, 
      position_x, 
      position_y, 
      (theta/10.0)*PI/180.0);
#endif 

  ///Simulation
  //Tourelle
#ifdef SIMULATION
  Simu_tourelle simu_tourelle(6,
                              0,
                              0,
                              NULL,
                              NULL);
#endif

  ///Periphériques
  //Tourelle
#ifdef SIMULATION
  Tourelle tourelle(communication_bus, 
                    simu_tourelle,
                    0x30, //je sait plus
                    6);
#else 
  Tourelle tourelle(communication_bus, 
                    0x30, //je sait plus
                    6);
#endif 

  double objX    =(rand()%2500)-1250;
  double objY    =(rand()%1500)-750;
  double objTheta=(rand()%3600)*PI/(180.0*10.0);
  std::cout << objX << " | " << objY << " | " << objTheta << std::endl;
  motorisation.avance(objX, objY, objTheta);

  //double t=0;
  while (!ragequit) {
    motorisation.get_position_HN(etat, position_x, position_y, theta);
    if (etat==STOP) {
      //objX    =(rand()%2500)-1250;
      //objY    =(rand()%1500)-750;
      //objTheta=(rand()%3600)*PI/(180.0*10.0);
      //std::cout << objX << " | " << objY << " | " << objTheta << std::endl;
	  ActionLaPlusRentable(objX, objY, objTheta);
	  motorisation.avance(1000, 800, 0);
    }


    packet.clear();

    packet << (sf::Uint8) 0x22;  //magic       // uint8
    packet << robot_name;                      // std::string
    packet << (sf::Uint8) etat;                // uint8
    packet << (sf::Int16) position_x; //mm     // int16
    packet << (sf::Int16) position_y; //mm     // int16
    packet << (sf::Int16) theta; //degres*10   // int16
    packet << (sf::Uint8) color_r; //rouge     // uint8
    packet << (sf::Uint8) color_g; //vert      // uint8
    packet << (sf::Uint8) color_b; //bleu      // uint8

    //packet << extra;  //vous pouvez ajouter des données relative à votre robot

    socket.send(packet, sf::IpAddress(interface_ip), 2222);

#ifdef SIMULATION
    sf::sleep(sf::milliseconds(5));
    simu_motorisation.update();
#endif
  }

  motorisation.t_ragequit=true;
  motorisation.t_updatePosition.wait();
  return 0;

}




