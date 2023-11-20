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
int ballInitialSpeed_X;
int ballInitialSpeed_Y;
int ballRangeRandomInterval_X;
int ballRangeRandomInterval_Y;
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
    ballInitialSpeed_X = 1000; //Velocidad pelota Inicial. Eje X
    ballInitialSpeed_Y = 1000; //Velocidad pelota Inicial. Eje Y
    ballRangeRandomInterval_X = 250 + ballInitialSpeed_X; //Intervalo de velocidad aleatoria. Cambiar unicamente los valores
    ballRangeRandomInterval_Y = 250 + ballInitialSpeed_Y; //Intervalo de velocidad aleatoria. Cambiar unicamente los valores
    for (size_t i = 0; i < cantPelotas; i++)
    {
        ballValues[i].x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
        ballValues[i].y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
        ballValues[i].width = ballWidth;
        ballValues[i].height = ballHeight;
        ballValues[i].vel_x = ballInitialSpeed_X;
        ballValues[i].vel_y = ballInitialSpeed_Y;
    }
}
void ballCollisions(int WINDOW_WIDTH, int WINDOW_HEIGHT, bool &startCooldown)
{
    for (int i = 0; i < cantPelotas; i++)
    {
        if (ballValues[i].x <= 0)
        {
            ballValues[i].x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
            ballValues[i].y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
            ballValues[i].vel_x = -ballValues[i].vel_x;
            ballValues[i].vel_y = -ballValues[i].vel_y;
            intScores[1]++;
            startCooldown = true;
            Mix_PlayChannel(-1, scoreSFX, 0);
        }
        if ((ballValues[i].x + ballWidth) >= WINDOW_WIDTH)
        {
            ballValues[i].x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
            ballValues[i].y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
            ballValues[i].vel_x = -ballValues[i].vel_x;
            ballValues[i].vel_y = -ballValues[i].vel_y;
            intScores[0]++;
            startCooldown = true;
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
void ballMovement(int WINDOW_WIDTH,int WINDOW_HEIGHT,float factor)
{
    for (int i = 0; i < cantPelotas; i++)
    {
        ballValues[i].x += ballValues[i].vel_x * factor;
        ballValues[i].y += ballValues[i].vel_y * factor;
    }
}
void ballCooldownReset(int WINDOW_WIDTH, int WINDOW_HEIGHT,bool &startCooldown)
{
    for (int i = 0; i < cantPelotas; i++)
    {
        if (startCooldown)
        {
            ballValues[i].x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
            ballValues[i].y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
            switch (rand() % 4 + 1)
            {
                case 1:
                {
                    ballValues[i].vel_x = ballInitialSpeed_X;
                    ballValues[i].vel_y = -ballInitialSpeed_Y;
                    break;
                }
                case 2:
                {
                    ballValues[i].vel_x = -ballInitialSpeed_X;
                    ballValues[i].vel_y = ballInitialSpeed_Y;
                    break;
                }
                case 3:
                {
                    ballValues[i].vel_x = ballInitialSpeed_X;
                    ballValues[i].vel_y = ballInitialSpeed_Y;
                    break;
                }
                case 4:
                {
                    ballValues[i].vel_x = -ballInitialSpeed_X;
                    ballValues[i].vel_y = -ballInitialSpeed_Y;
                    break;
                }
            }
            
        }
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