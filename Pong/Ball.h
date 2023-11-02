#pragma once
#include <SDL_image.h> 
#include <stdio.h>

extern SDL_Texture* textureBall;
extern int ballWidth;
extern int ballHeight;
extern int ballRangeRandomInterval_X;
extern int ballRangeRandomInterval_Y;
extern int initialSpeed_X;
extern int initialSpeed_Y;

struct ball
{
    int x;
    int y;
    int width;
    int height;
    int vel_x;
    int vel_y;
};
extern ball ballimg;

void textureInitialitationBall(SDL_Renderer* renderer);

void setupBall(int, int);

void ballCollisions(int, int);

void ballMovement(float);



//ERROR DE INCLUDE.
//ERROR DE GETCHAR