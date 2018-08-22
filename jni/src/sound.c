#include "prototype.h"

// Sounds Fx
Mix_Chunk *shoot_sound, *destroy_sound, *music;
int channel = 0;

void SOUND_init(){
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
    	LOGI("Unable to initialize SDL: %s\n", SDL_GetError());
    }

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
    	LOGI("Unable to initialize audio: %s\n", Mix_GetError());
    }
}

void SOUND_LoadSong(char filename[200])
{

	// Libération de la musique précèdante.
	if (music != NULL)
	{
		Mix_FreeChunk(music);
	}
	
	// Chargement de la nouvelle musique.
	music = Mix_LoadWAV(filename);
	if (music == NULL)
	{
		LOGI("Erreur au chargement de la musique");
	}
}

void SOUND_PlayMusic(){
	if(Mix_Playing(channel) == 0){
		Mix_VolumeMusic(50);
		// Activation de la répétition infinis de la musique.
		channel = Mix_PlayChannel(-1, music, 0);
		if (channel == -1)
		{
			LOGI("Mix_PlayMusic: %s\n", Mix_GetError());
		}
	}
}

void SOUND_LoadSound()
{
	shoot_sound = Mix_LoadWAV("sounds/shoot.wav");
	if (shoot_sound == NULL)
	{
		LOGI("Can't read the shoot sound FX \n");
	}
 
	destroy_sound = Mix_LoadWAV("sounds/destroy.wav");
	if (destroy_sound == NULL)
	{
		LOGI("Can't read the destroy sound FX \n");
	}
}
 
 
void SOUND_FreeSound()
{
	Mix_FreeChunk(shoot_sound);
	Mix_FreeChunk(destroy_sound);
	Mix_FreeChunk(music);
	Mix_CloseAudio();
}
 
 
void SOUND_PlaySoundFx(int type)
{
	switch (type)
	{
		case SHOOT:
			Mix_PlayChannel(-1, shoot_sound, 0);
			break;
 
		case DESTROY:
			Mix_PlayChannel(-1, destroy_sound, 0);
			break;
	}
}