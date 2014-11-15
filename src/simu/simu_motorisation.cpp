
#include "simu_motorisation.hpp"
#include <iostream>

Simu_motorisation::Simu_motorisation( uint8_t etat, 
                                      double posX, 
                                      double posY, 
                                      double posTheta) :
  p_ordre_courant(0),
  p_dernier_ordre(0)
{
  simu_position.Type  = etat;
  simu_position.X     = posX;
  simu_position.Y     = posY;
  simu_position.Theta = posTheta;
  simu_ordres=(Motorisation::Commande*)malloc(sizeof(Motorisation::Commande)*NB_ORDRES);
  for (int i=0; i<NB_ORDRES; i++) {
    simu_ordres[i].Type  = STOP;
    simu_ordres[i].X     = 0;
    simu_ordres[i].Y     = 0;
    simu_ordres[i].Theta = 0;
  }
}

Simu_motorisation::~Simu_motorisation() {
  free(simu_ordres);
}

int Simu_motorisation::recv_stop_force() {
  simu_position.Type  = STOP_F;
  for (int i=0; i<NB_ORDRES; i++) {
    simu_ordres[i].Type  = STOP_F;
    simu_ordres[i].X     = 0;
    simu_ordres[i].Y     = 0;
    simu_ordres[i].Theta = 0;
  }
  p_ordre_courant=0;
  p_dernier_ordre=0;
  return 0;
}

uint8_t Simu_motorisation::send_status_robot() {
  return simu_position.Type;
}

int Simu_motorisation::recv_position(double obj_X, double obj_Y, double obj_Theta) {
  simu_position.X     = obj_X;
  simu_position.Y     = obj_Y;
  simu_position.Theta = obj_Theta;
  return 0;
}

int Simu_motorisation::send_position_state(Motorisation::Commande &position) {
  position.Type  = simu_position.Type;
  position.X     = simu_position.X;
  position.Y     = simu_position.Y;
  position.Theta = simu_position.Theta;
  return 0;
}

int Simu_motorisation::recv_avance(double obj_X, double obj_Y, double obj_Theta) {
    p_dernier_ordre++;
  if (p_dernier_ordre >= NB_ORDRES) {
    p_dernier_ordre=0;
  }
    
  simu_ordres[p_dernier_ordre].Type  = AVANCE;
  simu_ordres[p_dernier_ordre].X     = obj_X;
  simu_ordres[p_dernier_ordre].Y     = obj_Y;
  simu_ordres[p_dernier_ordre].Theta = obj_Theta;
  return 0;
}

int Simu_motorisation::update() {
  
   const float dt = _delay.getElapsedTime().asSeconds();
   //const float diametre_roue=0.06; //6cm a verifier
   //const float vitesse_max=3.0; //rad*s-1 a mesurer

   _delay.restart();
  Motorisation::Commande obj = simu_ordres[p_ordre_courant];
    simu_position.Type  = obj.Type;
  if (obj.Type == AVANCE || obj.Type == TOURNE) {
    //attention, il ne faut pas que la vitesse soit trop lente
    double theta_speed = (PI/180.0)*1000.0*dt/6.0;
    double u_speed=5000.0*dt/6.0;
    Motorisation::Commande diff;
    diff.X     = obj.X - simu_position.X;
    diff.Y     = obj.Y - simu_position.Y;
    double u=sqrt(diff.X*diff.X + diff.Y*diff.Y);
    double sens_rotation;
    if (u<u_speed) {
      simu_position.X=obj.X;
      simu_position.Y=obj.Y;
      //calcul du delta d'angle entre le theta courant et le theta de l'objectif [0, 2*PI]
      diff.Theta = (obj.Theta-simu_position.Theta);
      double diff_2PI = fabs(diff.Theta-2*PI);
      double diff2PI = fabs(diff.Theta+2*PI);
      if (diff_2PI <fabs(diff.Theta)) {
        diff.Theta-=2.0*PI;
      }else if (diff2PI < fabs(diff.Theta)) {
        diff.Theta+=2.0*PI;
      }
      //calcul du sens de rotation
      if (diff.Theta > 0) {
        sens_rotation=1;
      } else {
        sens_rotation=-1;
      }
      if (fabs(diff.Theta) < theta_speed) {
        simu_position.Theta=obj.Theta;
        passe_ordre_suivant();
      }
      else
        simu_position.Theta+=sens_rotation*theta_speed;
      simu_position.Theta=fmod(simu_position.Theta, 2.0*PI);
    }else {
      //calcul angle trajectoire : theta =0 sur y, [-3*PI/2, PI/2]
      double Theta_B = -PI/2.0+atan2(diff.Y, diff.X);
      //normalise de [-3*PI/2, PI/2] � [0, 2*PI]
      if (Theta_B<0) Theta_B+=2.0*PI;
      //calcul du delta d'angle entre le theta courant et le theta de la trajectoire [0, 2*PI]
      diff.Theta = Theta_B-simu_position.Theta;
      double diff_2PI = fabs(diff.Theta-2*PI);
      double diff2PI = fabs(diff.Theta+2*PI);
      if (diff_2PI <fabs(diff.Theta)) {
        diff.Theta-=2.0*PI;
      }else if (diff2PI < fabs(diff.Theta)) {
        diff.Theta+=2.0*PI;
      }
      //calcul du sens de rotation
      if (diff.Theta > 0) {
        sens_rotation=1;
      } else {
        sens_rotation=-1;
      }
      //std::cout << "avant simu_t : " << simu_position.Theta*180.0/PI << std::endl;
      if (fabs(diff.Theta) < theta_speed)
        simu_position.Theta=Theta_B;
      else
        simu_position.Theta+=sens_rotation*theta_speed;
      //std::cout << "pendant simu_t : " << simu_position.Theta*180.0/PI << std::endl;
      if (simu_position.Theta > 2.0*PI)
        simu_position.Theta-=2.0*PI;
      else if (simu_position.Theta < 0) 
        simu_position.Theta+=2.0*PI; 
      //std::cout << "apres simu_t : " << simu_position.Theta*180.0/PI << std::endl;
      //on translate si diff.Theta < PI/4
      //std::cout << "diff_t : " << diff.Theta*180.0/PI << std::endl;
      if (fabs(diff.Theta) < PI/4.0) {
        /*
        double u_x=-u*sin(Theta_B);
        double u_y=u*cos(Theta_B); // coordonné du point arrivé sur le repère fixe au robot	
        std::cout << "T : " << Theta_B*180.0/PI << std::endl;
        std::cout << "U : " << u << std::endl;
        std::cout << "X : " << u_x << std::endl;
        std::cout << "Y : " << u_y << std::endl;
        */
          simu_position.X+=-u_speed*sin(simu_position.Theta);
          simu_position.Y+=u_speed*cos(simu_position.Theta);
      }
    }
  } else if (obj.Type == STOP_F) {
    if (p_ordre_courant!=p_dernier_ordre)
    {
      passe_ordre_suivant();
    }
  } else  {
    passe_ordre_suivant();
  }
  return 0;
}

void Simu_motorisation::show_position() {
  printf("position simulation motorisation\n");
  printf("\tType  = %d\n" , simu_position.Type);
  printf("\tX     = %lf\n", simu_position.X);
  printf("\tY     = %lf\n", simu_position.Y);
  printf("\tTheta = %lf\n", simu_position.Theta);
}

void Simu_motorisation::show_ordres(int ordre_id) {
  if (ordre_id == 4) {
    for (int i=0; i<NB_ORDRES; i++) {
      printf("ordre %d simulation motorisation\n", i);
      if (p_ordre_courant==i) {
        printf("\tordre_courant\n");
      } 
      if (p_dernier_ordre==i) {
        printf("\tdernier ordre ajoute\n");
      }
      printf("\tType  = %d\n" , simu_ordres[i].Type);
      printf("\tX     = %lf\n", simu_ordres[i].X);
      printf("\tY     = %lf\n", simu_ordres[i].Y);
      printf("\tTheta = %lf\n", simu_ordres[i].Theta);
    }
  } else {
    printf("ordre %d simulation motorisation\n", ordre_id);
    if (p_ordre_courant==ordre_id) {
      printf("\tordre_courant\n");
    } else if (p_dernier_ordre==ordre_id) {
      printf("\tdernier ordre ajoute\n");
    }
    printf("\tType  = %d\n" , simu_ordres[ordre_id].Type);
    printf("\tX     = %lf\n", simu_ordres[ordre_id].X);
    printf("\tY     = %lf\n", simu_ordres[ordre_id].Y);
    printf("\tTheta = %lf\n", simu_ordres[ordre_id].Theta);
  }
}

void Simu_motorisation::passe_ordre_suivant()
{
  if (p_ordre_courant == p_dernier_ordre) {
    for (int i=0; i<NB_ORDRES; i++) {
      simu_ordres[i].Type  = STOP;
      simu_ordres[i].X     = 0;
      simu_ordres[i].Y     = 0;
      simu_ordres[i].Theta = 0;
    }
    p_ordre_courant=0;
    p_dernier_ordre=0;
  }
  else  {
    p_ordre_courant++;
    if (p_ordre_courant >= NB_ORDRES) {
      p_ordre_courant=0;
    }
    simu_position.Type=simu_ordres[p_ordre_courant].Type;
  }
}



