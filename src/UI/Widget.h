#ifndef WIDGET_H
#define WIDGET_H
#include "../Math/Vector2f.h"
#include "../pch.h"
class Widget
{
public:
	Widget();
	virtual ~Widget();

	virtual void Render()const=0;
	virtual void Update(){}
	virtual bool Input(SDL_Event &rSDL_Event){return false;}
	virtual void SetPosition(Math::Vector2f position){m_position=position;}
	Math::Vector2f GetPosition()const{return m_position;}
	void SetVisible(bool val) { mb_IsVisible = val; }
protected:
	Math::Vector2f m_position;
	bool mb_IsVisible;

};

#endif