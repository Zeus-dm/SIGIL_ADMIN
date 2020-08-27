#ifndef FUNMAIN_H
#define FUNMAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "TDA/Mapa.h"
#include "MENU&CSV/CSV.h"
#include "Producto.h"

#define ENTER 13
#define ESC 27
#define MAX 50
#define min 20

//------------------------------------------------------------

void Espera();

//------------------------------------------------------------

void InsertarMapaIndividual( Mapa* Inv_CB, Mapa* Inventario ,Producto* product );

void Verificar( Mapa* Inventario, Mapa* Inv_CB, const char* nombre, const char* marca, const char* tipo, const char* BarCode, long stock, long precio, int flag);

//------------------------------------------------------------

void MostrarProductos( Mapa* Inventario );

void IngresoProducto( Mapa* Inventario, Mapa* Inv_CB);

void IngresarArchivo( Mapa* Inventario, Mapa* Inv_CB );

void EliminarProducto( Mapa* Inventario, Mapa* Inv_CB );

void BuscarProducto( Mapa* Inv_CB);

#endif // FUNMAIN_H
