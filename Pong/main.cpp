#include <stdio.h> //printf,NULL
#include <stdlib.h> //Rand
#include <SDL.h> //Libreria SDL
#include <SDL_image.h> //SDL Imagenes
#include <SDL_ttf.h> //SDL Textos
#include <SDL_mixer.h> //SDL Audio
#include <string> //Funcion String
#include <time.h> //Time
#include "main.h"
#include "Paletas.h"
#include "MenuTest.h"

int initialize_SDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != FALSE)
    {
        //SDL Initialization Verification.
        fprintf(stderr, "SDL Error Initialization\n");
        fprintf(stderr, SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

int initialize_window()
{

    window = SDL_CreateWindow(
        "GameLoop Pong",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN
    ); //(const char *title, int x, int y, int w, int h, Uint32 flags)


    //Window Initialization Verification
    if (!window)
    {
        fprintf(stderr, "Window Initialization Error\n");
        fprintf(stderr, SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

int initialize_renderer()
{
    renderer = SDL_CreateRenderer(
        window, //Window Name
        -1, //Driver to utilize
        0 //Flags            
    );

    //Renderer Initialization Verification
    if (!renderer)
    {
        fprintf(stderr, "Renderer Error Initialization\n");
        fprintf(stderr, SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

int initialize_SDLImg()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        //SDL_image Initialization Verification.
        fprintf(stderr, "SDL_Image Error Initialization\n");
        fprintf(stderr, SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

int initialize_SDLTtf()
{
    if (TTF_Init())
    {
        //SDL_text Initialization Verification.
        fprintf(stderr, "TTF_Init Error Initialization\n");
        fprintf(stderr, TTF_GetError());
        return FALSE;
    }
    return TRUE;
}

int initialize_SDLMixer()
{
    //SDL_Mixer Initialization Verification.
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)) //Frecuencia, Formato de Audio, Canales, Tamaño de las muestras de audio.
    {
        fprintf(stderr, "SDL_Mixer Error Initialization\n");
        return FALSE;
    }
    return TRUE;
}

void process_input()
{
    //KeyInputs
    SDL_Event inputEvent;
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&inputEvent))
    {
        if (inputEvent.type == SDL_QUIT)
        {
            game_is_running = FALSE;
        }
        if (inputEvent.type == SDL_KEYDOWN)
        {
            if (inputEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                game_is_running = FALSE;
            }
            if (inputEvent.key.keysym.sym == SDLK_SPACE)
            {
                gameStart = true;
            }
        }
    }

    //Jugador Izq
    if (keyboardState[SDL_SCANCODE_W])
    {
        paddleLeft.y -= paddleSpeed * delta_time;
    }
    if (keyboardState[SDL_SCANCODE_S])
    {
        paddleLeft.y += paddleSpeed * delta_time;
    }

    //Jugador Der
    if (keyboardState[SDL_SCANCODE_I])
    {
        paddleRight.y -= paddleSpeed * delta_time;
    }
    if (keyboardState[SDL_SCANCODE_K])
    {
        paddleRight.y += paddleSpeed * delta_time;
    }
}

void setup()
{
    ///////////////////
    ///Inicializadores
    ///////////////////

    initializeTextures(renderer);
    initializeMusic();
    initializeSFX();
    Mix_PlayMusic(music, -1);
    setupPrincipalMenu(WINDOW_WIDTH, WINDOW_HEIGHT);
    setupNormalGame(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void update()
{
    ////////////////////
    //FrameRate Limiter
    ////////////////////

    time_to_wait = (float)FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(time_to_wait);
    }
    delta_time = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    lastFrameTime = SDL_GetTicks();

    ////////////////////////
    ///Update Menu Principal
    ////////////////////////
    
    if(gameStart == false)
    {
        updatePrincipalMenu(renderer);
    }
    else
    {
        updateNormalGame(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, delta_time);
    }
}

void render()
{
    //////////////////////
    ///Dibujado de Fondo
    //////////////////////

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    ////////////////////////////////
    ///Dibujado de Textos y Objetos
    ////////////////////////////////

    
    if(gameStart == false)
    {
        renderPrincipalMenu(renderer);
    }
    else
    {
        renderNormalGame(renderer);
    }

    ///////////
    ///Buffers
    ///////////

    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    /////////////////////////
    ///Liberacion de Memoria
    /////////////////////////
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    destroyTexturesPrincipalMenu();
    destroyTexturesNormalGame();
    destroyMusicSFX();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    game_is_running = initialize_SDL() & initialize_window() & initialize_renderer() & initialize_SDLImg() & initialize_SDLTtf() & initialize_SDLMixer();

    setup();

    while (game_is_running) //While no errors
    {
        process_input();
        update();
        render();
    }
    destroy_window();
    return TRUE;
}