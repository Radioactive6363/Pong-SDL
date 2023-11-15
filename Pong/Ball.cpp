#include "Ball.h"
#include "Score.h"
#include "MenuyEventos.h"
#include <SDL_image.h> 
#include <stdio.h>
#include <vector>

using namespace std;

/////////////
///Variables
/////////////

int ballWidth = 20; //Altura Pelota
int ballHeight = 20; //Ancho Pelota
int ballRangeRandomInterval_X = 500; //Intervalo de velocidad aleatoria. Eje X
int ballRangeRandomInterval_Y = 500; //Intervalo de velocidad aleatoria. Eje Y
int ballInitialSpeed_X = 1000; //Velocidad pelota Inicial. Eje X
int BallInitialSpeed_Y = 1000; //Velocidad pelota Inicial. Eje Y
int cantPelotas = 1;
SDL_Texture* textureBall;
vector<ball> ballValues(cantPelotas);

///////////////////////////
///Inicializado de textura
///////////////////////////

void textureInitialitationBall(SDL_Renderer* renderer)
{
    textureBall = IMG_LoadTexture(renderer, "Pelota.png");
    if (!textureBall)
    {
        fprintf(stderr, "Texture Error\n");
        fprintf(stderr, IMG_GetError());
    }
}

//////////
///Pelota
//////////

void setupBall(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    ballValues[0].x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
    ballValues[0].y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
    ballValues[0].width = ballWidth;
    ballValues[0].height = ballHeight;
    ballValues[0].vel_x = ballInitialSpeed_X;
    ballValues[0].vel_y = BallInitialSpeed_Y;
}

void ballCollisions(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    for (int i = 0; i < cantPelotas; i++)
    {
        if (ballValues[i].x < 0)
        {
            ballValues[i].x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
            ballValues[i].y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
            ballValues[i].vel_x = -ballValues[i].vel_x;
            ballValues[i].vel_y = -ballValues[i].vel_y;
            intScores[0]++;
            Mix_PlayChannel(-1, scoreSFX, 0);
        }
        if ((ballValues[i].x + ballWidth) > WINDOW_WIDTH)
        {
            ballValues[i].x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
            ballValues[i].y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
            ballValues[i].vel_x = -ballValues[i].vel_x;
            ballValues[i].vel_y = -ballValues[i].vel_y;
            intScores[1]++;
            Mix_PlayChannel(-1, scoreSFX, 0);
        }
        if (ballValues[i].y < 0)
        {
            ballValues[i].y = 1;
            ballValues[i].vel_y = -ballValues[i].vel_y;
            Mix_PlayChannel(-1, bordersSFX, 0);
        }
        if ((ballValues[i].y + ballWidth) > WINDOW_HEIGHT)
        {
            ballValues[i].y = WINDOW_HEIGHT - ballValues[i].height;
            ballValues[i].vel_y = -ballValues[i].vel_y;
            Mix_PlayChannel(-1, bordersSFX, 0);
        }
    }
}
void ballMovement(float factor)
{
    for (int i = 0; i < cantPelotas; i++)
    {
        ballValues[i].x += ballValues[i].vel_x * factor;
        ballValues[i].y += ballValues[i].vel_y * factor;
    }
}

void renderBall(SDL_Renderer* renderer)
{
    vector <SDL_Rect> rectBall(cantPelotas);
    for (size_t i = 0; i < cantPelotas; i++)
    {
        rectBall[i] = {
        (int)ballValues[i].x,
        (int)ballValues[i].y,
        (int)ballValues[i].width,
        (int)ballValues[i].height
        };
        SDL_RenderCopy(renderer, textureBall, nullptr, &rectBall[i]);
    }
}