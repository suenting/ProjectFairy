#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"
#include "../pch.h"
#include "../Core/Sprite.h"

class Label : public Widget
{
public:
	Label();
	virtual ~Label();
	virtual void Render()const;
	void SetText(TTF_Font *font,std::string text, SDL_Color color);
	void SetImage(std::string path);
	int GetHeight()const{return mpSprite->GetHeight();}
	int GetWidth()const{return mpSprite->GetWidth();}
protected:
	Sprite * mpSprite;
};

#endif