#include "MenuTest.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Ball.h"
#include "Score.h"
#include "Paletas.h"

//Variables Modificables
int txtWidth = 300; //Ancho de texto.
int txtHeight = 300;//Alto de texto.
int txtSeparation = 250; //Separacion de textos.

TTF_Font *font;
texts txtStart, txtOptions, txtQuit;
SDL_Surface *surfaceStart, *surfaceOptions, *surfaceQuit;
SDL_Texture *textureStart, *textureOptions, *textureQuit;

//////////////////
//Fuente de texto.

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


//////////////////////////
///Inicializador Texturas
//////////////////////////

void initializeTextures(SDL_Renderer *renderer)
{
    FontInitialitation(); // Fuente
    textureInitialitationBall(renderer); //Pelota
    textureInitialitationPalette(renderer); //Paleta
}

//////////////////////////
// Menu
//////////////////////////

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
void renderPrincipalMenu(SDL_Renderer* renderer)
{
    SDL_Rect rectStart = {
        (int)txtStart.x,
        (int)txtStart.y,
        (int)txtStart.width,
        (int)txtStart.height
    };
    SDL_Rect rectOptions = {
        (int)txtOptions.x,
        (int)txtOptions.y,
        (int)txtOptions.width,
        (int)txtOptions.height
    };
    SDL_Rect rectQuit = {
        (int)txtQuit.x,
        (int)txtQuit.y,
        (int)txtQuit.width,
        (int)txtQuit.height
    };
    SDL_RenderCopy(renderer, textureStart, nullptr, &rectStart);
    SDL_RenderCopy(renderer, textureOptions, nullptr, &rectOptions);
    SDL_RenderCopy(renderer, textureQuit, nullptr, &rectQuit);
}
void destroyTexturesPrincipalMenu()
{
    SDL_DestroyTexture(textureStart);
    SDL_DestroyTexture(textureOptions);
    SDL_DestroyTexture(textureQuit);
}

//////////////////////////
//Juego
//////////////////////////

void setupNormalGame(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    setupScoreLeft(WINDOW_WIDTH, WINDOW_HEIGHT); //Puntaje Izquierdo
    setupScoreRight(WINDOW_WIDTH, WINDOW_HEIGHT); //Puntaje Derecho
    setupTimerGame(WINDOW_WIDTH, WINDOW_HEIGHT);
    setupBall(WINDOW_WIDTH, WINDOW_HEIGHT); //Pelota
    setupLeftPalette(WINDOW_WIDTH, WINDOW_HEIGHT); //Paleta Izquierda
    setupRightPalette(WINDOW_WIDTH, WINDOW_HEIGHT); //Paleta Derecha
}
void updateNormalGame(SDL_Renderer* renderer, int WINDOW_WIDTH, int WINDOW_HEIGHT, float delta_time)
{
    ballMovement(delta_time); //Movimiento Pelota
    ballCollisions(WINDOW_WIDTH, WINDOW_HEIGHT); //Colisiones Pelota
    collisionLeftPalette(WINDOW_HEIGHT); //Colisiones Paleta Izquierda
    collisionRightPalette(WINDOW_HEIGHT); //Colisiones Paleta Izquierda
    updateTimerGame(renderer);
    updateScoreLeft(renderer); //Puntaje Izquierdo
    updateScoreRight(renderer); //Puntaje Derecho
}
void renderNormalGame(SDL_Renderer* renderer)
{
    SDL_Rect rectBall = {
     (int)ballimg.x,
     (int)ballimg.y,
     (int)ballimg.width,
     (int)ballimg.height
    };
    SDL_Rect rectPaddle_Left = {
        (int)paddleLeft.x,
        (int)paddleLeft.y,
        (int)paddleLeft.width,
        (int)paddleLeft.height
    };
    SDL_Rect rectPaddle_Right = {
        (int)paddleRight.x,
        (int)paddleRight.y,
        (int)paddleRight.width,
        (int)paddleRight.height
    };
    SDL_Rect rectTimer_Game = {
        (int)timer.x,
        (int)timer.y,
        (int)timer.width,
        (int)timer.height
    };
    SDL_Rect rectScore_Left = {
        (int)scoreLeft.x,
        (int)scoreLeft.y,
        (int)scoreLeft.width,
        (int)scoreLeft.height,
    };
    SDL_Rect rectScore_Right = {
        (int)scoreRight.x,
        (int)scoreRight.y,
        (int)scoreRight.width,
        (int)scoreRight.height,
    };
    SDL_RenderCopy(renderer, textureBall, nullptr, &rectBall);
    SDL_RenderCopy(renderer, texturePaddle, nullptr, &rectPaddle_Left);
    SDL_RenderCopy(renderer, texturePaddle, nullptr, &rectPaddle_Right);
    SDL_RenderCopy(renderer, textureTimerGame, nullptr, &rectTimer_Game);
    SDL_RenderCopy(renderer, textureScoreLeft, nullptr, &rectScore_Left);
    SDL_RenderCopy(renderer, textureScoreRight, nullptr, &rectScore_Right);
}
void destroyTexturesNormalGame()
{
    SDL_DestroyTexture(textureBall);
    SDL_DestroyTexture(texturePaddle);
    SDL_DestroyTexture(textureScoreLeft);
    SDL_DestroyTexture(textureScoreRight);
}
