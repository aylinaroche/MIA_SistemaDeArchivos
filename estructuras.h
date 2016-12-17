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
	int noAsignados; //numero de bloques asignados
	int bloques[4];
	int indirecto; //apuntador indirecto por si ocupa mas de 4

	int uid;
	char uID[16];
	int gid;
	char gID[16];
	char type;
	char permisos[3];
} inodo;

typedef struct ARCHIVO { //archivo
	char name[12];
	int inodo;
	inodo ino;
} archivo;

typedef struct AVD { //ad
	char name[16]; //Tamanio de 64
	int subDirectorios[6];
	int directorio;
	int apuntadorAVD;
} avd;

typedef struct bloque { //bloque
	char contenido[64];
} datos;

typedef struct DETALLE { //detalle
	archivo archivos[4]; //16
	int detalle; //direc
} detalle;

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
	int inodosCount; //
	int bloquesCount; //
	int freeBloquesCount; //
	int freeInodosCount; //
	time_t DateCreacion; //
	time_t DateMontaje; ///
	int mountCount; //
	int magic; //
	int inodoSize; //
	int bloqueSize; //
	int firstFreeBitTablaInodo; //
	int firstFreeBitBloque; //
	int apuntadorBitTablaInodo; //
	int apuntadorBitmapInodo; //
	int apuntadorTablaInodo; //
	int apuntadorBloques; //
	int apuntadorCopia;
	int apuntadorAVD;
	int apuntadorLog;
	int apuntadorBitArbolDirectorio; //ad
	int apuntadorBitDetalleDirectorio;
	int apuntadorDetalleDirectorio;
	int arbolVirtualCount; //24
	//
	int detalleDirectorioCount;
	int freeArbolCount;
	int freeDetalleDirectorioCount;
	int arbolDirectorioSize;
	int detalleDirectorioSize;
	int firstFreeBitArbol;
	int firstFreeBitDetalleDirectorio;
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

typedef struct EBR {
	char status;
	char fit;
	int start;
	int size;
	int auxiliar;
	int next; //Byte en el que esta el sigueinte ebr -1 si no hay
	char name[16];
} ebr;

typedef struct PARTICION {
	char status; //1 activa, 0 caida
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
