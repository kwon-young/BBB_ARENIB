BBB_ARENIB
==========


La beaglebone black est la partie haut niveau du robot.
C'est-à-dire que c'est elle qui s'occupe de communiquer avec tous les actionneurs, base roulante et tourelle, 
et c'est donc elle qui s'occupe de prndre les décisions.


CRITIQUE :
==========
- ~~Codage de la couche i2c en c pour communiquer avec la base roulante et la tourelle.~~
- ~~Check de de la couche i2c depuis le merge !!!~~
- ~~Codage du simulateur de motorisation !!!~~
- Test sur cible !!!
- Communication avec l'interface pour connaitre l'emplacement des autres robots (simu_tourelle)
- Coder un systèmes de objectifs à point + recalculs en cas de rencontre


Un peu moins Critique :
=======================
- ~~Codage d'un simulateur de table pour pouvoir simuler un script de déplacement du robot.~~
Disponible ici -> https://github.com/lamogui/arenib_interface
- Coder proprement la classe moteur et rendre réaliste la classe motorisation.
- Radiocommande par point (posibiliter d'envoyer la position via l'interface)
