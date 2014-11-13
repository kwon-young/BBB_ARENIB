
#ifndef I2C_BUS
#define I2C_BUS

///\file i2c_interface.hpp
///\brief Classe permettant de communiquer en i2c
///\author Kwon-Young Choi & Julien De Loor
///\version 1
///\date 20/10/2014
///Definition de la classe i2c_bus qui permet de communiquer en i2c avec la BBB
/// et �galement de la classe fake_i2c_bus qui permet de simuler le delay 
/// d'envois des ordres

#include "utils.hpp"

#ifdef SIMULATION

///\class fake_i2c_bus i2c_bus.hpp
class fake_i2c_bus : public Mutex {
  public:
    ///\brief Constructeur 
    ///Le constructeur se charge d'initialiser le bus i2c comme il faut.
    ///Il lie un descripteur de fichier a un bus i2c et a une adresse esclave.
    ///\param[in] bus numero du bus i2c, sur une BBB debian c'est 1
    fake_i2c_bus(unsigned int udelay);

    ///\brief Destructeur
    virtual ~fake_i2c_bus();
    
    ///\brief permet d'ecrire sur le bus i2c
    ///\param[in] nombre d'octets �crits ou lus sur le bus
    ///\return 0 si tout s'est bien passe, -1 sinon
    int do_operation(unsigned int bytes);

    char name[42];   //!<nom du bus i2c (fake i2c system)
       
  protected:
    unsigned int _udelay; //!<delay simul� d'attente du bus en usec/byte
};

#else

///\class i2c_bus i2c_bus.hpp elle cr�er un fd g�n�rique du bus
class i2c_bus : public Mutex {
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
	
    char name[42]; //!<nom du bus i2c deduit de _bus
    
  protected:
    //int _bus;           //!<bus i2c
    int _fd;            //!<descripteur de fichier permettant d'ecrire et lire dans le bus i2c
};

#endif //SIMULATION

#endif //HEADER

