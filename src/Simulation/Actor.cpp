#include "ModContentManager.h"
#include "Actor.h"
#include "..\Core\AudioManager.h"
#include "Game.h"

Actor::Actor(ActorData* pData)
{
	mpActorData = pData;
	mState = 0;
	mHealth = 100;
	mTick = 0;
	mHealthState = 100;
	mbIsDead = false;
}

Actor::~Actor()
{
	ClearEffects();
}

void Actor::Init()
{
	SetHealth(mpActorData->GetMaxHealth());
	mpActorData->Init(this);
}

void Actor::Render() const
{
	// render actor effects
	for(std::vector<Effect*>::const_iterator it = mEffectList.begin(); it != mEffectList.end();++it)
	{
		(*it)->Render(mPosition);
	}

	mpActorData->Render(mPosition);
}

void Actor::Update()
{
	++mTick;
	// update effects
	for(std::vector<Effect*>::iterator it = mEffectList.begin(); it != mEffectList.end();++it)
	{
		(*it)->Update();
	}
	// update actor
	mpActorData->Update(this);

	//
	UpdatePosition();
}

void Actor::ClearEffects()
{
	for(std::vector<Effect*>::iterator it = mEffectList.begin(); it != mEffectList.end();++it)
	{
		delete (*it);
	}
	mEffectList.clear();
}

void Actor::AddEffect( std::string name )
{
	Effect *pEffect = ModContentManager::Instance().SpawnEffect(name);
	mEffectList.push_back(pEffect);
}

Math::Circle Actor::GetHitCircle() const
{
	Math::Circle c;
	c.SetPos(mPosition);
	c.SetRad(mpActorData->GetRadius());
	return c;
}

void Actor::TakeHit( Projectile* pProjectile )
{
	SetHealth(GetHealth()-pProjectile->GetData()->GetDamage());
}

void Actor::SetHealth( float val )
{
	mHealth = val;
	if(mHealth<0.f)
	{
		mHealth = 0.f;
	}
}

void Actor::UpdatePosition()
{
	float dist = sqrt(mPosition.SquaredDistance(mNextPosition));
	if(dist<2.f)
	{
		SetPosition(GetNextPosition());
		return;
	}
	Math::Vector2f dirVector = mNextPosition-mPosition;
	dirVector = dirVector.NormalizeSelf()*2.f;
	SetPosition(GetPosition()+dirVector);
}

void Actor::SetEffectTint( Uint8 r, Uint8 g, Uint8 b )
{
	for(std::vector<Effect*>::iterator it = mEffectList.begin(); it != mEffectList.end();++it)
	{
		(*it)->SetTint(r,g,b);
	}
}

void Actor::kill()
{
	mbIsDead = true;
	AudioManager::Instance().PlaySFX("scifi_explosion-001.ogg");

	Effect * pExplosion = ModContentManager::Instance().SpawnEffect("explosion");
	pExplosion->SetPosition(mPosition);
	Game::Instance().QueueEffect(pExplosion);
}

