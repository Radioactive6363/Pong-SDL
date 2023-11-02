#pragma once
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>

extern TTF_Font* font;
struct texts
{
    int x;
    int y;
    int width;
    int height;
};
extern texts txtStart, txtOptions, txtQuit;
extern SDL_Surface *surfaceStart, *surfaceOptions, *surfaceQuit;
extern SDL_Texture *textureStart, *textureOptions, *textureQuit;

void initializeTextures(SDL_Renderer*);
void setupJuegoNormal(int, int);
void updateJuegoNormal(SDL_Renderer*, int, int, float);
void setupPrincipalMenu(int, int);
void updatePrincipalMenu(SDL_Renderer*);