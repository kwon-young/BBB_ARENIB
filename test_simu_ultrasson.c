
//ligne de compilation
//gcc test_simu_ultrasson.c -o test_simu_ultrasson -std=c99 -W -Wall

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define PI 3.14159265

//definie la position d'un robot
typedef struct _robotPosition{
  double X;     //position en X, peut etre negatif, en mm
  double Y;     //position en X, peut etre negatif, en mm    
  double Theta; //position angulaire, en radian, [0, 2PI]    
  double Rayon; //on assimile la forme du robot a un cercle de rayon Rayon en mm
}RobotPosition;

//definie un ultrasson
typedef struct _ultrasson {
  double distance;      //distance a l'objet que l'ultrasson a detecte, en mm
                        //l'ultrasson ne peut pas detecter au dessous de 40mm (si la distance est inferieur, il renvoie 40 mm)
                        //et au dessus de 3300mm, (si la distance est de 3300 mm, c'est a dire que l'ultrasson ne detecte rien)
  double angleCouvert;  //l'angle couvert par l'ultrasson
}Ultrasson;

/*
 * c'est la fonction a completer
 * tabUltrasson est le tableau a completer, il contient nbrUltrasson ultrasson
 * myRobot est mon robot de reference, c'est par rapport a lui que je viens chercher si il y a une collision avec robotAdverse
 */
void simu_collision(Ultrasson *tabUltrasson,
                    const int nbrUltrasson,
                    const RobotPosition myRobot,
                    const RobotPosition robotAdverse)
{
  (void)tabUltrasson; //remove warning
  (void)nbrUltrasson; //remove warning
  (void)myRobot; //remove warning
  (void)robotAdverse; //remove warning
}

int main (void) {
  srand(time(NULL));

  //initialisation du tableau de 4 ultrasson
  //ils sont placés respectivement devant, derriere, a gauche, et a droite du robot
  Ultrasson tabUltrasson[4];
  for (int i=0; i<4; i++) {
    tabUltrasson[i].distance=3300;
    tabUltrasson[i].angleCouvert=PI/2;
  }

  //initialisation de mon robot et du robot adverse
  RobotPosition myRobot;
  myRobot.X=0;
  myRobot.Y=0;
  myRobot.Theta=0;
  myRobot.Rayon=400;
  RobotPosition robotAdverse;
  //je viens generer des positions aleatoires
  //mais tu peux changer le code pour mettre des positions en dures
  robotAdverse.X=(rand()%2500)-1250; //mm
  robotAdverse.Y=(rand()%1500)-750; //mm
  robotAdverse.Theta=(rand()%3600)*PI/180; //rad
  robotAdverse.Rayon=400;

  //appel de la fonction de recherche de collision
  simu_collision(tabUltrasson, 4, myRobot, robotAdverse);

  //affichage du resultat
  //pas besoin de regarder cette partie, je l'ai salement code
  char * string=(char*) malloc(100);
  char *zone=(char*)malloc(100);
  int detect=0;
  for (int i=0; i<4; i++) {
    string="le robot est ";
    if (i==0) zone="devant\n";
    else if (i==1) zone="a gauche\n";
    else if (i==2) zone="derriere\n";
    else zone="a droite\n";
    if (tabUltrasson[i].distance<=40) {
      strcat(string, zone);
      printf(zone);
      detect=1;
    }
  }
  if (!detect) {
    printf("il n'y a pas de robot dans la zone de detection des ultrassons !\n");
  }
  free(string);
  free(zone);
  return 0;
}

