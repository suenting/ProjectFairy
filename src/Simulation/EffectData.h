#ifndef EFFECTDATA_H
#define EFFECTDATA_H
#include "../core/Sprite.h"
#include "../pch.h"
#include "../Math/Vector2f.h"
#include "../Core/AnimatedSprite.h"

enum EffectType
{
	EFT_Rotate,
	EFT_Animate,
	EFT_Move
};
class EffectData
{
public:
	EffectData(std::string name, EffectType type, float rate=0.f);
	~EffectData();
	void Render(Math::Vector2f position, float rotation=0.f, int frame=0)const;
	void SetTimeToLive(int ttl);
	EffectType GetEffectType() const { return mEffectType; }
	float GetEffectRate() const { return mEffectRate; }
	void SetCenter(bool bCenter){mbCentered = bCenter;}

	void SetTint(Uint8 r, Uint8 g, Uint8 b)const;
	void ClearTint()const;

	void LoadSprite(std::string name);
	void LoadAnimatedSprite(std::string name, int start, int finish);

	// 
	void SetSpriteScale(float scale);
	int GetTimeToLive()const{return mTimeToLive;}
protected:
private:
	std::string mName;
	Sprite *mpSprite;
	AnimatedSprite *mpAnimatedSprite;
	float mEffectRate;
	
	EffectType mEffectType;
	int mTimeToLive;
	bool mbCentered;
};

#endif