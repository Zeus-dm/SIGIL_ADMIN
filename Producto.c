#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Producto.h"

//--------------------------------------------------------------

Producto* crearProducto( const char* Nombre, const char* Marca, const char* Tipo, const char* barCode, long Stock, long Precio){
	Producto* newP = (Producto*) malloc(sizeof(Producto));

  	strcpy( newP->Nombre, Nombre);
  	strcpy( newP->Marca, Marca);
  	strcpy( newP->Tipo, Tipo);
	strcpy( newP->BarCode, barCode);
  	newP->Stock = Stock;
  	newP->Precio = Precio;
  	return newP;
}
