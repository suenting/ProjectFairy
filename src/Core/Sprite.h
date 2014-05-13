#ifndef SPRITE_H
#define SPRITE_H
#include "../pch.h"

typedef SDL_Texture Texture;

class Sprite
{
public:
	Sprite();
	Sprite(std::string path);
	~Sprite();
	void Render(int x, int y, double angle = 0, SDL_Point* center = NULL)const;
	
	void RenderTint(int x, int y, Uint8 r, Uint8 g, Uint8 b)const;
	void SetTint(Uint8 r, Uint8 g, Uint8 b)const;
	void ClearTint()const;

	void LoadTexture(std::string path);
	void LoadText(TTF_Font *font,std::string text, SDL_Color color);
	void RenderCenter(int x, int y, double angle = 0)const;

	int GetWidth()const{return mWidth;}
	int GetHeight()const{return mHeight;}
	void SetScale(float scale){mScale = scale;}
	void SetCutRight(float val) { mCutRight = val; }


private:
	Texture *mpTexture;  
	int mWidth;
	int mHeight;
	float mScale;
	float mCutRight;
	
};

#endif