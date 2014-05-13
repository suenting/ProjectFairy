#include "ActorData.h"

ActorData::ActorData(std::string name)
{
	mName = name;
	mpSprite = new Sprite(mName+".png");
	mp_update=NULL;
	mp_init=NULL;
	SetRadius(mpSprite->GetWidth()/2.f);
	maxHealth=100;
}

ActorData::~ActorData()
{
	delete mpSprite;
}

void ActorData::Render( Math::Vector2f pos ) const
{
	mpSprite->RenderCenter(static_cast<int>(pos.x),static_cast<int>(pos.y));
}

void ActorData::Update( Actor *pActor )
{
	if(NULL != mp_update)
	{
		mp_update(pActor);
	}
}

void ActorData::Init( Actor *pActor )
{
	if(NULL != mp_init)
	{
		mp_init(pActor);
	}
}

