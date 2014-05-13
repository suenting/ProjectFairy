#include "PlayerHealth.h"
#include "..\Core\FontManager.h"
#include "..\Simulation\Game.h"

PlayerHealth::PlayerHealth()
{
	SDL_Color white = {255,255,255};
	char buf[3];
	for(int it = 0; it<33;++it)
	{
		Sprite *pSprite = new Sprite();
		sprintf(buf,"%d",it);
		pSprite->LoadText(FontManager::Instance().GetFont("airstrike"), std::string(buf), white);
		mSpriteList.push_back(pSprite);
	}
}

PlayerHealth::~PlayerHealth()
{
	for(std::vector<Sprite*>::iterator it = mSpriteList.begin(); it != mSpriteList.end(); ++it)
	{
		delete *it;
	}
	mSpriteList.clear();
}

void PlayerHealth::Render() const
{
	int playerHp = Game::Instance().GetPlayerHealth();

	mSpriteList[playerHp]->Render(GetPosition().x,GetPosition().y);
}
