#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
	mAnimationFrame = 0;
}

AnimatedSprite::~AnimatedSprite()
{
	for(std::vector<Sprite*>::iterator it = mFrames.begin(), et = mFrames.end(); it != et;++it)
	{
		delete *it;
	}
	mFrames.clear();
}

void AnimatedSprite::LoadSprite( std::string name, size_t start, size_t finish )
{
	for(size_t it = start; it<finish;++it)
	{
		char buffer [128];
		sprintf(buffer,name.c_str(),it);
		Sprite* pSprite = new Sprite(std::string(buffer));
		mFrames.push_back(pSprite);
	}
}

void AnimatedSprite::Render(int x, int y, int frame) const
{
	int f = mAnimationFrame%mFrames.size();
	if(-1 != frame)
	{
		f=frame;
	}
	if(f>=mFrames.size()){f=mFrames.size()-1;}
	mFrames[f]->Render(x,y);
}

void AnimatedSprite::Tick()
{
	++mAnimationFrame;
}

void AnimatedSprite::RenderCentered( int x, int y, int frame ) const
{
	int f = mAnimationFrame%mFrames.size();
	if(-1 != frame)
	{
		f=frame;
	}
	if(f>=mFrames.size()){f=mFrames.size()-1;}
	mFrames[f]->RenderCenter(x,y);
}
