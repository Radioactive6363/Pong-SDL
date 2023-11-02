#include "MenuTest.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>

int txtWidth = 300; //Ancho de texto.
int txtHeight = 300;//Alto de texto.
int txtSeparation = 250; //Separacion de textos.

TTF_Font *font;
texts txtStart, txtOptions, txtQuit;
SDL_Surface *surfaceStart, *surfaceOptions, *surfaceQuit;
SDL_Texture *textureStart, *textureOptions, *textureQuit;

//////////////////
//Fuente de texto.
//////////////////

void FontInitialitation()
{
    font = TTF_OpenFont("8bitOperatorPlus-Regular.ttf", 64);
    if (font == nullptr)
    {
        fprintf(stderr, "Font Error\n");
        fprintf(stderr, TTF_GetError());
    }
}

////////////////////
//Funciones de Menu
////////////////////

void setupStart(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    txtStart.x = (WINDOW_WIDTH / 2) - (txtWidth / 2);
    txtStart.y = (WINDOW_HEIGHT / 2) - (txtHeight / 2) - 200;
    txtStart.width = txtWidth;
    txtStart.height = txtHeight;
}
void updateStart(SDL_Renderer* renderer)
{
    surfaceStart = TTF_RenderText_Solid(font, "Start", {255,255,255});
    if (!surfaceStart)
    {
        fprintf(stderr, "Menu Surface error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureStart = SDL_CreateTextureFromSurface(renderer, surfaceStart);
    SDL_FreeSurface(surfaceStart);
}

void setupOptions(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    txtOptions.x = (WINDOW_WIDTH / 2) - (txtWidth / 2);
    txtOptions.y = txtStart.y + (txtSeparation);
    txtOptions.width = txtWidth;
    txtOptions.height = txtHeight;
}
void updateOptions(SDL_Renderer* renderer)
{
    surfaceOptions = TTF_RenderText_Solid(font, "Options", { 255,255,255 });
    if (!surfaceOptions)
    {
        fprintf(stderr, "Options Surface error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureOptions = SDL_CreateTextureFromSurface(renderer, surfaceOptions);
    SDL_FreeSurface(surfaceOptions);
}

void setupQuit(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    txtQuit.x = (WINDOW_WIDTH / 2) - (txtWidth / 2);
    txtQuit.y = txtOptions.y + (txtSeparation);
    txtQuit.width = txtWidth;
    txtQuit.height = txtHeight;
}
void updateQuit(SDL_Renderer* renderer)
{
    surfaceQuit = TTF_RenderText_Solid(font, "Quit", { 255,255,255 });
    if (!surfaceQuit)
    {
        fprintf(stderr, "Menu Surface error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureQuit = SDL_CreateTextureFromSurface(renderer, surfaceQuit);
    SDL_FreeSurface(surfaceQuit);
}

///////////////////////
//Inicializadores Menu
///////////////////////

void setupPrincipalMenu(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    setupStart(WINDOW_WIDTH, WINDOW_HEIGHT);
    setupOptions(WINDOW_WIDTH, WINDOW_HEIGHT);
    setupQuit(WINDOW_WIDTH, WINDOW_HEIGHT);
}
void updatePrincipalMenu(SDL_Renderer* renderer)
{
    updateStart(renderer);
    updateOptions(renderer);
    updateQuit(renderer);
}