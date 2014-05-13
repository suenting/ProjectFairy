#ifndef MENU_H
#define MENU_H

#include "../pch.h"
#include "Widget.h"
#include "Button.h"

class Menu : public Widget
{
public:
	Menu();
	virtual ~Menu();
	virtual void Render()const;
	virtual bool Input(SDL_Event &rSDL_Event);
	virtual void SetPosition(Math::Vector2f position);
	void AddButton(Button* pButton);
	void ClearButtons();
	void SetSelectedHighlight(std::string path);
	int GetSelectedIndex()const{return mSelectedIndex;}
protected:
private:
	std::vector<Button*> mButtonList;
	Label* mSelectedLabel;
	int mSelectedIndex;

};

#endif//MENU_H