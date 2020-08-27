
#include "FunMain.h"

//------------------------------------------------------------

void Espera(){
    printf("\n\n ->\t Atras\n");
    do{
        unsigned char tecla = getch();
        if( (tecla == ENTER) || tecla == ESC ){
            break;
        }
    }while(1);
    system("cls");
}

//-------------------------------------------------------------

void InsertarMapaIndividual( Mapa* Inv_CB, Mapa* Inventario ,Producto* product ){
    Producto* auxP = searchMap( Inv_CB, product->BarCode);
    if( auxP == NULL ){
        insertMap( Inv_CB, product->BarCode, product );

        Mapa* auxM = searchMap( Inventario, product->Tipo);
        if( auxM == NULL ){
            Mapa* newM = crearMapa(min);
            insertMap( newM, product->BarCode, product);
            insertMap( Inventario, product->Tipo, newM );
        }else{
            Producto* auxP = searchMap(auxM, product->BarCode);
            if( auxP == NULL ){
                insertMap( auxM, product->BarCode, product);
            }
        }
    }else{
        auxP->Stock += product->Stock;
    }
}

void Verificar( Mapa* Inventario, Mapa* Inv_CB, const char* nombre, const char* marca, const char* tipo, const char* BarCode, long stock, long precio, int flag){

    if( (strcmp( nombre, "")!=0) && (strcmp( marca, "")!=0) && (strcmp( tipo, "")!=0) && (strcmp( BarCode, "")!=0) && (stock > 0) && (precio > 0) ){
        Producto* product = crearProducto( nombre, marca, tipo, BarCode, stock, precio );
        InsertarMapaIndividual( Inv_CB, Inventario ,product);

        if( flag ){
            printf("\n     Producto Ingresado Correctamente");
        }
    }else{
        if( flag ){
            printf("\n     ERROR::Datos Incorrectos");
        }
    }
}

//------------------------------------------------------------

void MostrarProductos( Mapa* Inventario ){
    printf("\n\t\tTODOS LOS PRODUCTOS\n\n");

    Mapa *listProd = firstMap( Inventario);
    if( listProd == NULL){
        printf("    No existen productos actualmente");
    }else{
        while( listProd != NULL){
            Producto* product = firstMap( listProd);
            while( product != NULL ){
                printf("\n\t----------------------");
                printf("\n\t Nombre : %s", product->Nombre);
                printf("\n\t Marca  : %s", product->Marca);
                printf("\n\t Tipo   : %s", product->Tipo);
                printf("\n\t BarCode: %s", product->BarCode);
                printf("\n\t Stock  : %ld", product->Stock);
                printf("\n\t Precio : %ld", product->Precio);
                product = nextMap( listProd);
            }
            printf("\n\t----------------------");
            listProd = nextMap(Inventario);
        }
    }
    Espera();
}

void IngresoProducto( Mapa* Inventario, Mapa* Inv_CB) {
	char ind[MAX];
	char nombre [MAX] ;
  	char marca [MAX] ;
    char tipo [MAX] ;
  	char barCode[MAX] ;
  	long stock = 0 ;
  	long precio = 0 ;

  	printf("\n\t\tINGRESAR PRODUCTO MANUALMENTE\n\n\n");

  	printf("\tNombre del producto   : ") ;
  	gets( nombre);
  	printf("\tMarca del producto    : ") ;
    gets( marca);
  	printf("\tTipo de producto      : ") ;
  	gets( tipo);
  	printf("\tCodigo de barras      : ") ;
    gets( barCode);
  	printf("\tStock del producto    : ") ;
    scanf("%ld", &stock);
    printf("\tPrecio del producto   : ") ;
  	scanf("%ld", &precio);
  	gets(ind);

	if ( strcmp(ind, "") == 0){
		for(int i=0; tipo[i]!= '\0'; i++){
        	tipo[i] = toupper(tipo[i]);
  		}

  		Verificar(Inventario,Inv_CB,nombre,marca,tipo,barCode,stock,precio,1) ;
	}else{
		printf("\n\n     ERROR::Datos Incorrectos");
	}

  	Espera();
}

void IngresarArchivo( Mapa* Inventario, Mapa* Inv_CB ){
    long stock = 0, precio = 0;
    char TIPO[MAX];
	char archivo[MAX];

  	printf("\n\t\tPRODUCTOS DESDE UN ARCHIVO\n\n\n");
  	printf("\tNombre del archivo(sin.csv): ");
  	gets(archivo);
  	strcat(archivo,".csv");

  	FILE *PRODUCTOS = fopen( archivo, "r");

  	if( PRODUCTOS == NULL){
    	printf("\n    Archivo NO existe");
    }else{
    	char linea[1024];
      	printf("\n    Procesando archivo...\n");

      	while( fgets(linea,1023,PRODUCTOS) != NULL){
        	const char* nombre = get_csv_field(linea, 0);
          	const char* marca = get_csv_field(linea, 1);
          	const char* tipo = get_csv_field(linea, 2);
          	const char* BarCode = get_csv_field(linea, 3);
          	stock = atol( get_csv_field(linea, 4));
        	precio = atol( get_csv_field(linea, 5));

            strcpy(TIPO, tipo);
        	for(int i=0; TIPO[i]!= '\0'; i++){
                TIPO[i] = toupper(TIPO[i]);
            }

          	Verificar( Inventario, Inv_CB, nombre, marca, TIPO, BarCode, stock, precio, 0);
        }
      	printf("\n    Archivo finalizado\n");
    }
  	fclose( PRODUCTOS );
  	Espera();
}

void EliminarProducto( Mapa* Inventario, Mapa* Inv_CB ){
    char tipo[MAX];
    char barCode[MAX];

    printf("\n\t\tELIMINAR PRODUCTO\n\n\n");

    printf("\tCodigo de barras      : ") ;
    gets( barCode);

    if( strcmp(barCode,"") != 0){
        Producto* auxP = searchMap(Inv_CB, barCode);
        if(auxP != NULL){
            strcpy(tipo, auxP->Tipo);
            Mapa* auxM = searchMap(Inventario, tipo);
            deleteKeyMap(auxM, barCode);
            if(auxM->contN == 0){
                deleteKeyMap(Inventario, tipo);
                free(auxM);
            }
            deleteKeyMap(Inv_CB, barCode);
            free(auxP);
            printf("\n     Producto Eliminado Correctamente");
        }else{
            printf("\n     Producto No existe");
        }
    }else{
        printf("\n     ERROR::Datos Incorrectos");
    }

    Espera();
}

void BuscarProducto( Mapa* Inv_CB){
    char barCode[MAX];
    printf("\n\t\tBUSCAR PRODUCTO\n\n\n");

    printf("\tCodigo de barras      : ") ;
    gets( barCode);

    if( strcmp(barCode,"") != 0){
        Producto* product = searchMap(Inv_CB, barCode);
        if( product != NULL ){
            printf("\n\t----------------------");
                printf("\n\t Nombre : %s", product->Nombre);
                printf("\n\t Marca  : %s", product->Marca);
                printf("\n\t Tipo   : %s", product->Tipo);
                printf("\n\t BarCode: %s", product->BarCode);
                printf("\n\t Stock  : %ld", product->Stock);
                printf("\n\t Precio : %ld", product->Precio);
            printf("\n\t----------------------");
        }else{
            printf("\n     Producto No existe");
        }
    }else{
        printf("\n     ERROR::Datos Incorrectos");
    }

    Espera();
}

//------------------------------------------------------------














