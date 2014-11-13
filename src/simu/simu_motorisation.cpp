
#include "simu_motorisation.hpp"

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
  simu_ordres=(Commande*)malloc(sizeof(Commande)*NB_ORDRES);
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

int Simu_motorisation::send_position_state(Commande &position) {
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
  Commande obj = simu_ordres[p_ordre_courant];
  Commande diff;
  diff.X     = obj.X - simu_position.X;
  diff.Y     = obj.Y - simu_position.Y;
  double Theta = atan2(diff.Y, diff.X);
  double u=sqrt(diff.X*diff.X + diff.Y*diff.Y);
  double u_x=u*cos(Theta);
  double u_y=u*sin(Theta);
  //verification
  //printf("X %lf | Y ", simu_position.X+u_x);
  //printf("%lf\n", simu_position.Y+u_y);
  //printf("Theta %lf\n", Theta*180.0/PI);
  double sens=1;

  if (obj.Type == AVANCE || obj.Type == TOURNE) {
    if (u < VITESSE_U) {
      if (fabs(obj.Theta-simu_position.Theta)<VITESSE_THETA) {
        simu_position.Theta=obj.Theta;
      } else if (obj.Theta-simu_position.Theta > 0) {
        simu_position.Theta += VITESSE_THETA;
      } else if  (obj.Theta-simu_position.Theta < 0) {
        simu_position.Theta -= VITESSE_THETA;
      }
      simu_position.X = obj.X;
      simu_position.Y = obj.Y;
    } else {
      if (diff.Y >0) {
        sens=1;
      } else {
        sens=-1;
      }
      if (fabs(Theta-simu_position.Theta)<VITESSE_THETA) {
        simu_position.Theta=Theta;
      } else if (Theta-simu_position.Theta > 0) {
        simu_position.Theta += VITESSE_THETA;
      } else if  (Theta-simu_position.Theta < 0) {
        simu_position.Theta -= VITESSE_THETA;
      }
      printf("%lf\n", Theta*180.0/PI);
      simu_position.X += sens*cos(simu_position.Theta)*VITESSE_U;
      simu_position.Y += sens*sin(simu_position.Theta)*VITESSE_U;
    }
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



