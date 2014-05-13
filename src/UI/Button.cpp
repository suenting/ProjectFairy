#include "Button.h"
#include "../pch.h"
#include "../Math/Rect2f.h"
#include "../Core/ResourceManager.h"

Button::Button()
{
	mp_callback = NULL;
	mbDown = false;
	mpDownSprite = NULL;
}

Button::~Button()
{
	if(NULL != mpDownSprite)
	{
		delete mpDownSprite;
	}
}

void Button::SetCallback( void (*callback)() )
{
	mp_callback=callback;
}

bool Button::Input( SDL_Event &rSDL_Event )
{
	if((SDL_MOUSEBUTTONDOWN == rSDL_Event.type))
	{
		Math::Rect2f rect;
		rect.x = ResourceManager::Instance().ScaleTextureWidth(m_position.x);
		rect.y = ResourceManager::Instance().ScaleTextureHeight(m_position.y);
		rect.w = ResourceManager::Instance().ScaleTextureWidth(mpSprite->GetWidth());
		rect.h = ResourceManager::Instance().ScaleTextureHeight(mpSprite->GetHeight());

		int px = rSDL_Event.motion.x;
		int py = rSDL_Event.motion.y;
		if(rect.Intersect(px,py))
		{
			mbDown = true;
		}
	}

	if((SDL_MOUSEBUTTONUP == rSDL_Event.type))
	{
		mbDown = false;
		Math::Rect2f rect;
		rect.x = ResourceManager::Instance().ScaleTextureWidth(m_position.x);
		rect.y = ResourceManager::Instance().ScaleTextureHeight(m_position.y);
		rect.w = ResourceManager::Instance().ScaleTextureWidth(mpSprite->GetWidth());
		rect.h = ResourceManager::Instance().ScaleTextureHeight(mpSprite->GetHeight());

		int px = rSDL_Event.motion.x;
		int py = rSDL_Event.motion.y;
		if(rect.Intersect(px,py))
		{
			if(NULL != mp_callback)
			{
				mp_callback();
			}
			return true;
		}
	}
	return false;
		
}

void Button::SetDownSprite( std::string path )
{
	if(NULL == mpDownSprite)
	{
		mpDownSprite = new Sprite();
		mpDownSprite->LoadTexture(path);
	}
	
}

void Button::Render() const
{
	if(mb_IsVisible)
	{
		if( (NULL != mpDownSprite) && (mbDown) )
		{
			mpDownSprite->Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y));
		}
		else
		{
			mpSprite->Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y));
		}
		
	}
}
