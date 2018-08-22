#include "prototype.h"

int x, y, w, h;

// Fonction qui affiche le menu.
void DRAW_DrawMenu(InputMenu *input)
{
	int space = 50;
	/* Draw a gray background */
	SDL_SetRenderDrawColor(INIT_GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(INIT_GetRenderer());
	//drawImage(getBackground()->texture, 0, 0);

	// Déclaration des images des object graphique du menu.
	OW_Image *title = MAP_GetTitle(), *btnPlay = MAP_GetBtnPlay(), *btnRanking = MAP_GetBtnRanking(), *btnLeave = MAP_GetBtnLeave();

	input->PosXTitle = DRAW_CenterElementX(title->width);
	input->posXBtnPlay = DRAW_CenterElementX(btnPlay->width);
	input->posXBtnRanking = DRAW_CenterElementX(btnRanking->width);
	input->posXBtnLeave = DRAW_CenterElementX(btnLeave->width);

	input->PosYTitle = (INIT_GetHeightWindow() - (title->height + btnPlay->height + btnRanking->height + btnLeave->height)) / 2;
	input->posYBtnPlay = input->PosYTitle + title->height;
	input->posYBtnRanking = input->posYBtnPlay + btnPlay->height;
	input->posYBtnLeave = input->posYBtnRanking + btnRanking->height;
	
	DRAW_DrawImage(title->texture, input->PosXTitle, input->PosYTitle);
	DRAW_DrawImage(btnPlay->texture, input->posXBtnPlay, input->posYBtnPlay);
	DRAW_DrawImage(btnRanking->texture, input->posXBtnRanking, input->posYBtnRanking);
	DRAW_DrawImage(btnLeave->texture, input->posXBtnLeave, input->posYBtnLeave);
	
	SDL_RenderPresent(INIT_GetRenderer());
	
	SDL_Delay(1);
}

// Fonction permettant d'afficher le jeu et ses animations.
void DRAW_DrawGame(InputGame *input)
{
	/* Draw a black background */
	OW_Image *background = MAP_GetBackground();
	SDL_RenderClear(INIT_GetRenderer());
	DRAW_DrawImage(background->texture, 0, 0);
	Player *player = PLAYER_GetPlayer();
	if (player->isDead == 0)
	{
		PLAYER_drawPlayer(input);
	
		// Dessin ennemie.
		ENEMY_InitializeNewEnemy();
		ENEMY_UpdateEnemy();
		ENEMY_DrawEnemy();
	}

	// Dessin du tableau d'état du joueur.
	x = 1;
	y = (player->y + player->sharp->height);
	w = INIT_GetWidthWindow() - 2;
	h = (INIT_GetHeightWindow() - ((player->y + player->sharp->height) + 1) + 1);
	SDL_Rect rectStat = {x, y, w, h};
	SDL_SetRenderDrawColor(INIT_GetRenderer(), 0, 0, 0, 0);
	SDL_RenderFillRect(INIT_GetRenderer(),  &rectStat );
	SDL_SetRenderDrawColor(INIT_GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(INIT_GetRenderer(),  &rectStat );
	DRAW_DrawText(player, x + 20, y + ((INIT_GetHeightWindow() - y) / 2));
	
	x = INIT_GetWidthWindow() - 40;
	y = y + ((INIT_GetHeightWindow() - y) / 2) - 20;
	w = 20;
	h = INIT_GetHeightWindow() - y - 40;
	
	int i;
	
	for (i = player->life; i > 0 ; i--)
	{
		SDL_Rect rectlife = {x - ( i * 40), y, w, h};
		SDL_SetRenderDrawColor(INIT_GetRenderer(), 255, 255, 255, 255);
		SDL_RenderFillRect(INIT_GetRenderer(),  &rectlife );
	}
	
	
	if  (player->isDead == 1)
	{
		DRAW_DrawGameOver();
	}
	
	COLLISION_collision();
	
	//set the draw color
    //SDL_SetRenderDrawColor(INIT_GetRenderer(), 255, 0, 0,255);
		
	/* Update the screen! */
	SDL_RenderPresent(INIT_GetRenderer());
	
	SDL_Delay(1);
}

void DRAW_DrawRanking(InputRanking *input)
{
	//FILE *file;
	//long tabScore[10];
	
	//file = fopen("score.dat", "w");
	
	/* Draw a black background */
	SDL_SetRenderDrawColor(INIT_GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(INIT_GetRenderer());
	
	char textScore[200];
	
	// Ecriture du score
	sprintf(textScore, "MEILLEURS SCORES : ");
	
	FONT_DrawString(textScore, 50, 50, 255, 255, 255, 255);
		
	//if (file == NULL)
	//{
		int i;
		for (i = 0; i < 10; i++)
		{
			sprintf(textScore, "%d. 0", i + 1);
		
			FONT_DrawString(textScore, 50, 50 * (i + 2), 255, 255, 255, 255);
		}
	//}
	/*else
	{
		int i;
		fscanf(file, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &tabScore[0], &tabScore[1], &tabScore[2], &tabScore[3], &tabScore[4], &tabScore[5], &tabScore[6], &tabScore[7], &tabScore[8], &tabScore[9]);
		
		for (i = 0; i < 10; i++)
		{
			sprintf(textScore, "%d. %ld", i + 1, tabScore[i]);
	
			FONT_DrawString(textScore, 50, 50 * (i + 2), 255, 255, 255, 255);
		}
	}*/

	//fclose(file);
	
	/* Update the screen! */
	SDL_RenderPresent(INIT_GetRenderer());
	
	SDL_Delay(1);
}

OW_Image* DRAW_LoadImage(char *name){
	SDL_Surface *loadedImage = NULL;
	OW_Image *image;
	loadedImage = SDL_LoadBMP (name);
	Uint32 colorkey = SDL_MapRGB (loadedImage->format, 237, 28, 36);
	image = malloc(sizeof(OW_Image));

	if (image == NULL)
		return NULL;

	if (loadedImage != NULL)
	{
		//get image weight
		image->width = loadedImage->w;
		//get image height
		image->height = loadedImage->h;

		SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);

		// Conversion de l'image en texture.
		image->texture = SDL_CreateTextureFromSurface(INIT_GetRenderer(), loadedImage);
		// Liberation du pointeur sur la surface.
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	else image = NULL;
	return image;
}

void DRAW_DrawImage(SDL_Texture *image, int x, int y)
{
	SDL_Rect dest;
	
	// Réglage du rectangle qui va contenir l'image.
	dest.x = x;
	dest.y = y;
	
	// Dessin de l'image.
	SDL_QueryTexture (image, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(INIT_GetRenderer(), image, NULL, &dest);
}

int DRAW_CenterElementX(int element){
	return (INIT_GetWidthWindow() - element) / 2;
}

// Fonciton permettant d'attendre le temps necessaire pour respecter les 60 fps.
void DRAW_Delay(unsigned int frameLimit)
{
	// Gestion des 60 fps (images/stories/seconde)
	unsigned int ticks = SDL_GetTicks();
	
	if (frameLimit < ticks)
	{
		return;
	}
	
	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}
	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}

void DRAW_DrawText(Player* player, int x, int y)
{
	char textScore[200];
	
	// Ecriture du score
	sprintf(textScore, "SCORE : %ld", player->score);
	
	FONT_DrawString(textScore, x, y, 255, 255, 255, 255);
}

void DRAW_DrawTextGameOver(int x, int y)
{
	char textGameOver[200];
	
	// Ecriture du score
	sprintf(textGameOver, "GAME OVER");
	
	FONT_DrawString(textGameOver, x, y, 255, 255, 255, 255);
}

void DRAW_DrawGameOver()
{
	SDL_Rect rectStat = {1, 1, INIT_GetWidthWindow() - 2, INIT_GetHeightWindow() / 2};
	SDL_SetRenderDrawColor(INIT_GetRenderer(), 0, 0, 0, 0);
	SDL_RenderFillRect(INIT_GetRenderer(),  &rectStat );
	SDL_SetRenderDrawColor(INIT_GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(INIT_GetRenderer(),  &rectStat );
	DRAW_DrawTextGameOver(INIT_GetWidthWindow() / 4 + 20, INIT_GetHeightWindow() / 4);
}

void DRAW_RegisterScore(Player* player)
{
	int sizeMax = 1000;
	char chaine[sizeMax];
	FILE *file;
	size_t size;
	long tabScore[10];
	
	file = fopen("score.dat", "a+");
	
	if (file != NULL)
	{
		size = ftell(file);
		
		if (size != 10)
		{
			fprintf(file, "%ld", player->score);
			
			int i;
			
			for (i = 0; i < 9; i++)
			{
				fprintf(file, " 0");
			}
		}
		else
		{
			fscanf(file, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &tabScore[0], &tabScore[1], &tabScore[2], &tabScore[3], &tabScore[4], &tabScore[5], &tabScore[6], &tabScore[7], &tabScore[8], &tabScore[9]);
			
			int i = 0;
			
			while (i < 10 || tabScore[i] < player->score)
			{
				if (tabScore[i] < player->score)
				{
					int j;
					
					for (j = i; j < 9; j++)
					{
						tabScore[j - 1] = tabScore[j];
					}
					 tabScore[i] = player->score;
				}
			}
			
			for (i = 0; i < 10; i++)
			{
				fprintf(file, " %ld", tabScore[i]);
			}
			
			fclose(file);
		}
	}
}