#include "prototype.h"

Collision collision;

void COLLISION_init(){
    collision.nbAnimate = 0;
    collision.nbImage = 6;
    collision.explosion1 = DRAW_LoadImage("graphics/explosion1.bmp");
    collision.explosion2 = DRAW_LoadImage("graphics/explosion2.bmp");
    collision.explosion3 = DRAW_LoadImage("graphics/explosion3.bmp");
    collision.explosion4 = DRAW_LoadImage("graphics/explosion4.bmp");
    collision.explosion5 = DRAW_LoadImage("graphics/explosion5.bmp");
    collision.explosion6 = DRAW_LoadImage("graphics/explosion6.bmp");
}

void COLLISION_animate(){
	int i;
	if(collision.nbAnimate>0){
		for(i=0; i<collision.nbAnimate; i++){
			AnimateCollision* animateCollision = collision.animateCollision + i;
			if( !(animateCollision->i > collision.nbImage) ){
				if(animateCollision->tickImage >= animateCollision->maxTimeImage){
					animateCollision->i++;
					animateCollision->tickImage = 0;
				}
				SDL_Texture* texture;
				switch(animateCollision->i){
					case 1:
						 texture = collision.explosion1->texture;
						break;
					case 2:
						texture = collision.explosion2->texture;
						break;
					case 3:
						texture = collision.explosion3->texture;
						break;
					case 4:
						texture = collision.explosion4->texture;
						break;
					case 5:
						texture = collision.explosion5->texture;
						break;
					case 6:
						texture = collision.explosion6->texture;
						break;
					default:
						break;
				}

				DRAW_DrawImage(texture, animateCollision->x, animateCollision->y);
				animateCollision->tickImage++;
			} else {
				COLLISION_deleteAnimation(i--);
			}
		}
	}
}

void COLLISION_addAnimation(int x, int y){
	collision.animateCollision = realloc(collision.animateCollision, (++collision.nbAnimate)*sizeof(AnimateCollision));
	if(collision.animateCollision!=NULL){
		AnimateCollision newAnimate;
		newAnimate.x = x;
		newAnimate.y = y;
		newAnimate.i = 1;
		newAnimate.tickImage = 0;
		newAnimate.maxTimeImage = 3;
		*(collision.animateCollision + (collision.nbAnimate-1)) = newAnimate;
	}
}

void COLLISION_deleteAnimation(int index){
	AnimateCollision* tmp = malloc(collision.nbAnimate*sizeof(AnimateCollision));
	int i;
	COLLISION_copyCollision(tmp, collision.animateCollision, collision.nbAnimate);
		collision.animateCollision = realloc(collision.animateCollision, (--collision.nbAnimate)*sizeof(AnimateCollision));
		if (collision.animateCollision != NULL){
			for (i=0; i<collision.nbAnimate; i++){
				if(i<index){
					*(collision.animateCollision +i) = *(tmp + i);
				}
				else{
					*(collision.animateCollision +i) = *(tmp + i+1);
				}
			}
		} else {
			LOGI("reallocation impossible lors de la destruction du missile");
		}
	free(tmp);
}

void COLLISION_copyCollision(AnimateCollision* dest, AnimateCollision* src, int length){
    int i;
    for (i=0; i<length; i++){
        dest[i] = src[i];
    }
}

void COLLISION_collision(){
	Player* player = PLAYER_GetPlayer();
	GameObject* enemies = ENEMY_GetEnemy();
	SDL_Rect* missilePlayer;
	GameObject* enemy;
	int i, j, removeEnemy, removeMissile;
	int boxRightEnemy, boxBottomEnemy, boxRightMPlayer, boxBottomMPlayer, boxRightMEnemy, boxBottomMEnemy;

	//collision entre, le player et ses missiles, et les enemies
	for (i = 0; i < ENEMY_GetCountEnemy(); i++)
	{
		enemy = enemies + i;
		removeEnemy = 0;
		boxRightEnemy = enemy->x + enemy->sharp->width;
		boxBottomEnemy = enemy->y + enemy->sharp->height;
		//si une seule de ces conditions est vraie, il n'y a pas de collision
		if (!(player->boxLeft > boxRightEnemy || player->boxRight < enemy->x
			|| player->boxTop > boxBottomEnemy || player->boxBottom < enemy->y)  )
			{
				LOGI("collision entre le player et l'ennemy %d", i);
				PLAYER_collision();
				COLLISION_addAnimation(enemy->x, enemy->y);
				enemies = ENEMY_RemoveEnemy(i);
				removeEnemy = !removeEnemy;
			}

		for(j=0; j < player->missiles.nbMissiles; j++){
			missilePlayer = player->missiles.sprites + j;

			//si une seule de ces conditions est vraie, il n'y a pas de collision
			if(!(missilePlayer->x > boxRightEnemy || missilePlayer->x + missilePlayer->w < enemy->x
					|| missilePlayer->y > boxBottomEnemy || missilePlayer->y + missilePlayer->h < enemy->y))
			{
				LOGI("le player à toucher l'ennemy %d avec le missile %d",i, j);

				if(enemy->life > 0){
					enemy->life--;
					enemy->hit = 1;
				}else if(!removeEnemy) {
					COLLISION_addAnimation(enemy->x, enemy->y);
					Enemy_UpdateScore(i, player);
					enemies = ENEMY_RemoveEnemy(i);
					removeEnemy = !removeEnemy;
				}

				MISSILE_removeMissile(&player->missiles, j--);
			}
		}

		if (removeEnemy) i--;
	}


	//collision entre les missiles enemies et, le player et ses missiles

	Missile* missilesEnemies = ENEMY_getMissiles();
	for (i = 0; i < missilesEnemies->nbMissiles; i++){
		SDL_Rect* missileEnemy = missilesEnemies->sprites + i;
		removeMissile = 0;

		boxRightMEnemy = missileEnemy->x + missileEnemy->w; //
		boxBottomMEnemy = missileEnemy->y + missileEnemy->h;

		if ( !(player->boxLeft > boxRightMEnemy || player->boxRight < missileEnemy->x
               			|| player->boxTop > boxBottomMEnemy  || player->boxBottom < missileEnemy->y) )
		{
			LOGI("collision entre le player et missileEnemy %d", i);
			MISSILE_removeMissile(missilesEnemies, i);
			removeMissile = !removeMissile;
			PLAYER_collision();
        }

		for (j=0; j<player->missiles.nbMissiles; j++){
			missilePlayer = player->missiles.sprites + j;

			boxRightMPlayer = missilePlayer->x + missilePlayer->w;
			boxBottomMPlayer = missilePlayer->y + missilePlayer->h;

			if( !(missilePlayer->x > boxRightMEnemy || boxRightMPlayer < missileEnemy->x
					|| missilePlayer->y > boxBottomMEnemy || boxBottomMPlayer < missileEnemy->y) )
			{
				LOGI("collision entre missile %d du player et missile %d des enemies",i, j);
				if(!removeMissile){
					removeMissile = !removeMissile;
					MISSILE_removeMissile(missilesEnemies, i);
				}
				MISSILE_removeMissile(&player->missiles, j--);
			}
		}

		if(removeMissile) i--;
	}

	COLLISION_animate();
}