#include "FontManager.h"

namespace
{
	static TTF_Font * LoadFont(std::string path, int size)
	{
#ifdef WIN32
		return TTF_OpenFont(("assets\\"+path+".ttf").c_str(),size);
#endif
#ifdef __ANDROID__
		return TTF_OpenFont((path+".png").c_str(),size);
#endif
	}
}

FontManager::~FontManager()
{
	for(std::map<std::string,TTF_Font*>::iterator it = mFontData.begin(); it != mFontData.end();++it)
	{
		TTF_CloseFont(it->second);
	}
}

FontManager::FontManager()
{
	TTF_Init();
	TTF_Font *pSketchRockwell = LoadFont("Sketch",56);
	TTF_Font *pScriptFont = LoadFont("script",96);
	TTF_Font *pAirStrike = LoadFont("airstrike",56);
	mFontData.insert(std::pair<std::string,TTF_Font*>("Sketch",pSketchRockwell));
	mFontData.insert(std::pair<std::string,TTF_Font*>("script",pScriptFont));
	mFontData.insert(std::pair<std::string,TTF_Font*>("airstrike",pAirStrike));
}


SDL_Surface* FontManager::GetSurface( TTF_Font *font,std::string text, SDL_Color color )
{
	SDL_Surface * pSurface = TTF_RenderText_Solid( font, text.c_str(),color);
	return pSurface;
}

TTF_Font* FontManager::GetFont( std::string name ) const
{
	std::map<std::string,TTF_Font*>::const_iterator iter = mFontData.find(name);
	if(iter != mFontData.end())
	{
		return iter->second;
	}
	return NULL;
}

void FontManager::LoadGlyphTable( std::string name, SDL_Color color )
{
	TTF_Font* pFont = GetFont(name);
	char buffer [4];
	for(int iter = 32; iter<123;++iter)
	{
		char a = static_cast<char>(iter);
		sprintf(buffer,"%c",iter);
		Sprite* pSprite = new Sprite();
		pSprite->LoadText(pFont, std::string(buffer),color);
		mGlyphTable[name][a]=pSprite;
	}
}

void FontManager::RenderText( std::string name, std::string text, int x, int y )
{
	int posX = x;
	for(int it = 0; it<text.length();++it)
	{
		char c = text[it];
		mGlyphTable[name][c]->Render(posX,y);
		posX += mGlyphTable[name][c]->GetWidth();
	}
}

void FontManager::InitGlyphTable()
{
	SDL_Color white = {255,255,255};
	LoadGlyphTable("airstrike",white);
}


