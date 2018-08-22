#ifndef DEF_DEFINITION
#define DEF_DEFINITION

/* Fichier d'en tête qui va contenir tout les définitions */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include <EGL/egl.h>
#include <GLES/gl.h>


#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "OzmaWars Activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "OzmaWars Activity", __VA_ARGS__))

enum
{
	SHOOT,
	DESTROY
};

#endif