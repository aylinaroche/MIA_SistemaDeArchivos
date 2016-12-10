/*
 * estructuras.h
 *
 *  Created on: 4/08/2016
 *      Author: aylin
 */

#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#include <time.h>

typedef struct ATRIBUTOS {
	char* atributos;
} atrib;

typedef struct INODO {
	int noInodo;
	int size;
	int bloquesAsig; //numero de bloques asignados
	int bloques[4];
	int indirecto; //apuntador indirecto por si ocupa mas de 4

	int uid;
	char uID[16];
	int gid;
	char gID[16];
	char type;
	char permisos[3];
	int aux;
} inodo;

typedef struct ARCHIVO { //archivo
	char name[12];
	int inodo;
	inodo ino;
	time_t fechaCreacion;
	time_t fechaModifica;
} archivo;

typedef struct AVD { //arbol virtual de directorio
	time_t fechaCreacion;
	char name[16];
	int subDirectorios[6];
	int directorio; //primer directorio
	int apuntadorAVD; //apuntador para que sigan creciendo los directorios
} avd;

typedef struct DATOS { //bloque
	char data[64];
} datos;

typedef struct DETALLE { //detalle
	archivo archivos[5]; //16
	int d; //direc
	int detalle; //Si ya no caben apunta a otro detalle
} detalle;

typedef struct USU {
	int usuario;
} usu;

typedef struct JOURNAL {
	int operacion;
	int tipo; //0 archivo / 1 directorio
	char nombre[50];
	char contenido[50];
	time_t fecha;
////
//	datos datos;
//int usuario;
//char permiso[50];
} journal;

typedef struct SUPERBLOQUE {
	char* nombre;
	int arbolVirtualCount;
	int detalleDirectorioCount;
	int inodosCount;
	int bloquesCount;
	int freeArbolCount;
	int freeDetalleDirectorioCount;
	int freeBloquesCount;
	int freeInodosCount;
	time_t DateCreacion;
	time_t DateMontaje;
	int mountCount;
	int apuntadorBitArbolDirectorio;
	int apuntadorArbolDirectorio;
	int apuntadorBitDetalleDirectorio; //Directorio = Carpeta
	int apuntadorDetalleDirectorio;
	int apuntadorBitTablaInodo;
	int apuntadorTablaInodo;
	int apuntadorBitBloques;
	int apuntadorBloques;
	int apuntadorLog;
	int arbolDirectorioSize;
	int detalleDirectorioSize;
	int inodoSize;
	int bloqueSize;
	int firstFreeBitArbol;
	int firstFreeBitDetalleDirectorio;
	int firstFreeBitTablaInodo;
	int firstFreeBitBloque;
	int magic;
	int apuntadorCopia;
	int apuntadorBitmapInodo;
} superbloque;

typedef struct MONTAR { //Cola para realizar el mount
	char path[70];
	char name[40];
	int var;
	int part;
	char *vdID;
	int estado;
	int uso;
} mount;

typedef struct EBR { //Cambiar
	char status;
	char fit;
	int start;
	int size;
	int auxiliar;
	int next; //Byte en el que esta el sigueinte ebr -1 si no hay
	char name[16];
} ebr;

typedef struct PARTICION {
	char status; //1 activa, 0
	char type;
	char fit; //ajuste
	int start; //en que byte inicia
	int size;
	int auxiliar;
	char name[16];
	ebr exten[20];
} particion;

typedef struct MBR { //Master Boot Record -> Registro de arranque principal
	int size;
	time_t fecha;
	int signature;
	particion part[4];
} mbr;

#endif /* ESTRUCTURAS_H_ */
