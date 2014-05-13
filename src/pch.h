#ifndef PCH_H
#define PCH_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <algorithm>

#ifdef WIN32
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <windows.h>
#include <tchar.h>
#endif

#ifdef __ANDROID__
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#endif


#endif