#include "menu.h"

Menu::Menu()
{
	mSelectedLabel = NULL;
	mSelectedIndex = 0;
}

Menu::~Menu()
{
	ClearButtons();
}

void Menu::Render() const
{
	for(std::vector<Button*>::const_iterator it = mButtonList.begin(), et = mButtonList.end(); it != et; ++it)
	{
		(*it)->Render();
	}
	if(NULL != mSelectedLabel)
	{
		mSelectedLabel->Render();
	}
}

void Menu::SetPosition( Math::Vector2f position )
{
	m_position = position;
	Math::Vector2f tempPosition = position;
	for(std::vector<Button*>::iterator it = mButtonList.begin(), et = mButtonList.end(); it != et; ++it)
	{
		(*it)->SetPosition(tempPosition);
		tempPosition.y += (*it)->GetHeight();
	}
}

void Menu::AddButton( Button* pButton )
{
	if(0==mButtonList.size())
	{
		pButton->SetPosition(m_position);
	}
	else
	{
		Math::Vector2f tempPos = mButtonList[mButtonList.size()-1]->GetPosition();
		tempPos.y += mButtonList[mButtonList.size()-1]->GetHeight();
		pButton->SetPosition(tempPos);
	}
	mButtonList.push_back(pButton);
}

void Menu::ClearButtons()
{
	for(std::vector<Button*>::iterator it = mButtonList.begin(), et = mButtonList.end(); it != et; ++it)
	{
		delete (*it);
	}
	mButtonList.clear();
}

bool Menu::Input( SDL_Event &rSDL_Event )
{
	int clickedIndex = 0;
	for(std::vector<Button*>::iterator it = mButtonList.begin(), et = mButtonList.end(); it != et; ++it)
	{
		bool bClicked = (*it)->Input(rSDL_Event);
		if(bClicked)
		{
			if(NULL != mSelectedLabel)
			{
				mSelectedLabel->SetPosition((*it)->GetPosition());
				mSelectedLabel->SetVisible(true);
				mSelectedIndex=clickedIndex;
			}
			return true;
		}
		++clickedIndex;
	}
	if(((SDL_MOUSEBUTTONUP == rSDL_Event.type) || ( SDL_FINGERUP == rSDL_Event.type))&& (NULL != mSelectedLabel))
	{
		mSelectedLabel->SetVisible(false);
		mSelectedIndex=-1;
	}
	return false;
}

void Menu::SetSelectedHighlight( std::string path )
{
	Label* pLabel = new Label();
	pLabel->SetImage(path);
	mSelectedLabel = pLabel;
}

