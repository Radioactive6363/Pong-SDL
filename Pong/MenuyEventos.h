#pragma once
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

using namespace std;
extern bool winner;

extern Mix_Music* music;
extern Mix_Chunk* paddleLeftSFX;
extern Mix_Chunk* paddleRightSFX;
extern Mix_Chunk* bordersSFX;
extern Mix_Chunk* scoreSFX;

extern TTF_Font* font;
struct texts
{
    int x;
    int y;
    int width;
    int height;
};
extern vector<texts> txtMenu;
extern vector<SDL_Surface*> surfaceMenu;
extern vector<SDL_Texture*> textureMenu;


void initializeTextures(SDL_Renderer*);
void initializeMusic();
void initializeSFX();
void destroyMusicSFX();

void setupMenu(int, int);
void updateMenu(SDL_Renderer*);
void renderMenu(SDL_Renderer*);
void destroyTexturesMenu();

void setupNormalGame(int, int);
void updateNormalGame(SDL_Renderer*, int, int, float);
void renderNormalGame(SDL_Renderer*);
void destroyTexturesNormalGame();

void reset(int, int);