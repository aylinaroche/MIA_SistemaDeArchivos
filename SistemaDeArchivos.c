/*
 ============================================================================
 Name        : SistemaDeArchivos.c
 Author      : Aly
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "acciones.h"
#include "estructuras.h"
#include "comandos.h"
#include <stdio_ext.h>
#include <unistd.h>
#include <fcntl.h>

int opcion=1;
int salida;
char letras[15];

int main() {
	//puts("!!!Hello puto World!!!"); /* prints !!!Hello World!!! */
    printf("* * * * * * * * * * * * * COMANDOS . SA* * * * * * * * * * * * * \n");
    char com[1000];
    char com2[1000];
    int fdflags;

    while(opcion!=0){

        printf("-> Comando: ");
        fgets(com,500,stdin);
        fflush(stdin);

        strcpy(com2, com);
        char *comando = NULL;
        comando = strtok( com, " ");
        char *atr;
        if(comando!=NULL){
    	   atr = com2;
    	   verificarComando(comando, atr);
        }
    }
    return 0;

}
