#include "prototype.h"
Player player;
ASensorEventQueue* sensorEventQueue;
int tickGame=25;
int widthMissile = 15;
int visibleP = 0, maxVisibilityP=10, maxInvincibility = 120, tickVisibleP=0, tickInvincibility=0;


void PLAYER_InitPlayer(){
    player.sharp = DRAW_LoadImage("graphics/vaisseauPlayer.bmp");
    if(player.sharp != NULL){
        int height = player.sharp->height, width = player.sharp->width;
        player.x = DRAW_CenterElementX(width);
        player.y = INIT_GetHeightWindow() - (height + (height/2));
        PLAYER_setHitBox(width, height);
		player.score = 0;
		player.life = 10;
		player.isDead = 0;
		player.invincible = 0;
		tickGame=25;
		widthMissile = 15;
		visibleP = 0;
		maxVisibilityP=10;
		maxInvincibility = 120;
		tickVisibleP=0;
		tickInvincibility=0;
    }
}

int PLAYER_centerMissile(int sizeMissile){
    return player.x + ((player.sharp->width - sizeMissile)/2);
}

void PLAYER_drawPlayer(InputGame *input){
    //draw sharp Player
    PLAYER_displacementPlayer(input->accelX);

    if (player.invincible){
        if (tickVisibleP >= maxVisibilityP){
            visibleP = !visibleP;
            tickVisibleP = 0;
        }
        if (tickInvincibility >= maxInvincibility){
            player.invincible = !player.invincible;
            tickInvincibility = 0;
        }
        tickVisibleP++;
        tickInvincibility++;
    }

    if(!player.invincible || visibleP){
        DRAW_DrawImage(PLAYER_GetTextureSharp(), player.x, player.y);
    }


    //draw the player missile
    PLAYER_destroyMissiles();
    PLAYER_shoot();
    SDL_SetRenderDrawColor(INIT_GetRenderer(), 80, 220, 40, 255);

    MISSILE_drawMissiles(&player.missiles, MISSILE_displacementUp(), 2.50);
}

void PLAYER_shoot(){
    if(tickGame >= 25){
        MISSILE_addMissile(&player.missiles, widthMissile, 25, PLAYER_centerMissile(widthMissile), player.y);
        tickGame =0;
    }
    else {
        tickGame++;
    }
}

void PLAYER_destroyMissiles(){
    if(player.missiles.sprites != NULL){
        if((*(player.missiles.sprites)).y < 0){
            MISSILE_removeMissile(&player.missiles, 0);
        }
    }
}

SDL_Texture* PLAYER_GetTextureSharp(){
    if (player.sharp != NULL)
        return player.sharp->texture;
    return NULL;
}

Player* PLAYER_GetPlayer(){
    return &player;
}

void PLAYER_collision(){
    if(player.life > 0){
        if(!player.invincible){
            player.life--;
            player.invincible = !player.invincible;
        }
    }else{
		player.isDead = 1;
    }
}

void PLAYER_displacementPlayer(float coef){
    float secondes = 6.00, fps = 60.00;
    int width = player.sharp->width;
    int widthWindow = INIT_GetWidthWindow();
    float v = (float)(widthWindow) * (-coef*2.00) / (secondes * fps);
    //LOGI("width window: %d, coef : %f, vitesse:  %f", INIT_GetWidthWindow(), coef, v);

    if(player.x + player.sharp->width + v > widthWindow)
        player.x = widthWindow - width;
    else if (player.x + v < 0)
        player.x = 0;
    else player.x += v;
    PLAYER_setHitBox(width, player.sharp->height);
}

void PLAYER_setHitBox(int width, int height){
    float percent = 0.10;
    //hit box, padding 10% compare to image
    player.boxLeft = player.x + (width*percent);
    player.boxRight = player.x + width - (width*percent);
    player.boxTop = player.y + (height*percent);
    player.boxBottom = player.y + height - (height*percent);
}

void PLAYER_InvokeCapteur(InputGame *input){

    ASensorEvent event;
    int looper_id = 3;
    ASensorManager* sensorManager;
    const ASensor* accSensor;
    void* sensor_data = malloc(1000);
    ALooper* looper = ALooper_forThread();

    if(looper == NULL)
    {
        looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    }

    sensorManager = ASensorManager_getInstance();
    accSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);

    sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, looper_id, NULL, sensor_data);
    ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);

    //Sampling rate: 100Hz
    int a = ASensor_getMinDelay(accSensor);
    ASensorEventQueue_setEventRate(sensorEventQueue, accSensor, 100000);

    pthread_t thread;
    if(pthread_create(&thread, NULL, PLAYER_SensorEvent, input) == -1) {
        perror("pthread_create");
    }

}

void *PLAYER_SensorEvent(void *arg){
    int events;
    InputGame* input = (InputGame *)(arg);
    while(1){
        ASensorEvent event;
        while (ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0) {

            if(event.type == ASENSOR_TYPE_ACCELEROMETER) {
                //LOGI("accl(x,y,z,t): %f %f %f %lld", event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);
                input->accelX = event.acceleration.x;
                input->accelY = event.acceleration.y;
                input->accelZ = event.acceleration.z;
            }

        }
    }
    pthread_exit(NULL); /* Fin du thread */
}

void PLAYER_CleanPlayer(){
    if (player.sharp != NULL)
    	{
    	    if(player.sharp->texture !=NULL)
    		    SDL_DestroyTexture(player.sharp->texture);
    		player.sharp->texture = NULL;
    		free(player.sharp);
    	}/*
    if(player.missiles.sprites != NULL){
        player.missiles.sprites = NULL;
    }*/
}