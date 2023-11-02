#pragma once
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>

extern int scoreWidth;
extern int scoreHeight;
extern int scoreSeparation;
extern int intLeftScore;
extern int intRightScore;
extern std::string stringScoreLeft;
extern std::string stringScoreRight;
extern const char* scoreCharLeft;
extern const char* scoreCharRight;

extern TTF_Font* font;
struct score
{
    float x;
    float y;
    float width;
    float height;
};
extern score scoreLeft, scoreRight;
extern SDL_Surface* surfaceScoreLeft;
extern SDL_Texture* textureScoreLeft;
extern SDL_Surface* surfaceScoreRight;
extern SDL_Texture* textureScoreRight;

void FontInitialitation();

void setupScoreLeft(int, int);
void updateScoreLeft(SDL_Renderer* renderer);

void setupScoreRight(int, int);
void updateScoreRight(SDL_Renderer* renderer);