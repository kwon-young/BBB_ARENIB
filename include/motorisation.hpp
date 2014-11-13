
#ifndef MOTORISATION_HPP
#define MOTORISATION_HPP

///\file motorisation.hpp
///\brief Classe permettant de communiquer avec l'asservissement
///\author Kwon-Young Choi
///\version 1
///\date 20/10/2014
///Definition de la classe Motorisation qui permet de communiquer avec l'asservissement
///Definition de deux structures :
///Commande et i2c_packet

// Ce sont les différents états du robot
#define STOP_F          1
#define AVANCE          2
#define TOURNE          3
#define STOP            4
#define POSITION_W      5
#define AVANCE_FREE     6
#define POSITION_R      7
#define BLOQUE          8
#define STATUS_ROB      10

#include "utils.hpp"
#include "i2c_bus.hpp"
#include "i2c_slave.hpp"




///\struct commande
///\brief permet de representer soit l'etat du robot ou bien un ordre pour le robot
///Le but de cette structure est de soit representer l'etat ou un ordre du robot de facon tres precise en utilisant des doubles
typedef struct _commande
{
  uint8_t Type;   //!<peut representer un etat du robot definie plus haut
  double X;       //!<position en X
  double Y;       //!<position en Y
  double Theta;   //!<position en Theta
}Commande;

///\class Motorisation
///\brief Classe permettant de communiquer avec l'asservisssment
///Cette classe fait le pont entre la vrai carte d'asservissement et le haut niveau.
///Cette classe sait communiquer en i2c avec l'asservissment
#ifdef SIMULATION
class Motorisation  {
#else
class Motorisation : public i2c_slave {
#endif

  public:
  
	///\struct i2c_packet
	///\brief permet de traduire plus facilement la structure commande pour l'envoyer en i2c
	///Le but de cette structure est de traduire la structure Commande en format de donnees facile a envoyer pour l'i2c, qui n'envoie que des paquets d'octet.
	///la precision du codage peut aller jusqu'au micron pour X et Y
	typedef struct _i2c_packet {
	  uint8_t type;     //!<peut representer un etat du robot definie plus haut
	  uint8_t x[4];     //!<position en X, entier sur 4 octets dont le bit de poid fort represente le signe, actuellement en 10eme de milimetre
	  uint8_t y[4];     //!<position en Y, entier sur 4 octets dont le bit de poid fort represente le signe, actuellement en 10eme de milimetre
	  uint8_t theta[4]; //!<position en Theta, entier sur 4 octets dont le bit de poid fort represente le signe, actuellement en 10 000eme de radian
	}i2c_packet;
  
  
    ///\brief Constructeur par defaut
    ///\param[in] etat etat du robot
    ///\param[in] posX position initial en X
    ///\param[in] posY position initial en Y
    ///\param[in] posTheta position initial en Theta
    Motorisation( int bus, 
                  uint8_t slave_addr, 
                  unsigned int etat, 
                  double posX, 
                  double posY, 
                  double posTheta);
    virtual ~Motorisation();

    ///\brief stop le robot de force
    ///on vient forcer l'etat et la position de l'asservissment du robot en i2c a 0
    ///cela revient reinitialiser le robot
    ///\return 0 si tout s'est bien passe, -1 sinon
    int stop_force();
    
    ///\brief demande a l'asservissement si le robot est bloque
    ///\return 0 si tout s'est bien passe, -1 sinon
    int status_robot();

    ///\brief force la position du robot 
    ///on vient forcer l'etat et la position de l'asservissment du robot en i2c avec ce qui est mis dans la structure commmande_ordre
    ///\param[in] obj_X force la position en X a obj_X
    ///\param[in] obj_Y force la position en Y a obj_Y
    ///\param[in] obj_Theta force la position en Theta a obj_Theta
    ///\return 0 si tout s'est bien passe, -1 sinon
    int set_position(double obj_X, double obj_Y, double obj_Theta);

    ///\brief met a jour la position et l'etat du robot dans etat_courant
    ///on vient mettre a jour la position du robot dans commande_etat_courant en i2c avec l'asservissment
    ///\return 0 si tout s'est bien passe, -1 sinon
    int get_position_state();
    
    ///\brief envoie l'ordre tourne a l'asservissement
    ///envoie l'ordre tourne en i2c a l'asservissement d'un angle en radian
    ///\param[in] obj_Theta angle dans lequel on veut que le robot soit, en radian
    ///\return retourne 0 si tout s'est bien passe, -1 sinon
    int tourne(double obj_X, double obj_Y, double obj_Theta);

    ///\brief envoie l'ordre avance et tourne en meme temps
    ///cette ordre sert a positionner le robot en angle et en position
    ///\param[in] obj_X coordonnee en x de l'objectif en mm
    ///\param[in] obj_Y coordonnee en y de l'objectif en mm
    ///\param[in] obj_Theta angle dans lequel on veut que le robot soit, en radian
    ///\return retourne 0 si tout s'est bien passe, -1 sinon
    int avance(double obj_X, double obj_Y, double obj_Theta);

    ///\brief convertie une structure commande en i2c_packet
    ///cette fonction convertie les membres X, Y, Theta codes en double dans la structure commande en uint8_t[4] dans la structure i2c_packet
    ///\param[in] myCommande reference constante sur la structure commande que l'on veut traduire
    ///\param[out] myI2c_packet reference sur la structure i2c_packet de destination
    int commandeToI2c_packet(const Commande &myCommande, I2c_packet &myI2c_packet);

    ///\brief convertie une structure i2c_packet en commande 
    ///cette fonction convertie les membres X, Y, Theta codes en uint8_t[4] dans la structure i2c_packet en double dans la structure commande
    ///\param[in] myI2c_packet reference constante sur la structure i2c_packet que l'on veut traduire
    ///\param[out] myCommande reference sur la structure commande de destination
    int i2c_packetToCommande(const I2c_packet &myI2c_packet, Commande &myCommande);

    void update();

    I2c_packet i2c_envoie; //!<structure i2c_packet qui sert a envoyer des octets sur le bus i2c
    Commande commande_etat_courant; //!<structure qui permet de decrire les differents ordres que l'on veut affecter au robot
    Commande commande_ordre; //!<structure qui decrit l'etat et la position du robot
		
	protected
};

#endif
