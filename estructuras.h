/*
 * estructuras.h
 *
 *  Created on: 4/08/2016
 *      Author: aylin
 */

#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#include <time.h>

typedef struct ATRIBUTOS{
	char* atributos;
}atrib;

typedef struct INODO {
	int nLink; //enlace duro
	char* pathLink;
	int uid;
	char uID[16];
	int gid;
	char gID[16];
	int size;
	time_t atime; //fecha que se leyo sin modificarlo
	time_t ctime; //fecha en que se creo
	time_t ntime; //fecha en que se modifico
	int bloque[15];
	char type;
	char permisos[3];

	int aux; //Ind
	int contador; //bloques
	int noInodo;
} inodo;

typedef struct CONTENT { //archivo
	char name[12];
	int inodo;
	inodo ino;
} content;

typedef struct APUNTADOR { //ad
	char puntero[16]; //Tamanio de 64
	int subCarpetas[6];
	int carpeta;
	int apuntador;
} apunt;

typedef struct ARCHIVO { //bloque
	char contenido[64];
} archivoBloque;

typedef struct CARPETA { //detalle
	content contenido[4];//16
	int d; //direc
} carpeta;

typedef struct DATOS{
	int usuario;
}datos;

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
	int fileSystemType; //sistema de archivos
	int inodosCount; //
	int bloquesCount; //
	int bloquesLibresCount; //
	int inodosLibresCount; //
	time_t mtime; //
	time_t umtime; ///
	int mountCount; //
	int magic; //
	int inodoSize;//
	int bloqueSize;//
	int primerInodo; //
	int primerBloque; //
	int inicioBitInodo;//
	int inicioBitBloque;//
	int inicioTablaInodo;//
	int inicioTablaBloque;//
//17 datos
	int apuntadorSuperBloque;
	int apuntador;
	int apuntadorJournal;
	int apuntadorBitmap; //ad
	int apuntadorBitmapCarpeta;
	int apuntadorCarpeta;
	int arbolContador;
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
	int sign;
	particion part[4];
} mbr;

#endif /* ESTRUCTURAS_H_ */
