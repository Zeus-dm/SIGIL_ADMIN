#include <stdio.h>
#include <conio.h>
#include "Menu.h"

#define UP 72
#define DOWN 80
#define ENTER 13
#define ESC 27

int crearMenu( char menu[][50], int tope, int pos ){
    int opc = pos;

    while(1){
        printf("\n\t\t");
        puts( menu[0] );
        printf("\n\n");

        for(int i=1; i<tope; i++){
            if( opc == i-1 ){
                printf(" ->\t ");
            }else{
                printf("\t");
            }
            puts(menu[i]);
        }

        unsigned char tecla = getch();
        switch(tecla){
            case UP:
                if( opc == 0 ){
                    opc = tope-2;
                }else{
                    opc--;
                }
            break;
            case DOWN:
                if( opc == (tope-2) ){
                    opc = 0;
                }else{
                    opc++;
                }
            break;
            case ENTER:
                system("cls");
                return opc;
            break;
            case ESC:
                system("cls");
                return (tope-2);
            break;
        }
        system("cls");
    }
}
