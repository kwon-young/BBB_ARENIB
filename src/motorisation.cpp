
#include "motorisation.hpp"

Motorisation::Motorisation(int bus, 
                           uint8_t slave_addr, 
                           unsigned int etat, 
                           double posX, 
                           double posY, 
                           double posTheta) :
#ifndef SIMULATION
I2c_interface(bus, slave_addr)
#endif
{
  commande_etat_courant.Type=etat;
  commande_etat_courant.X=posX;
  commande_etat_courant.Y=posY;
  commande_etat_courant.Theta=posTheta;
  commande_ordre.Type=0;
  commande_ordre.X=0.0;
  commande_ordre.Y=0.0;;
  commande_ordre.Theta=0.0;;
  commandeToI2c_packet(commande_ordre, i2c_envoie);
}

Motorisation::~Motorisation() {
}

int Motorisation::stop_force() {
  i2c_envoie.Type=STOP_F;
#ifndef SIMULATION
  i2c_write(i2c_envoie.Type, i2c_envoie.X, 12);
#endif
  return 0;
}

int Motorisation::status_robot() {
  i2c_envoie.Type=STATUS_ROB;
  int r=0;
#ifndef SIMULATION
  r=i2c_read(i2c_envoie.Type, &i2c_envoie.Type, 1);
#endif
  if (r==-1) {
    return r;
  }
  commande_etat_courant.Type=i2c_envoie.Type;
  /*
  printf("status_courant\n");
  printf("\t%d\n", commande_etat_courant.Type);
  */
  return commande_etat_courant.Type;
}

int Motorisation::set_position(double obj_X, double obj_Y, double obj_Theta) {
  commande_etat_courant.Type=POSITION_W;
  commande_etat_courant.X=obj_X;
  commande_etat_courant.Y=obj_Y;
  commande_etat_courant.Theta=obj_Theta;
  commandeToI2c_packet(commande_etat_courant, i2c_envoie);
#ifndef SIMULATION
  i2c_write(i2c_envoie.Type, i2c_envoie.X, 12);
#endif
  return 0;
}
  
int Motorisation::get_position() {
  i2c_envoie.Type=POSITION_R;
#ifndef SIMULATION
  i2c_read(i2c_envoie.Type, i2c_envoie.X-1, 13);
#endif
  i2c_packetToCommande(i2c_envoie, commande_etat_courant);
  printf("etat_courant\n");
  printf("\tX     = %lf\n", commande_etat_courant.X);
  printf("\tY     = %lf\n", commande_etat_courant.Y);
  printf("\tTheta = %lf\n", commande_etat_courant.Theta);
  return 0;
}

int Motorisation::tourne(double obj_X, double obj_Y, double obj_Theta) {
  commande_ordre.Type=TOURNE;
  commande_ordre.X=obj_X;
  commande_ordre.Y=obj_Y;
  commande_ordre.Theta=obj_Theta;
  commandeToI2c_packet(commande_ordre, i2c_envoie);
#ifndef SIMULATION
  i2c_write(i2c_envoie.Type, i2c_envoie.X, 12);
#endif
  return 0;
}

int Motorisation::avance(double obj_X, double obj_Y, double obj_Theta)
{
  commande_ordre.Type=AVANCE;
  commande_ordre.X=obj_X;
  commande_ordre.Y=obj_Y;
  commande_ordre.Theta=obj_Theta;
  commandeToI2c_packet(commande_ordre, i2c_envoie);
#ifndef SIMULATION
  i2c_write(i2c_envoie.Type, i2c_envoie.X, 12);
#endif
  return 0;
}

int Motorisation::commandeToI2c_packet(const Commande &myCommande, 
                                       I2c_packet &myI2c_packet) {
  myI2c_packet.Type=myCommande.Type;
  uint8_t signe[3]={0};
  uint32_t masque=0xFF;
  double monX=myCommande.X;
  double monY=myCommande.Y;
  double monTheta=myCommande.Theta;
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
  myCommande.Type=myI2c_packet.Type;
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
  myCommande.X=signe[0]*((double)(temp[0]))/10.0;
  myCommande.Y=signe[1]*((double)(temp[1]))/10.0;
  myCommande.Theta=signe[2]*((double)(temp[2]))/10000.0;
  return 0;
}

void Motorisation::update() {
}




