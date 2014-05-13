#ifndef PLAYERHEALTH_H
#define PLAYERHEALTH_H

#include "Widget.h"
#include "..\Core\Sprite.h"
#include "..\pch.h"

class PlayerHealth : public Widget
{
public:
	PlayerHealth();
	virtual ~PlayerHealth();
	virtual void Render()const;
protected:
private:
	// mutable hack
	mutable std::vector<Sprite*> mSpriteList;
};

#endif