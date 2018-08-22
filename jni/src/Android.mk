LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include 

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.c draw.c init.c input.c map.c player.c enemy.c missile.c sound.c font.c collision.c

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv1_CM -ldl -lGLESv2 -lstdc++ -lz

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_mixer
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)
$(call import-module,android/native_app_glue)
APP_PLATFORM := android-10
