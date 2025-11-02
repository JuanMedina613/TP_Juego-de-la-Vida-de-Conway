#include <stdlib.h>
#include <time.h>
#include "matrices.h"
#ifdef __MINGW32__
#define SDL_MAIN_HANDLED
#include "../SDL2/include/SDL2/SDL_main.h"
#endif

#include <SDL.h>

char** crearMatriz(int cf, int cc)
{
    char** matriz;
    int i, j;

    matriz = malloc(sizeof(char*) * cf);
    if (!matriz)
        return NULL;

    for (i = 0; i < cf; i++)
    {
        matriz[i] = malloc(sizeof(char) * cc);
        if (!matriz[i])
        {
            for (j = 0; j < i; j++)
                free(matriz[j]);

            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

void destruirMatriz(char** matriz, int cf)
{
    int i;
    if (matriz)
    {
        for (i = 0; i < cf; i++)
            free(matriz[i]);

        free(matriz);

        matriz = NULL;
    }
}

void aleatorio(char** matriz, const int cf, const int cc)
{
    int i, j, random;

    srand(time(NULL));

    for (i = 0; i < cf; i++)
        for (j = 0; j < cc; j++)
        {
            random = rand() %2;
            if (random == 1)
            {
                random = rand() %2;
                if (random == 1)
                    matriz[i][j] = VIVE;
                else
                    matriz[i][j] = MUERE;
            }
            else
                matriz[i][j] = MUERE;
        }
}

int leerArchGeneradores(const char* nomArch, char** matriz, const int cf, const int cc)
{
    int filas, columnas;
    char linea[MAX_LINE];
    FILE* pf = fopen(nomArch, "rt");

    if (!pf)
        return 0;

    fgets(linea, MAX_LINE-1, pf); /// omite la 1ra linea del archivo (significados de c/ campo)

    while (fgets(linea, MAX_LINE-1, pf))
    {
        sscanf(linea, "%d|%d", &filas, &columnas);
        matriz[cf/2+filas][cc/2+columnas] = VIVE;
    }

    return 1;
}

/*void planeador(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-1][cc/2] = VIVE;
    matriz[cf/2][cc/2+1] = VIVE;
    matriz[cf/2+1][cc/2-1] = VIVE;
    matriz[cf/2+1][cc/2] = VIVE;
    matriz[cf/2+1][cc/2+1] = VIVE;
}

void sapo(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-1][cc/2-2] = VIVE;
    matriz[cf/2-1][cc/2-1] = VIVE;
    matriz[cf/2-1][cc/2] = VIVE;
    matriz[cf/2][cc/2-1] = VIVE;
    matriz[cf/2][cc/2] = VIVE;
    matriz[cf/2][cc/2+1] = VIVE;
}

void pulsar(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-6][cc/2-2] = VIVE;
    matriz[cf/2-6][cc/2-3] = VIVE;
    matriz[cf/2-6][cc/2-4] = VIVE;
    matriz[cf/2-6][cc/2+2] = VIVE;
    matriz[cf/2-6][cc/2+3] = VIVE;
    matriz[cf/2-6][cc/2+4] = VIVE;

    matriz[cf/2-4][cc/2-1] = VIVE;
    matriz[cf/2-4][cc/2-6] = VIVE;
    matriz[cf/2-4][cc/2+1] = VIVE;
    matriz[cf/2-4][cc/2+6] = VIVE;

    matriz[cf/2-3][cc/2-1] = VIVE;
    matriz[cf/2-3][cc/2-6] = VIVE;
    matriz[cf/2-3][cc/2+1] = VIVE;
    matriz[cf/2-3][cc/2+6] = VIVE;

    matriz[cf/2-2][cc/2-1] = VIVE;
    matriz[cf/2-2][cc/2-6] = VIVE;
    matriz[cf/2-2][cc/2+1] = VIVE;
    matriz[cf/2-2][cc/2+6] = VIVE;

    matriz[cf/2-1][cc/2-2] = VIVE;
    matriz[cf/2-1][cc/2-3] = VIVE;
    matriz[cf/2-1][cc/2-4] = VIVE;
    matriz[cf/2-1][cc/2+2] = VIVE;
    matriz[cf/2-1][cc/2+3] = VIVE;
    matriz[cf/2-1][cc/2+4] = VIVE;

    matriz[cf/2+1][cc/2-2] = VIVE;
    matriz[cf/2+1][cc/2-3] = VIVE;
    matriz[cf/2+1][cc/2-4] = VIVE;
    matriz[cf/2+1][cc/2+2] = VIVE;
    matriz[cf/2+1][cc/2+3] = VIVE;
    matriz[cf/2+1][cc/2+4] = VIVE;

    matriz[cf/2+2][cc/2-1] = VIVE;
    matriz[cf/2+2][cc/2-6] = VIVE;
    matriz[cf/2+2][cc/2+1] = VIVE;
    matriz[cf/2+2][cc/2+6] = VIVE;

    matriz[cf/2+3][cc/2-1] = VIVE;
    matriz[cf/2+3][cc/2-6] = VIVE;
    matriz[cf/2+3][cc/2+1] = VIVE;
    matriz[cf/2+3][cc/2+6] = VIVE;

    matriz[cf/2+4][cc/2-1] = VIVE;
    matriz[cf/2+4][cc/2-6] = VIVE;
    matriz[cf/2+4][cc/2+1] = VIVE;
    matriz[cf/2+4][cc/2+6] = VIVE;

    matriz[cf/2+6][cc/2-2] = VIVE;
    matriz[cf/2+6][cc/2-3] = VIVE;
    matriz[cf/2+6][cc/2-4] = VIVE;
    matriz[cf/2+6][cc/2+2] = VIVE;
    matriz[cf/2+6][cc/2+3] = VIVE;
    matriz[cf/2+6][cc/2+4] = VIVE;
}

void mickeyMouse(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-3][cc/2-3] = VIVE;
    matriz[cf/2-3][cc/2-4] = VIVE;
    matriz[cf/2-3][cc/2+2] = VIVE;
    matriz[cf/2-3][cc/2+3] = VIVE;

    matriz[cf/2-2][cc/2-2] = VIVE;
    matriz[cf/2-2][cc/2-5] = VIVE;
    matriz[cf/2-2][cc/2+1] = VIVE;
    matriz[cf/2-2][cc/2+4] = VIVE;

    matriz[cf/2-1][cc/2] = VIVE;
    matriz[cf/2-1][cc/2-1] = VIVE;
    matriz[cf/2-1][cc/2-2] = VIVE;
    matriz[cf/2-1][cc/2-5] = VIVE;
    matriz[cf/2-1][cc/2+1] = VIVE;
    matriz[cf/2-1][cc/2+4] = VIVE;

    matriz[cf/2][cc/2-3] = VIVE;
    matriz[cf/2][cc/2-4] = VIVE;
    matriz[cf/2][cc/2+2] = VIVE;
    matriz[cf/2][cc/2+3] = VIVE;

    matriz[cf/2+1][cc/2] = VIVE;
    matriz[cf/2+1][cc/2-1] = VIVE;
    matriz[cf/2+1][cc/2-2] = VIVE;
    matriz[cf/2+1][cc/2+1] = VIVE;

    matriz[cf/2+2][cc/2-2] = VIVE;
    matriz[cf/2+2][cc/2+1] = VIVE;

    matriz[cf/2+3][cc/2] = VIVE;
    matriz[cf/2+3][cc/2-1] = VIVE;
}

void canionDePlaneadores(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-4][cc/2+7] = VIVE;

    matriz[cf/2-3][cc/2+5] = VIVE;
    matriz[cf/2-3][cc/2+7] = VIVE;

    matriz[cf/2-2][cc/2-5] = VIVE;
    matriz[cf/2-2][cc/2-4] = VIVE;
    matriz[cf/2-2][cc/2+3] = VIVE;
    matriz[cf/2-2][cc/2+4] = VIVE;
    matriz[cf/2-2][cc/2+17] = VIVE;
    matriz[cf/2-2][cc/2+18] = VIVE;

    matriz[cf/2-1][cc/2-6] = VIVE;
    matriz[cf/2-1][cc/2-2] = VIVE;
    matriz[cf/2-1][cc/2+3] = VIVE;
    matriz[cf/2-1][cc/2+4] = VIVE;
    matriz[cf/2-1][cc/2+17] = VIVE;
    matriz[cf/2-1][cc/2+18] = VIVE;

    matriz[cf/2][cc/2-16] = VIVE;
    matriz[cf/2][cc/2-17] = VIVE;
    matriz[cf/2][cc/2-7] = VIVE;
    matriz[cf/2][cc/2-1] = VIVE;
    matriz[cf/2][cc/2+3] = VIVE;
    matriz[cf/2][cc/2+4] = VIVE;

    matriz[cf/2+1][cc/2-16] = VIVE;
    matriz[cf/2+1][cc/2-17] = VIVE;
    matriz[cf/2+1][cc/2-7] = VIVE;
    matriz[cf/2+1][cc/2-3] = VIVE;
    matriz[cf/2+1][cc/2-1] = VIVE;
    matriz[cf/2+1][cc/2] = VIVE;
    matriz[cf/2+1][cc/2+5] = VIVE;
    matriz[cf/2+1][cc/2+7] = VIVE;

    matriz[cf/2+2][cc/2-7] = VIVE;
    matriz[cf/2+2][cc/2-1] = VIVE;
    matriz[cf/2+2][cc/2+7] = VIVE;

    matriz[cf/2+3][cc/2-6] = VIVE;
    matriz[cf/2+3][cc/2-2] = VIVE;

    matriz[cf/2+4][cc/2-5] = VIVE;
    matriz[cf/2+4][cc/2-4] = VIVE;
}

void biGun(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-7][cc/2-14] = VIVE;

    matriz[cf/2-6][cc/2-14] = VIVE;
    matriz[cf/2-6][cc/2-15] = VIVE;

    matriz[cf/2-5][cc/2-15] = VIVE;
    matriz[cf/2-5][cc/2-16] = VIVE;

    matriz[cf/2-4][cc/2-10] = VIVE;
    matriz[cf/2-4][cc/2-11] = VIVE;
    matriz[cf/2-4][cc/2-14] = VIVE;
    matriz[cf/2-4][cc/2-15] = VIVE;

    matriz[cf/2-3][cc/2+13] = VIVE;

    matriz[cf/2-2][cc/2+13] = VIVE;
    matriz[cf/2-2][cc/2+14] = VIVE;
    matriz[cf/2-2][cc/2+23] = VIVE;
    matriz[cf/2-2][cc/2+24] = VIVE;

    matriz[cf/2-1][cc/2+14] = VIVE;
    matriz[cf/2-1][cc/2+15] = VIVE;
    matriz[cf/2-1][cc/2+23] = VIVE;
    matriz[cf/2-1][cc/2+24] = VIVE;

    matriz[cf/2][cc/2-10] = VIVE;
    matriz[cf/2][cc/2-11] = VIVE;
    matriz[cf/2][cc/2-14] = VIVE;
    matriz[cf/2][cc/2-15] = VIVE;
    matriz[cf/2][cc/2+9] = VIVE;
    matriz[cf/2][cc/2+10] = VIVE;
    matriz[cf/2][cc/2+13] = VIVE;
    matriz[cf/2][cc/2+14] = VIVE;

    matriz[cf/2+1][cc/2-15] = VIVE;
    matriz[cf/2+1][cc/2-16] = VIVE;
    matriz[cf/2+1][cc/2-24] = VIVE;
    matriz[cf/2+1][cc/2-25] = VIVE;

    matriz[cf/2+2][cc/2-14] = VIVE;
    matriz[cf/2+2][cc/2-15] = VIVE;
    matriz[cf/2+2][cc/2-24] = VIVE;
    matriz[cf/2+2][cc/2-25] = VIVE;

    matriz[cf/2+3][cc/2-14] = VIVE;

    matriz[cf/2+4][cc/2+9] = VIVE;
    matriz[cf/2+4][cc/2+10] = VIVE;
    matriz[cf/2+4][cc/2+13] = VIVE;
    matriz[cf/2+4][cc/2+14] = VIVE;

    matriz[cf/2+5][cc/2+14] = VIVE;
    matriz[cf/2+5][cc/2+15] = VIVE;

    matriz[cf/2+6][cc/2+13] = VIVE;
    matriz[cf/2+6][cc/2+14] = VIVE;

    matriz[cf/2+7][cc/2+13] = VIVE;
}

void molinete(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-4][cc/2] = VIVE;
    matriz[cf/2-4][cc/2-1] = VIVE;
    matriz[cf/2-4][cc/2-2] = VIVE;
    matriz[cf/2-4][cc/2-3] = VIVE;
    matriz[cf/2-4][cc/2-4] = VIVE;
    matriz[cf/2-4][cc/2+1] = VIVE;
    matriz[cf/2-4][cc/2+3] = VIVE;
    matriz[cf/2-4][cc/2+4] = VIVE;

    matriz[cf/2-3][cc/2] = VIVE;
    matriz[cf/2-3][cc/2-1] = VIVE;
    matriz[cf/2-3][cc/2-2] = VIVE;
    matriz[cf/2-3][cc/2-3] = VIVE;
    matriz[cf/2-3][cc/2-4] = VIVE;
    matriz[cf/2-3][cc/2+1] = VIVE;
    matriz[cf/2-3][cc/2+3] = VIVE;
    matriz[cf/2-3][cc/2+4] = VIVE;

    matriz[cf/2-2][cc/2+3] = VIVE;
    matriz[cf/2-2][cc/2+4] = VIVE;

    matriz[cf/2-1][cc/2-3] = VIVE;
    matriz[cf/2-1][cc/2-4] = VIVE;
    matriz[cf/2-1][cc/2+3] = VIVE;
    matriz[cf/2-1][cc/2+4] = VIVE;

    matriz[cf/2][cc/2-3] = VIVE;
    matriz[cf/2][cc/2-4] = VIVE;
    matriz[cf/2][cc/2+3] = VIVE;
    matriz[cf/2][cc/2+4] = VIVE;

    matriz[cf/2+1][cc/2-3] = VIVE;
    matriz[cf/2+1][cc/2-4] = VIVE;
    matriz[cf/2+1][cc/2+3] = VIVE;
    matriz[cf/2+1][cc/2+4] = VIVE;

    matriz[cf/2+2][cc/2-3] = VIVE;
    matriz[cf/2+2][cc/2-4] = VIVE;

    matriz[cf/2+3][cc/2] = VIVE;
    matriz[cf/2+3][cc/2-1] = VIVE;
    matriz[cf/2+3][cc/2-3] = VIVE;
    matriz[cf/2+3][cc/2-4] = VIVE;
    matriz[cf/2+3][cc/2+1] = VIVE;
    matriz[cf/2+3][cc/2+2] = VIVE;
    matriz[cf/2+3][cc/2+3] = VIVE;
    matriz[cf/2+3][cc/2+4] = VIVE;

    matriz[cf/2+4][cc/2] = VIVE;
    matriz[cf/2+4][cc/2-1] = VIVE;
    matriz[cf/2+4][cc/2-3] = VIVE;
    matriz[cf/2+4][cc/2-4] = VIVE;
    matriz[cf/2+4][cc/2+1] = VIVE;
    matriz[cf/2+4][cc/2+2] = VIVE;
    matriz[cf/2+4][cc/2+3] = VIVE;
    matriz[cf/2+4][cc/2+4] = VIVE;
}

void G4P2H1V0(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-7][cc/2-7] = VIVE;
    matriz[cf/2-7][cc/2-8] = VIVE;
    matriz[cf/2-7][cc/2-9] = VIVE;
    matriz[cf/2-7][cc/2+9] = VIVE;
    matriz[cf/2-7][cc/2+10] = VIVE;
    matriz[cf/2-7][cc/2+11] = VIVE;

    matriz[cf/2-6][cc/2-6] = VIVE;
    matriz[cf/2-6][cc/2-10] = VIVE;
    matriz[cf/2-6][cc/2+8] = VIVE;
    matriz[cf/2-6][cc/2+12] = VIVE;

    matriz[cf/2-5][cc/2-5] = VIVE;
    matriz[cf/2-5][cc/2-10] = VIVE;
    matriz[cf/2-5][cc/2-11] = VIVE;
    matriz[cf/2-5][cc/2+7] = VIVE;
    matriz[cf/2-5][cc/2+12] = VIVE;
    matriz[cf/2-5][cc/2+13] = VIVE;

    matriz[cf/2-4][cc/2+1] = VIVE;
    matriz[cf/2-4][cc/2] = VIVE;
    matriz[cf/2-4][cc/2-4] = VIVE;
    matriz[cf/2-4][cc/2-5] = VIVE;
    matriz[cf/2-4][cc/2-7] = VIVE;
    matriz[cf/2-4][cc/2-8] = VIVE;
    matriz[cf/2-4][cc/2-10] = VIVE;
    matriz[cf/2-4][cc/2-12] = VIVE;
    matriz[cf/2-4][cc/2+2] = VIVE;
    matriz[cf/2-4][cc/2+6] = VIVE;
    matriz[cf/2-4][cc/2+7] = VIVE;
    matriz[cf/2-4][cc/2+9] = VIVE;
    matriz[cf/2-4][cc/2+10] = VIVE;
    matriz[cf/2-4][cc/2+12] = VIVE;
    matriz[cf/2-4][cc/2+14] = VIVE;

    matriz[cf/2-3][cc/2+1] = VIVE;
    matriz[cf/2-3][cc/2] = VIVE;
    matriz[cf/2-3][cc/2-2] = VIVE;
    matriz[cf/2-3][cc/2-3] = VIVE;
    matriz[cf/2-3][cc/2-5] = VIVE;
    matriz[cf/2-3][cc/2-10] = VIVE;
    matriz[cf/2-3][cc/2-12] = VIVE;
    matriz[cf/2-3][cc/2-13] = VIVE;
    matriz[cf/2-3][cc/2+2] = VIVE;
    matriz[cf/2-3][cc/2+4] = VIVE;
    matriz[cf/2-3][cc/2+5] = VIVE;
    matriz[cf/2-3][cc/2+7] = VIVE;
    matriz[cf/2-3][cc/2+12] = VIVE;
    matriz[cf/2-3][cc/2+14] = VIVE;
    matriz[cf/2-3][cc/2+15] = VIVE;

    matriz[cf/2-2][cc/2] = VIVE;
    matriz[cf/2-2][cc/2-5] = VIVE;
    matriz[cf/2-2][cc/2-9] = VIVE;
    matriz[cf/2-2][cc/2-14] = VIVE;
    matriz[cf/2-2][cc/2+2] = VIVE;
    matriz[cf/2-2][cc/2+7] = VIVE;
    matriz[cf/2-2][cc/2+11] = VIVE;
    matriz[cf/2-2][cc/2+16] = VIVE;

    matriz[cf/2-1][cc/2-2] = VIVE;
    matriz[cf/2-1][cc/2+4] = VIVE;

    matriz[cf/2][cc/2-4] = VIVE;
    matriz[cf/2][cc/2-5] = VIVE;
    matriz[cf/2][cc/2-13] = VIVE;
    matriz[cf/2][cc/2-14] = VIVE;
    matriz[cf/2][cc/2+6] = VIVE;
    matriz[cf/2][cc/2+7] = VIVE;
    matriz[cf/2][cc/2+15] = VIVE;
    matriz[cf/2][cc/2+16] = VIVE;
}

void filler(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-17][cc/2-5] = VIVE;
    matriz[cf/2-17][cc/2-6] = VIVE;
    matriz[cf/2-17][cc/2-7] = VIVE;
    matriz[cf/2-17][cc/2+5] = VIVE;
    matriz[cf/2-17][cc/2+6] = VIVE;
    matriz[cf/2-17][cc/2+7] = VIVE;

    matriz[cf/2-16][cc/2-4] = VIVE;
    matriz[cf/2-16][cc/2-7] = VIVE;
    matriz[cf/2-16][cc/2+5] = VIVE;
    matriz[cf/2-16][cc/2+8] = VIVE;

    matriz[cf/2-15][cc/2] = VIVE;
    matriz[cf/2-15][cc/2-7] = VIVE;
    matriz[cf/2-15][cc/2+5] = VIVE;

    matriz[cf/2-14][cc/2] = VIVE;
    matriz[cf/2-14][cc/2-1] = VIVE;
    matriz[cf/2-14][cc/2-7] = VIVE;
    matriz[cf/2-14][cc/2+1] = VIVE;
    matriz[cf/2-14][cc/2+5] = VIVE;

    matriz[cf/2-13][cc/2-1] = VIVE;
    matriz[cf/2-13][cc/2-7] = VIVE;
    matriz[cf/2-13][cc/2+1] = VIVE;
    matriz[cf/2-13][cc/2+2] = VIVE;
    matriz[cf/2-13][cc/2+5] = VIVE;

    matriz[cf/2-12][cc/2] = VIVE;
    matriz[cf/2-12][cc/2-7] = VIVE;
    matriz[cf/2-12][cc/2+1] = VIVE;
    matriz[cf/2-12][cc/2+2] = VIVE;
    matriz[cf/2-12][cc/2+5] = VIVE;

    matriz[cf/2-11][cc/2] = VIVE;
    matriz[cf/2-11][cc/2-3] = VIVE;
    matriz[cf/2-11][cc/2-6] = VIVE;
    matriz[cf/2-11][cc/2+1] = VIVE;
    matriz[cf/2-11][cc/2+2] = VIVE;
    matriz[cf/2-11][cc/2+6] = VIVE;

    matriz[cf/2-10][cc/2] = VIVE;
    matriz[cf/2-10][cc/2-4] = VIVE;
    matriz[cf/2-10][cc/2+1] = VIVE;
    matriz[cf/2-10][cc/2+2] = VIVE;

    matriz[cf/2-9][cc/2-3] = VIVE;
    matriz[cf/2-9][cc/2+3] = VIVE;
    matriz[cf/2-9][cc/2+4] = VIVE;

    matriz[cf/2-8][cc/2-1] = VIVE;
    matriz[cf/2-8][cc/2-2] = VIVE;

    matriz[cf/2-7][cc/2-2] = VIVE;

    matriz[cf/2-6][cc/2] = VIVE;
    matriz[cf/2-6][cc/2-1] = VIVE;

    matriz[cf/2-5][cc/2] = VIVE;
    matriz[cf/2-5][cc/2-2] = VIVE;
    matriz[cf/2-5][cc/2-11] = VIVE;
    matriz[cf/2-5][cc/2+2] = VIVE;
    matriz[cf/2-5][cc/2+11] = VIVE;

    matriz[cf/2-4][cc/2] = VIVE;
    matriz[cf/2-4][cc/2-2] = VIVE;
    matriz[cf/2-4][cc/2-4] = VIVE;
    matriz[cf/2-4][cc/2-6] = VIVE;
    matriz[cf/2-4][cc/2-12] = VIVE;
    matriz[cf/2-4][cc/2+2] = VIVE;
    matriz[cf/2-4][cc/2+3] = VIVE;
    matriz[cf/2-4][cc/2+6] = VIVE;
    matriz[cf/2-4][cc/2+12] = VIVE;

    matriz[cf/2-3][cc/2] = VIVE;
    matriz[cf/2-3][cc/2-4] = VIVE;
    matriz[cf/2-3][cc/2-5] = VIVE;
    matriz[cf/2-3][cc/2-6] = VIVE;
    matriz[cf/2-3][cc/2-12] = VIVE;
    matriz[cf/2-3][cc/2+2] = VIVE;
    matriz[cf/2-3][cc/2+4] = VIVE;
    matriz[cf/2-3][cc/2+5] = VIVE;
    matriz[cf/2-3][cc/2+6] = VIVE;
    matriz[cf/2-3][cc/2+12] = VIVE;

    matriz[cf/2-2][cc/2-1] = VIVE;
    matriz[cf/2-2][cc/2-2] = VIVE;
    matriz[cf/2-2][cc/2-6] = VIVE;
    matriz[cf/2-2][cc/2-8] = VIVE;
    matriz[cf/2-2][cc/2-9] = VIVE;
    matriz[cf/2-2][cc/2-10] = VIVE;
    matriz[cf/2-2][cc/2-11] = VIVE;
    matriz[cf/2-2][cc/2-12] = VIVE;
    matriz[cf/2-2][cc/2+2] = VIVE;
    matriz[cf/2-2][cc/2+6] = VIVE;
    matriz[cf/2-2][cc/2+8] = VIVE;
    matriz[cf/2-2][cc/2+9] = VIVE;
    matriz[cf/2-2][cc/2+10] = VIVE;
    matriz[cf/2-2][cc/2+11] = VIVE;
    matriz[cf/2-2][cc/2+12] = VIVE;

    matriz[cf/2-1][cc/2-2] = VIVE;
    matriz[cf/2-1][cc/2-4] = VIVE;
    matriz[cf/2-1][cc/2+1] = VIVE;
    matriz[cf/2-1][cc/2+2] = VIVE;
    matriz[cf/2-1][cc/2+4] = VIVE;

    matriz[cf/2][cc/2] = VIVE;
    matriz[cf/2][cc/2-2] = VIVE;
    matriz[cf/2][cc/2-4] = VIVE;
    matriz[cf/2][cc/2-5] = VIVE;
    matriz[cf/2][cc/2+2] = VIVE;
    matriz[cf/2][cc/2+4] = VIVE;
    matriz[cf/2][cc/2+5] = VIVE;

    matriz[cf/2+1][cc/2-1] = VIVE;
    matriz[cf/2+1][cc/2-2] = VIVE;
    matriz[cf/2+1][cc/2-4] = VIVE;
    matriz[cf/2+1][cc/2+2] = VIVE;
    matriz[cf/2+1][cc/2+4] = VIVE;

    matriz[cf/2+2][cc/2-2] = VIVE;
    matriz[cf/2+2][cc/2-6] = VIVE;
    matriz[cf/2+2][cc/2-8] = VIVE;
    matriz[cf/2+2][cc/2-9] = VIVE;
    matriz[cf/2+2][cc/2-10] = VIVE;
    matriz[cf/2+2][cc/2-11] = VIVE;
    matriz[cf/2+2][cc/2-12] = VIVE;
    matriz[cf/2+2][cc/2+1] = VIVE;
    matriz[cf/2+2][cc/2+2] = VIVE;
    matriz[cf/2+2][cc/2+6] = VIVE;
    matriz[cf/2+2][cc/2+8] = VIVE;
    matriz[cf/2+2][cc/2+9] = VIVE;
    matriz[cf/2+2][cc/2+10] = VIVE;
    matriz[cf/2+2][cc/2+11] = VIVE;
    matriz[cf/2+2][cc/2+12] = VIVE;

    matriz[cf/2+3][cc/2] = VIVE;
    matriz[cf/2+3][cc/2-2] = VIVE;
    matriz[cf/2+3][cc/2-4] = VIVE;
    matriz[cf/2+3][cc/2-5] = VIVE;
    matriz[cf/2+3][cc/2-6] = VIVE;
    matriz[cf/2+3][cc/2-12] = VIVE;
    matriz[cf/2+3][cc/2+4] = VIVE;
    matriz[cf/2+3][cc/2+5] = VIVE;
    matriz[cf/2+3][cc/2+6] = VIVE;
    matriz[cf/2+3][cc/2+12] = VIVE;

    matriz[cf/2+4][cc/2] = VIVE;
    matriz[cf/2+4][cc/2-2] = VIVE;
    matriz[cf/2+4][cc/2-3] = VIVE;
    matriz[cf/2+4][cc/2-6] = VIVE;
    matriz[cf/2+4][cc/2-12] = VIVE;
    matriz[cf/2+4][cc/2+2] = VIVE;
    matriz[cf/2+4][cc/2+4] = VIVE;
    matriz[cf/2+4][cc/2+6] = VIVE;
    matriz[cf/2+4][cc/2+12] = VIVE;

    matriz[cf/2+5][cc/2] = VIVE;
    matriz[cf/2+5][cc/2-2] = VIVE;
    matriz[cf/2+5][cc/2-11] = VIVE;
    matriz[cf/2+5][cc/2+2] = VIVE;
    matriz[cf/2+5][cc/2+11] = VIVE;

    matriz[cf/2+6][cc/2] = VIVE;
    matriz[cf/2+6][cc/2+1] = VIVE;

    matriz[cf/2+7][cc/2+2] = VIVE;

    matriz[cf/2+8][cc/2+1] = VIVE;
    matriz[cf/2+8][cc/2+2] = VIVE;

    matriz[cf/2+9][cc/2-3] = VIVE;
    matriz[cf/2+9][cc/2-4] = VIVE;
    matriz[cf/2+9][cc/2+3] = VIVE;

    matriz[cf/2+10][cc/2] = VIVE;
    matriz[cf/2+10][cc/2-1] = VIVE;
    matriz[cf/2+10][cc/2-2] = VIVE;
    matriz[cf/2+10][cc/2+4] = VIVE;

    matriz[cf/2+11][cc/2] = VIVE;
    matriz[cf/2+11][cc/2-1] = VIVE;
    matriz[cf/2+11][cc/2-2] = VIVE;
    matriz[cf/2+11][cc/2-6] = VIVE;
    matriz[cf/2+11][cc/2+3] = VIVE;
    matriz[cf/2+11][cc/2+6] = VIVE;

    matriz[cf/2+12][cc/2] = VIVE;
    matriz[cf/2+12][cc/2-1] = VIVE;
    matriz[cf/2+12][cc/2-2] = VIVE;
    matriz[cf/2+12][cc/2-5] = VIVE;
    matriz[cf/2+12][cc/2+7] = VIVE;

    matriz[cf/2+13][cc/2-1] = VIVE;
    matriz[cf/2+13][cc/2-2] = VIVE;
    matriz[cf/2+13][cc/2-5] = VIVE;
    matriz[cf/2+13][cc/2+1] = VIVE;
    matriz[cf/2+13][cc/2+7] = VIVE;

    matriz[cf/2+14][cc/2] = VIVE;
    matriz[cf/2+14][cc/2-1] = VIVE;
    matriz[cf/2+14][cc/2-5] = VIVE;
    matriz[cf/2+14][cc/2+1] = VIVE;
    matriz[cf/2+14][cc/2+7] = VIVE;

    matriz[cf/2+15][cc/2] = VIVE;
    matriz[cf/2+15][cc/2-5] = VIVE;
    matriz[cf/2+15][cc/2+7] = VIVE;

    matriz[cf/2+16][cc/2-5] = VIVE;
    matriz[cf/2+16][cc/2-8] = VIVE;
    matriz[cf/2+16][cc/2+4] = VIVE;
    matriz[cf/2+16][cc/2+7] = VIVE;

    matriz[cf/2+17][cc/2-5] = VIVE;
    matriz[cf/2+17][cc/2-6] = VIVE;
    matriz[cf/2+17][cc/2-7] = VIVE;
    matriz[cf/2+17][cc/2+5] = VIVE;
    matriz[cf/2+17][cc/2+6] = VIVE;
    matriz[cf/2+17][cc/2+7] = VIVE;
}

void I24P37(char** matriz, const int cf, const int cc)
{
    matriz[cf/2-18][cc/2-6] = VIVE;
    matriz[cf/2-18][cc/2-7] = VIVE;
    matriz[cf/2-18][cc/2+6] = VIVE;
    matriz[cf/2-18][cc/2+7] = VIVE;

    matriz[cf/2-17][cc/2-6] = VIVE;
    matriz[cf/2-17][cc/2-7] = VIVE;
    matriz[cf/2-17][cc/2+6] = VIVE;
    matriz[cf/2-17][cc/2+7] = VIVE;

    matriz[cf/2-14][cc/2-12] = VIVE;
    matriz[cf/2-14][cc/2+12] = VIVE;

    matriz[cf/2-13][cc/2-5] = VIVE;
    matriz[cf/2-13][cc/2-11] = VIVE;
    matriz[cf/2-13][cc/2-13] = VIVE;
    matriz[cf/2-13][cc/2+5] = VIVE;
    matriz[cf/2-13][cc/2+11] = VIVE;
    matriz[cf/2-13][cc/2+13] = VIVE;

    matriz[cf/2-12][cc/2-2] = VIVE;
    matriz[cf/2-12][cc/2-3] = VIVE;
    matriz[cf/2-12][cc/2-5] = VIVE;
    matriz[cf/2-12][cc/2-11] = VIVE;
    matriz[cf/2-12][cc/2-14] = VIVE;
    matriz[cf/2-12][cc/2+2] = VIVE;
    matriz[cf/2-12][cc/2+3] = VIVE;
    matriz[cf/2-12][cc/2+5] = VIVE;
    matriz[cf/2-12][cc/2+11] = VIVE;
    matriz[cf/2-12][cc/2+14] = VIVE;

    matriz[cf/2-11][cc/2-1] = VIVE;
    matriz[cf/2-11][cc/2-12] = VIVE;
    matriz[cf/2-11][cc/2-13] = VIVE;
    matriz[cf/2-11][cc/2+1] = VIVE;
    matriz[cf/2-11][cc/2+12] = VIVE;
    matriz[cf/2-11][cc/2+13] = VIVE;

    matriz[cf/2-10][cc/2-1] = VIVE;
    matriz[cf/2-10][cc/2-3] = VIVE;
    matriz[cf/2-10][cc/2+1] = VIVE;
    matriz[cf/2-10][cc/2+3] = VIVE;

    matriz[cf/2-9][cc/2-2] = VIVE;
    matriz[cf/2-9][cc/2+2] = VIVE;

    matriz[cf/2-7][cc/2-17] = VIVE;
    matriz[cf/2-7][cc/2-18] = VIVE;
    matriz[cf/2-7][cc/2+17] = VIVE;
    matriz[cf/2-7][cc/2+18] = VIVE;

    matriz[cf/2-6][cc/2-17] = VIVE;
    matriz[cf/2-6][cc/2-18] = VIVE;
    matriz[cf/2-6][cc/2+17] = VIVE;
    matriz[cf/2-6][cc/2+18] = VIVE;

    matriz[cf/2-5][cc/2-12] = VIVE;
    matriz[cf/2-5][cc/2-13] = VIVE;
    matriz[cf/2-5][cc/2+12] = VIVE;
    matriz[cf/2-5][cc/2+13] = VIVE;

    matriz[cf/2-3][cc/2-10] = VIVE;
    matriz[cf/2-3][cc/2-12] = VIVE;
    matriz[cf/2-3][cc/2+10] = VIVE;
    matriz[cf/2-3][cc/2+12] = VIVE;

    matriz[cf/2-2][cc/2-9] = VIVE;
    matriz[cf/2-2][cc/2-12] = VIVE;
    matriz[cf/2-2][cc/2+9] = VIVE;
    matriz[cf/2-2][cc/2+12] = VIVE;

    matriz[cf/2-1][cc/2-10] = VIVE;
    matriz[cf/2-1][cc/2-11] = VIVE;
    matriz[cf/2-1][cc/2+10] = VIVE;
    matriz[cf/2-1][cc/2+11] = VIVE;

    matriz[cf/2+1][cc/2-10] = VIVE;
    matriz[cf/2+1][cc/2-11] = VIVE;
    matriz[cf/2+1][cc/2+10] = VIVE;
    matriz[cf/2+1][cc/2+11] = VIVE;

    matriz[cf/2+2][cc/2-9] = VIVE;
    matriz[cf/2+2][cc/2-12] = VIVE;
    matriz[cf/2+2][cc/2+9] = VIVE;
    matriz[cf/2+2][cc/2+12] = VIVE;

    matriz[cf/2+3][cc/2-10] = VIVE;
    matriz[cf/2+3][cc/2-12] = VIVE;
    matriz[cf/2+3][cc/2+10] = VIVE;
    matriz[cf/2+3][cc/2+12] = VIVE;

    matriz[cf/2+5][cc/2-12] = VIVE;
    matriz[cf/2+5][cc/2-13] = VIVE;
    matriz[cf/2+5][cc/2+12] = VIVE;
    matriz[cf/2+5][cc/2+13] = VIVE;

    matriz[cf/2+6][cc/2-17] = VIVE;
    matriz[cf/2+6][cc/2-18] = VIVE;
    matriz[cf/2+6][cc/2+17] = VIVE;
    matriz[cf/2+6][cc/2+18] = VIVE;

    matriz[cf/2+7][cc/2-17] = VIVE;
    matriz[cf/2+7][cc/2-18] = VIVE;
    matriz[cf/2+7][cc/2+17] = VIVE;
    matriz[cf/2+7][cc/2+18] = VIVE;

    matriz[cf/2+9][cc/2-2] = VIVE;
    matriz[cf/2+9][cc/2+2] = VIVE;

    matriz[cf/2+10][cc/2-1] = VIVE;
    matriz[cf/2+10][cc/2-3] = VIVE;
    matriz[cf/2+10][cc/2+1] = VIVE;
    matriz[cf/2+10][cc/2+3] = VIVE;

    matriz[cf/2+11][cc/2-1] = VIVE;
    matriz[cf/2+11][cc/2-12] = VIVE;
    matriz[cf/2+11][cc/2-13] = VIVE;
    matriz[cf/2+11][cc/2+1] = VIVE;
    matriz[cf/2+11][cc/2+12] = VIVE;
    matriz[cf/2+11][cc/2+13] = VIVE;

    matriz[cf/2+12][cc/2-2] = VIVE;
    matriz[cf/2+12][cc/2-3] = VIVE;
    matriz[cf/2+12][cc/2-5] = VIVE;
    matriz[cf/2+12][cc/2-11] = VIVE;
    matriz[cf/2+12][cc/2-14] = VIVE;
    matriz[cf/2+12][cc/2+2] = VIVE;
    matriz[cf/2+12][cc/2+3] = VIVE;
    matriz[cf/2+12][cc/2+5] = VIVE;
    matriz[cf/2+12][cc/2+11] = VIVE;
    matriz[cf/2+12][cc/2+14] = VIVE;

    matriz[cf/2+13][cc/2-5] = VIVE;
    matriz[cf/2+13][cc/2-11] = VIVE;
    matriz[cf/2+13][cc/2-13] = VIVE;
    matriz[cf/2+13][cc/2+5] = VIVE;
    matriz[cf/2+13][cc/2+11] = VIVE;
    matriz[cf/2+13][cc/2+13] = VIVE;

    matriz[cf/2+14][cc/2-12] = VIVE;
    matriz[cf/2+14][cc/2+12] = VIVE;

    matriz[cf/2+17][cc/2-6] = VIVE;
    matriz[cf/2+17][cc/2-7] = VIVE;
    matriz[cf/2+17][cc/2+6] = VIVE;
    matriz[cf/2+17][cc/2+7] = VIVE;

    matriz[cf/2+18][cc/2-6] = VIVE;
    matriz[cf/2+18][cc/2-7] = VIVE;
    matriz[cf/2+18][cc/2+6] = VIVE;
    matriz[cf/2+18][cc/2+7] = VIVE;
}
void Pentadecathlon(char** matriz, const int cf, const int cc)
{
    matriz[cf/2][cc/2] = VIVE;
    matriz[cf/2][cc/2-1] = VIVE;
    matriz[cf/2][cc/2+1] = VIVE;

    matriz[cf/2-1][cc/2] = VIVE;
    matriz[cf/2-1][cc/2-1] = VIVE;
    matriz[cf/2-1][cc/2+1] = VIVE;

    matriz[cf/2-2][cc/2] = VIVE;
    matriz[cf/2-2][cc/2-1] = VIVE;
    matriz[cf/2-2][cc/2+1] = VIVE;

    matriz[cf/2-3][cc/2-1] = VIVE;
    matriz[cf/2-3][cc/2+1] = VIVE;

    matriz[cf/2-4][cc/2] = VIVE;
    matriz[cf/2-4][cc/2-1] = VIVE;
    matriz[cf/2-4][cc/2+1] = VIVE;

    matriz[cf/2+1][cc/2] = VIVE;
    matriz[cf/2+1][cc/2-1] = VIVE;
    matriz[cf/2+1][cc/2+1] = VIVE;

    matriz[cf/2+2][cc/2-1] = VIVE;
    matriz[cf/2+2][cc/2+1] = VIVE;

    matriz[cf/2+3][cc/2] = VIVE;
    matriz[cf/2+3][cc/2-1] = VIVE;
    matriz[cf/2+3][cc/2+1] = VIVE;
}*/

void proximaJugada(char** matriz, const int cf, const int cc)
{
    int i, j;

    for (i = 0; i < cf; i++)
    {
        for (j = 0; j < cc; j++)
        {
            if (matriz[i][j] >= VIVE)
            {
                if (i == 0 || i == cf - 1) // se fija si se esta posicionado en la primera o ultima fila
                {
                    if (i == 0) // si esta posicionado en la 1ra fila
                    {
                        if (j == 0) // si esta posicionado en la esquina superior izquierda
                        {
                            matriz[i][j+1]++;
                            matriz[i+1][j+1]++;
                            matriz[i+1][j]++;
                        }
                        if (j == cc - 1) // si esta posicionado en la esquina superior derecha
                        {
                            matriz[i][j-1]++;
                            matriz[i+1][j-1]++;
                            matriz[i+1][j]++;
                        }

                        if (j != 0 && j != cc - 1) // si esta posicionado en la fila 1, menos en las 2 esquinas superiores
                        {
                            matriz[i][j-1]++;
                            matriz[i][j+1]++;
                            matriz[i+1][j-1]++;
                            matriz[i+1][j]++;
                            matriz[i+1][j+1]++;
                        }
                    }
                    else // esta posicionado en la ultima fila
                    {
                        if (j == 0) // si esta posicionado en la esquina inferior izquierda
                        {
                            matriz[i-1][j]++;
                            matriz[i-1][j+1]++;
                            matriz[i][j+1]++;
                        }
                        if (j == cc - 1) // si esta posicionado en la esquina inferior derecha
                        {
                            matriz[i-1][j]++;
                            matriz[i-1][j-1]++;
                            matriz[i][j-1]++;
                        }

                        if (j != 0 && j != cc - 1) // si esta posicionado en la ultima fila, menos en las 2 esquinas inferiores
                        {
                            matriz[i][j-1]++;
                            matriz[i][j+1]++;
                            matriz[i-1][j-1]++;
                            matriz[i-1][j]++;
                            matriz[i-1][j+1]++;
                        }
                    }
                }
                else // no se encuentra en la primera ni ultima fila
                {
                    if (j == 0 || j == cc - 1) // si esta posicionado en la 1ra o ultima columna
                    {
                        matriz[i-1][j]++;
                        matriz[i+1][j]++;
                        if (j == 0) // si esta posicionado en la 1ra columna
                        {
                            matriz[i-1][j+1]++;
                            matriz[i][j+1]++;
                            matriz[i+1][j+1]++;
                        }
                        else // esta posicionado en la ultima columna
                        {
                            matriz[i-1][j-1]++;
                            matriz[i][j-1]++;
                            matriz[i+1][j-1]++;
                        }
                    }
                    else // no cumple con ninguna de las condiciones anteriores (resto de la matriz)
                    {
                        matriz[i-1][j-1]++;
                        matriz[i-1][j]++;
                        matriz[i-1][j+1]++;
                        matriz[i][j-1]++;
                        matriz[i][j+1]++;
                        matriz[i+1][j-1]++;
                        matriz[i+1][j]++;
                        matriz[i+1][j+1]++;
                    }

                }
            }
        }
    }
}

void inicializarMatriz(char** matriz, const int cf, const int cc)
{
    int i, j;

    for (i = 0; i < cf; i++)
        for (j = 0; j < cc; j++)
            matriz[i][j] = MUERE;
}

void mostrarYActualizarMatriz(SDL_Renderer* renderer, SDL_Rect fillRect, char** matriz, const int cf, const int cc, const int tamanioDePixel)
{
    int i, j, posX, posY, posIniX = fillRect.x;

    fillRect.h = tamanioDePixel; //Alto
    fillRect.w = tamanioDePixel; //Ancho

    //SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    //Plantilla para pintar circulos si gusta mas
    //drawFilledCircle(renderer, fillRect.x+fillRect.w/2, fillRect.y+fillRect.h/2, (fillRect.w>fillRect.h?fillRect.h/2:fillRect.w/2));
    //printf("\n  1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 2 1 2 3 4 5 6 7 8 9 3 1 2 3 4 5 6");

    for (i = 0; i < cf; i++)
    {
        fillRect.x = posIniX; //Pos X de inicio en cada iteracion de i
        //printf("\n  ");
        for (j = 0; j < cc; j++)
        {
            if (matriz[i][j] >= VIVE)
            {
                if (matriz[i][j] == 12 || matriz[i][j] == 13)
                {
                    matriz[i][j] = VIVE; /// valor que va a tener la celula en el siguiente ciclo
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x00);
                    drawFilledCircle(renderer, fillRect.x+fillRect.w/2, fillRect.y+fillRect.h/2, fillRect.w/2);
                    //printf("%c ", 254);
                }
                else
                {
                    matriz[i][j] = MUERE;
                    SDL_SetRenderDrawColor(renderer, 0x60, 0xFF, 0xFF, 0x00);
                    drawFilledCircle(renderer, fillRect.x+fillRect.w/2, fillRect.y+fillRect.h/2, fillRect.w/2);
                    //printf("%c ", 254); // estaria piola otro tipo d cosa que mostrar para este caso
                }
            }
            else
            {
                if (matriz[i][j] == 3)
                {
                    matriz[i][j] = VIVE;
                    posX = fillRect.x; /// guardo la pos X del lienzo, porque al moverse luego, la posicion previa se pierde
                    posY = fillRect.y; /// guardo la pos Y por el mismo motivo
                    fillRect.h /= 5;
                    fillRect.w /= 5;
                    fillRect.x += tamanioDePixel / 2.5; /// me muevo en
                    fillRect.y += tamanioDePixel / 2.5; /// diagonal
                    SDL_SetRenderDrawColor(renderer, 0xAB, 0xFF, 0xFF, 0x00);
                    //SDL_RenderFillRect(renderer, &fillRect);
                    drawFilledCircle(renderer, fillRect.x+fillRect.w/2, fillRect.y+fillRect.h/2, fillRect.w/2);
                    fillRect.x = posX; /// vuelvo a la pos previa a mover en diagonal
                    fillRect.y = posY; /// lo mismo pero con Y
                    fillRect.h = tamanioDePixel;
                    fillRect.w = tamanioDePixel;
                    //printf("%c ", 250);
                }
                else
                {
                    matriz[i][j] = MUERE;
                    //printf("  ");
                }
            }
            fillRect.x += tamanioDePixel; //Pos X
        }
        fillRect.y += tamanioDePixel; //Pos Y
    }

    //puts("\n"); // doble salto de linea
}

void comienzo(char** matriz, const int cf, const int cc, const int opcion)
{
    inicializarMatriz(matriz, cf, cc);

    system("cls");
    printf("\n  Generador %02d (", opcion);

    switch(opcion)
    {
        case 1: printf("Aleatorio)\n");
                aleatorio(matriz,cf,cc);
        break;
        case 2: printf("Planeador)\n");
                leerArchGeneradores("Generadores/planeador.txt", matriz, cf, cc);
        break;
        case 3: printf("Sapo)\n");
                leerArchGeneradores("Generadores/sapo.txt", matriz, cf, cc);
        break;
        case 4: printf("Pulsar)\n");
                leerArchGeneradores("Generadores/pulsar.txt", matriz, cf, cc);
        break;
        case 5: printf("Mickey Mouse)\n");
               leerArchGeneradores("Generadores/mickeyMouse.txt", matriz, cf, cc);
        break;
        case 6: printf("Ca%con de Planeadores)\n",164);
                leerArchGeneradores("Generadores/canionDePlaneadores.txt", matriz, cf, cc);
        break;
        case 7: printf("Bi Gun)\n");
                leerArchGeneradores("Generadores/biGun.txt", matriz, cf, cc);
        break;
        case 8: printf("Molinete)\n");
                leerArchGeneradores("Generadores/molinete.txt", matriz, cf, cc);
        break;
        case 9: printf("64P2H1V0)\n");
                leerArchGeneradores("Generadores/G4P2H1V0.txt", matriz, cf, cc);
        break;
        case 10: printf("Filler)\n");
                 leerArchGeneradores("Generadores/filler.txt", matriz, cf, cc);
        break;
        case 11: printf("124P37)\n");
                 leerArchGeneradores("Generadores/124P37.txt", matriz, cf, cc);
        break;
        case 12: printf("Pentadecathlon)\n");
                 leerArchGeneradores("Generadores/Pentadecathlon.txt", matriz, cf, cc);
    }
}
