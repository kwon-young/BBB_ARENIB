
///\file main.cpp
///\brief Programme pour robot réele programmation sur cible BeagleBone Black
///\author Kwon-Young Choi
///\version 1
///\date 20/10/2014


#include "i2c_slave.hpp"
#include "utils.hpp"
#include "tourelle.hpp"
#include "ultrasson.hpp"
#include "simu_motorisation.hpp"
#include "motorisation.hpp"
#include <csignal>
#include <iostream>

bool ragequit=false; //:D

void handle_sigint(int parameter)
{
  ragequit=true;
}

int main (int argc, char *argv[]) {

  ///Interrupts
  signal (SIGINT, handle_sigint);

  ///Communication
  //Network
  std::string interface_ip="127.0.0.1";
  if (argc > 1) {
    interface_ip=argv[1];
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
  std::string robot_name="EchecCritique"; 
  sf::Uint8 etat=0;
  sf::Int16 position_x=0; //mm
  sf::Int16 position_y=0; //mm
  sf::Int16 theta=0;      //degrees*10 [0, 3600]
  sf::Uint8 color_r=255;
  sf::Uint8 color_g=0;
  sf::Uint8 color_b=0;

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

    motorisation.avance(-1000.0, 0.0, 0.0);

    //double t=0;
  while (!ragequit) {
   /* 
    motorisation.avance(cos(t*PI/180.0), sin(t*PI/180.0), 0.0);
    if (t==90)
      std::cout << "En avant" << std::endl;
    else if (t==270)
      std::cout << "En arriere" << std::endl;
    else if (t==180)
      std::cout << "A gauche" << std::endl;
    else if (t==0)
      std::cout << "A droite" << std::endl;
   // std::cout << t << std::endl;
    t++;
    if (t==360)
      t=0;
   */
    if (motorisation.get_position_state() == -1)
    {
      std::cerr << "Error i2c motorisation.get_position_state()" << std::endl;
    }

    etat = motorisation.commande_etat_courant.Type;
    position_x = motorisation.commande_etat_courant.X;
    position_y = motorisation.commande_etat_courant.Y;
    theta = motorisation.commande_etat_courant.Theta*180.0*10.0/PI;

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
    sf::sleep(sf::milliseconds(50));
    simu_motorisation.update();
#endif
  }


  return 0;

}


