#include "Score.h"
#include "MenuTest.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>

//Variables Modificables
int scoreWidth = 100; //Alto de Score
int scoreHeight = 150;//Ancho de Score
int scoreSeparation = 100;//Separacion respecto al centro
int intLeftScore = 0; //Puntaje Inicial Izquierdo
int intRightScore = 0; // Puntaje Inicial Derecho
Uint32 ticksTracker = 0; //Tracker en milisegundos. NO TOCAR
bool endTimer = false;
int TimerGame = 10 + (1); //Cantidad de segundos x partido. No cambiar (1)
int timerGameWidth = 150; //Alto de tiempo
int timerGameHeight = 150;//Ancho de tiempo

//Almacenamiento de Strings
std::string stringScoreLeft, stringScoreRight, stringTimerGame;
const char *scoreCharLeft = stringScoreLeft.c_str();
const char *scoreCharRight = stringScoreRight.c_str();
const char *timerCharGame = stringTimerGame.c_str();
score scoreLeft, scoreRight, timer;
SDL_Surface *surfaceScoreLeft, *surfaceScoreRight, *surfaceTimerGame;
SDL_Texture *textureScoreLeft, *textureScoreRight, *textureTimerGame;

///////////////////
//Puntaje Izquierdo
///////////////////

void setupScoreLeft(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    scoreLeft.x = WINDOW_WIDTH / 2 - (scoreWidth / 2) - scoreSeparation;
    scoreLeft.y = WINDOW_HEIGHT / 8 - (scoreHeight / 2);
    scoreLeft.width = scoreWidth;
    scoreLeft.height = scoreHeight;
}
void updateScoreLeft(SDL_Renderer* renderer)
{
    stringScoreLeft = std::to_string(intLeftScore);
    surfaceScoreLeft = TTF_RenderText_Solid(font, scoreCharLeft, { 0,0,255 });
    if (!surfaceScoreLeft)
    {
        fprintf(stderr, "Surface score left error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureScoreLeft = SDL_CreateTextureFromSurface(renderer, surfaceScoreLeft);
    SDL_FreeSurface(surfaceScoreLeft);
}

///////////////////
//Puntaje Derecho
///////////////////

void setupScoreRight(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    scoreRight.x = (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) - (scoreWidth / 2) + scoreSeparation;
    scoreRight.y = WINDOW_HEIGHT / 8 - (scoreHeight / 2);
    scoreRight.width = scoreWidth;
    scoreRight.height = scoreHeight;
}
void updateScoreRight(SDL_Renderer* renderer)
{
    stringScoreRight = std::to_string(intRightScore);
    surfaceScoreRight = TTF_RenderText_Solid(font, scoreCharRight, { 255,0,0 });
    if (!surfaceScoreRight)
    {
        fprintf(stderr, "Surface score left error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureScoreRight = SDL_CreateTextureFromSurface(renderer, surfaceScoreRight);
    SDL_FreeSurface(surfaceScoreRight);
}

///////////////////
//Timer
///////////////////

void setupTimerGame(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    timer.x = WINDOW_WIDTH / 2 - (timerGameWidth / 2);
    timer.y = WINDOW_HEIGHT - (WINDOW_HEIGHT/ 8) - (timerGameHeight / 2);
    timer.width = timerGameWidth;
    timer.height = timerGameHeight;
}
void updateTimerGame(SDL_Renderer* renderer)
{
    stringTimerGame = std::to_string(TimerGame);
    surfaceTimerGame = TTF_RenderText_Solid(font, timerCharGame, { 255,255,255 });
    if (!surfaceTimerGame)
    {
        fprintf(stderr, "Timer Game error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureTimerGame = SDL_CreateTextureFromSurface(renderer, surfaceTimerGame);
    SDL_FreeSurface(surfaceTimerGame);

    while (ticksTracker <= SDL_GetTicks() && endTimer == false)
    {
        TimerGame = --TimerGame;
        ticksTracker = SDL_GetTicks() + 1000.0f;
        if(TimerGame == 0)
        {   
            endTimer = true;
        }
    }
}