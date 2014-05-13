#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include "../pch.h"

class AnimatedSprite
{
public:
	AnimatedSprite();
	~AnimatedSprite();
	void LoadSprite(std::string name, size_t start, size_t finish);
	void Render(int x, int y, int frame=-1)const;
	void RenderCentered(int x, int y, int frame=-1)const;
	void Tick();
protected:

private:
	std::vector<Sprite*> mFrames;
	size_t mAnimationFrame;
};

#endif//ANIMATEDSPRITE_H