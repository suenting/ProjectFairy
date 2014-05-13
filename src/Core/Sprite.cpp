#include "Sprite.h"
#include "ResourceManager.h"
#include "FontManager.h"

Sprite::Sprite( std::string path )
{
	LoadTexture(path);
	mScale = 1.f;
	mCutRight = 1.f;
}

Sprite::Sprite()
{
	mpTexture=NULL;
	mScale = 1.f;
	mCutRight = 1.f;
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(mpTexture);
}

void Sprite::Render( int x, int y, double angle, SDL_Point* center) const
{
	int scaled_x = ResourceManager::Instance().ScaleTextureWidth(x);
	int scaled_y = ResourceManager::Instance().ScaleTextureHeight(y);
	SDL_Rect target_rect = {scaled_x,scaled_y,ResourceManager::Instance().ScaleTextureWidth(mWidth*mScale),ResourceManager::Instance().ScaleTextureHeight(mHeight*mScale)};
	SDL_Rect source_rect = {0,0,mWidth,mHeight};

	if(mCutRight<1.f)
	{
		source_rect.w = source_rect.w * mCutRight;
		target_rect.w = target_rect.w * mCutRight;
	}

	// handle edge case for android
	int windowWidth=ResourceManager::Instance().GetWindowWidth();
	int windowHeight=ResourceManager::Instance().GetWindowHeight();
	if(0>scaled_x)
	{
		int overlapp = ResourceManager::Instance().SourceTextureWidth(scaled_x);
		source_rect.x=abs(overlapp);
		source_rect.w=source_rect.w+overlapp;
		target_rect.x = 0;
		target_rect.w = target_rect.w+scaled_x;
	}
	else if (windowWidth<(scaled_x+target_rect.w))
	{
		int overlapp = ResourceManager::Instance().SourceTextureWidth(scaled_x+target_rect.w-windowWidth);
		source_rect.w = source_rect.w-overlapp;
		target_rect.w = target_rect.w+(windowWidth-(scaled_x+target_rect.w));
	}
	if(0>scaled_y)
	{
		int overlapp = ResourceManager::Instance().SourceTextureWidth(scaled_y);
		source_rect.y=abs(overlapp);
		source_rect.h=source_rect.h+overlapp;
		target_rect.y = 0;
		target_rect.h = target_rect.h+scaled_y;
	}
	else if (windowHeight<(scaled_y+target_rect.h))
	{
		int overlapp = ResourceManager::Instance().SourceTextureWidth(scaled_y+target_rect.h-windowHeight);
		source_rect.h = source_rect.h-overlapp;
		target_rect.h = target_rect.h+(windowHeight-(scaled_y+target_rect.h));
	}

	// render
	if(0 == angle)
	{
		SDL_RenderCopy(ResourceManager::Instance().GetRenderer(), mpTexture, &source_rect, &target_rect);
	}
	else
	{
		SDL_RenderCopyEx(ResourceManager::Instance().GetRenderer(), mpTexture, &source_rect, &target_rect, angle, center, SDL_FLIP_NONE);
	}
}

void Sprite::LoadTexture( std::string path )
{
#ifdef WIN32
	SDL_Surface* surface = IMG_Load(("assets\\"+path).c_str());
#endif
#ifdef __ANDROID__
	SDL_Surface* surface = IMG_Load(path.c_str());
#endif

	mpTexture = SDL_CreateTextureFromSurface(ResourceManager::Instance().GetRenderer(), surface);
	mWidth = surface->w;
	mHeight = surface->h;
	SDL_FreeSurface(surface);
}

void Sprite::LoadText( TTF_Font *font,std::string text, SDL_Color color )
{
	SDL_Surface* surface = FontManager::Instance().GetSurface(font,text,color);
	mpTexture = SDL_CreateTextureFromSurface(ResourceManager::Instance().GetRenderer(), surface);
	mWidth = surface->w;
	mHeight = surface->h;
	SDL_FreeSurface(surface);
}

void Sprite::RenderTint( int x, int y, Uint8 r, Uint8 g, Uint8 b ) const
{
	SetTint(r,g,b);
	Render(x,y);
	ClearTint();
}

void Sprite::RenderCenter( int x, int y, double angle) const
{
	int nx = x-mWidth*mScale/2;
	int ny = y-mHeight*mScale/2;
	if(0==angle)
	{
		Render(nx,ny);
	}
	else
	{
		Render(nx,ny,angle,NULL);
	}
}

void Sprite::SetTint( Uint8 r, Uint8 g, Uint8 b )const
{
	SDL_SetTextureColorMod(mpTexture,r,g,b);
}

void Sprite::ClearTint()const
{
	SDL_SetTextureColorMod(mpTexture,255,255,255);
}
