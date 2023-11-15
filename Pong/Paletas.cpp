#include "Paletas.h"
#include "Ball.h"
#include "MenuTest.h"
#include <SDL_image.h>
#include <time.h> //Time
#include <stdlib.h> //Rand
#include <stdio.h> //printf,NULL
#include <vector> //Vector

/////////////
///Variables
/////////////

int cantPaddles = 2;
int paddleWidth = 20; //Ancho de las Paletas
int paddleHeight = paddleWidth * 8; //Altura de las paletas
int reachTolerance = 5; //Tasa de tolerancia.
int paddleSpeed = 2000; //Velocidad de la paleta por seg (segun tiempo presionado).

vector<SDL_Texture*> texturePaddle(cantPaddles);
vector<paddles> paddle(cantPaddles);

///////////////////////////
///Inicializado de textura
///////////////////////////

void textureInitialitationPalette(SDL_Renderer* renderer)
{
    for (int i = 0; i < cantPaddles; i++)
    {
        texturePaddle[i] = IMG_LoadTexture(renderer, "Paleta.png");
        if (!texturePaddle[i])
        {
            fprintf(stderr, "Texture Error\n");
            fprintf(stderr, IMG_GetError());
        }
    }
    
} 

////////////////////
///Paletas
////////////////////

void setupPalette(int WINDOW_WIDTH,int WINDOW_HEIGHT)
{
    for (int i = 0; i < cantPaddles; i++)
    {
        if (i == 0)
        {
            ///Paleta Izq
            paddle[i].x = (WINDOW_WIDTH / 10) - (paddleWidth / 2);
            paddle[i].y = (WINDOW_HEIGHT / 2) - (paddleHeight / 2);
            paddle[i].width = paddleWidth;
            paddle[i].height = paddleHeight;
        }
        if (i == 1)
        {
            ///Paleta Der
            paddle[i].x = WINDOW_WIDTH - (WINDOW_WIDTH / 10);
            paddle[i].y = (WINDOW_HEIGHT / 2) - (paddleHeight / 2);
            paddle[i].width = paddleWidth;
            paddle[i].height = paddleHeight;
        }
    }
}
void collisionPalette(int WINDOW_HEIGHT)
{
    for (size_t i = 0; i < cantPaddles; i++)
    {
        if (i == 0)
        {
            ///Paleta Izq
            if (ballimg.x <= paddle[i].x + paddleWidth && (ballimg.x + ballWidth) >= paddle[i].x)
            {
                if (((ballimg.y + reachTolerance) <= (paddle[i].y + paddleHeight)) && (ballimg.y + ballHeight - reachTolerance) >= paddle[i].y)
                {
                    ballimg.x = (paddle[i].x + ballimg.width);
                    ballimg.vel_x = (rand() % (ballimg.vel_x - ballRangeRandomInterval_X + 1) + ballRangeRandomInterval_X);
                    ballimg.vel_y = -(rand() % (ballimg.vel_y - ballRangeRandomInterval_Y + 1) + ballRangeRandomInterval_Y);
                    Mix_PlayChannel(-1, paddleLeftSFX, 0);
                }
            }
            if (paddle[i].y < 0)
            {
                paddle[i].y = 0;
            }
            if (paddle[i].y + paddleHeight > WINDOW_HEIGHT)
            {
                paddle[i].y = WINDOW_HEIGHT - paddleHeight;
            }
        }
        if (i == 1)
        {
            if ((ballimg.x + ballWidth) >= paddle[i].x && ballimg.x <= paddle[i].x + paddleWidth)
            {
                if (((ballimg.y + ballHeight - reachTolerance) >= paddle[i].y && (ballimg.y + reachTolerance) <= (paddle[i].y + paddleHeight)))
                {
                    ballimg.x = (paddle[i].x - ballimg.width);
                    ballimg.vel_x = -(rand() % (ballimg.vel_x - ballRangeRandomInterval_X + 1) + ballRangeRandomInterval_X);
                    ballimg.vel_y = -(rand() % (ballimg.vel_y - ballRangeRandomInterval_Y + 1) + ballRangeRandomInterval_Y);
                    Mix_PlayChannel(-1, paddleRightSFX, 0);
                }
            }
            if (paddle[i].y < 0)
            {
                paddle[i].y = 0;
            }
            if (paddle[i].y + paddleHeight > WINDOW_HEIGHT)
            {
                paddle[i].y = WINDOW_HEIGHT - paddleHeight;
            }
        }
    }
    
}
void renderPalette(SDL_Renderer* renderer)
{
    vector<SDL_Rect> rectPaddle(cantPaddles);
    for (size_t i = 0; i < cantPaddles; i++)
    {
        rectPaddle[i] = {
        (int)paddle[i].x,
        (int)paddle[i].y,
        (int)paddle[i].width,
        (int)paddle[i].height
        };
        SDL_RenderCopy(renderer, texturePaddle[i], nullptr, &rectPaddle[i]);
    }
}
void destroyTexturePaddles()
{
    for (int i = 0; i < cantPaddles; i++)
    {
        SDL_DestroyTexture(texturePaddle[i]);
    }
}