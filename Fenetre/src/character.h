#include <SDL2/SDL.h>
#include "foreground.h"
#define MAX_CH	MAX_FG
#define MAX_NAME 16
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
enum behaviour{standing,moving,jumping};
enum direction{N,NE,E,SE,S,SW,W,NW};

typedef struct
{
	char name[MAX_NAME];
	char PV, PO, LVL;
	Foreground fg;
	SDL_Rect position;
	enum direction dir;
	enum behaviour bhv;
}Character;

//crée un nouveau personnage
Character* character_Init();
//détruit le personnage
void character_Destroy(Character* pCh);
void character_DestroyAll();

//getter
Character* getCh(byte_t b);

//setter
void character_setDirection(Character* pCh,const byte_t dirMask);
void character_move(Character* pCh);
void character_copyToRender(Character* ch);
void character_copyAllToRender();
//tue le personnage
void character_Kill(Character* pCh);
//sauvegarde le personnage
int character_Save();
//charge le personnage
int character_Load();
