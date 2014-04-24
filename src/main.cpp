
#ifdef SIMULATION
#define LARGEUR_TABLE 600.0
#define HAUTEUR_TABLE 400.0
#define PAS_U 1.0
#define PAS_THETA 1.0
#else
#include "i2c_interface.hpp"
#include "i2c_LM75.hpp"
#include "i2c_ultrasson.hpp"
#endif

#include "utils.hpp"
#include "robot.hpp"

int main (int argc, char *argv[]) {
  for (int i=0; i<argc; i++) {
    if (i==1) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
    else if (i==2) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
  }
  Robot mon_robot(100.0, 50.0);
  mon_robot.asserv.avance_tourne(-10, -10, -10);
  mon_robot.asserv.get_position();
  
#ifdef SIMULATION

  sf::RenderWindow window(sf::VideoMode(LARGEUR_TABLE, HAUTEUR_TABLE), "SFML works!");
  window.setFramerateLimit(60);
  //sf::CircleShape shape(100.f);
  //shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    mon_robot.draw(window);
    window.display();
  }

#else
  I2c_LM75 * myLM75 = new I2c_LM75(1, 0x48);
  uint8_t temp_hex[2];
  myLM75->temp_floattohex(temp_hex, 25.5);

  printf("%x %x\n", temp_hex[0], temp_hex[1]);
  printf("%f\n", myLM75->temp_hextofloat(temp_hex));

  printf("%.1f\n", myLM75->get_temp());

  I2c_ultrasson * myUltrasson= new I2c_ultrasson(1, 0x10);
  printf("%1.f\n", myUltrasson->get_distance());
  printf("%d\n", sizeof(uint8_t));

#endif
  return 0;

}


