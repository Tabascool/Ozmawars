#include "prototype.h"

SDL_Window *window;
SDL_Renderer *renderer;
int width, height;

// Fonction qui retourne simplement le renderer.
SDL_Renderer *INIT_GetRenderer()
{
	return renderer;
}

// Fonction qui retourne la fen�tre du programme.
SDL_Window *INIT_GetWindow()
{
	return window;
}

// Fonction qui initialise la SDL et pr�pare la fen�tre.
void INIT_Init(char *title)
{
	if(SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0){
        printf("erreur lors de la creation du render");
        exit(2);
    }
	
	SDL_GetWindowSize(INIT_GetWindow() , &width , &height);
}

// Fonction chargeant les composant graphique du jeu
void INIT_LoadGame()
{
	MAP_InitMap();
	PLAYER_InitPlayer();
	ENEMY_InitEnemySprite();
	COLLISION_init();
	
	if (TTF_Init() < 0)
	{
		printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
		exit(1);
	}
	
	FONT_LoadFont("font/ARIAL.TTF", 32);

	//On initialise SDL_Mixer 2, qui g�rera la musique et les effets sonores
	SOUND_init();
	SOUND_LoadSong("music/Kubbi-PewPewPew-FLUVORE.wav");
	SOUND_LoadSound();
}

// Fonction chargeant les composant graphique du jeu
void INIT_LoadReplay()
{
	PLAYER_InitPlayer();
	ENEMY_InitEnemySprite();
	COLLISION_init();
	
	//On initialise SDL_Mixer 2, qui g�rera la musique et les effets sonores
	/*SOUND_init();
	SOUND_LoadSong("music/Kubbi-PewPewPew-FLUVORE.wav");
	SOUND_LoadSound();*/
}

// Fonciton qui lib�re la m�moire occup�e par la window et le renderer actuels.
void INIT_Cleanup()
{
	MAP_CleanMap();
	PLAYER_CleanPlayer();
	ENEMY_CleanEnemy();
	SOUND_FreeSound();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Fonction qui retourne la largeur de la fen�tre.
int INIT_GetWidthWindow()
{
	return width;
}

// Fonction qui retourne la hauteur de la fen�tre.
int INIT_GetHeightWindow()
{
	return height;
}