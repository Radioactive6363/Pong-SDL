#pragma once
#include <SDL_image.h>
extern SDL_Texture* texturePaddle;

extern int paddleWidth;
extern int paddleHeight;
extern int reachTolerance;
extern int paddleSpeed;

struct game_object {
    float x;
    float y;
    float width;
    float height;
    int vel_x;
    int vel_y;
}; extern game_object paddleLeft, paddleRight;

void textureInitialitationPalette(SDL_Renderer* renderer);

void setupLeftPalette(int, int);
void collisionLeftPalette(int );

void setupRightPalette(int, int);
void collisionRightPalette(int );
