#include "Ball.h"
#include "Score.h"
#include "MenuTest.h"
#include <SDL_image.h> 
#include <stdio.h>

SDL_Texture* textureBall;
ball ballimg;

/////////////
///Variables
/////////////

int ballWidth = 20; //Altura Pelota
int ballHeight = 20; //Ancho Pelota
int ballRangeRandomInterval_X = 500; //Intervalo de velocidad aleatoria. Eje X
int ballRangeRandomInterval_Y = 500; //Intervalo de velocidad aleatoria. Eje Y
int ballInitialSpeed_X = 1000; //Velocidad pelota Inicial. Eje X
int BallInitialSpeed_Y = 1000; //Velocidad pelota Inicial. Eje Y


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
    ballimg.x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
    ballimg.y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
    ballimg.width = ballWidth;
    ballimg.height = ballHeight;
    ballimg.vel_x = ballInitialSpeed_X;
    ballimg.vel_y = BallInitialSpeed_Y;
}

void ballCollisions(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    if (ballimg.x < 0)
    {
        ballimg.x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
        ballimg.y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
        ballimg.vel_x = -ballimg.vel_x;
        ballimg.vel_y = -ballimg.vel_y;
        intScores[0]++;
        Mix_PlayChannel(-1, scoreSFX, 0);
    }
    if ((ballimg.x + ballWidth) > WINDOW_WIDTH)
    {
        ballimg.x = (WINDOW_WIDTH / 2) - (ballWidth / 2);
        ballimg.y = (WINDOW_HEIGHT / 2) - (ballHeight / 2);
        ballimg.vel_x = -ballimg.vel_x;
        ballimg.vel_y = -ballimg.vel_y;
        intScores[1]++;
        Mix_PlayChannel(-1, scoreSFX, 0);
    }
    if (ballimg.y < 0)
    {
        ballimg.y = 1;
        ballimg.vel_y = -ballimg.vel_y;
        Mix_PlayChannel(-1, bordersSFX, 0);
    }
    if ((ballimg.y + ballWidth) > WINDOW_HEIGHT)
    {
        ballimg.y = WINDOW_HEIGHT - ballimg.height;
        ballimg.vel_y = -ballimg.vel_y;
        Mix_PlayChannel(-1, bordersSFX, 0);
    }
}

void ballMovement(float factor)
{
    ballimg.x += ballimg.vel_x * factor;
    ballimg.y += ballimg.vel_y * factor;
}