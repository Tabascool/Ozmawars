#include "prototype.h"

// Déclaration de la police de font.
TTF_Font *font;

// Fonction qui va charger la police à la taille spécifiée.
void FONT_LoadFont(char *name, int size)
{
	// On utilise SDL_TTF pour charger la police (font) à la taille spécicifiée par size.
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

// Fonction permettant d'afficher du texte à l'écrant en précisant la chaine, sa position et les code couleur RGBA.
void FONT_DrawString(char *text, int x, int y, int r, int g, int b, int a)
{
	SDL_Rect dest;
	//Pour écrire le texte
	SDL_Surface *surface;
	//Pour convertir la surface en texture
	SDL_Texture *texture;
	SDL_Color foregroundColor;
 
	// Couleur du texte RGBA
	foregroundColor.r = r;
	foregroundColor.g = g;
	foregroundColor.b = b;
	foregroundColor.a = a;
 
	// On utilise SDL_TTF pour générer une SDL_Surface à partir d'une chaîne de caractères (string)
	surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);
 
	if (surface != NULL)
	{
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(INIT_GetRenderer(), surface);
 
		// On libère la SDL_Surface temporaire (pour éviter les fuites de mémoire)
		SDL_FreeSurface(surface);
		surface = NULL;
 
		// On dessine cette texture à l'écran
		dest.x = x;
		dest.y = y;
 
		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
		SDL_RenderCopy(INIT_GetRenderer(), texture, NULL, &dest);
 
		//On supprime la texture
		SDL_DestroyTexture(texture);
 
	}
	else
	{
		printf("La chaine n'a pu être écrite %s: %s\n", text, TTF_GetError());
		exit(0);
	}
}