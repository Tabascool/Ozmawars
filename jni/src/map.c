#include "prototype.h"

Map map;
Menu menu;

// Fonction qui initialise les composant graphique du jeu
void MAP_InitMap()
{
	map.background = DRAW_LoadImage("graphics/background.bmp"); //load image declare in draw.c
	
	menu.title = DRAW_LoadImage("menu/titleSpace.bmp");
	menu.btnPlay =  DRAW_LoadImage("menu/boutonSpaceJouer.bmp");
	menu.btnRanking = DRAW_LoadImage("menu/boutonSpaceClassement.bmp");
	menu.btnLeave = DRAW_LoadImage("menu/boutonSpaceQuitter.bmp");
}

// Fonction qui retourne le font d'écran.
OW_Image *MAP_GetBackground()
{
	return map.background;
}

// Fonction qui retourne le titre
OW_Image *MAP_GetTitle()
{
	return menu.title; 
}

OW_Image *MAP_GetBtnPlay()
{
	return menu.btnPlay;
}

OW_Image *MAP_GetBtnRanking()
{
	return menu.btnRanking;
}

OW_Image *MAP_GetBtnLeave()
{
	return menu.btnLeave;
}

// Fonction permettant de vider la mémoire graphique des objets graphiques sur la map.
void MAP_CleanMap()
{
	if (map.background->texture != NULL)
	{
		SDL_DestroyTexture(map.background->texture);
		map.background->texture = NULL;
	}
}