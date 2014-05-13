#include "InputManager.h"

namespace
{
	
}
InputManager::InputManager()
{
	
#ifdef WIN32
	SDL_GameControllerAddMapping("6d0418c2000000000000504944564944,Logitech RumblePad 2 USB,platform:Windows,x:b0,a:b1,b:b2,y:b3,back:b8,start:b9,dpleft:h0.8,dpdown:h0.4,dpright:h0.2,dpup:h0.1,leftshoulder:b4,lefttrigger:b6,rightshoulder:b5,righttrigger:b7,leftstick:b10,rightstick:b11,leftx:a0,lefty:a1,rightx:a2,righty:a3");
	SDL_GameControllerAddMapping("xinput,X360 Controller,a:b10,b:b11,back:b5,dpdown:b1,dpleft:b2,dpright:b3,dpup:b0,guide:b14,leftshoulder:b8,leftstick:b6,lefttrigger:a4,leftx:a0,lefty:a1,rightshoulder:b9,rightstick:b7,righttrigger:a5,rightx:a2,righty:a3,start:b4,x:b12,y:b13,platform:Windows");

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) 
		{
			SDL_GameController *gameController;
			gameController = SDL_GameControllerOpen(i);
			const char * name = SDL_GameControllerName(gameController);
			mControllerList.insert(std::pair<std::string, SDL_GameController*>(std::string(name),gameController));
		}
	}
	mbUp=false;
	mbDown=false;
	mbLeft=false;
	mbRight=false;
#endif
}

InputManager::~InputManager()
{

}

void InputManager::ControllerInputEvent( SDL_Event &rSDL_Event )
{
	// movement
	if((rSDL_Event.type == SDL_JOYHATMOTION)||(rSDL_Event.type == SDL_JOYAXISMOTION))
	{
		//SDL_assert(false);
	}
	// keyboard
	if(rSDL_Event.type == SDL_KEYDOWN)
	{
		switch( rSDL_Event.key.keysym.sym )
		{
		case SDLK_UP: mbUp=true; break;
		case SDLK_DOWN: mbDown=true; break;
		case SDLK_LEFT: mbLeft=true; break;
		case SDLK_RIGHT: mbRight=true; break;
		}
	}
	if(rSDL_Event.type == SDL_KEYUP)
	{
		switch( rSDL_Event.key.keysym.sym )
		{
		case SDLK_UP: mbUp=false; break;
		case SDLK_DOWN: mbDown=false; break;
		case SDLK_LEFT: mbLeft=false; break;
		case SDLK_RIGHT: mbRight=false; break;
		}
	}
	// buttons
	if(rSDL_Event.type == SDL_JOYBUTTONUP)
	{
		//SDL_assert(false);
	}
}



void InputManager::UpdatePosition()
{
	bool bUp=false;
	bool bDown=false;
	bool bLeft=false;
	bool bRight=false;
#ifdef WIN32
	// poll inputs from any controller
	for(std::map<std::string,SDL_GameController*>::iterator it = mControllerList.begin(); it != mControllerList.end();++it)
	{
		SDL_GameController* pController = it->second;
		Uint8 dpad_up = SDL_GameControllerGetButton(pController,SDL_CONTROLLER_BUTTON_DPAD_UP);
		Uint8 dpad_down = SDL_GameControllerGetButton(pController,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		Uint8 dpad_left = SDL_GameControllerGetButton(pController,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		Uint8 dpad_right = SDL_GameControllerGetButton(pController,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		bUp = bUp||mbUp||(dpad_up>0);
		bDown = bDown||mbDown||(dpad_down>0);
		bLeft = bLeft||mbLeft||(dpad_left>0);
		bRight = bRight||mbRight||(dpad_right>0);
	}
	if(bUp && !bDown){mDirection.y=-1.f;}
	if(bDown && !bUp){mDirection.y=1.f;}
	if(bLeft && !bRight){mDirection.x=-1.f;}
	if(bRight && !bLeft){mDirection.x=1.f;}
#endif

	mDirection += mScreenDirection;
	mDirection.NormalizeSelf();

}

void InputManager::ClearInput()
{
	mDirection.x = 0.f;mDirection.y=0.f;
}

void InputManager::UpdateScreenDirection( Math::Vector2f direction )
{
	mScreenDirection = direction.NormalizeSelf();
}

