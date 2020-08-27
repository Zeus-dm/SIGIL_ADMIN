#ifndef I_SESION_H
#define I_SESION_H

#include <stdbool.h>

#define MAX 50

typedef struct{
    char usuario[MAX];
    char contra[MAX];
}Usuario;

bool InicioSesion(void);

#endif // I_SESION_H
