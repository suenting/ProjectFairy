#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "../pch.h"

class FontManager
{
public:
	static FontManager& Instance()
	{
		static FontManager instance;
		return instance;
	}
	~FontManager();
	SDL_Surface* GetSurface(TTF_Font *font,std::string text, SDL_Color color);
	TTF_Font* GetFont(std::string name)const;
private:
	FontManager();
	FontManager( const FontManager& other ){};
	FontManager& operator=( const FontManager& rhs ){};
	std::map<std::string,TTF_Font*> mFontData;
};

#endif