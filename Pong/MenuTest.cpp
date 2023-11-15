#include "MenuTest.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "Ball.h"
#include "Score.h"
#include "Paletas.h"

using namespace std;

//Variables Modificables
int txtWidth = 300; //Ancho de texto.
int txtHeight = 300;//Alto de texto.
int txtSeparation = 250; //Separacion de textos.
int cantTextos = 3;
Mix_Music* music = NULL;
Mix_Chunk* paddleLeftSFX = NULL;
Mix_Chunk* paddleRightSFX = NULL;
Mix_Chunk* bordersSFX = NULL;
Mix_Chunk* scoreSFX = NULL;

TTF_Font *font;

vector<texts> txtMenu(cantTextos);
vector<SDL_Surface*> surfaceMenu(cantTextos);
vector<SDL_Texture*> textureMenu(cantTextos);
//texts txtStart, txtOptions, txtQuit;
//SDL_Surface *surfaceStart, *surfaceOptions, *surfaceQuit;
//SDL_Texture *textureStart, *textureOptions, *textureQuit;

//////////////////
//Fuente de texto.

void FontInitialitation()
{
    font = TTF_OpenFont("8bitOperatorPlus-Regular.ttf", 64);
    if (font == nullptr)
    {
        fprintf(stderr, "Font Error\n");
        fprintf(stderr, TTF_GetError());
    }
}

////////////////////
//Funciones de Menu

void setupMenu(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    for (int i = 0; i < cantTextos; i++)
    {
        if (i == 0)
        {
            txtMenu[i].x = (WINDOW_WIDTH / 2) - (txtWidth / 2);
            txtMenu[i].y = (WINDOW_HEIGHT / 2) - (txtHeight / 2) - 200;
            txtMenu[i].width = txtWidth;
            txtMenu[i].height = txtHeight;
        }
        if (i == 1)
        {
            txtMenu[i].x = (WINDOW_WIDTH / 2) - (txtWidth / 2);
            txtMenu[i].y = txtMenu[i-1].y + (txtSeparation);
            txtMenu[i].width = txtWidth;
            txtMenu[i].height = txtHeight;
        }
        if (i == 2)
        {
            txtMenu[i].x = (WINDOW_WIDTH / 2) - (txtWidth / 2);
            txtMenu[i].y = txtMenu[i-1].y + (txtSeparation);
            txtMenu[i].width = txtWidth;
            txtMenu[i].height = txtHeight;
        }
    }
}
void updateMenu(SDL_Renderer* renderer)
{
    vector<string> stringTxtMenu(cantTextos);
    for (int i = 0; i < cantTextos; i++)
    {
        if (i == 0)
        {
            stringTxtMenu[i] = "Start";
        }
        if (i == 1)
        {
            stringTxtMenu[i] = "Options";
        }
        if (i == 2)
        {
            stringTxtMenu[i] = "Quit";
        }
        surfaceMenu[i] = TTF_RenderText_Solid(font, stringTxtMenu[i].c_str(), {255,255,255});
        if (!surfaceMenu[i])
        {
            fprintf(stderr, "String Txt error\n");
            fprintf(stderr, IMG_GetError());
        }
        textureMenu[i] = SDL_CreateTextureFromSurface(renderer, surfaceMenu[i]);
        SDL_FreeSurface(surfaceMenu[i]);
    }
}
void renderMenu(SDL_Renderer* renderer)
{
    vector<SDL_Rect> rectMenu(cantTextos);
    for (int i = 0; i < cantTextos; i++)
    {
        rectMenu[i] = {
        (int)txtMenu[i].x,  
        (int)txtMenu[i].y,
        (int)txtMenu[i].width,
        (int)txtMenu[i].height
        };
        SDL_RenderCopy(renderer, textureMenu[i], nullptr, &rectMenu[i]);
    }
}
void destroyTexturesMenu()
{
    for (size_t i = 0; i < cantTextos; i++)
    {
        SDL_DestroyTexture(textureMenu[i]);
    }
}

//////////////////////////
///Inicializador Texturas
//////////////////////////

void initializeTextures(SDL_Renderer *renderer)
{
    FontInitialitation(); // Fuente
    textureInitialitationBall(renderer); //Pelota
    textureInitialitationPalette(renderer); //Paleta
}

////////////////////////////////
///Audio y Musica
////////////////////////////////

void initializeMusic()
{
    music = Mix_LoadMUS("ServantsOfScourage.wav");
}
void initializeSFX()
{
    paddleLeftSFX = Mix_LoadWAV("PaddleLeft.wav");
    paddleRightSFX = Mix_LoadWAV("PaddleRight.wav");
    bordersSFX = Mix_LoadWAV("Borders.wav");
    scoreSFX = Mix_LoadWAV("ScoreSFX.wav");
}
void destroyMusicSFX()
{
    Mix_FreeMusic(music);
    Mix_FreeChunk(paddleLeftSFX);
    Mix_FreeChunk(paddleRightSFX);
    Mix_FreeChunk(bordersSFX);
    Mix_FreeChunk(scoreSFX);
}

//////////////////////////
//Juego
//////////////////////////

void setupNormalGame(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    setupBall(WINDOW_WIDTH, WINDOW_HEIGHT); //Pelota
    setupPalette(WINDOW_WIDTH, WINDOW_HEIGHT); //Paletas
    setupScoreLeft(WINDOW_WIDTH, WINDOW_HEIGHT); //Puntaje Izquierdo
    setupScoreRight(WINDOW_WIDTH, WINDOW_HEIGHT); //Puntaje Derecho
    setupTimerGame(WINDOW_WIDTH, WINDOW_HEIGHT);
}
void updateNormalGame(SDL_Renderer* renderer, int WINDOW_WIDTH, int WINDOW_HEIGHT, float delta_time)
{
    ballMovement(delta_time); //Movimiento Pelota
    ballCollisions(WINDOW_WIDTH, WINDOW_HEIGHT); //Colisiones Pelota
    collisionPalette(WINDOW_HEIGHT);
    updateScoreLeft(renderer); //Puntaje Izquierdo
    updateScoreRight(renderer); //Puntaje Derecho
    updateTimerGame(renderer);
}
void renderNormalGame(SDL_Renderer* renderer)
{
    //vector<SDL_Rect> rectGameTextures(6);
    SDL_Rect rectBall = {
     (int)ballimg.x,
     (int)ballimg.y,
     (int)ballimg.width,
     (int)ballimg.height
    };
    SDL_Rect rectTimer_Game = {
        (int)timer.x,
        (int)timer.y,
        (int)timer.width,
        (int)timer.height
    };
    SDL_Rect rectScore_Left = {
        (int)scoreLeft.x,
        (int)scoreLeft.y,
        (int)scoreLeft.width,
        (int)scoreLeft.height,
    };
    SDL_Rect rectScore_Right = {
        (int)scoreRight.x,
        (int)scoreRight.y,
        (int)scoreRight.width,
        (int)scoreRight.height,
    };
    SDL_RenderCopy(renderer, textureBall, nullptr, &rectBall);
    renderPalette(renderer);
    SDL_RenderCopy(renderer, textureTimerGame, nullptr, &rectTimer_Game);
    SDL_RenderCopy(renderer, textureScoreLeft, nullptr, &rectScore_Left);
    SDL_RenderCopy(renderer, textureScoreRight, nullptr, &rectScore_Right);
}
void destroyTexturesNormalGame()
{
    SDL_DestroyTexture(textureBall);
    destroyTexturePaddles();
    SDL_DestroyTexture(textureScoreRight);
    SDL_DestroyTexture(textureScoreLeft);
}
