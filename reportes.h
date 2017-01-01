/*
 * reportes.h
 *
 *  Created on: 9/08/2016
 *      Author: aylin
 */

#ifndef REPORTES_H_
#define REPORTES_H_
#include "estructuras.h"

int reporteMBR(char* id, char* name, char* path);
int reporteDISK(char* id, char* name, char* path);
int reporteEXEC();
///////////////////////////////////////////////////
int reporteBITACORA(char* name, char* path, char* id);
int reporteBITMAP_INODO(char* name,char* path,char* id);
int reporteBITMAP_BLOQUE(char* name,char* path,char* id);
int reporteBITMAP_DETALLE(char* name,char* path,char* id);
int reporteBITMAP_ARBOL(char* name,char* path,char* id);
int reporteSB(char* name, char* path, char* id);
int reporteTREE(char* name, char* path, char* id);
int llenarTREE(char* ruta, char* texto, char* posicion);
int reporteFILE(char*name,char* path,char*id,char*ruta);
int reporteF(char*name,char*pa,char*id,char*ruta);
int reporteDIRECTORIO(char* id, char* name, char* path);
char* completarDIRECTORIO(char* ruta, char*mensaje,int posicion);
int reporteTREE_DIRECTORIO(char* id, char* name, char* path, char* ruta) ;
char* completarTreeD1(char* aux4, char* mensaje, int posicion,char*path) ;
char* completarTreeD2(char*aux4,char* mensaje,int posicion);
int reporteINODO(char* id, char* name, char* path);
char* completarINODO(char* ruta, char* mensaje, int posicion);
int reporteTREE_FILE(char* id, char* name, char* path, char* ruta);
char* completarTreeF1(char* ruta, char* mensaje, int posicion, char* path);
int reporteTREE_F(char* id, char* name, char* path, char* ruta) ;
char* LlenarReporteFile(char*aux4,char*mensaje,int posicion,char*path1);
char* LlenarReporteFile2(char*aux4,char*mensaje,int posicion);
#endif /* REPORTES_H_ */
