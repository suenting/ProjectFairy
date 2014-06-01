#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "../pch.h"
#include "Sprite.h"
typedef std::map<char, Sprite*> GlyphMap;

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
	void InitGlyphTable();
	void RenderText(std::string name, std::string text, int x, int y);
private:
	FontManager();
	FontManager( const FontManager& other ){};
	FontManager& operator=( const FontManager& rhs ){};
	void LoadGlyphTable(std::string name, SDL_Color color);
	GlyphMap GetGlyph(std::string name){return mGlyphTable[name];}
	std::map<std::string,TTF_Font*> mFontData;
	std::map<std::string, GlyphMap> mGlyphTable;
};

#endif