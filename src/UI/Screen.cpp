#include "Screen.h"

Screen::Screen()
{

}

Screen::~Screen()
{
	for(std::vector<Widget*>::iterator it = mpWidgetList.begin(); it != mpWidgetList.end();++it)
	{
		delete (*it);
	}
}

void Screen::Render() const
{
	for(std::vector<Widget*>::const_iterator it = mpWidgetList.begin(); it != mpWidgetList.end();++it)
	{
		(*it)->Render();
	}

}

void Screen::Update()
{
	for(std::vector<Widget*>::const_iterator it = mpWidgetList.begin(); it != mpWidgetList.end();++it)
	{
		(*it)->Update();
	}
}

void Screen::AddWidget( Widget *widget )
{
	mpWidgetList.push_back(widget);
}

bool Screen::Input( SDL_Event &rSDL_Event )
{
	for(std::vector<Widget*>::const_iterator it = mpWidgetList.begin(); it != mpWidgetList.end();++it)
	{
		bool bEatInput = (*it)->Input(rSDL_Event);
		if(bEatInput)
		{
			return true;
		}
	}
	return false;
}

