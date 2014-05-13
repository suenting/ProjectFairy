#include "ResourceManager.h"

#define HD

namespace
{
	// FHD
	//static int TARGET_WIDTH=1920;
	//static int TARGET_HEIGHT=1080;
	// HD
	//static int TARGET_WIDTH=1280;
	//static int TARGET_HEIGHT=720;
	// qHD
	static int TARGET_WIDTH=960;
	static int TARGET_HEIGHT=540;
}


ResourceManager::ResourceManager()
{
	SDL_Init(SDL_INIT_EVERYTHING);
#ifdef qHD
	m_window = SDL_CreateWindow("Project Fairy", 1920,50,960,540,0);
#elif defined(HD)
	m_window = SDL_CreateWindow("Project Fairy", 50,50,1280,720,0);
#elif defined(FHD)
	m_window = SDL_CreateWindow("Project Fairy", 1920,0,1920,1080,SDL_WINDOW_BORDERLESS);
#endif
	//m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_SOFTWARE);

	// required for texture rotation
	m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetWindowSize(m_window,&m_window_width,&m_window_height);

}

ResourceManager::~ResourceManager()
{
	SDL_DestroyWindow(m_window);
}

int ResourceManager::ScaleTextureWidth(int width) const
{
	float percentage = static_cast<float>(m_window_width)/static_cast<float>(TARGET_WIDTH);
	return static_cast<int>(width*percentage);
}

int ResourceManager::ScaleTextureHeight(int height) const
{
	float percentage = static_cast<float>(m_window_height)/static_cast<float>(TARGET_HEIGHT);
	return static_cast<int>(height*percentage);
}

int ResourceManager::SourceTextureWidth( int width ) const
{
	float percentage = static_cast<float>(TARGET_WIDTH)/static_cast<float>(m_window_width);
	return static_cast<int>(width*percentage);
}

int ResourceManager::SourceTextureHeight( int height ) const
{
	float percentage = static_cast<float>(TARGET_HEIGHT)/static_cast<float>(m_window_height);
	return static_cast<int>(height*percentage);
}
