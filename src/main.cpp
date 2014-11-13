
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


int main (int argc, char *argv[]) {
	
	std::string interface_ip="127.0.0.1";
	if (argc > 1) {
		interface_ip=argv[1];
	}
	
	sf::UdpSocket socket;
  
	sf::Uint8 etat=0;
	sf::Int16 position_x=0;
	sf::Int16 position_y=0;
	sf::Int16 theta=0;
	sf::Uint8 color_r=255;
	sf::Uint8 color_g=0;
	sf::Uint8 color_b=0;
	sf::Packet packet;
	packet << (sf::Uint8) 0x22;  //magic       // uint8
	packet << std::string("EchecCritique"); // std::string
	packet << (sf::Uint8) etat;                // uint8
	packet << (sf::Int16) position_x; //mm     // int16
	packet << (sf::Int16) position_y; //mm     // int16
	packet << (sf::Int16) theta; //degres*10   // int16
	packet << (sf::Uint8) color_r; //rouge     // uint8
	packet << (sf::Uint8) color_g; //vert      // uint8
	packet << (sf::Uint8) color_b; //bleu      // uint8

	//packet << extra;  //vous pouvez ajouter des données relative à votre robot

	socket.send(packet, sf::IpAddress(interface_ip), 2222);
  
  
  return 0;

}


