#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include "../SDL2/include/SDL2/SDL_main.h"
#endif
#include <stdio.h>
#include <SDL.h>

#define OK 0
#define ERR -1
#define SIN_MEM 2
#define MAX_LINE 15
#define VIVE 10
#define MUERE 0

/// SDL2
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius);

/// matriz con memoria dinamica
char** crearMatriz(int cf, int cc);
void destruirMatriz(char** matriz, int cf);

/// generadores
void aleatorio(char** matriz, const int cf, const int cc);
int leerArchGeneradores(const char* nomArch, char** matriz, const int cf, const int cc);
/*void planeador(char** matriz, const int cf, const int cc);
void sapo(char** matriz, const int cf, const int cc);
void pulsar(char** matriz, const int cf, const int cc);
void mickeyMouse(char** matriz, const int cf, const int cc); // adicional
void canionDePlaneadores(char** matriz, const int cf, const int cc);
void biGun(char** matriz, const int cf, const int cc); // adicional
void molinete(char** matriz, const int cf, const int cc); // adicional
void G4P2H1V0(char** matriz, const int cf, const int cc); // adicional
void filler(char** matriz, const int cf, const int cc); // adicional
void I24P37(char** matriz, const int cf, const int cc); // adicional
void Pentadecathlon(char** matriz, const int cf, const int cc); // adicional*/

/// recorren la matriz
void inicializarMatriz(char** matriz, const int cf, const int cc);
void proximaJugada(char** matriz, const int cf, const int cc);
void mostrarYActualizarMatriz(SDL_Renderer* renderer, SDL_Rect fillRect, char** matriz, const int cf, const int cc, const int tamanioDePixel);

/// llama al generador correspondiente segun la opcion
void comienzo(char** matriz, const int cf, const int cc, const int opcion);

#endif // MATRICES_H_INCLUDED
