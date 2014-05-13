#ifndef SCREEN_H
#define SCREEN_H

#include "../pch.h"
#include "Widget.h"

class Screen
{
public:
	Screen();
	~Screen();

	void Render()const;
	void Update();
	bool Input(SDL_Event &rSDL_Event);
	void AddWidget(Widget *widget);
private:
	SDL_Color background_color;
	std::vector<Widget*> mpWidgetList;
};

#endif // SCREEN_H