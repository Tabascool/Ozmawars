#include "prototype.h"

#define ENEMY_1 1
#define ENEMY_2 2
#define ENEMY_3 3
#define ENEMY_4 4
#define BOSS_1 5
#define BOSS_2 6
#define RIGHT 0
#define LEFT 1
#define DOWN 3
#define UP 4

GameObject *enemy;
Missile missilesEnemies;
SpriteEnemy spriteEnemy;
int nbEnemy = 0;
int timeS = 0;
int tempsScoreBoss1 = 0;
int tempsScoreBoss2 = 0;
int tempsScoreE2 = 0;
int tempsScoreE3 = 0;
int tempsScoreE4 = 0;
int bossTime = 0;
int visible=0, tickVisible = 0, tickBlink = 0, maxVisibility=10, maxBlink = 30;
int downPhase = 0;

GameObject * ENEMY_GetEnemy()
{
	return enemy;
}

// Fonction qui va charger les sprites des ennemis.
void ENEMY_InitEnemySprite()
{
	spriteEnemy.sharpEnemy1 = DRAW_LoadImage("graphics/enemy1.bmp");
	spriteEnemy.sharpEnemy2 = DRAW_LoadImage("graphics/enemy2.bmp");
	spriteEnemy.sharpEnemy3 = DRAW_LoadImage("graphics/enemy3.bmp");
	spriteEnemy.sharpEnemy4 = DRAW_LoadImage("graphics/enemy4.bmp");
	spriteEnemy.sharpBoss1 = DRAW_LoadImage("graphics/boss.bmp");
	spriteEnemy.sharpBoss2 = DRAW_LoadImage("graphics/boss2.bmp");
	
	nbEnemy = 0;
	timeS = 0;
	tempsScoreBoss1 = 0;
	tempsScoreBoss2 = 0;
	tempsScoreE2 = 0;
	tempsScoreE3 = 0;
	tempsScoreE4 = 0;
	bossTime = 0;
	visible=0; 
	tickVisible = 0; 
	tickBlink = 0; 
	maxVisibility=10; 
	maxBlink = 30;
	downPhase = 0;
}

// Fonction qui libère la mémoire des sprites des ennemis.
void ENEMY_CleanEnemy()
{
	/*int i;
	for (i = 0; i < nbEnemy; i++)
	{
		// Libération des sprites des ennemis.
		if (enemy[i].sharp != NULL)
		{
			if(enemy[i].sharp->texture !=NULL)
			{
				SDL_DestroyTexture(enemy[i].sharp->texture);
				enemy[i].sharp->texture = NULL;
			}
			free(enemy[i].sharp);
		}
	}
	
	if(missilesEnemies.sprites != NULL){
		missilesEnemies.sprites = NULL;
	}*/
	
	//missilesEnemies.sprites = realloc(missilesEnemies.sprites, 0*sizeof(SDL_Rect));
	
}

// Fonction qui initialise un nouvel ennemi.
void ENEMY_InitializeNewEnemy()
{
	if (timeS >= 100 && bossTime == 0) {
		timeS = 0;
		nbEnemy++;
		enemy = realloc(enemy, nbEnemy*sizeof(GameObject));
		int randomPosX;
		GameObject newEnemy;
		
		if (tempsScoreE2 > 30)
		{
			tempsScoreE2 = 0;
			if(enemy != NULL){
				newEnemy.sharp = spriteEnemy.sharpEnemy2;
				int width = spriteEnemy.sharpEnemy2->width;
		
				randomPosX = (rand() % (INIT_GetWidthWindow() - (width * 2)) + width);
				newEnemy.x = randomPosX;
				newEnemy.y = 0 - spriteEnemy.sharpEnemy2->height;
				newEnemy.life = 2;
				newEnemy.type = ENEMY_2;
				newEnemy.direction = RIGHT;
				ENEMY_shoot(&newEnemy);
				newEnemy.cadenceShoot = 150;
				newEnemy.tickEnemy = newEnemy.cadenceShoot;
				newEnemy.hit = 0;
				*(enemy + (nbEnemy - 1)) = newEnemy;
			}
		}
		else if (tempsScoreE3 > 50)
		{
			tempsScoreE3 = 0;
			if(enemy != NULL){
				newEnemy.sharp = spriteEnemy.sharpEnemy3;
				int width = spriteEnemy.sharpEnemy3->width;
		
				randomPosX = (rand() % (INIT_GetWidthWindow() - (width * 2)) + width);
				newEnemy.x = randomPosX;
				newEnemy.y = 0 - spriteEnemy.sharpEnemy3->height;
				newEnemy.life = 3;
				newEnemy.type = ENEMY_3;
				newEnemy.direction = RIGHT;
				newEnemy.direction2 = DOWN;
				newEnemy.cadenceShoot = 160;
				newEnemy.cadenceShoot2 = 180;
				newEnemy.tickEnemy = newEnemy.cadenceShoot;
				newEnemy.tickEnemy2 = newEnemy.cadenceShoot2;
				newEnemy.hit = 0;
				*(enemy + (nbEnemy - 1)) = newEnemy;
			}
		}
		else if (tempsScoreE4 > 100)
		{
			tempsScoreE4 = 0;
			newEnemy.sharp = spriteEnemy.sharpEnemy4;
			int width = spriteEnemy.sharpEnemy4->width;
			randomPosX = (rand() % (INIT_GetWidthWindow() - (width * 4)) + width * 2);
			if(enemy != NULL)
			{
				newEnemy.x = randomPosX;
				newEnemy.y = 0 - spriteEnemy.sharpEnemy4->height;
				newEnemy.life = 1;
				newEnemy.type = ENEMY_4;
				newEnemy.direction = RIGHT;
				newEnemy.cadenceShoot = 160;
				newEnemy.tickEnemy = newEnemy.cadenceShoot;
				newEnemy.hit = 0;
				*(enemy + (nbEnemy - 1)) = newEnemy;
			}
		}
		else if (tempsScoreBoss1 > 1000)
		{
			tempsScoreBoss1 = 0;
			bossTime = 1;
			if(enemy != NULL){
				newEnemy.sharp = spriteEnemy.sharpBoss1;
				int width = spriteEnemy.sharpBoss1->width;
		
				newEnemy.x = INIT_GetWidthWindow() / 2 - spriteEnemy.sharpBoss1->width / 2;
				newEnemy.y = 0 - spriteEnemy.sharpBoss1->height;
				newEnemy.life = 100;
				newEnemy.type = BOSS_1;
				newEnemy.direction = RIGHT;
				newEnemy.cadenceShoot = 100;
				newEnemy.cadenceShoot2 = 150;
				newEnemy.tickEnemy = newEnemy.cadenceShoot;
				newEnemy.tickEnemy2 = newEnemy.cadenceShoot2;
				newEnemy.hit = 0;
				*(enemy + (nbEnemy - 1)) = newEnemy;
			}
		}
		else if (tempsScoreBoss2 > 3000)
		{
			tempsScoreBoss2 = 0;
			bossTime = 1;
			if(enemy != NULL){
				newEnemy.sharp = spriteEnemy.sharpBoss2;
				int width = spriteEnemy.sharpBoss2->width;
		
				newEnemy.x = INIT_GetWidthWindow() / 2 - spriteEnemy.sharpBoss2->width / 2;
				newEnemy.y = 0 - spriteEnemy.sharpBoss2->height;
				newEnemy.life = 300;
				newEnemy.type = BOSS_2;
				newEnemy.direction = RIGHT;
				newEnemy.cadenceShoot = 100;
				newEnemy.cadenceShoot2 = 150;
				newEnemy.cadenceShoot3 = 200;
				newEnemy.tickEnemy = newEnemy.cadenceShoot;
				newEnemy.tickEnemy2 = newEnemy.cadenceShoot2;
				newEnemy.tickEnemy3 = newEnemy.cadenceShoot3;
				newEnemy.hit = 0;
				*(enemy + (nbEnemy - 1)) = newEnemy;
			}
		}
		else
		{
			if(enemy != NULL){
				newEnemy.sharp = spriteEnemy.sharpEnemy1;
				int width = spriteEnemy.sharpEnemy1->width;
		
				randomPosX = (rand() % (INIT_GetWidthWindow() - (width * 2)) + width);
				newEnemy.x = randomPosX;
				newEnemy.y = 0 - spriteEnemy.sharpEnemy1->height;
				newEnemy.life = 0;
				newEnemy.type = ENEMY_1;
				newEnemy.cadenceShoot = 180;
				newEnemy.tickEnemy = newEnemy.cadenceShoot;
				newEnemy.hit = 0;
				*(enemy + (nbEnemy - 1)) = newEnemy;
			}
		}
	}
	else 
		timeS++;
	
}

GameObject* ENEMY_RemoveEnemy(int index)
{
	GameObject tmp[nbEnemy];
	ENEMY_CopyEnemy(tmp, enemy);
	enemy = realloc(enemy, (--nbEnemy)*sizeof(GameObject));
	if (enemy != NULL)
	{	
		int i;
		for (i = 0; i < nbEnemy; i++) {
			if (i < index)
				*(enemy + i) = *(tmp + i);
			else
				*(enemy + i) = *(tmp + i + 1);
		}
	}
	return enemy;
}

void ENEMY_UpdateEnemy()
{
	float secondes = 4.00, fps = 60.00;
    int widthWindow = INIT_GetWidthWindow();
    float v = (float)(widthWindow) / (secondes * fps);

	int i;
	
	for (i = 0; i < nbEnemy; i++)
	{
		if(enemy[i].type == ENEMY_1)
			enemy[i].y += v;
		else if(enemy[i].type == ENEMY_2)
		{
			if (enemy[i].x + enemy[i].sharp->width >= INIT_GetWidthWindow())
				enemy[i].direction = LEFT;
			else if (enemy[i].x <= 0)
				enemy[i].direction = RIGHT;
			
			enemy[i].y += v / 2;
			
			if (enemy[i].direction == RIGHT)
				enemy[i].x += v;
			else
				enemy[i].x -= v;
		}
		else if (enemy[i].type == ENEMY_3)
		{
			if (enemy[i].x + enemy[i].sharp->width >= INIT_GetWidthWindow())
				enemy[i].direction = LEFT;
			else if (enemy[i].x <= 0)
				enemy[i].direction = RIGHT;
			
			if (enemy[i].y >= INIT_GetHeightWindow() / 2)
				enemy[i].direction2 = UP;
			else if (enemy[i].y <= 0)
				enemy[i].direction2 = DOWN;
			
			enemy[i].y += v;
			
			if (enemy[i].direction == RIGHT)
				enemy[i].x += v;
			else
				enemy[i].x -= v;
			
			if (enemy[i].direction2 == DOWN)
				enemy[i].y += v;
			else
				enemy[i].y -= v;
			
		}
		else if (enemy[i].type == ENEMY_4)
		{
			if (enemy[i].x + enemy[i].sharp->width >= INIT_GetWidthWindow())
			{
				if (downPhase <= enemy[i].sharp->height)
				{
					enemy[i].y += v * 2;
					downPhase++;
				}
				else
				{
					downPhase = 0;
					enemy[i].direction = LEFT;
				}
			}
			else if (enemy[i].x <= 0)
			{
				if (downPhase <= enemy[i].sharp->height)
				{
					enemy[i].y += v * 2;
					downPhase++;
				}
				else
				{
					downPhase = 0;
					enemy[i].direction = RIGHT;
				}
			}
			
			if (enemy[i].direction == RIGHT && downPhase == 0)
				enemy[i].x += v * 2;
			else if (enemy[i].direction == LEFT && downPhase == 0)
				enemy[i].x -= v * 2;
		}
		else if ( enemy[i].type == BOSS_1)
		{
			if (enemy[i].y < 0)
				enemy[i].y += 1;
			else
			{
				if (enemy[i].x + enemy[i].sharp->width >= INIT_GetWidthWindow())
					enemy[i].direction = LEFT;
				else if (enemy[i].x <= 0)
					enemy[i].direction = RIGHT;
			
			
			
				if (enemy[i].direction == RIGHT)
					enemy[i].x += v;
				else
					enemy[i].x -= v;
			}
		}
		else if (enemy[i].type == BOSS_2)
		{
			if (enemy[i].y < 0 - enemy[i].sharp->height / 2 + 100)
				enemy[i].y += 1;
			else
			{
				if (enemy[i].x + enemy[i].sharp->width >= INIT_GetWidthWindow() + enemy[i].sharp->width / 2)
					enemy[i].direction = LEFT;
				else if (enemy[i].x <= 0 - enemy[i].sharp->width / 2)
					enemy[i].direction = RIGHT;
			
			
			
				if (enemy[i].direction == RIGHT)
					enemy[i].x += v;
				else
					enemy[i].x -= v;
			}
		}
		
		if (enemy[i].y > INIT_GetHeightWindow()) 
		{	
			ENEMY_RemoveEnemy(i);
		}
	}
}

void ENEMY_destroyMissileOutside(){
	int i;
	if(missilesEnemies.sprites != NULL){
		for (i = 0; i < missilesEnemies.nbMissiles; i++){
			if( (*(missilesEnemies.sprites+i)).y > INIT_GetHeightWindow()){
				MISSILE_removeMissile(&missilesEnemies, i);
			}
		}
	}
}

void ENEMY_shoot(GameObject* enemy){
	int widthMissile = 15;
	int x = enemy->x + ((enemy->sharp->width - widthMissile)/2);
	if(enemy->tickEnemy >= enemy->cadenceShoot){

		if (enemy->type == ENEMY_1 || enemy->type == ENEMY_2 || enemy->type == ENEMY_4)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x, enemy->y + enemy->sharp->height);
		}
		else if (enemy->type == ENEMY_3)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x - 15, enemy->y + enemy->sharp->height);
		}
		else if (enemy->type == BOSS_1)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x - 17, enemy->y + enemy->sharp->height);
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x + 48, enemy->y + enemy->sharp->height);
		}
		else if (enemy->type == BOSS_2)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x, enemy->y + enemy->sharp->height);
		}
        enemy->tickEnemy =0;
    }
    else {
        enemy->tickEnemy++;
    }
	
	if(enemy->tickEnemy2 >= enemy->cadenceShoot2)
	{
		if (enemy->type == ENEMY_3)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x + 15, enemy->y + enemy->sharp->height);
		}
		else if (enemy->type == BOSS_1)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x - 85, enemy->y + enemy->sharp->height);
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x + 102, enemy->y + enemy->sharp->height);
		}
		else if (enemy->type == BOSS_2)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x + 105, enemy->y + enemy->sharp->height - 22);
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x - 105, enemy->y + enemy->sharp->height - 22);
		}
		enemy->tickEnemy2 = 0;
	}
	else
	{
		enemy->tickEnemy2++;
	}
	
	if(enemy->tickEnemy3 >= enemy->cadenceShoot3)
	{
		if (enemy->type == BOSS_2)
		{
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x + 202, enemy->y + enemy->sharp->height - 200);
			MISSILE_addMissile(&missilesEnemies,widthMissile , 25, x - 202, enemy->y + enemy->sharp->height - 200);
		}
		enemy->tickEnemy3 = 0;
	}
	else
	{
		enemy->tickEnemy3++;
	}
}

void ENEMY_DrawEnemy()
{
	ENEMY_destroyMissileOutside();
	// Dessin ennemie.
	int i;
	for (i = 0; i < nbEnemy; i++)
	{
		ENEMY_shoot(enemy + i);
		if(enemy[i].hit){
			if(tickVisible >= maxVisibility){
				tickVisible = 0;
				visible = !visible;
			}
			if(tickBlink >= maxBlink){
				enemy[i].hit = !enemy[i].hit;
				tickBlink = 0;
			}
			tickVisible++;
			tickBlink++;
		}
		if(!enemy[i].hit || visible){
			DRAW_DrawImage(enemy[i].sharp->texture, enemy[i].x, enemy[i].y);
		}
	}

	SDL_SetRenderDrawColor(INIT_GetRenderer(), 255, 0, 0, 255);
	MISSILE_drawMissiles(&missilesEnemies, MISSILE_displacementDown(), 3.50);
}

void ENEMY_CopyEnemy(GameObject* dest, GameObject* src)
{
	int i;
	for(i = 0; i < nbEnemy; i++)
	{
		dest[i] = src[i];
	}
}

int ENEMY_GetCountEnemy() {
	return nbEnemy;
}

Missile* ENEMY_getMissiles(){
 return &missilesEnemies;
}

void Enemy_UpdateScore(int index, Player* player)
{
	if (enemy[index].type == ENEMY_1)
	{
		player->score += 10;
		tempsScoreE2 += 10;
		tempsScoreE3 += 10;
		tempsScoreE4 += 10;
		tempsScoreBoss1 += 10;
		tempsScoreBoss2 += 10;
	}
	else if (enemy[index].type == ENEMY_2)
	{
		player->score += 20;
		tempsScoreBoss1 += 20;
		tempsScoreBoss2 += 20;
	}
	else if (enemy[index].type == ENEMY_3)
	{
		player->score += 50;
		tempsScoreBoss1 += 50;
		tempsScoreBoss2 += 50;
	}
	else if (enemy[index].type == ENEMY_4)
	{
		player->score += 100;
		tempsScoreBoss1 += 100;
		tempsScoreBoss2 += 100;
	}
	else if (enemy[index].type == BOSS_1)
	{
		player->score += 1000;
		bossTime = 0;
		player->life = 10;
	}
	else if (enemy[index].type == BOSS_2)
	{
		player->score += 5000;
		bossTime = 0;
		player->life = 10;
	}
}