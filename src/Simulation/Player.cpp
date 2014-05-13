#include "Player.h"
#include "..\Core\InputManager.h"
#include "ModContentManager.h"
#include "Game.h"
#include "..\Core\ResourceManager.h"

namespace
{
	static const int rateOfFire = 3;
	static int ticks;
}
Player::Player()
{
	mpSprite=new Sprite("bot.png");
	Init();

}

Player::~Player()
{
	delete mpSprite;
}

void Player::Render() const
{
	mpSprite->RenderCenter(static_cast<int>(mPosition.x),static_cast<int>(mPosition.y));
}

void Player::Update()
{
	mPosition += InputManager::Instance().GetDirection()*mSpeed;
	if(mPosition.x<0){mPosition.x = 0;}
	if(mPosition.y<0){mPosition.y = 0;}
	if(mPosition.x>960){mPosition.x = 960;}
	if(mPosition.y>540){mPosition.y = 540;}

	// shoot
	++ticks;
	if(0==(ticks%rateOfFire))
	{
		Projectile *pProjectile = ModContentManager::Instance().SpawnProjectile("player_bullet");
		Math::Vector2f refPosition = mPosition;
		refPosition.x += 32;
		pProjectile->SetPosition(refPosition);
		pProjectile->SetVector(Math::Vector2f(1.f,0.f));
		pProjectile->SetOwner(PO_Player);
		Game::Instance().AddPlayerProjectile(pProjectile);
	}
}

Math::Circle Player::GetHitCircle() const
{
	Math::Circle c;
	c.SetPos(mPosition);
	c.SetRad(static_cast<float>(ResourceManager::Instance().ScaleTextureWidth(16)));
	return c;
}

void Player::TakeHit( Projectile* pProjectile )
{
	SetHealth(GetHealth()-pProjectile->GetData()->GetDamage());
}

void Player::Init()
{
	mPosition.x = 50;
	mPosition.y = 100;
	mHealth = 32;
	mSpeed = 5.f;
	ticks = 0;
}

