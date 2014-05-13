#include "ThumbStick.h"
#include "..\Core\ResourceManager.h"
#include "..\Core\InputManager.h"

namespace
{
	static bool bMouseDown = false;
}

ThumbStick::ThumbStick(Math::Vector2f center)
{
	mCenter = center;
	mpBaseSprite = new Sprite();
	mpBaseSprite->LoadTexture("thumb_base.png");
	mpTopSprite = new Sprite();
	mpTopSprite->LoadTexture("thumb_top.png");
	mPosition.x = 0.f;
	mPosition.y = 0.f;

	Math::Vector2f scaledPos;
	mBaseCircle.SetPos(center);
	mBaseCircle.SetRad(84.f);// 64.f + extra le way

	
}

ThumbStick::~ThumbStick()
{
	delete mpBaseSprite;
	delete mpTopSprite;
}

void ThumbStick::Render() const
{
	mpBaseSprite->RenderCenter(static_cast<int>(mCenter.x),static_cast<int>(mCenter.y));
	Math::Vector2f topPos = mCenter + mPosition;
	mpTopSprite->RenderCenter(static_cast<int>(topPos.x),static_cast<int>(topPos.y));
}

void ThumbStick::Update()
{
	InputManager::Instance().UpdateScreenDirection(mPosition);
}

bool ThumbStick::Input( SDL_Event &rSDL_Event )
{
	if((SDL_MOUSEBUTTONDOWN == rSDL_Event.type))
	{
		bMouseDown = true;
		UpdateThumbPosition(rSDL_Event);
	}
	if((SDL_MOUSEMOTION == rSDL_Event.type))
	{
		if(bMouseDown)
		{
			UpdateThumbPosition(rSDL_Event);
		}
	}
	if((SDL_MOUSEBUTTONUP == rSDL_Event.type))
	{
		mPosition.x = 0;
		mPosition.y = 0;
		bMouseDown = false;
	}

	return false;
}

void ThumbStick::UpdateThumbPosition( SDL_Event &rSDL_Event )
{
	int px = ResourceManager::Instance().SourceTextureWidth(rSDL_Event.motion.x);
	int py = ResourceManager::Instance().SourceTextureHeight(rSDL_Event.motion.y);

	Math::Vector2f fingerPos(px,py);
	if(mBaseCircle.Collide(fingerPos))
	{
		mPosition.x =  px - mCenter.x;
		mPosition.y =  py - mCenter.y;
	}
	else
	{
		mPosition.x = 0;
		mPosition.y = 0;
	}
}

