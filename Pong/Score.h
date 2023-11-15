#pragma once
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

extern int scoreWidth, scoreHeight, scoreSeparation, TimerGame;
extern vector <int> intScores;
extern vector<string> stringScores;
extern vector<const char*> scoreChar;
extern Uint32 ticksTracker;
extern bool endTimer;

struct scores
{
    int x;
    int y;
    int width;
    int height;
};
extern vector<scores> score;
extern vector<SDL_Surface*> surfaceScores;
extern vector<SDL_Texture*> textureScores;

void setupScores(int, int);
void updateScores(SDL_Renderer*);
void renderScores(SDL_Renderer*);
void destroyTextureScore();