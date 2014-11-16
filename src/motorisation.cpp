
#include <iostream>
#include "motorisation.hpp"
#ifdef SIMULATION
#include "simu_motorisation.hpp"
#endif

int Motorisation::t_ragequit=false;

Motorisation::Motorisation(i2c_bus &mybus, 
                           uint8_t slave_addr, 
#ifdef SIMULATION
                    Simu_motorisation &my_simu_asserv,
#endif
                           unsigned int etat, 
                           double posX, 
                           double posY, 
                           double posTheta) :
i2c_slave(mybus, slave_addr),
t_updatePosition(&Motorisation::updatePosition, this)
#ifdef SIMULATION
,simu_asserv(&my_simu_asserv)
#endif
{
  t_updatePosition.launch();
  m_commande_etat_courant.lock();
  commande_etat_courant.Type=etat;
  commande_etat_courant.X=posX;
  commande_etat_courant.Y=posY;
  commande_etat_courant.Theta=posTheta;
  m_commande_etat_courant.unlock();
  commande_ordre.Type=0;
  commande_ordre.X=0.0;
  commande_ordre.Y=0.0;
  commande_ordre.Theta=0.0;
}

Motorisation::~Motorisation() {
}

int Motorisation::stop_force() {
  I2c_packet i2c_envoie;
  i2c_envoie.Type=STOP_F;
  write((uint8_t*) &i2c_envoie, sizeof(I2c_packet));
  //Surcouche simulation
  #ifdef SIMULATION
  simu_asserv->recv_stop_force();
  #endif
  return 0;
}

int Motorisation::set_position(double obj_X, double obj_Y, double obj_Theta) {
  I2c_packet i2c_envoie;
  m_commande_etat_courant.lock();
  commande_etat_courant.Type=POSITION_W;
  commande_etat_courant.X=obj_X;
  commande_etat_courant.Y=obj_Y;
  commande_etat_courant.Theta=obj_Theta;
  m_commande_etat_courant.unlock();
  commandeToI2c_packet(commande_etat_courant, i2c_envoie);
  write((uint8_t*)  &i2c_envoie, sizeof(I2c_packet));
  
  //Surcouche simulation
  #ifdef SIMULATION
  m_commande_etat_courant.lock();
  simu_asserv->recv_position(obj_X,obj_Y,obj_Theta);
  m_commande_etat_courant.unlock();
  #endif
  
  
  return 0;
}
  
int Motorisation::get_position_state() {
  int r;
  I2c_packet i2c_envoie;
  i2c_envoie.Type=POSITION_R;
  r=fast_read(i2c_envoie.Type, (uint8_t*) &i2c_envoie, sizeof(I2c_packet));
  if (r==-1) {
    return r;
  }
  i2c_packetToCommande(i2c_envoie, commande_etat_courant);
  
  //Surcouche simulation
  #ifdef SIMULATION
  m_commande_etat_courant.lock();
  simu_asserv->send_position_state(commande_etat_courant);
  m_commande_etat_courant.unlock();
  #endif
  
  return 0;
}

int Motorisation::tourne(double obj_X, double obj_Y, double obj_Theta) {
  I2c_packet i2c_envoie;
  m_commande_etat_courant.lock();
  commande_ordre.Type=TOURNE;
  commande_ordre.X=obj_X;
  commande_ordre.Y=obj_Y;
  commande_ordre.Theta=obj_Theta;
  m_commande_etat_courant.unlock();
  commandeToI2c_packet(commande_ordre, i2c_envoie);
  write((uint8_t*) &i2c_envoie, sizeof(I2c_packet));
  
  //Surcouche simulation
  #ifdef SIMULATION
  //TODO
  #endif
  
  return 0;
}

int Motorisation::avance(double obj_X, double obj_Y, double obj_Theta)
{
  I2c_packet i2c_envoie;
  m_commande_etat_courant.lock();
  commande_ordre.Type=AVANCE;
  commande_ordre.X=obj_X;
  commande_ordre.Y=obj_Y;
  commande_ordre.Theta=obj_Theta;
  m_commande_etat_courant.unlock();
  commandeToI2c_packet(commande_ordre, i2c_envoie);
  write((uint8_t*) &i2c_envoie, sizeof(I2c_packet));
  
  //Surcouche simulation
  #ifdef SIMULATION
  m_commande_etat_courant.lock();
  simu_asserv->recv_avance( obj_X,  obj_Y,  obj_Theta);
  m_commande_etat_courant.unlock();
  #endif
  return 0;
}

int Motorisation::commandeToI2c_packet(const Commande &myCommande, 
                                       I2c_packet &myI2c_packet) {
  myI2c_packet.Type=myCommande.Type;
  uint8_t signe[3]={0};
  uint32_t masque=0xFF;
  m_commande_etat_courant.lock();
  double monX=myCommande.X;
  double monY=myCommande.Y;
  double monTheta=myCommande.Theta;
  m_commande_etat_courant.unlock();
  if (monX<0) {
    signe[0]=1;
    monX*=-1;
  }
  if (monY<0) {
    signe[1]=1;
    monY*=-1;
  }
  if (monTheta<0) {
    signe[2]=1;
    monTheta*=-1;
  }
  for (int i=0; i<4; i++) {
    if (i==3) masque=0x7F;
    myI2c_packet.X[i]=(uint8_t)((masque)&(((uint32_t)(monX*10))>>(i*8)));
    myI2c_packet.Y[i]=(uint8_t)((masque)&(((uint32_t)(monY*10))>>(i*8)));
    myI2c_packet.Theta[i]=(uint8_t)((masque)&(((uint32_t)(monTheta*10000))>>(i*8)));
  }
  myI2c_packet.X[3]|=signe[0]<<7;
  myI2c_packet.Y[3]|=signe[1]<<7;
  myI2c_packet.Theta[3]|=signe[2]<<7;
  return 0;
}

int Motorisation::i2c_packetToCommande(const I2c_packet &myI2c_packet,
                                       Commande &myCommande) {
  int32_t temp[3]={0};
  double signe[3]={1,1,1};
  for (int i=0; i<4; i++) {
    temp[0]|=((uint32_t)(myI2c_packet.X[i])) << (i*8);
    temp[1]|=((uint32_t)(myI2c_packet.Y[i])) << (i*8);
    temp[2]|=((uint32_t)(myI2c_packet.Theta[i])) << (i*8);
  }
  for (int i=0; i<3; i++) {
    if (temp[i]>>(8*4-1)) {
      signe[i]=-1;
      temp[i]&=~(1<<(8*4-1));
    }
  }
  m_commande_etat_courant.lock();
  myCommande.Type=myI2c_packet.Type;
  myCommande.X=signe[0]*((double)(temp[0]))/10.0;
  myCommande.Y=signe[1]*((double)(temp[1]))/10.0;
  myCommande.Theta=signe[2]*((double)(temp[2]))/10000.0;
  m_commande_etat_courant.unlock();
  return 0;
}

void Motorisation::updatePosition(Motorisation *motorisation) {
  while(!t_ragequit) {
    if (motorisation->get_position_state() == -1)
    {
      std::cerr << "Error i2c motorisation.get_position_state()" << std::endl;
    }
    sf::sleep(sf::milliseconds(5));
  }
}


