#define BBB 0
#define simu 1
#define CIBLE simu

#if CIBLE == BBB
#include "i2c_interface.hpp"
#include "i2c_LM75.hpp"
#include "i2c_ultrasson.hpp"

#elif CIBLE == simu
#define LARGEUR_TABLE 600.0
#define HAUTEUR_TABLE 400.0
#define PAS_U 1.0
#define PAS_THETA 1.0
#endif

#include "utils.hpp"

int main (int argc, char *argv[]) {
  for (int i=0; i<argc; i++) {
    if (i==1) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
    else if (i==2) {
      printf ("argc = %d : %s\n", i, argv[i]);
    }
  }

#if CIBLE == simu

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
    
    window.display();
  }

#elif CIBLE == BBB
  I2c_LM75 * myLM75 = new I2c_LM75(1, 0x48);
  char temp_hex[2];
  myLM75->temp_floattohex(temp_hex, 25.5);

  printf("%x %x\n", temp_hex[0], temp_hex[1]);
  printf("%f\n", myLM75->temp_hextofloat(temp_hex));

  printf("%.1f\n", myLM75->get_temp());

  I2c_ultrasson * myUltrasson= new I2c_ultrasson(1, 0x10);
  printf("%1.f\n", myUltrasson->get_distance());

  /*
     int i2c_bus=1;
     int i2c_addr=0x48;
     int temp_int;
     float temp_float;
     char temp[2], config[1];

     I2c_interface * my_interface=new I2c_interface(i2c_bus, i2c_addr);

     my_interface->i2c_read(0x0, temp, 2);

     temp_int=temp[0];
     if (temp[0]>>7) {
     temp_int*=-1;
     temp_int&=~(1<<7);
     }

     temp_float=temp_int;
     if (temp[1]>>7) temp_float+=0.5;
     printf("il fait %.1f degree celsius\n", temp_float);

     config[0]=1;
     my_interface->i2c_write(0x1, config, 1);
     config[0]=0xf;
     my_interface->i2c_read(0x1, config, 1);
     printf("config du capteur temp : %d\n", config[0]);
     */
#endif
  return 0;

}


