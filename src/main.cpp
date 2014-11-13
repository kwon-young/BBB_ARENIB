
#ifdef SIMULATION
#define LARGEUR_TABLE 600.0
#define HAUTEUR_TABLE 400.0
#define PAS_U 1.0
#define PAS_THETA 1.0
#else
#include "i2c_interface.hpp"
#include "i2c_LM75.hpp"
#endif

#include "utils.hpp"
#include "robot.hpp"
#include "tourelle.hpp"
#include "ultrasson.hpp"
#include "simu_motorisation.hpp"


int main (int argc, char *argv[]) {
  for (int i=0; i<argc; i++) {
    if (i==1) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
    else if (i==2) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
  }
  Robot mon_robot(100.0, 50.0, 1, 0x30);

  /*
  //mon_robot.asserv.set_position(0, 0, 0);
  mon_robot.asserv.avance(0, 200, -PI/2.0);
  mon_robot.asserv.avance(200, 200, -2.0*PI/2.0);
  mon_robot.asserv.avance(200, 0, PI/2.0);
  mon_robot.asserv.avance(0, 0, 0.0);

  while(mon_robot.asserv.status_robot()!=STOP) {
  }
  mon_robot.asserv.get_position();
  mon_robot.asserv.avance(0, 200, -PI/2.0);
  while(mon_robot.asserv.status_robot()!=STOP) {
  }
  mon_robot.asserv.get_position();
  while(mon_robot.asserv.status_robot()!=STOP) {
  }
  mon_robot.asserv.get_position();
  Tourelle mytourelle(1, 0x45, 6);
  printf("%c\n", mytourelle.get_error());
  mytourelle.get_datas();
  */

#ifdef SIMULATION

  sf::RenderWindow window(sf::VideoMode(LARGEUR_TABLE, HAUTEUR_TABLE), "SFML works!");
  window.setFramerateLimit(60);
  //sf::CircleShape shape(100.f);
  //shape.setFillColor(sf::Color::Green);

  Simu_motorisation mySimu(STOP, 50, 50, 0);
  //Simu_motorisation mySimu(STOP, 300, 100, 0);
  mySimu.recv_avance(100, 100, 0);
  mySimu.show_position();
  mySimu.show_ordres(4);

  sf::Vector2f origin=mon_robot.surface_robot.getSize();
  mon_robot.surface_robot.setOrigin(origin.x/2.0, origin.y/2.0);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    mySimu.update();
    mon_robot.surface_robot.setPosition(mySimu.simu_position.X, mySimu.simu_position.Y);
    mon_robot.surface_robot.setRotation(-mySimu.simu_position.Theta*180.0/PI);

    window.clear();
    mon_robot.draw(window);
    window.display();
    sf::sleep(sf::milliseconds(100));
  }
  mySimu.show_ordres(4);

#else
  /*
     I2c_LM75 * myLM75 = new I2c_LM75(1, 0x48);
     uint8_t temp_hex[2];
     myLM75->temp_floattohex(temp_hex, 25.5);

     printf("%x %x\n", temp_hex[0], temp_hex[1]);
     printf("%f\n", myLM75->temp_hextofloat(temp_hex));

     printf("%.1f\n", myLM75->get_temp());

     Ultrasson * myUltrasson= new Ultrasson(1, 0x10, 2);
     while(1) {
     myUltrasson->get_distances();
     }
     */
#endif
  return 0;

}


