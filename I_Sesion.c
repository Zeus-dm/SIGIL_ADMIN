#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "I_Sesion.h"
#include "TDA/Mapa.h"
#include "MENU&CSV/CSV.h"
#include "MENU&CSV/Menu.h"


Usuario *CrearUsuario( const char* name, const char* contra ){
    Usuario* newU = (Usuario*)malloc(sizeof(Usuario));
    strcpy( newU->usuario, name);
    strcpy( newU->contra, contra);
    return newU;
}

void G_U( Mapa* MapaUsuarios ){
    FILE *Usuarios = fopen( "USUARIOS.csv", "r" );

    char linea[1024];
    while( fgets( linea, 1023, Usuarios) != NULL ){
        const char* nombre = get_csv_field( linea, 0);
        const char* contra = get_csv_field( linea, 1);
        Usuario* newU = CrearUsuario( nombre, contra);
        insertMap(MapaUsuarios, newU->usuario, newU);
    }
    fclose( Usuarios );
}

bool I_S_C( Mapa* MapaUsuarios ){
    int intentos = 3, ind = 0;
    char nombre[MAX], contra[MAX];

    do{
        printf("\n\t\tINICIAR SESION\n\n");

        if( ind == 1 ){
            printf("     Usuario Incorrecto\n");
        }else if( ind == 2 ){
            printf("     Contrasena Incorrecta\n");
        }

        printf("\tIntentos : %d\n", intentos);

        printf("\n\tUSUARIO    : ");
        gets( nombre );
        printf("\tCONTRASENA : ");
        gets( contra );

        Usuario* auxU = searchMap(MapaUsuarios, nombre);

        if( auxU != NULL ){
            if( strcmp( contra, auxU->contra) == 0 ){
                    return true;
            }else{
                    ind = 2;
            }
        }else{
            ind = 1;
        }

        intentos--;

        system("cls");
    }while( intentos > 0 );
    return false;
}

void C_C( Mapa* MapaUsuarios ){
    char nombre[MAX], contra[MAX], verContra[MAX];
    int ind = 0;

    do{
        printf("\n\t\tCREAR CUENTA\n\n");

        if( ind == 1){
            printf("     El usuario ya existe\n");
        }else if( ind == 2){
            printf("     Las contrasenas no coinciden\n");
        }

        printf("\tUSUARIO         : ");
        gets( nombre );
        printf("\tCONTRASENA      : ");
        gets( contra );
        printf("\tVer. CONTRASENA : ");
        gets( verContra);

        Usuario* auxU = searchMap(MapaUsuarios, nombre);
        if(auxU != NULL){
            ind = 1;
        }else{
            if( strcmp( contra, verContra ) == 0 ){
                FILE *Usuarios = fopen("USUARIOS.csv","a");
                fprintf( Usuarios, "%s,%s\n", nombre, contra);
                fclose(Usuarios);
                break;
            }else{
                ind = 2;
            }
        }
        system("cls");
    }while(1);
}

bool InicioSesion(void){
    int opcion = 0;
    char inicio[4][MAX] = { "BIENVENIDO","INICIAR SESION","CREAR CUENTA","SALIR"};

    Mapa* MapaUsuarios = crearMapa( 2 );
    G_U( MapaUsuarios );

    do{
        opcion = crearMenu( inicio, 4, opcion );

        switch( opcion ){
            case 0:
                if( I_S_C( MapaUsuarios ) ){
                    return true;
                }
            break;
            case 1:
                C_C( MapaUsuarios );
                return true;
            break;
        }
    }while( opcion != 2 );
    return false;
}
