#include "EffectData.h"



EffectData::EffectData(std::string name, EffectType type, float rate)
{
	mName = name;
	mEffectType = type;
	mEffectRate = rate;
	mTimeToLive = 0;
	mbCentered = false;
	mpSprite = NULL;
	mpAnimatedSprite = NULL;
}

EffectData::~EffectData()
{
	if(NULL != mpSprite)
	{
		delete mpSprite;
	}
	if(NULL != mpAnimatedSprite)
	{
		delete mpAnimatedSprite;
	}
}

void EffectData::Render( Math::Vector2f position, float rotation, int frame) const
{
	if(NULL != mpSprite)
	{
		if(mbCentered)
		{
			mpSprite->RenderCenter(static_cast<int>(position.x),static_cast<int>(position.y),rotation);
		}
		else
		{
			mpSprite->Render(static_cast<int>(position.x),static_cast<int>(position.y),rotation);
		}
	}
	if(NULL != mpAnimatedSprite)
	{
		if(mbCentered)
		{
			mpAnimatedSprite->RenderCentered(static_cast<int>(position.x),static_cast<int>(position.y),frame);
		}
		else
		{
			mpAnimatedSprite->Render(static_cast<int>(position.x),static_cast<int>(position.y),frame);
		}
	}
}

void EffectData::SetTimeToLive( int ttl )
{
	mTimeToLive = ttl;
}

void EffectData::SetTint( Uint8 r, Uint8 g, Uint8 b ) const
{
	if(NULL != mpSprite)
	{
		mpSprite->SetTint(r,g,b);
	}
}

void EffectData::ClearTint() const
{
	if(NULL != mpSprite)
	{
		mpSprite->ClearTint();
	}
}

void EffectData::SetSpriteScale( float scale )
{
	if(NULL != mpSprite)
	{
		mpSprite->SetScale(scale);
	}
}

void EffectData::LoadSprite( std::string name )
{
	mpSprite = new Sprite(name+".png");
}

void EffectData::LoadAnimatedSprite( std::string name, int start, int finish )
{
	mpAnimatedSprite = new AnimatedSprite();
	mpAnimatedSprite->LoadSprite(name,start,finish);
}


