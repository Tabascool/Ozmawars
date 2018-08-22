#include "prototype.h"

// D�claration de la police de font.
TTF_Font *font;

// Fonction qui va charger la police � la taille sp�cifi�e.
void FONT_LoadFont(char *name, int size)
{
	// On utilise SDL_TTF pour charger la police (font) � la taille sp�cicifi�e par size.
	font = TTF_OpenFont(name, size);
 
	if (font == NULL)
	{
		printf("Failed to open Font %s: %s\n", name, TTF_GetError());
		exit(1);
	}
}

// Fonction qui ferme la police.
void FONT_CloseFont()
{
	// On ferme la police (font).
	if (font != NULL)
	{
		TTF_CloseFont(font);
	}
}

// Fonction permettant d'afficher du texte � l'�crant en pr�cisant la chaine, sa position et les code couleur RGBA.
void FONT_DrawString(char *text, int x, int y, int r, int g, int b, int a)
{
	SDL_Rect dest;
	//Pour �crire le texte
	SDL_Surface *surface;
	//Pour convertir la surface en texture
	SDL_Texture *texture;
	SDL_Color foregroundColor;
 
	// Couleur du texte RGBA
	foregroundColor.r = r;
	foregroundColor.g = g;
	foregroundColor.b = b;
	foregroundColor.a = a;
 
	// On utilise SDL_TTF pour g�n�rer une SDL_Surface � partir d'une cha�ne de caract�res (string)
	surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);
 
	if (surface != NULL)
	{
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(INIT_GetRenderer(), surface);
 
		// On lib�re la SDL_Surface temporaire (pour �viter les fuites de m�moire)
		SDL_FreeSurface(surface);
		surface = NULL;
 
		// On dessine cette texture � l'�cran
		dest.x = x;
		dest.y = y;
 
		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
		SDL_RenderCopy(INIT_GetRenderer(), texture, NULL, &dest);
 
		//On supprime la texture
		SDL_DestroyTexture(texture);
 
	}
	else
	{
		printf("La chaine n'a pu �tre �crite %s: %s\n", text, TTF_GetError());
		exit(0);
	}
}