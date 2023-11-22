#pragma once
/////////////////
///True or False
/////////////////

#define FALSE 0 
#define TRUE 1

///////////////
///Resolutions
///////////////

#define WINDOW_WIDTH 1920 //Constante de Ancho
#define WINDOW_HEIGHT 1080 //Constante de Altura

///////
///FPS
///////

#define FPS 144 //Limite de fotogramas deseado
#define FRAME_TARGET_TIME (1000/FPS) //Frame duration between miliseconds.
float time_to_wait;//Delay de Fotogramas, limitador.
float delta_time; //Factor de fotogramas por segundo
Uint32 lastFrameTime = 0;//Factor de diferencia entre ultimo fotograma.

/////////////////////
///Funcionalidad SDL
/////////////////////

int game_is_running = TRUE; //TRUE= Funciona. FALSE= ERROR, Finaliza Gameloop.
SDL_Window* window = NULL;//Generacion de ventana
SDL_Renderer* renderer = NULL;//Generacion de render

bool gameStart = false;