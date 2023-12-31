#include "MenuyEventos.h"
#include "Ball.h"
#include "Score.h"
#include "Paletas.h"
#include <string>
#include <stdio.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

//Variables Modificables
int txtWidth = 700; //Ancho de texto.
int txtHeight = 300;//Alto de texto.
int txtSeparation = 250; //Separacion de textos.
int cantTextos = 3; //Cantidad de Textos Solicitados.
bool winner;
bool botModeActive = false;
Mix_Music* music = NULL;
Mix_Chunk* paddleLeftSFX = NULL;
Mix_Chunk* paddleRightSFX = NULL;
Mix_Chunk* bordersSFX = NULL;
Mix_Chunk* scoreSFX = NULL;
TTF_Font *font;
vector<SDL_Color> txtColors(cantTextos);
vector<texts> txtMenu(cantTextos);
vector<SDL_Surface*> surfaceMenu(cantTextos);
vector<SDL_Texture*> textureMenu(cantTextos);

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
            txtMenu[i].width = txtWidth;
            txtMenu[i].height = txtHeight;
            txtMenu[i].x = (WINDOW_WIDTH / 2) - (txtMenu[i].width / 2);
            txtMenu[i].y = (WINDOW_HEIGHT / 2) - (txtHeight / 2) - 200;
        }
        else
        {
            txtMenu[i].width = txtWidth + 200;
            txtMenu[i].height = txtHeight;
            txtMenu[i].x = (WINDOW_WIDTH / 2) - (txtMenu[i].width / 2);
            txtMenu[i].y = txtMenu[i - 1].y + (txtSeparation);
        }
    }
}
void updateMenu(SDL_Renderer* renderer)
{
    vector<string> stringTxtMenu(cantTextos);
    for (int i = 0; i < cantTextos; i++)
    {
        txtColors[i] = { 255,255,255,255 };
        if (i == 0)
        {
            stringTxtMenu[i] = "Press SPACE to Start";
        }
        if (i == 1)
        {
            
            if (botModeActive == true)
            {
                txtColors[i] = { 0,255,0,255 };
            }
            else
            {
                txtColors[i] = { 255,0,0,255 };
            }
            stringTxtMenu[i] = "Bot mode Active";
        }
        if (i == 2)
        {
            txtColors[i] = { 0,0,200,255/3 };
            stringTxtMenu[i] = "Change Mode: E";
        }
        surfaceMenu[i] = TTF_RenderText_Solid(font, stringTxtMenu[i].c_str(), txtColors[i]);
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
        winner = false;
        Mix_PlayMusic(music, -1);
        setupBall(WINDOW_WIDTH, WINDOW_HEIGHT); //Pelota
        setupPalette(WINDOW_WIDTH, WINDOW_HEIGHT); //Paletas
        setupScores(WINDOW_WIDTH, WINDOW_HEIGHT); //Puntaje
        setupTimers(WINDOW_WIDTH, WINDOW_HEIGHT); //Timers
}
void updateNormalGame(SDL_Renderer* renderer, int WINDOW_WIDTH, int WINDOW_HEIGHT, float delta_time)
{
    if (!winner && !endTimer)
    {
        srand(time(NULL));
        ballMovement(WINDOW_WIDTH, WINDOW_HEIGHT, delta_time); //Movimiento Pelota
        ballCollisions(WINDOW_WIDTH, WINDOW_HEIGHT, cooldownTimer); //Colisiones Pelota
        botModePalette(ballValues[0].y, ballValues[0].height, delta_time);
        collisionPalette(WINDOW_HEIGHT, cantPelotas);//Colisiones Paleta
        updateTimers(renderer); //Update Timers
        ballCooldownReset(WINDOW_WIDTH, WINDOW_HEIGHT, cooldownTimer);
    }
    else
    {
        Mix_HaltMusic();
    }
        endingGameTimer();
        winnerDeclarationScore(winner);
        updateScores(renderer); //Puntaje
}
void renderNormalGame(SDL_Renderer* renderer)
{
    if (!winner && !endTimer)
    {
        renderBall(renderer);
        renderPalette(renderer);
        renderTimers(renderer);
    }
    renderScores(renderer, winner);
 
}
void destroyTexturesNormalGame()
{
    SDL_DestroyTexture(textureBall);
    destroyTexturePaddles();
    destroyTextureScoresTimers();
}


//////////////////////////
///Funciones Extra
//////////////////////////

void saveFile()
{
    fstream lastGameStats;
    lastGameStats.open("LastGame.txt", ios::out);

    vector<string> resultados;
    resultados.push_back("Puntaje Jugador 1: " + to_string(intScores[0]) + " Puntos");
    resultados.push_back("Puntaje Jugador 2: " + to_string(intScores[1]) + " Puntos");
    resultados.push_back("Tiempo Restante: " + to_string(timerGame[0]) + " Segundos");
    for (int i = 0; i < resultados.size(); i++)
    {
        lastGameStats << resultados[i] << endl;
    }
}

void reset(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
    winner = false;
    saveFile();
    setupNormalGame(WINDOW_WIDTH, WINDOW_HEIGHT);
}