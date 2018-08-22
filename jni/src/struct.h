#ifndef DEF_STRUCT
#define DEF_STRUCT

#include "definition.h"

/* Fichier d'en tête qui contiendra toute les structures du projet */

typedef struct OW_Image
{
	SDL_Texture* texture;
	int width, height;
} OW_Image;

// Structure contenant les différentes actions du joueur dans le jeu.
typedef struct InputGame
{
	int moveX, moveY;
	float accelX, accelY, accelZ;
	
} InputGame;

// Structure contenant les différentes actions du joueur dans le menu.
typedef struct InputMenu
{
	int play, ranking, leave;
	int PosXTitle, PosYTitle;
	int posXBtnPlay, posYBtnPlay;
	int posXBtnRanking, posYBtnRanking;
	int posXBtnLeave, posYBtnLeave;
} InputMenu;

// Structure contenant le classement.
typedef struct InputRanking
{
	int PosXTitle, PosYTitle;
} InputRanking;

typedef struct Map
{
	OW_Image *background;
} Map;

typedef struct Menu
{
	OW_Image *title;
	OW_Image *btnPlay;
	OW_Image *btnRanking;
	OW_Image *btnLeave;
} Menu;

typedef struct AnimateCollision
{
	int i, tickImage, maxTimeImage;
	int x, y;

}AnimateCollision;

typedef struct Collision
{
	OW_Image* explosion1;
	OW_Image* explosion2;
	OW_Image* explosion3;
	OW_Image* explosion4;
	OW_Image* explosion5;
	OW_Image* explosion6;
	AnimateCollision* animateCollision;
	int nbAnimate, nbImage;

} Collision;

typedef struct Missile
{
	SDL_Rect* sprites;
	int nbMissiles;
} Missile;

typedef struct Player
{
	OW_Image* sharp;
	int x, y;
	int boxLeft, boxRight;
	int boxTop, boxBottom;
	long score;
	int life, isDead;
	int invincible;
	Missile missiles;
} Player;

// Structure contenant les paramètre des objects du jeu (joueur et ennemis).
typedef struct GameObject
{
	OW_Image* sharp;
	
	// Point de vie.
	int life;
	
	// Coordonnées du sprite.
	int x, y;

	//repère dans le temps et cadence de tir
	int tickEnemy, tickEnemy2, tickEnemy3, cadenceShoot, cadenceShoot2, cadenceShoot3;
	
	// Largeur et hauteur du sprite.
	int h, w;
	
	int type;
	
	int direction;
	int direction2;
	int hit;

} GameObject;

typedef struct SpriteEnemy
{
	OW_Image* sharpEnemy1;
	OW_Image* sharpEnemy2;
	OW_Image* sharpEnemy3;
	OW_Image* sharpEnemy4;
	OW_Image* sharpBoss1;
	OW_Image* sharpBoss2;
} SpriteEnemy;

#endif