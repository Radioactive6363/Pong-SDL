#pragma once
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <SDL_mixer.h>

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

void setupPrincipalMenu(int, int);
void updatePrincipalMenu(SDL_Renderer*);
void renderPrincipalMenu(SDL_Renderer*);
void destroyTexturesPrincipalMenu();

void setupNormalGame(int, int);
void updateNormalGame(SDL_Renderer*, int, int, float);
void renderNormalGame(SDL_Renderer*);
void destroyTexturesNormalGame();
