#include <stdio.h>
#include <stdlib.h>
#include "Libs/matrices.h"
#include "Libs/herramientas.h"

#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include "SDL2/include/SDL2/SDL_main.h"
#endif

#include <SDL.h>

/**
    Pablo Soligo. Plantilla de proyecto codeblocks para juego de la vida.
    Funciona con mingw 64 bits y no requiere tener instalado SDL.
    Los fuentes son multiplataforma (windows/linux Debian;Ubuntu). Para ubuntu se
    requiere de diferente configuración de proyecto.
*/

void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius){
    for (int y = -radius; y <= radius; y++){
        for (int x = -radius; x <= radius; x++){
            if (x*x + y*y <= radius*radius){
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int i, opcion, cf, cc, delay, width, height, tamanioDePixel;
    float relacionDeAspecto;
    char** matriz, titulo[TAM_TITULO], generacion[TAM_TITULO], cambiarTamanio = 's';
    unsigned char done;

    if (argc != 4)
    {
        printf("\n  Error en la cantidad de argumentos...\n\n");
        system("pause");
        return ERR;
    }

    cf = SDL_atoi(argv[1]);
    cc = SDL_atoi(argv[2]);
    delay = SDL_atoi(argv[3]);

    if (!cf || !cc || !delay)
    {
        printf("\n  Error en los argumentos...\n\n");
        system("pause");
        return ERR;
    }

    system("COLOR 0B"); /// cmd fondo negro y caracteres aguamarina claro.

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event e;
    SDL_Rect fillRect;

    SDL_DisplayMode pantallaActual;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_GetCurrentDisplayMode(0, &pantallaActual) != 0)
    {
        printf("Error al obtener el modo de pantalla actual: %s\n", SDL_GetError());
        SDL_Quit();
        return ERR;
    }

    if (cf > pantallaActual.h || cc > pantallaActual.w) /// valida si las filas y columnas ingresadas por linea de comando no superan el tamaño de la pantalla.
    {
        cf > pantallaActual.h && cc <= pantallaActual.w ? cf = pantallaActual.h : cc > pantallaActual.w && cf <= pantallaActual.h ? cc = pantallaActual.w : ({cf = pantallaActual.h;  cc = pantallaActual.w;});
        printf("\n  El tama%co de la matriz deseada excede la resolucion de la pantalla...\n\n  Se creara la matriz de tama%co: %d X %d\n\n", 164, 164, cf, cc);
        system("pause");
    } /// si es asi, revisa si las filas, o las columnas, o ambas superan la resolucion de la pantalla, y reasigna los valores a la resolucion de la pantalla.

    opcion = cargaOpcion(); /// menu donde podes elegir que generador usar.

    if (opcion != 13)
    {
        if (verificar(cf,cc,opcion) == ERR) /// validar que la cf y cc enviadas x linea de comando sean válidas para el generador deseado.
            reasignarFilasYColumnas(&cf, &cc, opcion); /// si cf y cc son muy chicos, se reasignan al valor mínimo requerido para el generador deseado.
        matriz = crearMatriz(cf, cc); /// funcion constructora

        if (!matriz)
        {
            printf("\n  ERROR AL CREAR LA MATRIZ...\n\n");
            system("pause");
            SDL_Quit();
            return SIN_MEM; /// si no se pudo crear la matriz, sale del programa con codigo de error.
        }
    }

    while (opcion != 13)
    {
        if (cambiarTamanio == 's')
        {
            relacionDeAspecto = (float)cc / cf; /// se calcula la relacion de aspecto de la matriz creada.

            if (relacionDeAspecto > 1) /// si las columnas son mayores que las filas, se calcula la resolucion de la ventana tomando el ancho de la pantalla y la relacion de
            {                          /// aspecto de la matriz, y se obtiene el alto de la ventana SDL, quedando una ventana proporcional a la matriz.
                width = pantallaActual.w;
                height = width / relacionDeAspecto;
            }
            else /// en caso que las filas sean mayor o igual que las columnas, se toma como base el alto de la pantalla, y multiplicandolo por la relacion de aspecto, se obtiene
            {    /// el ancho de la ventan SDL, y queda una resolucion de ventana proporcional a la matriz.
                height = pantallaActual.h;
                width = height * relacionDeAspecto;
            }

            tamanioDePixel = REDONDEO((float)width / cc); /// se calcula la relacion entre la resolucion de la ventana SDL y la matriz, para obtener el tamaño que deben tener las celulas.
                                                          /// se le aplica redondeo a la relacion, ya que puede dar FLOAT, y al truncarse, por ser int, puede perder el mayor tamaño posible
                                                          /// que puede llegar a tener cada pixel, lo cual luego afecta a la resolucion definitiva mas adelante.
            while (tamanioDePixel * cf > pantallaActual.h || tamanioDePixel * cc > pantallaActual.w) /// en caso que tamaño de cada pixel sea muy grande, y al recalcular las resoluciones de
                tamanioDePixel--;                                                                    /// la ventana SDL exceda la resolucion de la pantalla, se va achicando el tamaño
                                                                                                     /// que va a tener cada pixel hasta que no exceda la resolucion de la pantalla del monitor.
            width = tamanioDePixel * cc;  /// lo mas probable es que haya cambiado el tamaño de cada celula, entonces, se recalculan las dimensiones de la ventana SDL,
            height = tamanioDePixel * cf; /// calculando el tamaño de cada pixel * la cantidad de filas y columnas de la matriz, obtenemso la resolucion definitiva de la ventana SDL.
        }

        i = 0;

        comienzo(matriz, cf, cc, opcion); /// llama a la funcion generadora seleccionada previamente

        printf("\n\n  .Tama%co de la matriz: %d X %d\n", 164, cf, cc);
        printf("\n  .Resolucion de la Ventana SDL: %d X %d\n", width, height);
        printf("\n  .Tama%co de las Celulas Vivas: %d Pixeles\n", 164, tamanioDePixel);
        printf("\n  .Pulse la Tecla F11 para Pantalla Completa\n");
        printf("\n  .Pulse la Tecla F12 para salir de Pantalla Completa\n");
        printf("\n  .Pulse la Tecla ESCAPE para Salir de la ventana SDL\n\n\n");
        system("pause");

        //Create window
        window = SDL_CreateWindow("Juego de la vida",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  width,
                                  height,
                                  SDL_WINDOW_SHOWN);
        if (!window)
        {
            SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
            SDL_Quit();
            return -1;
        }

        // Creamos el lienzo
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -1;
        }

        SDL_RaiseWindow(window); /// llevar la ventana al frente
        SDL_SetWindowInputFocus(window); /// intentar darle el foco de entrada, en caso que la funcion anterior falle al darle foco. puede NO FUNCIONAR en algunos Sistemas Operativos

        done = 0;
        fillRect.x = 0; /// comience a dibujar el lienzo desde la pos 0
        fillRect.y = 0;

        while (!done)  //Se puede parar tambien cuando no se observen cambios!
        {
            while (SDL_PollEvent(&e) != 0)
            {
                // Salida del usuario
                if (e.type == SDL_QUIT)
                    done = 1;
                if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE: done = 1; /// salir
                        break;
                        case SDLK_F11: SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); /// pantalla completa.
                                       fillRect.x = (pantallaActual.w - width) / 2; /// modifico de donde empieza a dibujar el lienzo, porque sino, al poner pantalla completa,
                                       fillRect.y = (pantallaActual.h - height) / 2; /// dibuja desde arriba a la izquierda, y queremos que se vea desde el centro.
                        break;
                        case SDLK_F12: SDL_SetWindowFullscreen(window, 0); /// salir de pantalla completa
                                       fillRect.x = 0; /// volver a asignar 0, porque sino, no se va a ver completo el dibujo en la ventana,
                                       fillRect.y = 0; /// se ve una parte del lienzo dibujado si no se hace esto.
                    }
                }
            }

            if (!done)
            {
                // Se limpia la pantalla
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderClear(renderer);

                //Procesamiento de matriz?
                proximaJugada(matriz, cf, cc);
                mostrarYActualizarMatriz(renderer, fillRect, matriz, cf, cc, tamanioDePixel);

                //Plantilla para pintar cuadrados
                //SDL_RenderFillRect(renderer, &fillRect);

                // Actualizacion del "lienzo"
                SDL_RenderPresent(renderer);
                //SDL_UpdateWindowSurface(window);  // SDL_RenderPresent es mas eficiente

                //Titulo/caption de la ventana
                SDL_itoa(i, generacion, 10);
                mi_strcpy(titulo, "El Juego de La Vida - Generacion: ");
                mi_strcat(titulo, generacion);
                SDL_SetWindowTitle(window, titulo);
                SDL_Delay(delay);

                i++;
            }
        }

        //destruyo todos los elementos creados
        //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        printf("\n  Cantidad de Generaciones: %d\n\n", i-1);
        system("pause");

        opcion = cargaOpcion();

        if (opcion != 13)
        {
            printf("\n  Desea cambiar el tama%co de la matriz? (S/N): ", 164);
            cambiarTamanio = ingreseSiNo();

            if (cambiarTamanio == 's')
            {
                destruirMatriz(matriz, cf); /// funcion destructora
                system("cls");

                printf("\n  Ingrese la nueva cantidad de filas de la matriz (Maximo: %d): ", pantallaActual.h);
                cf = ingreseNumVal(1, pantallaActual.h); /// validar que no se ingrese una cantidad de filas mayor al alto de la pantalla, y menor a 1.
                printf("\n  Ingrese la nueva cantidad de columnas de la matriz (Maximo: %d): ", pantallaActual.w);
                cc = ingreseNumVal(1, pantallaActual.w); /// valida que no se ingrese una cantidad de columnas mayor al ancho de la pantalla, y menor 1.

                if (verificar(cf, cc, opcion) == ERR) /// validar que la cf y cc nuevas sean validas para el generador deseado.
                {
                    printf("\n  El tama%co de la matriz (%d X %d) es insuficiente para este generador...\n", 164, cf, cc);
                    reasignarFilasYColumnas(&cf, &cc, opcion); /// se reasignan cf y cc al valor minimo requerido para el generador deseado.
                    printf("\n  La matriz tomara el tama%co minimo para el generador: %d X %d\n\n", 164, cf, cc);
                    system("pause");
                }

                matriz = crearMatriz(cf, cc); /// funcion constructora

                if (!matriz)
                {
                    printf("\n  ERROR AL REDIMENSIONAR LA MATRIZ...\n\n");
                    system("pause");
                    SDL_Quit();
                    return SIN_MEM; /// si no se pudo redimensionar la matriz, sale del programa con codigo de error.
                }
            }
            else
            {
                if (verificar(cf, cc, opcion) == ERR) /// validar cf y cc, si, otra vez
                {
                    printf("\n  El tama%co de la matriz (%d X %d) es insuficiente para este generador...\n", 164, cf, cc);
                    destruirMatriz(matriz, cf);
                    reasignarFilasYColumnas(&cf, &cc, opcion);
                    printf("\n  La matriz tomara el tama%co minimo para el generador: %d X %d\n\n", 164, cf, cc);
                    system("pause");
                    matriz = crearMatriz(cf, cc);

                    if (!matriz)
                    {
                        printf("\n  ERROR AL REDIMENSIONAR LA MATRIZ...\n\n");
                        system("pause");
                        SDL_Quit();
                        return SIN_MEM; /// si no se pudo redimensionar la matriz, sale del programa con codigo de error.
                    }

                    cambiarTamanio = 's';
                }
            }
        }
        else
            destruirMatriz(matriz, cf); /// funcion destructora
    }

    SDL_Quit();

    return 0;
}


