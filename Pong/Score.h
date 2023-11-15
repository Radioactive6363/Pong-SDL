#pragma once
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>

using namespace std;

extern int scoreWidth, scoreHeight, scoreSeparation, TimerGame;
extern vector <int> intScores;

extern Uint32 ticksTracker;
extern bool endTimer;

struct scores
{
    int x;
    int y;
    int width;
    int height;
};
extern vector<scores> score, timer;
extern vector<string> stringScores, stringTimers;
extern vector<const char*> charScores, charTimers;
extern vector<SDL_Surface*> surfaceScores, surfaceTimers;
extern vector<SDL_Texture*> textureScores, textureTimers;

void setupScores(int, int);
void updateScores(SDL_Renderer*);
void renderScores(SDL_Renderer*);

void setupTimers(int, int);
void updateTimers(SDL_Renderer*);
void renderTimers(SDL_Renderer*);

void destroyTextureScoresTimers();