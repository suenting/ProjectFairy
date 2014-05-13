#include "Label.h"
#include "../pch.h"

Label::Label()
{
	mpSprite = NULL;
}

Label::~Label()
{
	if(NULL != mpSprite)
	{
		delete mpSprite;
		mpSprite = NULL;
	}
}

void Label::Render() const
{
	if(mb_IsVisible)
	{
		mpSprite->Render(static_cast<int>(m_position.x), static_cast<int>(m_position.y));
	}
}

void Label::SetText( TTF_Font *font,std::string text, SDL_Color color )
{
	mpSprite = new Sprite();
	mpSprite->LoadText(font, text, color);
}

void Label::SetImage( std::string path )
{
	mpSprite = new Sprite();
	mpSprite->LoadTexture(path);
}

