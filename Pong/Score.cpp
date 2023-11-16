#include "Score.h"
#include "MenuyEventos.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <vector>

using namespace std;

//Variables Modificables
int cantJugadores = 2; //Cantidad de Jugadores
int cantTimers = 2; //Cantidad de Timers
int cantScores = 2 + cantJugadores; //Cantidad de Scores
int puntajeGanador = 3; //Puntaje para ganar
int scoreSeparation = 100;//Separacion respecto al centro
Uint32 ticksTracker = 0; //Tracker en milisegundos. NO TOCAR
bool endTimer = false; //Finalizacion del Timer
bool cooldownTimer = true; //Comienzo de Cooldown
int timerGameWidth = 150; //Alto de tiempo
int timerGameHeight = 200;//Ancho de tiempo

//Almacenamiento de Strings
vector <int> scoreWidth(cantScores);
vector <int> scoreHeight(cantScores);
vector <bool> playerWinner(cantScores / 2);
vector <int> intScores = { 0,0 };
vector<int> timerGame = { 120 + (1), 3 + (1) }; //Cantidad de segundos x partido. No cambiar (1)
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
        scoreWidth[i] = 100;
        scoreHeight[i] = 200;
        if (i == 0) 
        {
            //Score Izq
            score[i].x = WINDOW_WIDTH / 2 - (scoreWidth[i] / 2) - scoreSeparation;
            score[i].y = WINDOW_HEIGHT / 8 - (scoreHeight[i] / 2);
            score[i].width = scoreWidth[i];
            score[i].height = scoreHeight[i];
        }
        else if (i == 1)
        {
            //Score Der
            score[i].x = (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) - (scoreWidth[i] / 2) + scoreSeparation;
            score[i].y = WINDOW_HEIGHT / 8 - (scoreHeight[i] / 2);
            score[i].width = scoreWidth[i];
            score[i].height = scoreHeight[i];
        }
        else
        {
            scoreWidth[i] = 1200;
            scoreHeight[i] = 500;
            score[i].x = (WINDOW_WIDTH / 2) - (scoreWidth[i] / 2);
            score[i].y = (WINDOW_HEIGHT / 2) - (scoreHeight[i] / 2);
            score[i].width = scoreWidth[i];
            score[i].height = scoreHeight[i];
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
        else if (i == 1)
        {
            colorTxtScores[i] = { 255,0,0,255 };
        }
        if ((i == 2 || i == 3))
        {
            if (i == 2)
            {
                colorTxtScores[i] = { 0,0,255,255 };
            }
            if (i == 3)
            {
                colorTxtScores[i] = { 255,0,0,255 };
            }
            stringScores[i] = "Jugador " + to_string(i-1) + " Gana!";
            charScores[i] = stringScores[i].c_str();
            surfaceScores[i] = TTF_RenderText_Solid(font, charScores[i], colorTxtScores[i]);
        }
        else
        {
            charScores[i] = stringScores[i].c_str();
            stringScores[i] = to_string(intScores[i]);
            surfaceScores[i] = TTF_RenderText_Solid(font, charScores[i], colorTxtScores[i]);
        }
        textureScores[i] = SDL_CreateTextureFromSurface(renderer, surfaceScores[i]);
        SDL_FreeSurface(surfaceScores[i]);
    }
}
void winnerDeclarationScore(bool &winner)
{
    for (int i = 0; i < cantScores - cantJugadores; i++)
    {
        if (intScores[i] == puntajeGanador)
        {
            winner = true;
        }
    }
}
void renderScores(SDL_Renderer* renderer, bool &winner)
{
    vector<SDL_Rect> rectScores(cantScores);
    for (int i = 0; i < cantScores; i++)
    {
        rectScores[i] = {
        (int)score[i].x,
        (int)score[i].y,
        (int)score[i].width,
        (int)score[i].height
        };
        if (i<(cantScores-cantJugadores))
        {
            SDL_RenderCopy(renderer, textureScores[i], nullptr, &rectScores[i]);
        }
        else if (winner && (intScores[i - cantJugadores] == puntajeGanador))
        {
            SDL_RenderCopy(renderer, textureScores[i], nullptr, &rectScores[i]);
        }
    }
}

//Timer
void setupTimers(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    for (int i = 0; i < cantTimers; i++)
    {
         //Timer
        if (i != 1)
        {
            timer[i].x = WINDOW_WIDTH / 2 - (timerGameWidth / 2);
            timer[i].y = WINDOW_HEIGHT - (WINDOW_HEIGHT / 8) - (timerGameHeight / 2);
            timer[i].width = timerGameWidth;
            timer[i].height = timerGameHeight;
        }
        else
        {
            timer[i].x = WINDOW_WIDTH / 2 - (timerGameWidth / 2);
            timer[i].y = (WINDOW_HEIGHT / 2)- (timerGameHeight / 2);
            timer[i].width = timerGameWidth;
            timer[i].height = timerGameHeight;
        }
    }
}
void updateTimers(SDL_Renderer* renderer)
{
    for (int i = 0; i < cantTimers; i++)
    {
        //Timer
        if (i != 1)
        {
            colorTxtTimers[i] = { 255,255,255,255/4 };
        }
        else
        {
            colorTxtTimers[i] = { 255,255,255,255/2 };
        }
        charTimers[i] = stringTimers[i].c_str();
        stringTimers[i] = to_string(timerGame[i]);
        surfaceTimers[i] = TTF_RenderText_Solid(font, charTimers[i], colorTxtTimers[i]);
        if (!surfaceTimers[i])
        {
            fprintf(stderr, "Surface Timer error\n");
            fprintf(stderr, IMG_GetError());
        }
        textureTimers[i] = SDL_CreateTextureFromSurface(renderer, surfaceTimers[i]);
        SDL_FreeSurface(surfaceTimers[i]);

        if (!cooldownTimer)
        {
            timerGame[1] = 3;
        }

        while (ticksTracker <= SDL_GetTicks())
        {
            ticksTracker = SDL_GetTicks() + 1000.0f;
            //TimerGame[i] = --TimerGame[i]; NO FUNCIONAL. Solo modifica el timer, no el "Cooldown"
            if (!endTimer)
            {
                timerGame[0] = --timerGame[0];
            }
            if (cooldownTimer)
            {
                timerGame[1] = --timerGame[1];
            }
            if (timerGame[0] <= 0) //timerGame[i] == 0 TAMPOCO FUNCIONAL
            {
                endTimer = true;
            }
            if (timerGame[1] <= 0) //timerGame[i] == 0 TAMPOCO FUNCIONAL
            {
                cooldownTimer = false;
            }
        }
    }
}
void renderTimers(SDL_Renderer* renderer)
{
    vector<SDL_Rect> rectTimers(cantTimers);
    for (int i = 0; i < cantTimers; i++)
    {
        rectTimers[i] = {
        (int)timer[i].x,
        (int)timer[i].y,
        (int)timer[i].width,
        (int)timer[i].height
        };
        if (!endTimer && i == 0)
        {
            SDL_RenderCopy(renderer, textureTimers[0], nullptr, &rectTimers[0]);
        }
        if (cooldownTimer && i == 1)
        {
            SDL_RenderCopy(renderer, textureTimers[1], nullptr, &rectTimers[1]);
        }
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
        SDL_DestroyTexture(textureTimers[j]);
    }
}