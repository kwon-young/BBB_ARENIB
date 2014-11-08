
#ifndef I2C_SLAVE
#define I2C_SLAVE


///\file i2c_slave.hpp
///\brief Classe permettant de communiquer en i2c
///\author Julien De Loor
///\version 1
///\date 20/10/2014
///Definition de la classe i2c_slave utilisant un i2c_bus pour communiquer

#ifndef SIMULATION

#include "i2c_bus.hpp"

class i2c_slave 
{
  public:
    i2c_slave(i2c_bus& bus, uint8_t addr);
    virtual ~i2c_slave();
    
    
    ///\brief permet de choisir le bus i2c
    ///\param[in] bus
    ///\return 0 si tout s'est bien passe, -1 sinon
    int set_bus(i2c_bus& bus);
    
    ///\brief permet d'obtenir le mutex associé au bus ( si besoin )
    ///\return mutex associé au bus 
    inline std::mutex& get_mutex() {
      return *_bus;
    }
    
    ///\brief permet d'ecrire à l'esclave sur le bus i2c 
    ///\param[in] buffer pointeur sur un paquet d'octet a ecrire
    ///\param[in] length taille de buffer en octet
    ///\return le nombre d'octets écris si tout s'est bien passe, -1 sinon
    int write(const uint8_t *buffer, int length);
    
    ///\brief permet de lire depuis l'esclave sur le bus i2c en lui écrivant une commande
    ///\param[in] commande ou registre 
    ///\param[out] buffer pointeur sur un paquet d'octet qui recupere les donnees lues
    ///\param[in] length taille de buffer en octet
    ///\return le nombre d'octets lus si tout s'est bien passe, -1 sinon
    int fast_read(uint8_t cmd, uint8_t *buffer, int length);
    
    ///\brief permet d'ecrire et de lire succesivement sur le bus i2c
    ///\param[in] out pointeur sur un paquet d'octet a ecrire
    ///\param[in] lout taille de buffer en octet
    ///\param[out] buffer pointeur sur un paquet d'octet qui recupere les donnees lues
    ///\param[in] length taille de buffer en octet
    ///\return 0 si tout s'est bien passe, -1 sinon
    int write_read( const uint8_t *out, int lout 
                        , uint8_t *in, int lin);
    
  protected:
    int _derivated_fd;
    i2c_bus* _bus; //Must always be alive !
    uint8_t _addr; 
};

#endif

#endif //HEADER