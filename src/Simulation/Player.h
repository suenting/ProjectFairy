#ifndef PLAYER_H
#define PLAYER_H

#include "../Core/Sprite.h"
#include "../Math/Vector2f.h"
#include "ProjectileData.h"
#include "../Math/Circle2f.h"

class Player
{
public:
	Player();
	~Player();
	void Render()const;
	void Update();
	Math::Circle GetHitCircle()const;
	void TakeHit(Projectile* pProjectile);
	float GetHealth() const { return mHealth; }
	void SetHealth(float val) { mHealth = val; }
	void Init();
protected:
private:
	Sprite* mpSprite;
	Math::Vector2f mPosition;

	float mSpeed;
	float mHealth;

};

#endif