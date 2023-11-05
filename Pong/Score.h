#pragma once
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>

extern int scoreWidth, scoreHeight, scoreSeparation, intLeftScore, intRightScore, TimerGame;
extern std::string stringScoreLeft, stringScoreRight, stringTimerGame;
extern const char *scoreCharLeft, *scoreCharRight, *timerCharGame;
extern Uint32 ticksTracker;
extern bool endTimer;

struct score
{
    int x;
    int y;
    int width;
    int height;
};
extern score scoreLeft, scoreRight, timer;
extern SDL_Surface* surfaceScoreLeft;
extern SDL_Texture* textureScoreLeft;
extern SDL_Surface* surfaceScoreRight;
extern SDL_Texture* textureScoreRight;
extern SDL_Surface* surfaceTimerGame;
extern SDL_Texture* textureTimerGame;

void setupScoreLeft(int, int);
void updateScoreLeft(SDL_Renderer*);

void setupScoreRight(int, int);
void updateScoreRight(SDL_Renderer*);

void setupTimerGame(int, int);
void updateTimerGame(SDL_Renderer*);