#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "I_Sesion.h"
#include "Producto.h"
#include "FunMain.h"
#include "MENU&CSV/Menu.h"
#include "MENU&CSV/CSV.h"
#include "TDA/Mapa.h"

#define min 20

void subMenuProducto( Mapa* Inventario, Mapa* Inv_CB);

void G_I( Mapa* Inventario, Mapa* Inv_CB){
    FILE *INVENTARIO = fopen("INVENTARIO.csv", "r");
    long stock = 0, precio = 0;

    char linea[1024];

    while( fgets( linea, 1023, INVENTARIO) != NULL){
        const char* nombre = get_csv_field( linea, 0);
        const char* marca = get_csv_field( linea, 1);
        const char* tipo = get_csv_field( linea, 2);
        const char* BarCode = get_csv_field( linea, 3);
        stock = atol( get_csv_field( linea, 4));
        precio = atol( get_csv_field( linea, 5));

        Verificar( Inventario, Inv_CB, nombre, marca, tipo, BarCode, stock, precio, 0);
    }
    fclose( INVENTARIO );
}

void A_I( Mapa* Inv_CB){
    FILE *INVENTARIO = fopen("INVENTARIO.csv", "w");

    Producto* product = firstMap( Inv_CB );
    while( product != NULL ){
        fprintf(INVENTARIO,"%s,%s,%s,%s,", product->Nombre,product->Marca,product->Tipo,product->BarCode);
        fprintf(INVENTARIO,"%ld,%ld\n", product->Stock,product->Precio);
        product = nextMap( Inv_CB );
    }
    fclose(INVENTARIO);
}

int main(){
    system("COLOR A");

    if( InicioSesion() ){
        system("cls");
      	Mapa *Inventario = crearMapa( min );
        Mapa *Inv_CB = crearMapa( min );

        G_I( Inventario, Inv_CB);

        int opcion = 0;
      	char menuInicio[6][MAX] = {"SIGIL","Agregar Producto(s)","Eliminar Producto","Buscar Producto","Mostrar Inventario","Salir"};

      	do{
        	opcion = crearMenu( menuInicio, 6, opcion);
        	switch( opcion ){
              	case 0:
                    subMenuProducto( Inventario, Inv_CB );
                break;
                case 1:
                    EliminarProducto( Inventario, Inv_CB );
                break;
                case 2:
                    BuscarProducto( Inv_CB);
                break;
              	case 3:
                    MostrarProductos( Inventario );
                break;
        	}
        }while( opcion != 4 );
        A_I( Inv_CB );

    }
    return 0;
}

void subMenuProducto(Mapa* Inventario, Mapa* Inv_CB ){
	int opcion = 0 ;
  	char subMenu[4][MAX] = {"AGREGAR PRODUCTO(S)","Agregar desde archivo","Agregar manualmente","Atras"};

  	do{
    	opcion = crearMenu(subMenu,4,opcion) ;
    	switch (opcion) {
            case 0:
                IngresarArchivo( Inventario, Inv_CB);
            break;
            case 1:
                IngresoProducto( Inventario, Inv_CB);
            break;
        }
    }while (opcion != 2);
}



















