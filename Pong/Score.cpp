#include "Score.h"
#include "MenuyEventos.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <vector>

using namespace std;

//Variables Modificables
int cantScores = 2;
int cantTimers = 1;
int scoreWidth = 100; //Alto de Score
int scoreHeight = 150;//Ancho de Score
int scoreSeparation = 100;//Separacion respecto al centro
vector <int> intScores = { 0,0 };
Uint32 ticksTracker = 0; //Tracker en milisegundos. NO TOCAR
bool endTimer = false;
int TimerGame = 10 + (1); //Cantidad de segundos x partido. No cambiar (1)
int timerGameWidth = 150; //Alto de tiempo
int timerGameHeight = 150;//Ancho de tiempo

//Almacenamiento de Strings
vector<SDL_Color> colorTxtScores(cantScores), colorTxtTimers(cantTimers);
vector<string> stringScores (cantScores), stringTimers(cantTimers);
vector<const char*> charScores (cantScores), charTimers(cantTimers);
vector<scores> score(cantScores), timer(cantTimers);
vector<SDL_Surface*> surfaceScores(cantScores), surfaceTimers(cantTimers);
vector<SDL_Texture*> textureScores(cantScores), textureTimers(cantTimers);


//////////////////////////////////
//Puntaje y Timer Inicializadores.
//////////////////////////////////


//Puntaje
void setupScores(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    for (int i = 0; i < cantScores; i++)
    {
        if (i == 0) 
        {
            //Score Izq
            score[i].x = WINDOW_WIDTH / 2 - (scoreWidth / 2) - scoreSeparation;
            score[i].y = WINDOW_HEIGHT / 8 - (scoreHeight / 2);
            score[i].width = scoreWidth;
            score[i].height = scoreHeight;
        }
        if (i == 1)
        {
            //Score Der
            score[i].x = (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) - (scoreWidth / 2) + scoreSeparation;
            score[i].y = WINDOW_HEIGHT / 8 - (scoreHeight / 2);
            score[i].width = scoreWidth;
            score[i].height = scoreHeight;
        }
    }
}
void updateScores(SDL_Renderer* renderer)
{
    for (int i = 0; i < cantScores; i++)
    {
        colorTxtScores[i] = { 255,255,255,255 };
        if (i == 0)
        {
            colorTxtScores[i] = { 0,0,255,255 };
        }
        if (i == 1)
        {
            colorTxtScores[i] = { 255,0,0,255 };
        }
        charScores[i] = stringScores[i].c_str();
        stringScores[i] = to_string(intScores[i]);
        surfaceScores[i] = TTF_RenderText_Solid(font, charScores[i], colorTxtScores[i]);
        if (!surfaceScores[i])
        {
            fprintf(stderr, "Surface score error\n");
            fprintf(stderr, IMG_GetError());
        }
        textureScores[i] = SDL_CreateTextureFromSurface(renderer, surfaceScores[i]);
        SDL_FreeSurface(surfaceScores[i]);
    }
}
void renderScores(SDL_Renderer* renderer)
{
    vector<SDL_Rect> rectScores(cantScores);
    for (size_t i = 0; i < cantScores; i++)
    {
        rectScores[i] = {
        (int)score[i].x,
        (int)score[i].y,
        (int)score[i].width,
        (int)score[i].height
        };
        SDL_RenderCopy(renderer, textureScores[i], nullptr, &rectScores[i]);
    }
}

//Timer
void setupTimers(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    for (int i = 0; i < cantTimers; i++)
    {
         //Timer
         timer[i].x = WINDOW_WIDTH / 2 - (timerGameWidth / 2);
         timer[i].y = WINDOW_HEIGHT - (WINDOW_HEIGHT / 8) - (timerGameHeight / 2);
         timer[i].width = timerGameWidth;
         timer[i].height = timerGameHeight;
    }
}
void updateTimers(SDL_Renderer* renderer)
{
    for (int i = 0; i < cantTimers; i++)
    {
        //Timer
        colorTxtTimers[i] = { 255,255,255,255 };
        charTimers[i] = stringTimers[i].c_str();
        stringTimers[i] = to_string(TimerGame);
        surfaceTimers[i] = TTF_RenderText_Solid(font, charScores[i], colorTxtTimers[i]);
        if (!surfaceTimers[i])
        {
            fprintf(stderr, "Surface Timer error\n");
            fprintf(stderr, IMG_GetError());
        }
        textureTimers[i] = SDL_CreateTextureFromSurface(renderer, surfaceTimers[i]);
        SDL_FreeSurface(surfaceTimers[i]);

        while (ticksTracker <= SDL_GetTicks() && endTimer == false)
        {
            TimerGame = --TimerGame;
            ticksTracker = SDL_GetTicks() + 1000.0f;
            if (TimerGame == 0)
            {
                endTimer = true;
            }
        }
    }
}
void renderTimers(SDL_Renderer* renderer)
{
    vector<SDL_Rect> rectScores(cantScores);
    for (size_t i = 0; i < cantScores; i++)
    {
        rectScores[i] = {
        (int)score[i].x,
        (int)score[i].y,
        (int)score[i].width,
        (int)score[i].height
        };
        SDL_RenderCopy(renderer, textureScores[i], nullptr, &rectScores[i]);
    }
}

//Liberacion Memoria.
void destroyTextureScoresTimers()
{
    for (int i = 0; i < cantScores; i++)
    {
        SDL_DestroyTexture(textureScores[i]);
    }
    for (int j = 0; j < cantTimers; j++)
    {
        SDL_DestroyTexture(textureScores[j]);
    }
}