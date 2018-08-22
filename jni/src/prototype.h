#ifndef PROTOTYPE
#define PROTOTYPE

#include "struct.h"

/* Fichier d'en tête contenant les prototypes de fonctions à utiliser dans le projet (en précisant extern pour préciser qu'il se trouve dans un fichier du projet)*/

// === INIT === //
extern SDL_Renderer *INIT_GetRenderer();
extern SDL_Window *INIT_GetWindow();
extern void INIT_Init(char *);
extern void INIT_LoadGame();
extern void INIT_Cleanup();
extern int INIT_GetWidthWindow();
extern int INIT_GetHeightWindow();
extern void INIT_LoadReplay();

// === INPUT === //
extern void INPUT_GestionInputGame(InputGame *input, InputMenu *inputM);
extern void INPUT_GestionInputMenu(InputMenu *input);
extern void INPUT_GestionInputRanking(InputRanking *input, InputMenu *inputM);
extern void INPUT_GetInputMenu(InputMenu *input);
extern void INPUT_GetInputGame(InputGame *input, InputMenu *inputM);
extern void INPUT_GetInputRanking(InputRanking *input, InputMenu *inputM);

// === DRAW ===//
extern void DRAW_DrawMenu();
extern void DRAW_DrawGame();
extern void DRAW_DrawRanking();
extern OW_Image* DRAW_LoadImage(char* name);
extern void DRAW_DrawImage(SDL_Texture *, int, int);
extern int DRAW_CenterElementX(int element);
extern void DRAW_Delay(unsigned int frameLimit);
extern void DRAW_collision();
extern void DRAW_DrawText();
extern void DRAW_RegisterScore();
extern void DRAW_DrawGameOver();
extern void DRAW_DrawTextGameOver(int x, int y);

// === COLLISION === //
extern void COLLISION_init();
extern void COLLISION_collision();
extern void COLLISION_animate();
extern void COLLISION_addAnimation(int x, int y);
extern void COLLISION_deleteAnimation(int index);
extern void COLLISION_copyCollision(AnimateCollision* dest, AnimateCollision* src, int length);


// === MAP === //
extern void MAP_InitMap();
extern OW_Image *MAP_GetBackground();
extern OW_Image *MAP_GetTitle();
extern OW_Image *MAP_GetBtnPlay();
extern OW_Image *MAP_GetBtnRanking();
extern OW_Image *MAP_GetBtnLeave();
extern void MAP_cleanMap();

// === ENEMY === //
extern GameObject *ENEMY_GetEnemy();
extern void ENEMY_InitEnemySprite();
extern void ENEMY_CleanEnemy();
extern void ENEMY_InitializeNewEnemy();
extern void ENEMY_UpdateEnemy();
extern void ENEMY_DrawEnemy();
extern void ENEMY_CopyEnemy(GameObject* dest, GameObject* src);
extern GameObject* ENEMY_RemoveEnemy(int index);
extern int ENEMY_GetCountEnemy();
extern void ENEMY_destroyMissileOutside();
extern void ENEMY_shoot(GameObject* enemy);
extern Missile* ENEMY_getMissiles();
extern void Enemy_UpdateScore(int index, Player* player);

// === PLAYER === //
extern void PLAYER_InitPlayer();
extern SDL_Texture* PLAYER_GetTextureSharp();
extern Player* PLAYER_GetPlayer();
extern void PLAYER_InvokeCapteur();
extern void *PLAYER_SensorEvent(void *arg);
extern void PLAYER_CleanPlayer();
extern void PLAYER_setHitBox();
extern void PLAYER_displacementPlayer(float coef);
extern int PLAYER_centerMissile(int sizeMissile);
extern void PLAYER_destroyMissiles();
extern void PLAYER_shoot();
extern void PLAYER_drawPlayer(InputGame *input);
extern void PLAYER_collision();

// === SOUND === //
extern void SOUND_init();
extern void SOUND_LoadSong(char filename[200]);
extern void SOUND_LoadSound();
extern void SOUND_FreeSound();
extern void SOUND_PlaySoundFx(int type);
extern void SOUND_PlayMusic();

// === MISSILE === //
extern void MISSILE_copyMissile(SDL_Rect* dest, SDL_Rect* src, int length);
extern void MISSILE_addMissile(Missile* missiles, int w, int h, int x, int y);
extern void MISSILE_removeMissile(Missile* missiles, int index);
extern void MISSILE_drawMissiles(Missile* missiles, int displacementDirection,  float secondes);
extern int MISSILE_displacementDown();
extern int MISSILE_displacementUp();
extern void FONT_LoadFont(char *name, int size);
extern void FONT_CloseFont();
extern void FONT_DrawString(char *text, int x, int y, int r, int g, int b, int a);

#endif