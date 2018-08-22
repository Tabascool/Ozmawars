#include "prototype.h"

/* Fichier permettant de g�rer les action effectu� par le joueur sur l'application */

// Fonction qui g�re les actions du joueur dans le jeu.
void INPUT_GestionInputGame(InputGame *input, InputMenu *inputM)
{
	INPUT_GetInputGame(input, inputM);
}

// Fonction qui g�re les actions du joueur dans le menu.
void INPUT_GestionInputMenu(InputMenu *input)
{
	INPUT_GetInputMenu(input);
}

void INPUT_GestionInputRanking(InputRanking *input, InputMenu *inputM)
{
	INPUT_GetInputRanking(input, inputM);
}

// Fonction qui g�re les �v�nements �mis par une action et les enregistres dans la structure input.
void INPUT_GetInputMenu(InputMenu *input)
{
	SDL_Event event;
	
	// V�rification des �v�nements
    while(SDL_PollEvent(&event))
	{
		// TODO : Mettre les actions en rapport avec les mouvement de l'acc�l�rom�tre, les tires, la pause etc... (pr�f�res un switch, c'est plus classe ;))
		if(event.type == SDL_QUIT)
		{
            input->leave = 1;
        }
		// Si le joueur pause son doigt sur une zone pr�cise de l'�cran Menu.
        else if(event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION){
        	OW_Image * btnPlay = MAP_GetBtnPlay();
			OW_Image * btnLeave = MAP_GetBtnLeave();
			OW_Image * btnRanking = MAP_GetBtnRanking();
			// Si le joueur selectionne le bouton JOUER.
			if (event.tfinger.x * INIT_GetWidthWindow() > input->posXBtnPlay 
					&& event.tfinger.x * INIT_GetWidthWindow() < input->posXBtnPlay + btnPlay->width
						&& event.tfinger.y * INIT_GetHeightWindow() > input->posYBtnPlay 
							&& event.tfinger.y * INIT_GetHeightWindow() < input->posYBtnPlay + btnPlay->height)
			{
				input->play = 1;
				input->leave = 0;
				input->ranking = 0;		
			}
			// Si le joueur selectionne le bouton QUITTER
			else if (event.tfinger.x * INIT_GetWidthWindow() > input->posXBtnLeave 
					&& event.tfinger.x * INIT_GetWidthWindow() < input->posXBtnLeave + btnLeave->width
						&& event.tfinger.y * INIT_GetHeightWindow() > input->posYBtnLeave 
							&& event.tfinger.y * INIT_GetHeightWindow() < input->posYBtnLeave + btnLeave->height)
			{
				input->leave = 1;
				input->play = 0;
				input->ranking = 0;						
			}
			// Si le joueur selectionne le bouton CLASSEMENT.
			else if (event.tfinger.x * INIT_GetWidthWindow() > input->posXBtnRanking
					&& event.tfinger.x * INIT_GetWidthWindow() < input->posXBtnRanking + btnRanking->width
						&& event.tfinger.y * INIT_GetHeightWindow() > input->posYBtnRanking 
							&& event.tfinger.y * INIT_GetHeightWindow() < input->posYBtnRanking + btnRanking->height)
			{
				input->ranking = 1;
				input->leave = 0;
				input->play = 0;
			}
        }
    }
}

// Fonction qui g�re les �v�nements �mis par une action et les enregistres dans la strucutre input.
void INPUT_GetInputGame (InputGame *input, InputMenu *inputM)
{	
	SDL_Event event;
	
	// V�rification des �v�nements
    while(SDL_PollEvent(&event))
	{
		// TODO : Mettre les actions en rapport avec les mouvement de l'acc�l�rom�tre, les tires, la pause etc... (pr�f�res un switch, c'est plus classe ;))
		if(event.type == SDL_QUIT)
		{
            inputM->play = 0;
        }
        else if(event.type == SDL_FINGERDOWN){
			Player * player = PLAYER_GetPlayer();
			if (player->isDead == 1)
			{
				inputM->play = 0;
				//ENEMY_CleanEnemy();
				//PLAYER_CleanPlayer();
				
				INIT_LoadReplay();
			}
        }
    }
	
}

void INPUT_GetInputRanking(InputRanking *input, InputMenu *inputM)
{
	SDL_Event event;
	
	// V�rification des �v�nements
    while(SDL_PollEvent(&event))
	{
		// TODO : Mettre les actions en rapport avec les mouvement de l'acc�l�rom�tre, les tires, la pause etc... (pr�f�res un switch, c'est plus classe ;))
		if(event.type == SDL_QUIT)
		{
            inputM->ranking = 0;
        }
        else if(event.type == SDL_FINGERDOWN){
			Player * player = PLAYER_GetPlayer();
				inputM->ranking = 0;
        }
    }
}