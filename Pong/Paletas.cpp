#include "Paletas.h"
#include "Ball.h"
#include <SDL_image.h>
#include <time.h> //Time
#include <stdlib.h> //Rand
#include <stdio.h> //printf,NULL
SDL_Texture* texturePaddle;
game_object paddleLeft, paddleRight;

/////////////
///Variables
/////////////

int paddleWidth = 20; //Ancho de las Paletas
int paddleHeight = paddleWidth * 8; //Altura de las paletas
int reachTolerance = 5; //Tasa de tolerancia.
int paddleSpeed = 2000; //Velocidad de la paleta por seg (segun tiempo presionado).

///////////////////////////
///Inicializado de textura
///////////////////////////

void textureInitialitationPalette(SDL_Renderer* renderer)
{
    texturePaddle = IMG_LoadTexture(renderer, "Paleta.png");
    if (!texturePaddle)
    {
        fprintf(stderr, "Texture Error\n");
        fprintf(stderr, IMG_GetError());
    }
} 

////////////////////
///Paleta Izquierda
////////////////////

void setupLeftPalette(int WINDOW_WIDTH,int WINDOW_HEIGHT)
{
    paddleLeft.x = (WINDOW_WIDTH / 10) - (paddleWidth / 2);
    paddleLeft.y = (WINDOW_HEIGHT / 2) - (paddleHeight / 2);
    paddleLeft.width = paddleWidth;
    paddleLeft.height = paddleHeight;
}
void collisionLeftPalette(int WINDOW_HEIGHT)
{
    if (ballimg.x <= paddleLeft.x + paddleWidth && (ballimg.x + ballWidth) >= paddleLeft.x)
    {
        if (((ballimg.y + reachTolerance) <= (paddleLeft.y + paddleHeight)) && (ballimg.y + ballHeight - reachTolerance) >= paddleLeft.y)
        {
            ballimg.x = (paddleLeft.x + ballimg.width);
            ballimg.vel_x = (rand() % (ballimg.vel_x - ballRangeRandomInterval_X + 1) + ballRangeRandomInterval_X);
            ballimg.vel_y = -(rand() % (ballimg.vel_y - ballRangeRandomInterval_Y + 1) + ballRangeRandomInterval_Y);
        }
    }
    if (paddleLeft.y < 0)
    {
        paddleLeft.y = 0;
    }
    if (paddleLeft.y + paddleHeight > WINDOW_HEIGHT)
    {
        paddleLeft.y = WINDOW_HEIGHT - paddleHeight;
    }
}

///////////////////
///Paleta Derecha
///////////////////

void setupRightPalette(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
paddleRight.x = WINDOW_WIDTH - (WINDOW_WIDTH / 10);
paddleRight.y = (WINDOW_HEIGHT / 2) - (paddleHeight / 2);
paddleRight.width = paddleWidth;
paddleRight.height = paddleHeight;
}
void collisionRightPalette(int WINDOW_HEIGHT)
{
    if ((ballimg.x + ballWidth) >= paddleRight.x && ballimg.x <= paddleRight.x + paddleWidth)
    {
        if (((ballimg.y + ballHeight - reachTolerance) >= paddleRight.y && (ballimg.y + reachTolerance) <= (paddleRight.y + paddleHeight)))
        {
            ballimg.x = (paddleRight.x - ballimg.width);
            ballimg.vel_x = -(rand() % (ballimg.vel_x - ballRangeRandomInterval_X + 1) + ballRangeRandomInterval_X);
            ballimg.vel_y = -(rand() % (ballimg.vel_y - ballRangeRandomInterval_Y + 1) + ballRangeRandomInterval_Y);
        }
    }
    if (paddleRight.y < 0)
    {
        paddleRight.y = 0;
    }
    if (paddleRight.y + paddleHeight > WINDOW_HEIGHT)
    {
        paddleRight.y = WINDOW_HEIGHT - paddleHeight;
    }
}