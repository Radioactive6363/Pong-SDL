#include <stdio.h> //printf,NULL
#include <stdlib.h> //Rand
#include <SDL.h> //Libreria SDL
#include <SDL_image.h> //SDL Imagenes
#include <SDL_ttf.h> //SDL Textos
#include <string> //Funcion String
#include <time.h> //Time
#include "main.h"
#include "Ball.h"
#include "Score.h"
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
        //SDL_image Initialization Verification.
        fprintf(stderr, "TTF_Init Error Initialization\n");
        fprintf(stderr, TTF_GetError());
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
            if (keyboardState[SDL_SCANCODE_W])
            {
                paddleLeft.y -= paddleSpeed * delta_time;
            }
            if (keyboardState[SDL_SCANCODE_S])
            {
                paddleLeft.y += paddleSpeed * delta_time;
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
    //////////////////////////
    // Inicializacion Texturas
    //////////////////////////
    initializeTextures(renderer);
    setupPrincipalMenu(WINDOW_WIDTH, WINDOW_HEIGHT);
    setupJuegoNormal(WINDOW_WIDTH, WINDOW_HEIGHT);
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
    updatePrincipalMenu(renderer);
    updateJuegoNormal(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, delta_time);
}

void render()
{
    SDL_Rect rectStart = {
        (int)txtStart.x,
        (int)txtStart.y,
        (int)txtStart.width,
        (int)txtStart.height
    };
    SDL_Rect rectOptions = {
        (int)txtOptions.x,
        (int)txtOptions.y,
        (int)txtOptions.width,
        (int)txtOptions.height
    };
    SDL_Rect rectQuit = {
        (int)txtQuit.x,
        (int)txtQuit.y,
        (int)txtQuit.width,
        (int)txtQuit.height
    };
    SDL_Rect rectBall = {
        (int)ballimg.x,
        (int)ballimg.y,
        (int)ballimg.width,
        (int)ballimg.height
    };
    SDL_Rect rectPaddle_Left = {
        (int)paddleLeft.x,
        (int)paddleLeft.y,
        (int)paddleLeft.width,
        (int)paddleLeft.height
    };
    SDL_Rect rectPaddle_Right = {
        (int)paddleRight.x,
        (int)paddleRight.y,
        (int)paddleRight.width,
        (int)paddleRight.height
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureStart, nullptr, &rectStart);
    SDL_RenderCopy(renderer, textureOptions, nullptr, &rectOptions);
    SDL_RenderCopy(renderer, textureQuit, nullptr, &rectQuit);
    SDL_RenderCopy(renderer, textureBall, nullptr, &rectBall);
    SDL_RenderCopy(renderer, texturePaddle, nullptr, &rectPaddle_Left);
    SDL_RenderCopy(renderer, texturePaddle, nullptr, &rectPaddle_Right);
    SDL_RenderCopy(renderer, textureScoreLeft, nullptr, &rectScore_Left);
    SDL_RenderCopy(renderer, textureScoreRight, nullptr, &rectScore_Right);

    //Buffers
    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(textureBall);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    game_is_running = initialize_SDL() & initialize_window() & initialize_renderer() & initialize_SDLImg() & initialize_SDLTtf();

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