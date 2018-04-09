#ifndef GLOBAL_fUNCTION_
#define GLOBAL_fUNCTION_

#include <stdio.h>
#include <stddef.h>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

/// Screen dimension constants

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 422;
const int SCREEN_BPP = 32;

/// global variable

static SDL_Surface* g_screen = NULL;
static SDL_Window* g_window = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_event;

namespace SDL_commonFunc
{
    SDL_Surface* Load_Image(std::string file_path);
    void applySurface(SDL_Surface* screen, SDL_Surface* des, int x, int y);
    void CleanUp();
}

#endif
