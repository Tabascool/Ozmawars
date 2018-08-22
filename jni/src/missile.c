#include "prototype.h"

int up = -1;
int down = 1;

int MISSILE_displacementUp(){
    return up;
}

int MISSILE_displacementDown(){
    return down;
}

void MISSILE_addMissile(Missile* missiles, int w, int h, int x, int y){
    if(missiles->nbMissiles == NULL){
        missiles->nbMissiles = 0;
    }
    int nb = ++missiles->nbMissiles;
    missiles->sprites = realloc(missiles->sprites, nb*sizeof(SDL_Rect));
    if(missiles->sprites != NULL){
        SDL_Rect sprite;
        sprite.w = w;
        sprite.h = h;
        sprite.x = x;
        sprite.y = y;
        *(missiles->sprites + (nb-1)) = sprite;
    }
    else{
        LOGI("réallocation impossible des missiles");
    }
}

void MISSILE_removeMissile(Missile* missiles, int index){
    SDL_Rect* tmp = malloc(missiles->nbMissiles*sizeof(SDL_Rect));
    int i;
    MISSILE_copyMissile(tmp, missiles->sprites, missiles->nbMissiles);
        missiles->sprites = realloc(missiles->sprites, (--missiles->nbMissiles)*sizeof(SDL_Rect));
        if (missiles->sprites != NULL){
            for (i=0; i<missiles->nbMissiles; i++){
                if(i<index){
                    *(missiles->sprites +i) = *(tmp + i);
                }
                else{
                    *(missiles->sprites +i) = *(tmp + i+1);
                }
            }
        } else {
            LOGI("reallocation impossible lors de la destruction du missile");
        }
    free(tmp);
}

void MISSILE_drawMissiles(Missile* missiles, int displacementDirection, float secondes){
	int i;
	float fps = 60.00;
	for (i =0; i<missiles->nbMissiles; i++){
		(*(missiles->sprites + i)).y += (float)(INIT_GetHeightWindow()) / (secondes * fps) * displacementDirection;
	}
	SDL_RenderFillRects(INIT_GetRenderer(), missiles->sprites, missiles->nbMissiles);
}



void MISSILE_copyMissile(SDL_Rect* dest, SDL_Rect* src, int length){
    int i;
    for (i=0; i<length; i++){
        dest[i] = src[i];
    }
}