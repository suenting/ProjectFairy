#ifndef EFFECT_H
#define EFFECT_H

#include "..\Math\Vector2f.h"
#include "EffectData.h"

class Effect
{
public:
	Effect(EffectData *pData);
	~Effect();
	void Update();
	void Render()const;
	void Render(Math::Vector2f position)const; // if effect is not owned by world
	void SetScale(float scale){mScale = scale;}

	void SetTint(Uint8 r, Uint8 g, Uint8 b);
	int GetTick()const{return mTick;}
	int GetTimeToLive()const;
	void SetPosition(Math::Vector2f val){mPosition = val;}
protected:
private:
	EffectData *mpData;
	Math::Vector2f mPosition;
	float mFrame; // used for rotation
	int mTick;
	float mScale;

	Uint8 mTintRed;
	Uint8 mTintGreen;
	Uint8 mTintBlue;
};

#endif