
#ifndef SIMU_MOTORISATION_HPP
#define SIMU_MOTORISATION_HPP

#include "utils.hpp"
#include "motorisation.hpp"

#define NB_ORDRES     4
#define VITESSE_U     5
#define VITESSE_THETA 0.05


class Simu_motorisation {

  public:
    Simu_motorisation(uint8_t etat, double posX, double posY, double posTheta);
    virtual ~Simu_motorisation();

    int update();

    ///\brief reception de l'ordre STOP_FORCE
    ///cela revient à reinitialiser le robot
    ///\return 0 si tout s'est bien passe, -1 sinon
    int recv_stop_force();
    
    ///\brief renvoie le status du robot
    ///\return renvoie le status du robot, -1 si un problème
    uint8_t send_status_robot();

    ///\brief recoit le forcage de la position du robot 
    ///\param[in] obj_X force la position en X a obj_X
    ///\param[in] obj_Y force la position en Y a obj_Y
    ///\param[in] obj_Theta force la position en Theta a obj_Theta
    ///\return 0 si tout s'est bien passe, -1 sinon
    int recv_position(double obj_X, double obj_Y, double obj_Theta);

    ///\brief renvoie la position et l'etat du robot 
    ///\return 0 si tout s'est bien passe, -1 sinon
    int send_position_state(Commande &position);
    
    ///\brief reception de l'ordre avance
    ///cette ordre sert a positionner le robot en angle et en position
    ///\param[in] obj_X coordonnee en x de l'objectif en mm
    ///\param[in] obj_Y coordonnee en y de l'objectif en mm
    ///\param[in] obj_Theta angle dans lequel on veut que le robot soit, en radian
    ///\return retourne 0 si tout s'est bien passe, -1 sinon
    int recv_avance(double obj_X, double obj_Y, double obj_Theta);

    void show_position();
    void show_ordres(int ordre_id);

    int p_ordre_courant;
    int p_dernier_ordre;
    Commande simu_position;
    Commande *simu_ordres;    
};

#endif

