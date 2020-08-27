#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <stdbool.h>
#define MAX 50

typedef struct{
	char Nombre[MAX];
  	char Marca[MAX];
  	char Tipo[MAX];
  	char BarCode[MAX];
    long Stock;
    long Precio;
}Producto;

Producto* crearProducto( const char* Nombre, const char* Marca, const char* Tipo, const char* barCode, long Stock, long Precio);


#endif // PRODUCTO_H
