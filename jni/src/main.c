#include "prototype.h"

// Ici on déclare les variables / structures utilisées par le jeu.
InputMenu inputMenu;
InputGame inputGame;
InputRanking inputRanking;

int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	
	// Initialisation de le SDL
	INIT_Init("Ozmawars - ESGI - by Antoine & Julien");
	
	// Chargement des ressources
	INIT_LoadGame();

	//gestion accelerometre
	PLAYER_InvokeCapteur(&inputGame);
	
	// Methode permettant d'appeller automatiquement la fonction de netoyage à la fin de programme.
	atexit(INIT_Cleanup);
	
	// La fameuse boucle infinie du jeu.
	while (inputMenu.leave != 1)

	{
		// Acces à une partie.
		if (inputMenu.play == 1)
		{
			INPUT_GestionInputGame(&inputGame, &inputMenu);
			// Dessin du jeu.
			DRAW_DrawGame(&inputGame);
			SOUND_PlayMusic();
		}
		// Acces au classement.
		else if (inputMenu.ranking == 1)
		{
			INPUT_GestionInputRanking(&inputRanking, &inputMenu);
			DRAW_DrawRanking();
		}
		// Acces au Menu.
		else
		{
			// Gestion des inputs.
			INPUT_GestionInputMenu(&inputMenu);
			DRAW_DrawMenu(&inputMenu);
		}
		
		// Gestion des 60 fps.
		DRAW_Delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}
	exit(0);
}