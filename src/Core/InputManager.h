#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "../pch.h"
#include "../Math/Vector2f.h"

class InputManager
{
public:
	static InputManager& Instance()
	{
		static InputManager instance;
		return instance;
	}
	~InputManager();

	// poll controller input
	void UpdatePosition();
	// keys/joystick
	void ControllerInputEvent(SDL_Event &rSDL_Event);
	Math::Vector2f GetDirection()const{return mDirection;}
	void ClearInput();

	void UpdateScreenDirection(Math::Vector2f direction);

protected:
private:
	InputManager();
	InputManager( const InputManager& other ){};
	InputManager& operator=( const InputManager& rhs ){};

	// not all xinput controllers the same?
	std::map<std::string,SDL_GameController*> mControllerList;

	Math::Vector2f mDirection;

	// keyboard keys
	bool mbUp;
	bool mbDown;
	bool mbLeft;
	bool mbRight;

	// onScreenInput
	Math::Vector2f mScreenDirection;

};

#endif