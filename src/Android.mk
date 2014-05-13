LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here... 
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp \
	Core/AnimatedSprite.cpp Core/AudioManager.cpp Core/FontManager.cpp Core/InputManager.cpp Core/ResourceManager.cpp Core/Sprite.cpp \
	Math/Circle2f.cpp Math/Rect2f.cpp Math/Vector2f.cpp \
	Simulation/Actor.cpp Simulation/ActorData.cpp Simulation/Effect.cpp Simulation/EffectData.cpp Simulation/Game.cpp Simulation/ModContentManager.cpp Simulation/Player.cpp Simulation/Projectile.cpp Simulation/ProjectileData.cpp Simulation/StageData.cpp \
	UI/Button.cpp UI/Label.cpp UI/ManaBar.cpp UI/Menu.cpp UI/PlayerHealth.cpp UI/Screen.cpp UI/ScreenDefs.cpp UI/ThumbStick.cpp UI/Widget.cpp \

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)

