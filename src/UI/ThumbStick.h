#ifndef THUMBSTICK_H
#define THUMBSTICK_H

#include "Widget.h"
#include "../pch.h"
#include "../Math/Vector2f.h"
#include "../Core/Sprite.h"
#include "../Math/Circle2f.h"

class ThumbStick : public Widget
{
public:
	ThumbStick(Math::Vector2f center);
	~ThumbStick();
	virtual void Render()const;
	virtual void Update();
	virtual bool Input(SDL_Event &rSDL_Event);

	void UpdateThumbPosition( SDL_Event &rSDL_Event );

protected:
private:
	Math::Vector2f mCenter;
	Math::Vector2f mPosition;
	// todo: make sprites static if multiple
	Sprite *mpBaseSprite;
	Sprite *mpTopSprite;
	Math::Circle mBaseCircle;
	
};

#endif