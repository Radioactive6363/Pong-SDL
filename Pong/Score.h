#pragma once
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>

extern int scoreWidth, scoreHeight, scoreSeparation, intLeftScore, intRightScore;
extern std::string stringScoreLeft, stringScoreRight;
extern const char *scoreCharLeft, * scoreCharRight;

struct score
{
    int x;
    int y;
    int width;
    int height;
};
extern score scoreLeft, scoreRight;
extern SDL_Surface* surfaceScoreLeft;
extern SDL_Texture* textureScoreLeft;
extern SDL_Surface* surfaceScoreRight;
extern SDL_Texture* textureScoreRight;

void setupScoreLeft(int, int);
void updateScoreLeft(SDL_Renderer*);

void setupScoreRight(int, int);
void updateScoreRight(SDL_Renderer*);