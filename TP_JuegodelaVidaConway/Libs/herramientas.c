#include "herramientas.h"

int cargaOpcion()
{
    int opcion;

    do  {
            system("cls");
            printf("\n  Ingrese el Generador:\n  ------- -- ----------\n");
            printf("\n  01. Aleatorio");
            printf("\n  02. Planeador");
            printf("\n  03. Sapo");
            printf("\n  04. Pulsar");
            printf("\n  05. Mickey Mouse");
            printf("\n  06. Ca%con de Planeadores", 164);
            printf("\n  07. Bi Gun");
            printf("\n  08. Molinete");
            printf("\n  09. 64P2H1V0");
            printf("\n  10. Filler");
            printf("\n  11. 124P37");
            printf("\n  12. Pentadecathlon");
            printf("\n  13. Salir");
            printf("\n\n\n  Ingrese su Opci%cn: ", 162);

            if (scanf("%d", &opcion) != 1)
            {
                limpiarBuffer();
                continue;
            }

            limpiarBuffer(); /// por si se ingresan varios numeros separados por espacio, para que no queden en el buffer de entrada.

        }   while(opcion < 1 || opcion > 13);

    return opcion;
}

int verificar(const int cf, const int cc, const int opcion)
{
        switch(opcion)
        {
            case 1:
                if (cf < 20 || cc < 20) // Aleatorio
                    return ERR;
            break;
            case 2:
                if (cf < 3 || cc < 3) // Planeador
                    return ERR;
            break;
            case 3:
                if (cf < 4 || cc < 4) // Sapo
                    return ERR;
            break;
            case 4:
                if (cf < 15 || cc < 15) // Pulsar
                    return ERR;
            break;
            case 5:
                if (cf < 7 || cc < 10) // Mickey Mouse
                    return ERR;
            break;
            case 6:
                if (cf < 13 || cc < 37) // Cañon de Planeadores
                    return ERR;
            break;
            case 7:
                if (cf < 17 || cc < 56) // Bi Gun
                    return ERR;
            break;
            case 8:
                if (cf < 13 || cc < 13) // Molinete
                    return ERR;
            break;
            case 9:
                if (cf < 14 || cc < 33) // 64P2H1V0
                    return ERR;
            break;
            case 10:
                if (cf < 37 || cc < 25) // Filler
                    return ERR;
            break;
            case 11:
                if (cf < 37 || cc < 37) // 124P37
                    return ERR;
            break;
            case 12:
                if (cf < 16 || cc < 9) // Pentadecathlon
                    return ERR;
        }
    return OK;
}

void reasignarFilasYColumnas(int* cf, int* cc, const int opcion)
{
    switch (opcion)
    {
        case 1: *cf = 20;
                *cc = 20;
        break;
        case 2: *cf = 3;
                *cc = 3;
        break;
        case 3: *cf = 4;
                *cc = 4;
        break;
        case 4: *cf = 15;
                *cc = 15;
        break;
        case 5: *cf = 7;
                *cc = 10;
        break;
        case 6: *cf = 13;
                *cc = 37;
        break;
        case 7: *cf = 17;
                *cc = 56;
        break;
        case 8: *cf = 13;
                *cc = 13;
        break;
        case 9: *cf = 14;
                *cc = 33;
        break;
        case 10: *cf = 37;
                 *cc = 25;
        break;
        case 11: *cf = 37;
                 *cc = 37;
        break;
        case 12: *cf = 16;
                 *cc = 9;
    }
}

char* mi_strcat(char* s1, const char* s2)
{
    char* ini = s1;

    while (*s1)
        s1++;

    while (*s2)
    {
        *s1 = *s2;
        s1++;
        s2++;
    }

    *s1 = '\0';

    return ini;
}

char* mi_strcpy(char* s1, const char* s2)
{
    char* ini = s1;

    while (*s2)
    {
        *s1 = *s2;
        s1++;
        s2++;
    }

    *s1 = '\0';

    return ini;
}

int mi_tolower(int ch)
{
    if (ch >= 65 && ch <= 90)
        ch += 32;

    return ch;
}

char ingreseSiNo()
{
    char opcion;

    do  {
            fflush(stdin);
            if (scanf("%c", &opcion) != 1)
            {
                printf("\n  Ingrese un valor valido (S/N): ");
                limpiarBuffer();
                continue;
            }

            limpiarBuffer(); /// por si se escribio mas de un caracter y quedaron caracteres en el buffer de entrada
            opcion = mi_tolower(opcion);

            if (opcion != 's' && opcion != 'n')
                printf("\n  Ingrese una opcion valida (S/N): ");
        }   while (opcion != 's' && opcion != 'n');

    return opcion;
}

int ingreseNumVal(const int lim1, const int lim2)
{
    int dato;

    do  {
            if (scanf("%d", &dato) != 1)
            {
                printf("\n  Ingrese un valor valido entre %d y %d: ", lim1, lim2);
                limpiarBuffer();
                continue;
            }

            limpiarBuffer(); /// para evitar problemas si se escribieron varios numeros separados por espacio

            if (dato < lim1 || dato > lim2)
                printf("\n  Ingrese un valor entre %d y %d: ", lim1, lim2);
        }   while (dato < lim1 || dato > lim2);

    return dato;
}

void limpiarBuffer()
{
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF);
}
