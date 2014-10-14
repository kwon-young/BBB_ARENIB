
#include "table.hpp"

Table::Table(float largeur, float hauteur, const sf::Color & my_couleur_table) :
surface_table(sf::Vector2f(largeur, hauteur))
{
  surface_table.setFillColor(my_couleur_table);
  surface_table.setPosition(0,0);
}

Table::~Table()
{}