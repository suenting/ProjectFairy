#include "ProjectileData.h"

ProjectileData::ProjectileData(std::string name)
{
	mName = name;
	mpSprite = new Sprite(mName+".png");
}

ProjectileData::~ProjectileData()
{
	delete mpSprite;
}

void ProjectileData::Render( Math::Vector2f pos, float angle ) const
{
	mpSprite->RenderCenter(static_cast<int>(pos.x),static_cast<int>(pos.y),angle);
}

void ProjectileData::Update( Projectile *pProjectile )
{

}

