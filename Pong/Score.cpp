#include "Score.h"
#include <SDL_ttf.h> 
#include <SDL_image.h>

int scoreWidth = 100; //Alto de Score
int scoreHeight = 150;//Ancho de Score
int scoreSeparation = 100;//Separacion respecto al centro
int intLeftScore = 0; //Puntaje Inicial Izquierdo
int intRightScore = 0; // Puntaje Inicial Derecho

//Almacenamiento de Strings
TTF_Font* font;
std::string stringScoreLeft;
std::string stringScoreRight;
const char* scoreCharLeft = stringScoreLeft.c_str();
const char* scoreCharRight = stringScoreRight.c_str();
score scoreLeft, scoreRight;
SDL_Surface* surfaceScoreLeft;
SDL_Texture* textureScoreLeft;
SDL_Surface* surfaceScoreRight;
SDL_Texture* textureScoreRight;


//////////////////
//Fuente de texto. 
//////////////////


void FontInitialitation()
{
    font = TTF_OpenFont("8bitOperatorPlus-Regular.ttf", 64);
    if (font == nullptr)
    {
        fprintf(stderr, "Font Error\n");
        fprintf(stderr, TTF_GetError());
    }
}
 

///////////////////
//Puntaje Izquierdo
///////////////////

void setupScoreLeft(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    scoreLeft.x = WINDOW_WIDTH / 2 - (scoreWidth / 2) - scoreSeparation;
    scoreLeft.y = WINDOW_HEIGHT / 8 - (scoreHeight / 2);
    scoreLeft.width = scoreWidth;
    scoreLeft.height = scoreHeight;
}
void updateScoreLeft(SDL_Renderer* renderer)
{
    stringScoreLeft = std::to_string(intLeftScore);
    surfaceScoreLeft = TTF_RenderText_Solid(font, scoreCharLeft, { 0,0,255 });
    if (!surfaceScoreLeft)
    {
        fprintf(stderr, "Surface score left error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureScoreLeft = SDL_CreateTextureFromSurface(renderer, surfaceScoreLeft);
    SDL_FreeSurface(surfaceScoreLeft);
}

///////////////////
//Puntaje Derecho
///////////////////

void setupScoreRight(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    scoreRight.x = (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) - (scoreWidth / 2) + scoreSeparation;
    scoreRight.y = WINDOW_HEIGHT / 8 - (scoreHeight / 2);
    scoreRight.width = scoreWidth;
    scoreRight.height = scoreHeight;
}
void updateScoreRight(SDL_Renderer* renderer)
{
    stringScoreRight = std::to_string(intRightScore);
    surfaceScoreRight = TTF_RenderText_Solid(font, scoreCharRight, { 255,0,0 });
    if (!surfaceScoreRight)
    {
        fprintf(stderr, "Surface score left error\n");
        fprintf(stderr, IMG_GetError());
    }
    textureScoreRight = SDL_CreateTextureFromSurface(renderer, surfaceScoreRight);
    SDL_FreeSurface(surfaceScoreRight);
}
