#ifndef HERRAMIENTAS_H_INCLUDED
#define HERRAMIENTAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR -1
#define TAM_TITULO 100
#define PARTE_ENTERA(x) ((int)(x))
#define PARTE_DECIMAL(x) ((x) - PARTE_ENTERA(x))
#define REDONDEO(x) (PARTE_DECIMAL(x) >= 0.5 ? (PARTE_ENTERA(x)+1) : PARTE_ENTERA(x))

/// string.h
char* mi_strcat(char* s1, const char* s2);
char* mi_strcpy(char* s1, const char* s2);

/// ctype.h
int mi_tolower(int ch);

/// validaciones
int cargaOpcion();
int verificar(const int cf, const int cc, const int opcion);
void reasignarFilasYColumnas(int* cf, int* cc, const int opcion);
char ingreseSiNo();
int ingreseNumVal(const int lim1, const int lim2);

/// extra
void limpiarBuffer();

#endif // HERRAMIENTAS_H_INCLUDED
