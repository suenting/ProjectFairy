#include "Effect.h"

Effect::Effect(EffectData* pData)
{
	mpData = pData;
	mFrame = 0;
	mScale = 1.f;
	mTintRed = 255;
	mTintGreen = 255;
	mTintBlue = 255;
	mTick = 0;
}

Effect::~Effect()
{

}

void Effect::Render() const
{
	Render(mPosition);
}

void Effect::Render( Math::Vector2f position )const
{
	mpData->SetTint(mTintRed,mTintGreen,mTintBlue);
	if(mScale != 1.f){mpData->SetSpriteScale(mScale);}

	if(EFT_Rotate == mpData->GetEffectType())
	{
		mpData->Render(position,mFrame);
	}
	else if(EFT_Animate == mpData->GetEffectType())
	{
		mpData->Render(position,0,static_cast<int>(mFrame));
	}
	else
	{
		mpData->Render(position);
	}
	

	if(mScale != 1.f){mpData->SetSpriteScale(1.f);}
	mpData->ClearTint();
}

void Effect::Update()
{
	++mTick;
	mFrame = mFrame + mpData->GetEffectRate();
}

void Effect::SetTint( Uint8 r, Uint8 g, Uint8 b )
{
	mTintRed = r;
	mTintGreen = g;
	mTintBlue = b;
}

int Effect::GetTimeToLive() const
{
	return mpData->GetTimeToLive();
}

