#pragma once
#include <SDL_image.h>
#include <time.h> //Time
#include <stdlib.h> //Rand
#include <stdio.h> //printf,NULL
#include <vector> //Vector

using namespace std;

extern int paddleWidth;
extern int paddleHeight;
extern int reachTolerance;
extern int paddleSpeed;

struct paddles {
    float x;
    float y;
    float width;
    float height;
    int vel_x;
    int vel_y;
}; 
extern vector<paddles> paddle;
extern vector<SDL_Texture*> texturePaddle;

void textureInitialitationPalette(SDL_Renderer* renderer);

void setupPalette(int, int);
void collisionPalette(int, int);
void renderPalette(SDL_Renderer*);
void destroyTexturePaddles();