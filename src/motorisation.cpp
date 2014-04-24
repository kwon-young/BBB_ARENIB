
#include "motorisation.hpp"

Motorisation::Motorisation(unsigned int etat, double posX, double posY, double posTheta) :
#ifndef SIMULATION
  my_i2c_interface(1, 0x30)
#endif
{
  commande_etat_courant.Type=etat;
  commande_etat_courant.X=posX;
  commande_etat_courant.Y=posY;
  commande_etat_courant.Theta=posTheta;
  commande_avance.Type=0;
  commande_avance.X=0.0;
  commande_avance.Y=0.0;;
  commande_avance.Theta=0.0;;
  commandeToI2c_packet();
}

Motorisation::~Motorisation() {
}

int Motorisation::set_position() {
  return 0;
}
  
int Motorisation::get_position() {
  i2c_envoie.Type=POSITION_R;
  my_i2c_interface.i2c_read(i2c_envoie.Type, i2c_envoie.X, 12);
  i2c_packetToEtat_courant();
  /*
  printf("etat_courant\n");
  printf("\tX     = %lf\n", commande_etat_courant.X);
  printf("\tY     = %lf\n", commande_etat_courant.Y);
  printf("\tTheta = %lf\n", commande_etat_courant.Theta);
  */
  return 0;
}

int Motorisation::avance(double obj_X, double obj_Y) {
  return 0;
}
int Motorisation::tourne(double obj_Theta) {
  return 0;
}
int Motorisation::avance_tourne(double obj_X, double obj_Y, double obj_Theta)
{
  commande_avance.Type=AVANCE_TOURNE;
  commande_avance.X=obj_X;
  commande_avance.Y=obj_Y;
  commande_avance.Theta=obj_Theta;
  commandeToI2c_packet();
#ifndef SIMULATION
  my_i2c_interface.i2c_write(i2c_envoie.Type, i2c_envoie.X, 12);
#endif
  return 0;
}

int Motorisation::commandeToI2c_packet() {
  i2c_envoie.Type=commande_avance.Type;
  uint8_t signe[3]={0};
  uint32_t masque=0xFF;
  double monX=commande_avance.X;
  double monY=commande_avance.Y;
  double monTheta=commande_avance.Theta;
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
    i2c_envoie.X[i]=(uint8_t)((masque)&(((uint32_t)(monX*10))>>(i*8)));
    i2c_envoie.Y[i]=(uint8_t)((masque)&(((uint32_t)(monY*10))>>(i*8)));
    i2c_envoie.Theta[i]=(uint8_t)((masque)&(((uint32_t)(monTheta*10000))>>(i*8)));
  }
  i2c_envoie.X[3]|=signe[0]<<7;
  i2c_envoie.Y[3]|=signe[1]<<7;
  i2c_envoie.Theta[3]|=signe[2]<<7;
  return 0;
}

int Motorisation::i2c_packetToEtat_courant() {
  commande_etat_courant.Type=i2c_envoie.Type;
  double monX;
  double monY;
  double monTheta;
  int32_t temp[3]={0};
  double signe[3]={1};
  for (int i=0; i<4; i++) {
    temp[0]|=((uint32_t)(i2c_envoie.X[i])) << (i*8);
    temp[1]|=((uint32_t)(i2c_envoie.Y[i])) << (i*8);
    temp[2]|=((uint32_t)(i2c_envoie.Theta[i])) << (i*8);
  }
  for (int i=0; i<3; i++) {
    if (temp[i]>>(8*4-1)) {
      signe[i]=-1;
      temp[i]&=~(1<<(8*4-1));
    }
  }
  commande_etat_courant.X=signe[0]*((double)(temp[0]))/10.0;
  commande_etat_courant.Y=signe[1]*((double)(temp[1]))/10.0;
  commande_etat_courant.Theta=signe[2]*((double)(temp[2]))/10000.0;
  return 0;
}

void Motorisation::update() {
}




