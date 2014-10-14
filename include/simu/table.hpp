
#ifndef TABLE_HPP
#define TABLE_HPP

#include "utils.hpp"
#include <SFML/Graphics.hpp>

class Table{

  public:
    Table(float largeur, float hauteur, sf::Color & my_couleur_table);
    ~Table();
  
    sf::RectangleShape surface_table;

};

#endif
