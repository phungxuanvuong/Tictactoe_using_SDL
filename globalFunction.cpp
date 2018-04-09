#include "globalFunction.h"

/// LOAD IMAGE FUNCION

SDL_Surface* SDL_commonFunc::Load_Image(std::string file_path)
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

void SDL_commonFunc::applySurface(SDL_Surface* screen, SDL_Surface* des, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(screen, NULL, des, &offset);
}

/// cleanup function

void SDL_commonFunc::CleanUp()
{
    SDL_FreeSurface(g_screen);
    SDL_FreeSurface(g_bkground);
    SDL_DestroyWindow(g_window);
    IMG_Quit();
    SDL_Quit();
}
