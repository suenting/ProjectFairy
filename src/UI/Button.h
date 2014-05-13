#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"


class Button : public Label
{
public:
	Button();
	virtual ~Button();
	virtual bool Input(SDL_Event &rSDL_Event);
	virtual void SetDownSprite(std::string path);
	virtual void Render()const;
	void SetCallback(void (*callback)());
	void Click(){mp_callback();}
private:
	void (*mp_callback)();
	bool mbDown;
	Sprite *mpDownSprite;

};

#endif