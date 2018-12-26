#include <SDL2/SDL.h>
#include "sprite.h"
#include <math.h>
/*
 * Brief : représente l'état du personnage
 * nb.Ce n'est pas un personnage de JDR, il n'a pas de caractéristique et de hasard entourant sa création.
 * Les niveaux que le personnage franchit sont implicites, le joueur n'est pas au courant du niveau de son personnage.
 * Le personnage peut débloquer des compétences qui lui permettent d'avançer.
 * L'équipement est corrélé avec le niveau, le niveau est corrélé avec l'avancement dans l'histoire (il n'y a pas d'XP).
 * Seul le joueur a de l'XP, pas le personnage.
 * Pas de stamina ou de mana
 */

/*
 * Tableau des niveaux
 * PV  3, 5, 7, 9, 11;
 * LVL 0, 1, 2, 3, 4;
 * Equipement par niveaux:
 * 		sarbacane			raquette		bombe
 * 		à boulette			de tennis		à peinture
 * 		à fléchette			club de golf 	déodorant
 * 		patator				gants de boxe	déodorant + briquet
 * 		pistolet à fusée	sabre			à fragmentation
 * 		tromblon
 */
typedef struct
{
	size_t PV, PO, LVL;
	Sprite*  sprite;
	SDL_Rect position;
}Character;

//crée un nouveau personnage
Character character_init();
//détruit le personnage
void character_destroy(Character* pCh);
//tue le personnage
void character_kill(Character* pCh);
//sauvegarde le personnage
int character_save();
//charge le personnage
int character_load();
