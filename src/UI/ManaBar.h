#ifndef MANABAR_H
#define MANABAR_H

#include "Widget.h"
#include "../pch.h"
#include "../Core/Sprite.h"

class ManaBar: public Widget
{
	public:
		ManaBar();
		virtual ~ManaBar();
		virtual void Render()const;
		virtual void Update();
		
	protected:
		Sprite* mpFrame;
		Sprite* mpSprite;
};

#endif