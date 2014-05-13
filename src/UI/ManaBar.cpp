#include "ManaBar.h"
#include "../pch.h"
#include "../Simulation/Game.h"

ManaBar::ManaBar()
{
	mpFrame = new Sprite();
	mpSprite = new Sprite();
	mpFrame->LoadTexture("manaBarFrame.png");
	mpSprite->LoadTexture("manaBar.png");
}

ManaBar::~ManaBar()
{
	delete mpFrame;
	delete mpSprite;
}

void ManaBar::Render()const
{
	if(mb_IsVisible)
	{
		
		mpSprite->Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y));
		mpFrame->Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y));
	}
}

void ManaBar::Update()
{
	float manaPercent = Game::Instance().GetHealthPercentage();
	mpSprite->SetCutRight(manaPercent);
}

