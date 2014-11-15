
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
  simu_position.Type  = STOP;
  simu_position.X     = 0;
  simu_position.Y     = 0;
  simu_position.Theta = 0;
  for (int i=0; i<NB_ORDRES; i++) {
    simu_ordres[i].Type  = STOP;
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
  /*
     const float dt = _delay.getElapsedTime().asSeconds();
     const float diametre_roue=0.06; //6cm à vérifier
     const float vitesse_max=3.0; //rad*s-1 à mesurer

     _delay.restart();

  //Mise à jour de la position
  sf::Vector2f pPos(simu_position.X, simu_position.Y);
  sf::Vector2f nPos = pPos + _speed*dt;
  simu_position.X = nPos.x;
  simu_position.Y = nPos.x;

  //Mise à jour angle 
  double pTheta=2.0*PI*simu_position.Theta/360.0;
  double nTheta=pTheta + _speedTheta*dt;
  simu_position.Theta=nTheta*360.0/(2.0*PI);


  Motorisation::Commande obj = simu_ordres[p_ordre_courant];
  Motorisation::Commande diff;
  diff.X     = obj.X - simu_position.X;
  diff.Y     = obj.Y - simu_position.Y;
  double Theta_B = -fmod(atan2(diff.Y, diff.X),2.0*PI);
  diff.Theta = fmod(obj.Theta-nTheta,2.0*PI);
  double u=sqrt(diff.X*diff.X + diff.Y*diff.Y);
  if (u > 0.01 && u < 1.7) //olol le trapèze
  u=1.7;

  double u_x=u*cos(Theta_B);
  double u_y=u*sin(Theta_B); // coordonné du point arrivé sur le repère fixe au robot	
  double r=(u_x-u_y);double l=(u_x+u_y);

  if (r > vitesse_max) r = vitesse_max;
  if (r < -vitesse_max) r = -vitesse_max;
  if (l > vitesse_max) l = vitesse_max;
  if (l < -vitesse_max) l = -vitesse_max;



  double sens_U=0.0; double sens_T=0.0;

  if (u_y<0){
  sens_U=-1; //une distance négative pour ordonner un recul du robot
  }
  else{
  sens_U=1; //distance positive pour ordonner une avance du robot
  }

  switch (obj.Type)
  {
  case AVANCE:
  _rotateSpeedRight=r;
  _rotateSpeedLeft=l;
  if ( u < 0.01 ) { // Au centimètre près
  p_ordre_courant++;
  if (p_ordre_courant >= NB_ORDRES) {
  p_ordre_courant=0;
  }
  }
  std::cout << "u " << u << std::endl;
  break;
  case TOURNE:
  break;
  default:
  if (obj.Type == STOP && p_ordre_courant != p_dernier_ordre) {
  p_ordre_courant++;
  if (p_ordre_courant >= NB_ORDRES) {
  p_ordre_courant=0;
  }
  }
  _rotateSpeedRight=0; //Moteurs eteints
  _rotateSpeedLeft=0;
  break;

}

float mspeed=(_rotateSpeedRight+_rotateSpeedLeft)*0.5*diametre_roue*2*PI;
_speedTheta=(_rotateSpeedRight-_rotateSpeedLeft)*0.5*diametre_roue*2*PI;
_speed=sf::Vector2f(cos(nTheta),sin(nTheta))*mspeed;

*/
  Motorisation::Commande obj = simu_ordres[p_ordre_courant];
  if (obj.Type == AVANCE || obj.Type == TOURNE) {
    double theta_speed = PI/180.0;
    double u_speed=5;
    Motorisation::Commande diff;
    diff.X     = obj.X - simu_position.X;
    diff.Y     = obj.Y - simu_position.Y;
    double u=sqrt(diff.X*diff.X + diff.Y*diff.Y);
    double sens_rotation;
    if (u<u_speed) {
    }else {
      //calcul angle trajectoire : theta =0 sur y, [-3*PI/2, PI/2]
      double Theta_B = -PI/2.0+atan2(diff.Y, diff.X);
      //normalise de [-3*PI/2, PI/2] � [0, 2*PI]
      if (Theta_B<0) Theta_B+=2.0*PI;
      //calcul du delta d'angle entre le theta courant et le theta de la trajectoire [0, 2*PI]
      diff.Theta = fmod(Theta_B-simu_position.Theta, 2.0*PI);
      //centrage de diff.Theta autour de simu_position.Theta => [simu_position.Theta-PI, simu_position.Theta+PI]
      if (diff.Theta>(simu_position.Theta+PI)) {
        diff.Theta-=2.0*PI;
      }
      //calcul du sens de rotation
      if (diff.Theta > 0)
        sens_rotation=1;
      else 
        sens_rotation=-1;
      if (fabs(diff.Theta) < theta_speed)
        simu_position.Theta=Theta_B;
      else
        simu_position.Theta+=sens_rotation*theta_speed;
    }

    /*
    double u_x=u*cos(Theta_B);
    double u_y=u*sin(Theta_B); // coordonné du point arrivé sur le repère fixe au robot	
    */
  } else if (obj.Type == STOP && p_ordre_courant != p_dernier_ordre) {
    p_ordre_courant++;
    if (p_ordre_courant >= NB_ORDRES) {
      p_ordre_courant=0;
    }
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



