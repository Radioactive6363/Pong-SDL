#include "Score.h"
#include "MenuTest.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <vector>

using namespace std;

//Variables Modificables
int cantScores = 3;
int scoreWidth = 100; //Alto de Score
int scoreHeight = 150;//Ancho de Score
int scoreSeparation = 100;//Separacion respecto al centro
vector <int> intScores = { 0,0 };
Uint32 ticksTracker = 0; //Tracker en milisegundos. NO TOCAR
bool endTimer = false;
int TimerGame = 10 + (1); //Cantidad de segundos x partido. No cambiar (1)
int timerGameWidth = 150; //Alto de tiempo
int timerGameHeight = 150;//Ancho de tiempo
vector<SDL_Color> colorTxt(cantScores);

//Almacenamiento de Strings
vector<string> stringScores (cantScores);
vector<const char*> scoreChar (cantScores);
vector<scores> score(cantScores);
vector<SDL_Surface*> surfaceScores(cantScores);
vector<SDL_Texture*> textureScores(cantScores);


///////////////////
//Puntaje Izquierdo
///////////////////

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
        if (i == 2)
        {
            //Timer
            score[i].x = WINDOW_WIDTH / 2 - (timerGameWidth / 2);
            score[i].y = WINDOW_HEIGHT - (WINDOW_HEIGHT / 8) - (timerGameHeight / 2);
            score[i].width = timerGameWidth;
            score[i].height = timerGameHeight;
        }
    }
    
}
void updateScores(SDL_Renderer* renderer)
{
    for (int i = 0; i < cantScores - 1; i++)
    {
        colorTxt[i] = { 255,255,255,255 };
        if (i == 0)
        {
            //Score Izq
            colorTxt[i] = {0,0,255,255};
            scoreChar[i] = stringScores[i].c_str();
            stringScores[i] = to_string(intScores[i]);
            surfaceScores[i] = TTF_RenderText_Solid(font, scoreChar[i], colorTxt[i]);
            if (!surfaceScores[i])
            {
                fprintf(stderr, "Surface score error\n");
                fprintf(stderr, IMG_GetError());
            }
            textureScores[i] = SDL_CreateTextureFromSurface(renderer, surfaceScores[i]);
            SDL_FreeSurface(surfaceScores[i]);
        }
        if (i == 1)
        {
            //Score Der
            colorTxt[i] = { 255,0,0,255 };
            scoreChar[i] = stringScores[i].c_str();
            stringScores[i] = to_string(intScores[i]);
            surfaceScores[i] = TTF_RenderText_Solid(font, scoreChar[i], colorTxt[i]);
            if (!surfaceScores[i])
            {
                fprintf(stderr, "Surface score error\n");
                fprintf(stderr, IMG_GetError());
            }
            textureScores[i] = SDL_CreateTextureFromSurface(renderer, surfaceScores[i]);
            SDL_FreeSurface(surfaceScores[i]);
        }
        if (i == 2)
        {
            //Timer
            colorTxt[i] = { 255,255,255,255 };
            scoreChar[i] = stringScores[i].c_str();
            stringScores[i] = to_string(TimerGame);
            surfaceScores[i] = TTF_RenderText_Solid(font, scoreChar[i], colorTxt[i]);
            if (!surfaceScores[i])
            {
                fprintf(stderr, "Surface score error\n");
                fprintf(stderr, IMG_GetError());
            }
            textureScores[i] = SDL_CreateTextureFromSurface(renderer, surfaceScores[i]);
            SDL_FreeSurface(surfaceScores[i]);

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
void destroyTextureScore()
{
    for (int i = 0; i < cantScores; i++)
    {
        SDL_DestroyTexture(textureScores[i]);
    }
}