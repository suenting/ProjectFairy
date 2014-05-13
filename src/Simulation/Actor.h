#ifndef ACTOR_H
#define ACTOR_H

#include "ActorData.h"
#include "Effect.h"
#include "../pch.h"
#include "../Math/Circle2f.h"
#include "Projectile.h"

class Actor
{
public:
	Actor(ActorData* pData);
	~Actor();

	void Init();
	void Render()const;
	void Update();

	void AddEffect(std::string name);
	void ClearEffects();

	Math::Circle GetHitCircle()const;
	Math::Vector2f GetPosition() const { return mPosition; };
	void SetPosition(Math::Vector2f val) { mPosition = val; };
	Math::Vector2f GetNextPosition() const { return mNextPosition; }
	void SetNextPosition(Math::Vector2f val) { mNextPosition = val; }

	void TakeHit(Projectile* pProjectile);
	float GetHealth() const { return mHealth; };
	void SetHealth(float val);
	float GetHealthState() const { return mHealthState; }
	void SetHealthState(float val) { mHealthState = val; }
	int GetState() const { return mState; };
	void SetState(int val) { mState = val; };
	int GetTick()const{return mTick;}
	bool GetIsDead() const { return mbIsDead; }
	void kill();
	void SetEffectTint(Uint8 r, Uint8 g, Uint8 b);
protected:
private:
	ActorData* mpActorData;
	Math::Vector2f mPosition;
	Math::Vector2f mNextPosition;

	float mHealth;
	float mHealthState;
	int mState;

	// tick used for sequence timing
	int mTick;

	// effects which follow actor (spell circles)
	std::vector<Effect*> mEffectList;
	bool mbIsDead;

	void UpdatePosition();
};

#endif