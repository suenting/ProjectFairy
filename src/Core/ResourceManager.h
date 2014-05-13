#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../pch.h"

class ResourceManager
{
public:
	static ResourceManager& Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	~ResourceManager();
	SDL_Window* GetWindow()const{return m_window;}
	SDL_Renderer* GetRenderer()const{return m_renderer;}

	// scale from texture to screen
	int ScaleTextureWidth(int width)const;
	int ScaleTextureHeight(int height)const;

	// scale from screen to texture
	int SourceTextureWidth(int width)const;
	int SourceTextureHeight(int height)const;

	int GetWindowWidth()const{return m_window_width;}
	int GetWindowHeight()const{return m_window_height;}

private:
	ResourceManager();
	ResourceManager( const ResourceManager& other ){};
	ResourceManager& operator=( const ResourceManager& rhs ){};


	// SDL Resource
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	int m_window_width;
	int m_window_height;
};

#endif