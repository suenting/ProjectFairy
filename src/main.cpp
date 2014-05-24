#include "pch.h"
#include "Core/ResourceManager.h"
#include "Simulation/Game.h"
#include "Core/Sprite.h"
#include "Core/FontManager.h"
#include "UI/Label.h"
#include "Math/Vector2f.h"
#include "Core/AudioManager.h"
namespace
{
	const int RENDER_FRAMES_PER_SECOND = 30;
	size_t renderStart=0;
	size_t currentTimer;
	size_t ticks;

	static void OnInput()
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			Game::Instance().Input(event);
			#ifndef WIN32
			if( event.type == SDL_QUIT || event.type == SDL_KEYDOWN )
			#else
			if( event.type == SDL_QUIT )
			#endif
			{
				SDL_Quit();
				exit(0);
			}

		}
	}

	static void OnUpdate()
	{
		Game::Instance().Update();
	}
	static void OnRender()
	{
		Game::Instance().Render();
		//Stage::Instance().Render();
		SDL_RenderPresent(ResourceManager::Instance().GetRenderer());
	}


	static void MainLoop()
	{
		currentTimer = SDL_GetTicks();
		renderStart=SDL_GetTicks();

		OnInput();
		OnUpdate();
		OnRender();

		// sdl delay
		ticks = SDL_GetTicks()-renderStart;
		if( ticks < (1000 / RENDER_FRAMES_PER_SECOND) )
		{
			SDL_Delay(( 1000 / RENDER_FRAMES_PER_SECOND ) - ticks);
		}
	}

	int SDLCALL exitEventFilter(void *userdata, SDL_Event * event)
	{
		if (event->type == SDL_APP_WILLENTERBACKGROUND) 
		{
			SDL_Quit();
			exit(0);
		}
		// etc
		return 1;
	}

}

int main(int argc, char **argv) 
{
	ResourceManager::Instance();
	bool done=false;
	AudioManager::Instance().PlayMusic("The Stage is Set.ogg");
	SDL_AddEventWatch(exitEventFilter, NULL);
	while(true)
	{
		MainLoop();
	}
	exit(0);
	return 0;
}