#include "Projectile.h"
#include "ModContentManager.h"
#include "Game.h"

Projectile::Projectile( ProjectileData * pData )
{
mpData = pData;
mPos = Math::Vector2f(0.f,0.f);
mVector = Math::Vector2f(0.f,0.f);
mbIsDead = false;
mTicks = 0;
mAngle = 0;
SetOwner(PO_Enemy);
}

Projectile::~Projectile()
{

}

void Projectile::Render() const
{
	mpData->Render(mPos,mAngle);
}

void Projectile::Update()
{
	++mTicks;
	if( (mPos.x <0) || 
		(mPos.x>960)||
		(mPos.y<0)||
		(mPos.y>540))
	{
		mbIsDead = true;
	}
	

	switch(mpData->GetType())
	{
	case PT_Vector:
	case PT_VectorGrenade:
		mPos = mPos + mVector*mpData->GetSpeed();
		break;
	case PT_Custom:
		break;
	}

	if(PT_VectorGrenade == mpData->GetType())
	{
		if(mTicks>mpData->GetFuse())
		{
			mbIsDead=true;
			for(int it = 0; it<8;++it)
			{
				Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile(mpData->GetShrapnelName());
				Math::Vector2f refPosition = mPos;
				int vec = 0+45*it;
				refPosition += Math::Vector2f::GetVectorFromDeg(vec)*mpData->GetRadius();
				pProjectile->SetPosition(refPosition);
				pProjectile->SetVector(vec);
				pProjectile->SetOwner(GetOwner());
				if(PO_Enemy==GetOwner())
				{
					Game::Instance().QueueProjectile(pProjectile);
				}
				else if(PO_Player==GetOwner())
				{
					Game::Instance().QueueProjectile(pProjectile);
				}
			}
		}
	}

}

Math::Circle Projectile::GetHitCircle() const
{
	Math::Circle c;
	c.SetPos(mPos);
	c.SetRad(mpData->GetRadius());
	return c;
}

void Projectile::SetVector( float deg )
{
	mVector = Math::Vector2f::GetVectorFromDeg(deg);
	mAngle = deg*-1;

}

