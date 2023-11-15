#pragma once
#include <SDL_image.h> 
#include <stdio.h>
#include <vector>

using namespace std;

extern SDL_Texture* textureBall;
extern int ballWidth, 
           ballHeight, 
           ballRangeRandomInterval_X, 
           ballRangeRandomInterval_Y,
           initialSpeed_X,
           initialSpeed_Y,
           cantPelotas;

struct ball
{
    int x;
    int y;
    int width;
    int height;
    int vel_x;
    int vel_y;
};
extern vector<ball> ballValues;

void textureInitialitationBall(SDL_Renderer* renderer);

void setupBall(int, int);

void ballCollisions(int, int);

void ballMovement(float);

void renderBall(SDL_Renderer*);
