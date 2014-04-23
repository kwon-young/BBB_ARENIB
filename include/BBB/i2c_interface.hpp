
#ifndef I2C_INTERFACE
#define I2C_INTERFACE

///\file i2c_interface.hpp
///\brief Classe permettant de communiquer en i2c
///\author Kwon-Young Choi
///\version 1
///\date 20/10/2014
///Definition de la classe I2c_interface qui permet de communiquer en i2c avec la BBB

#include "utils.hpp"

///\class I2c_interface i2c_interface.hpp
class I2c_interface {

  public:
    ///\brief Constructeur 
    ///Le constructeur se charge d'initialiser le bus i2c comme il faut.
    ///Il lie un descripteur de fichier a un bus i2c et a une adresse esclave.
    ///\param[in] bus numero du bus i2c, sur une BBB debian c'est 1
    ///\param[in] slave_addr adresse de l'esclave
    I2c_interface(int bus, char slave_addr);

    ///\brief Constructeur par recopie
    ///Le constructeur se charge d'initialiser le bus i2c comme il faut.
    ///Il lie un descripteur de fichier a un bus i2c et a une adresse esclave.
    ///\param my_i2c_interface objet I2c_interface a recopier
    I2c_interface(const I2c_interface &my_i2c_interface);

    ///\brief Destructeur
    virtual ~I2c_interface();
    
    ///\brief permet d'ecrire sur le bus i2c
    ///\param[in] reg_addr adresse du registre que l'on veut ecrire
    ///\param[in] buffer pointeur sur un paquet d'octet a ecrire
    ///\param[in] length taille de buffer en octet
    ///\return 0 si tout s'est bien passe, -1 sinon
    int i2c_write(uint8_t reg_addr, uint8_t *buffer=NULL, int length=0);

    ///\brief permet de lire sur le bus i2c
    ///\param[in] reg_addr adresse du registre que l'on veut lire
    ///\param[out] buffer pointeur sur un paquet d'octet qui recupere les donnees lues
    ///\param[in] length taille de buffer en octet
    ///\return 0 si tout s'est bien passe, -1 sinon
    int i2c_read(uint8_t reg_addr, uint8_t *buffer, int length);

    
  protected:
    int _bus;           //!<bus i2c
    char _slave_addr;   //!<adresse de l'esclave
    char _name_bus[42]; //!<nom du bus i2c deduit de _bus
    int _fd;            //!<descripteur de fichier permettant d'ecrire et lire dans le bus i2c
};


#endif

