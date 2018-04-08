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

SDL_Surface* g_screen = NULL;
SDL_Window* g_window = NULL;
SDL_Surface* g_bkground = NULL;
SDL_Event g_event;
SDL_Surface* g_opject = NULL;
/// Init function

bool Init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! error: %s", SDL_GetError());
        success = false;
    }
    else{
        g_window = SDL_CreateWindow( "Game - UET", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if(g_window==NULL)
        {
            printf("window could not create! error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            g_screen = SDL_GetWindowSurface( g_window );
        }
    }
    return success;
}
/// LOAD IMAGE FUNCION

SDL_Surface* Load_Image(std::string file_path)
{
    SDL_Surface* load_image = IMG_Load(file_path.c_str());
    SDL_Surface* optimize_image = NULL;

    if(load_image==NULL)
    {
        printf("image: %s could not load, error is: %s", file_path.c_str(),SDL_GetError());

    }
    else{
        optimize_image = SDL_ConvertSurface(load_image, g_screen->format, 0);
        if(optimize_image==NULL)
        {
            printf("could not optimize, error is: %s", SDL_GetError() );

        }
        SDL_FreeSurface(load_image);
        if (optimize_image != NULL)
        {
            UINT32 color_key = SDL_MapRGB(optimize_image->format, 0x2E, 0xC6, 0x35 );
            SDL_SetColorKey(optimize_image,SDL_TRUE, color_key);
        }
    }
    return optimize_image;
}

/// load image on screen

void applySurface(SDL_Surface* screen, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(screen, NULL, des, &offset);
}

/// cleanup function

void CleanUp()
{
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_bkground);
    SDL_DestroyWindow(g_window);
    IMG_Quit();
    SDL_Quit();
}

/// main

int main(int argc, char* args[])
{
    bool quit = false;
    if(!Init())
    {
        printf("could not initialize! \n");
        return 0;
    }
    g_bkground = Load_Image("main_bg.png");
    if(g_bkground==NULL)
    {
        printf("could not load bg");
        return 0;
    }
    g_opject = Load_Image("menu.png");
    if (g_opject == NULL)
    {
        printf("can't apply");
    }
    SDL_BlitSurface( g_bkground, NULL, g_screen, NULL );
    applySurface(g_opject, g_screen, 15, 115);
    SDL_UpdateWindowSurface( g_window );

    while(!quit)
    {
        while(SDL_PollEvent(&g_event))
        {
            if(g_event.type == SDL_QUIT)
            {
                quit  = true;
                break;
            }
        }
    }

    CleanUp();
    return 0;
    // ed
}
