
#ifndef I2C_BUS
#define I2C_BUS

///\file i2c_interface.hpp
///\brief Classe permettant de communiquer en i2c
///\author Kwon-Young Choi & Julien De Loor
///\version 1
///\date 20/10/2014
///Definition de la classe i2c_bus qui permet de communiquer en i2c avec la BBB
/// et également de la classe fake_i2c_bus qui permet de simuler le delay 
/// d'envois des ordres

#include "utils.hpp"

#ifdef SIMULATION

///\class fake_i2c_bus i2c_bus.hpp
class fake_i2c_bus : public std::mutex {
  public:
    ///\brief Constructeur 
    ///Le constructeur se charge d'initialiser le bus i2c comme il faut.
    ///Il lie un descripteur de fichier a un bus i2c et a une adresse esclave.
    ///\param[in] bus numero du bus i2c, sur une BBB debian c'est 1
    fake_i2c_bus(unsigned int udelay);

    ///\brief Destructeur
    virtual ~fake_i2c_bus();
    
    ///\brief permet d'ecrire sur le bus i2c
    ///\param[in] nombre d'octets écrits ou lus sur le bus
    ///\return 0 si tout s'est bien passe, -1 sinon
    int do_operation(unsigned int bytes);

    char name[42];   //!<nom du bus i2c (fake i2c system)
       
  protected:
    unsigned int _udelay; //!<delay simulé d'attente du bus en usec/byte
};

#else

///\class i2c_bus i2c_bus.hpp elle créer un fd générique du bus
class i2c_bus : public std::mutex {
  public:
    ///\brief Constructeur 
    ///Le constructeur se charge d'initialiser le bus i2c comme il faut.
    ///Il lie un descripteur de fichier a un bus i2c et a une adresse esclave.
    ///\param[in] bus numero du bus i2c, sur une BBB debian c'est 1
    i2c_bus(int id);

    ///\brief Destructeur
    virtual ~i2c_bus();
    
    ///\brief permet d'obtenir un fd pointant sur le bus
    ///\return derivated_fd si tout s'est bien passe, -1 sinon
    int request();
    
    /* non pas de raison d'exister
    
    ///\brief permet d'ecrire sur le bus i2c
    ///\param[in] file descriptor derivé du BUS
    ///\param[in] buffer pointeur sur un paquet d'octet a ecrire
    ///\param[in] length taille de buffer en octet
    ///\return 0 si tout s'est bien passe, -1 sinon
    int write(int derivated_fd, const uint8_t *buffer, int length);

    ///\brief permet de lire sur le bus i2c
    ///\param[out] buffer pointeur sur un paquet d'octet qui recupere les donnees lues
    ///\param[in] length taille de buffer en octet
    ///\return 0 si tout s'est bien passe, -1 sinon
    int read(int derivated_fd, uint8_t *buffer, int length);
    
    ///\brief permet d'ecrire et de lire succesivement sur le bus i2c
    ///\param[in] file descriptor derivé du BUS
    ///\param[in] out pointeur sur un paquet d'octet a ecrire
    ///\param[in] lout taille de buffer en octet
    ///\param[out] buffer pointeur sur un paquet d'octet qui recupere les donnees lues
    ///\param[in] length taille de buffer en octet
    ///\return 0 si tout s'est bien passe, -1 sinon
    int write_read(int derivated_fd, const uint8_t *out, int lout 
                                         , uint8_t *in, int lin);
    */
    
    char name[42]; //!<nom du bus i2c deduit de _bus
    
  protected:
    int _bus;           //!<bus i2c
    int _fd;            //!<descripteur de fichier permettant d'ecrire et lire dans le bus i2c
};

#endif //SIMULATION

#endif //HEADER

