/*
 * reportes.c
 *
 *  Created on: 9/08/2016
 *      Author: aylin
 */
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "reportes.h"
#include "estructuras.h"
#include "acciones.h"
#include <string.h>
#include "time.h"
#include "math.h"
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

//mount montar[50];

int reporteMBR(char* id, char* name, char* path) {
	//printf("\nID = %s\n",id);

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 51; i++) {
		if (montar[i].vdID != NULL) {
			if (strcasecmp(montar[i].vdID, id) == 0) {
				printf("-> Se ha encontrado una particion con el id.\n");
				boolIgual = 1;
			}
			if (boolIgual == 1) {
				if (montar[i].estado == 1) {
					direcc = montar[i].path;
					break;
				}
			}
		}
	}
	if (boolIgual == 0) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	printf("path =%s\n", direcc);

//VERIFICA SI EL ARCHIVO EXISTE
	FILE* archivo;
	archivo = fopen(direcc, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//CREA LA CARPETA SI NO EXISTE
	char direccion[200];
	char auxDirecc[200];
	for (i = 0; i < 200; i++) {
		auxDirecc[i] = '\0';
	}
	strcpy(direccion, path);
	char nombre[50];
	int n = 0;
	for (i = 0; i < 200; i++) {
		nombre[n] = direccion[i];
		if (direccion[i] == '/') {
			auxDirecc[i] = direccion[i];
			char *aux = (char*) malloc(150);
			strcpy(aux, "mkdir ");
			strcat(aux, auxDirecc);
			//   printf("auxD=%s\n",auxDirecc);
			system(aux);
			free(aux);
			n = 0;
		}
		auxDirecc[i] = direccion[i];
		n++;
		if (direccion[i] == '\0') {
			break;
		}
	}

	char d[200];
	strcpy(d, auxDirecc);

	char* ext = NULL;
	ext = &d;
	char* nam = NULL;
	nam = &d;
//printf("EEEE=%s\n",ext);
	int boolExt = 0;
	char* auxName;
	char* extImg;
	ext = strtok(nam, ".");
//printf("Ext=%s\n",ext);
	auxName = ext;

	while (ext != NULL) {
		ext = strtok(NULL, ".");
		//printf("ex =%s\n",ext);
		extImg = ext;
		if (ext != NULL) {
			if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
				boolExt = 1;
				break;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: La imagen no tiene extension.\n");
		return 0;
	}

//printf("auxName= %s\n",auxName);
	char *e = ".dot";
	char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
	strcpy(dot, auxName);
	strcat(dot, e);
//printf("dd=%s\n",dot);

	char fecha[100] = "fecha";
	struct tm *timeinfo;
	timeinfo = localtime(&structDisco.fecha);
	strftime(fecha, 100, "%c", timeinfo);

//CREA EL REPORTE
	FILE* report;
	report = fopen(dot, "w+");
	fprintf(report, "digraph mbr{\n");
	fprintf(report, "rankdir = LR;\n");
	fprintf(report,
			"node [shape = record, fontsize=12,fontname=\"%s\", style=filled ,fillcolor=lightsalmon, height = 1.2]; \n",
			"UBUNTU");
	fprintf(report, "Particion[label=\"");

	fprintf(report,
			"{%s}\n"
					"|* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
					"|{NOMBRE | VALOR}\n"
					"|{MBR_tamanio:| %d }\n"
					"|{ MBR_fecha:| %s }\n"
					"|{ MBR_disk_signature: | %d }\n"
					"", direcc, structDisco.size, fecha, structDisco.signature);
	int a = 0;
	for (a = 0; a < 4; a++) {
		if (structDisco.part[a].status == '1') {
			fprintf(report, "\n|{PART_status_%d: | %c}\n"
					"| { PART_type_%d: | %c} \n"
					"|{ PART_fit_%d : | %c}\n"
					"| { PART_start_%d :| %d}\n"
					"|{ PART_size_%d:| %d }\n"
					"|{ PART_name_%d :| %s}\n "
					"", a, structDisco.part[a].status, a,
					structDisco.part[a].type, a, structDisco.part[a].fit, a,
					structDisco.part[a].start, a, structDisco.part[a].size, a,
					structDisco.part[a].name);
		}
	}

	fprintf(report, "\"];\n");

	for (a = 0; a < 4; a++) {
		if (structDisco.part[a].type == 'E'
				|| structDisco.part[a].type == 'e') {
			int i = 0;
			int ii = 0;
			for (i = 0; i < 8; i++) {
				if (structDisco.part[a].exten[i].status == '1') {
					ii++;
					fprintf(report, "Particion%d[label=\"", ii);
					fprintf(report, "{EBR_%d}\n"
							"|{PART_status_%d: | %c}"
							"|{ PART_fit_%d : | %c}"
							"| { PART_start_%d :| %d}"
							"|{ PART_size_%d:| %d }"
							"|{ PART_next_%d:| %d }"
							"|{ PART_name_%d :| %s} ", ii, ii,
							structDisco.part[a].exten[i].status, ii,
							structDisco.part[a].exten[i].fit, ii,
							structDisco.part[a].exten[i].start, ii,
							structDisco.part[a].exten[i].size, ii,
							structDisco.part[a].exten[i].next, ii,
							structDisco.part[a].exten[i].name);

					fprintf(report, "\"];\n");
				}
			}
		}
	}
	fprintf(report, "}\n");
	fclose(report);

	char *r1 = "dot -Tjpg ";
	char *r2 = " -o ";
	char *ruta = (char*) malloc(
			1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
	strcpy(ruta, r1);
	strcat(ruta, dot);
	strcat(ruta, r2);
	strcat(ruta, path);
	printf("RUTA= %s\n", ruta);

	char consola[300];
	strcpy(consola, "");
	strcat(consola, ruta);
	printf("%s\n", consola);
	system(consola);
	printf("-> Se creo el reporte MBR correctamente.\n");
	char consola2[300];
	strcpy(consola2, "");
	strcat(consola2, "xdg-open ");
	strcat(consola2, auxDirecc);
	system(consola2);

	return 1;
}

int reporteDISK(char* id, char* name, char* path) {

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 51; i++) {
		if (montar[i].vdID != NULL) {
			// printf("\nM%d = %s\n",i,montar[i].vdID);
			//if/(montar[i].id[2]==nombre[2] &&  montar[i].disco==numID && montar[i].estado=='1'){
			if (strcasecmp(montar[i].vdID, id) == 0) {
				printf("-> Se ha encontrado una particion con el id.\n");
				boolIgual = 1;
			}
			if (boolIgual == 1) {
				if (montar[i].estado == 1) {
					direcc = montar[i].path;
					break;
				}
			}
		}
	}
	if (boolIgual == 0) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}
	printf("path =%s\n", direcc);

//VERIFICA SI EL ARCHIVO EXISTE
	FILE* archivo;
	archivo = fopen(direcc, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//CREA LA CARPETA SI NO EXISTE
	char direccion[200];
	char auxDirecc[200];
	for (i = 0; i < 200; i++) {
		auxDirecc[i] = '\0';
	}
	strcpy(direccion, path);
	char nombre[50];
	int n = 0;
	for (i = 0; i < 200; i++) {
		nombre[n] = direccion[i];
		if (direccion[i] == '/') {
			auxDirecc[i] = direccion[i];
			char *aux7 = (char*) malloc(150);
			strcpy(aux7, "mkdir ");
			strcat(aux7, auxDirecc);
			//   printf("auxD=%s\n",auxDirecc);
			system(aux7);
			free(aux7);
			n = 0;
		}
		auxDirecc[i] = direccion[i];
		n++;
		if (direccion[i] == '\0') {
			break;
		}
	}

	char d[200];
	strcpy(d, auxDirecc);

	char* ext = NULL;
	ext = &d;
	char* nam = NULL;
	nam = &d;
	//printf("EEEE=%s\n",ext);
	int boolExt = 0;
	char* auxName;
	char* extImg;
	ext = strtok(nam, ".");
	//printf("Ext=%s\n",ext);
	auxName = ext;

	while (ext != NULL) {
		ext = strtok(NULL, ".");
		//printf("ex =%s\n",ext);
		extImg = ext;
		if (ext != NULL) {
			if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
				boolExt = 1;
				break;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: La imagen no tiene extension.\n");
		return 0;
	}

	//printf("auxName= %s\n",auxName);
	char *e = ".dot";
	char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
	strcpy(dot, auxName);
	strcat(dot, e);
	//printf("dd=%s\n",dot);

	//CREA EL REPORTE
	int par = 0;
	FILE* report = fopen(dot, "w+");
	fprintf(report,
			"digraph particiones{\nrankdir=TB;\ncolor=blue;\n node[shape = record, color = cyan];\nsubgraph cluster{\n");
	fprintf(report, "label=\"%s\"", direcc);
	fprintf(report, "\nnode8[label=\"MBR");
	int j = 3;
	for (j = 0; j < 4; j++) {

		if (structDisco.part[j].status == '1'
				&& (structDisco.part[j].type == 'P'
						|| structDisco.part[j].type == 'p')) {
			fprintf(report, "|Primaria");
			par++;

		} else if (structDisco.part[j].status == '0') {	//&& structDisco.part[j].size!=0){
			fprintf(report, "|Libre");
			par++;
		} else if (structDisco.part[j].status == '1'
				&& (structDisco.part[j].type == 'E'
						|| structDisco.part[j].type == 'e')) {
			fprintf(report, "|{Extendida|{");
			int i;
			for (i = 0; i < 20; i++) {
				if (structDisco.part[j].exten[i].status == '1') {
					fprintf(report, "EBR|Logica |");
				} else if (structDisco.part[j].exten[i].status == '0'
						&& structDisco.part[j].exten[i].size != 0) {
					fprintf(report, "EBR|Libre |");
				}
			}
			par++;
			fprintf(report, "}}");
		}

	}
	fprintf(report, "\"];\n\t}\n}");
	fclose(report);

	char *r1 = "dot -Tjpg ";
	char *r2 = " -o ";
	char *ruta = (char*) malloc(
			1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
	strcpy(ruta, r1);
	strcat(ruta, dot);
	strcat(ruta, r2);
	strcat(ruta, path);
	printf("RUTA= %s\n", ruta);

	char consola[300];
	strcpy(consola, "");
	strcat(consola, ruta);
	printf("%s\n", consola);
	system(consola);
	printf("-> Se creo el reporte DISK correctamente.\n");
	char consola2[300];
	strcpy(consola2, "");
	strcat(consola2, "xdg-open ");
	strcat(consola2, auxDirecc);
	system(consola2);
	return 1;
}

int reporteJOURNAL(char* name, char* path, char* id) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		char* operacionrar = structDisco.part[i].name;
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 8; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}

	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;

	int posicion;
	if (existeLogica == 1) {
		posicion = structDisco.part[i].exten[j].start;
		ajuste = structDisco.part[i].exten[j].fit;
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		posicion = structDisco.part[i].start;
		ajuste = structDisco.part[i].fit;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}
	sb.magic = 61268;
	if (sb.magic == 61268) {
		fseek(archivo, sb.apuntadorLog, SEEK_SET);
		journal bitacora;
		fread(&bitacora, sizeof(bitacora), 1, archivo);

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		strcat(name, ".txt");
		//printf("name=%s\n",name);
		strcat(path, name);
		strcpy(direcc, path);

		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//printf("Ruta de Archivo: %s\n", aux);
				system(aux);
				free(aux);
			} else {
				direcc2[i] = direcc[i];
				if (direcc[i] == '\0') {
					break;
				}
			}
		}

		for (i = 0; i < 200; i++) {
			if (direcc2[i] == '\n') {
				direcc2[i] = '\0';
			}
		}

		printf("CrearArchivo");
//CREA EL ARCHIVO
		FILE* reporte;
		//char busqueda[100];
		//strcat(busqueda, "/home/FileSystem/reporteJOURNAL_");
		//strcat(busqueda, bitacora.nombre);
		//strcat(busqueda, ".dot");
		reporte = fopen(path, "w+");
		char fecha[100];
		struct tm *timeinfo;
		timeinfo = localtime(&bitacora.fecha);
		strftime(fecha, 100, "%c", timeinfo);
		//printf("a");
		int cont = 0;
		while (bitacora.tipo > 0) { //MIENTRAS SEA CARPETA
			cont += 1;
			char operacion[100];
			char tipoOperacion[100];
			if (bitacora.operacion == 1) {
				strcpy(operacion, "mkfile");
			} else if (bitacora.operacion == 2) {
				strcpy(operacion, "cat");
			} else if (bitacora.operacion == 3) {
				strcpy(operacion, "rm");
			} else if (bitacora.operacion == 5) {
				strcpy(operacion, "ren");
			} else if (bitacora.operacion == 6) {
				strcpy(operacion, "mkdir");
			} else {
				strcpy(operacion, "formatear");
			}
			printf("* %d\n", cont);
			int a = 0;
			int b = 0;
			char nombre[100];
			strcpy(nombre, bitacora.nombre);
			for (b = 0; b < 100; b++) {
				if (nombre[b] == '.') {
					a++;
				}
			}
			if (a > 0) {
				strcpy(tipoOperacion, "archivo");
			} else {
				strcpy(tipoOperacion, "carpeta");
			}
			fprintf(reporte,
					"OPERACION: \"%s\" \n TIPO: \"%s\" \n NOMBRE : \"%s\" \n CONTENIDO: \"%s\" \n FECHA: \"%s\" \n PROPIETARIO: \"%s\" \n PERMISOS: \"%s\"  ",
					operacion, tipoOperacion, bitacora.nombre,
					bitacora.contenido, asctime(timeinfo), "", "");
			fprintf(reporte, "\n\n\n\n");

			fseek(archivo, bitacora.tipo, SEEK_SET);
			fread(&bitacora, sizeof(bitacora), 1, archivo);

			if (cont == 20) {
				break;
			}
		}
		printf("c");
		char operacion[100];
		char tipoOperacion[100];
		if (bitacora.operacion == 1) {
			strcpy(operacion, "mkfile");
		} else if (bitacora.operacion == 2) {
			strcpy(operacion, "cat");
		} else if (bitacora.operacion == 3) {
			strcpy(operacion, "rm");
		} else if (bitacora.operacion == 5) {
			strcpy(operacion, "ren");
		} else if (bitacora.operacion == 6) {
			strcpy(operacion, "mkdir");
		}
		int a = 0;
		int b = 0;
		char nombre[100];
		strcpy(nombre, bitacora.nombre);
		for (b = 0; b < 100; b++) {
			if (nombre[b] == '.') {
				a++;
			}
		}
		if (a > 0) {
			strcpy(tipoOperacion, "archivo");
		} else {
			strcpy(tipoOperacion, "carpeta");
		}

		fprintf(reporte,
				"OPERACION: \"%s\" \n TIPO: \"%s\" \n NOMBRE : \"%s\" \n CONTENIDO: \"%s\" \n FECHA: \"%s\" \n PROPIETARIO: \"%s\" \n PERMISOS: \"%s\"  ",
				operacion, tipoOperacion, bitacora.nombre, bitacora.contenido,
				fecha, "", "");
		fprintf(reporte, "\n\n");

		fclose(reporte);

		printf("-> Se creo el reporte JOURNAL correctamente.\n");
		char consola[300];
		strcpy(consola, "");
		strcat(consola, "xdg-open ");
		strcat(consola, direcc2);
		system(consola);
	} else {
		printf("ERROR: La particion no se ha formateado.\n");
	}

	return 1;
}

int reporteBITMAP_INODO(char* name, char* path, char* id) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		//char* operacionrar = structDisco.part[i].name;
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 8; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}

	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
//CREA EL ARCHIVO
	superbloque sb;

	if (existeLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	printf("CrearArchivo");
	sb.magic = 61268;
	if (sb.magic == 61268) {

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		//XXX
		//strcat(name, ".txt");
		//printf("name=%s\n", name);
		//strcat(path, name);
		strcpy(direcc, path);

		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//printf("Ruta de Archivo: %s\n", aux);
				system(aux);
				free(aux);
			} else {
				direcc2[i] = direcc[i];
				if (direcc[i] == '\0') {
					break;
				}
			}
		}

		for (i = 0; i < 200; i++) {
			if (direcc2[i] == '\n') {
				direcc2[i] = '\0';
			}
		}

		fseek(archivo, sb.apuntadorBitmapInodo, SEEK_SET);
		//journal bitacora;
		//fread(&bitacora, sizeof(bitacora), 1, archivo);
		FILE* reporte;
		reporte = fopen(path, "w+");
		int cont = 1;
		fprintf(reporte, "Reporte INODO: %s\n", ruta);
		printf("Count = %d\n", sb.inodosCount);
		int j = 0;
		for (j = 0; j < sb.inodosCount; j++) {
			char p;
			fread(&p, 1, 1, archivo);
			if (p == '0') {
				fprintf(reporte, "| %c ", '0');
			} else {
				fprintf(reporte, "| %c ", '1');
			}
			if (cont == 20) {
				fprintf(reporte, "|\n");
				cont = 0;
			}
			cont++;
		}

		fclose(reporte);

		printf("-> Se creo el reporte BITMAP INODO correctamente.\n");
		char consola[300];
		strcpy(consola, "");
		strcat(consola, "xdg-open ");
		strcat(consola, direcc2);
		system(consola);
		return 1;

	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}

}

int reporteBITMAP_BLOQUE(char* name, char* path, char* id) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida
		//char* operacionrar = structDisco.part[i].name;
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 8; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}

	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	//CREA EL ARCHIVO
	superbloque sb;

	if (existeLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	printf("CrearArchivo");
	sb.magic = 61268;
	if (sb.magic == 61268) {

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		//XXX
		//strcat(name, ".txt");
		//printf("name=%s\n", name);
		//strcat(path, name);
		strcpy(direcc, path);

		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//printf("Ruta de Archivo: %s\n", aux);
				system(aux);
				free(aux);
			} else {
				direcc2[i] = direcc[i];
				if (direcc[i] == '\0') {
					break;
				}
			}
		}

		for (i = 0; i < 200; i++) {
			if (direcc2[i] == '\n') {
				direcc2[i] = '\0';
			}
		}

		fseek(archivo, sb.apuntadorBitmapInodo, SEEK_SET);

		FILE* reporte;
		reporte = fopen(path, "w+");
		int cont = 1;
		fprintf(reporte, "Reporte BLOQUE: %s\n", ruta);
		printf("INODO = %d\n", sb.apuntadorBitTablaInodo);
		printf("BLOQUE = %d\n", sb.apuntadorBitmapInodo);

		printf("Count = %d\n", sb.bloquesCount);
		int j = 0;
		for (j = 0; j < sb.bloquesCount; j++) {
			char p;
			fread(&p, 1, 1, archivo);
			if (p == '0') {
				fprintf(reporte, "| %c ", '0');
			} else {
				fprintf(reporte, "| %c ", '1');
			}
			if (cont == 20) {
				fprintf(reporte, "|\n");
				cont = 0;
			}
			cont++;
		}

		fclose(reporte);

		printf("-> Se creo el reporte BITMAP BLOQUE correctamente.\n");
		char consola[300];
		strcpy(consola, "");
		strcat(consola, "xdg-open ");
		strcat(consola, direcc2);
		system(consola);

		return 1;

	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}

}

int reporteSB(char* name, char* path, char* id) {
	//printf("sb");
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida

		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 8; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}

	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	//CREA EL ARCHIVO
	superbloque sb;

	if (existeLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	//printf("CrearArchivo");
	sb.magic = 61268;
	if (sb.magic == 61268) {

		char direccion[200];
		char auxDirecc[200];
		for (i = 0; i < 200; i++) {
			auxDirecc[i] = '\0';
		}
		strcpy(direccion, path);
		char nombre[50];
		int n = 0;
		for (i = 0; i < 200; i++) {
			nombre[n] = direccion[i];
			if (direccion[i] == '/') {
				auxDirecc[i] = direccion[i];
				char *aux = (char*) malloc(150);
				strcpy(aux, "mkdir ");
				strcat(aux, auxDirecc);
				//   printf("auxD=%s\n",auxDirecc);
				system(aux);
				free(aux);
				n = 0;
			}
			auxDirecc[i] = direccion[i];
			n++;
			if (direccion[i] == '\0') {
				break;
			}
		}

		char d[200];
		strcpy(d, auxDirecc);

		char* ext = NULL;
		ext = &d;
		char* nam = NULL;
		nam = &d;
		//printf("EEEE=%s\n",ext);
		int boolExt = 0;
		char* auxName;
		char* extImg;
		ext = strtok(nam, ".");
		//printf("Ext=%s\n",ext);
		auxName = ext;

		while (ext != NULL) {
			ext = strtok(NULL, ".");
			//printf("ex =%s\n",ext);
			extImg = ext;
			if (ext != NULL) {
				if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
					boolExt = 1;
					break;
				}
			}
		}
		if (boolExt == 0) {
			printf("ERROR: La imagen no tiene extension.\n");
			return 0;
		}

		//printf("auxName= %s\n",auxName);
		char *e = ".dot";
		char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
		strcpy(dot, auxName);
		strcat(dot, e);
		//printf("dd=%s\n",dot);

		FILE* reporte;
		reporte = fopen(dot, "w+");
		fprintf(reporte, "digraph sb{\n");
		fprintf(reporte, "rankdir = LR;\n");
		fprintf(reporte,
				"node [shape = record, fontsize=12,fontname=\"%s\", style=filled ,fillcolor=lightsalmon, height = 1.2]; \n",
				"UBUNTU");
		fprintf(reporte, "Particion[label=\"");
		char fecha[100];
		char fecha2[100];
		struct tm *timeinfo;
		struct tm *timeinfo2;
		timeinfo = localtime(&sb.DateCreacion);
		strftime(fecha, 100, "%c", timeinfo);
		timeinfo2 = localtime(&sb.DateMontaje);
		strftime(fecha2, 100, "%c", timeinfo2);

		fprintf(reporte, "{%s}|{NOMBRE | VALOR}|", ruta);
		fprintf(reporte, "{ s_inodos_count: | %d }|", sb.inodosCount);
		fprintf(reporte, "{ s_bloques_count: | %d }|", sb.bloquesCount);
		fprintf(reporte, "{ s_free_bloques_count: | %d }|",
				sb.freeBloquesCount);
		fprintf(reporte, "{ s_free_inodes_count: | %d }|",
				sb.freeInodosCount);
		fprintf(reporte, "{ s_mtime: | %s }|", fecha);
		fprintf(reporte, "{ s_umtime: | %s }|", fecha2);
		fprintf(reporte, "{ s_mnt_count: | %d }|", sb.mountCount);
		fprintf(reporte, "{ s_magic:| %d }|", sb.magic);
		fprintf(reporte, "{ s_inode_size: | %d }|", sb.inodoSize);
		fprintf(reporte, "{ s_block_size: | %d }|", sb.bloqueSize);
		fprintf(reporte, "{ s_first_ino: | %d }|", sb.firstFreeBitTablaInodo);
		fprintf(reporte, "{ s_first_blo: | %d }|", sb.firstFreeBitBloque);
		fprintf(reporte, "{ s_bm_inode_start: | %d }|", sb.apuntadorBitTablaInodo);
		fprintf(reporte, "{ s_bm_block_start: | %d }|", sb.apuntadorBitmapInodo);
		fprintf(reporte, "{ s_inode_start:| %d }|", sb.apuntadorTablaInodo);
		fprintf(reporte, "{ s_block_start:| %d }|", sb.apuntadorBloques);

		fclose(archivo);
		fprintf(reporte, "\"];\n}");

		fclose(reporte);

		char *r1 = "dot -Tjpg ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		//	printf("RUTA= %s\n", ruta);

		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte SB correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, auxDirecc);
		system(consola2);
		return 1;

	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}

}

int reporteTREE(char* name, char* path, char* id) {
	//printf("sb");
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				if (montar[i].estado == 1) {
					ruta = montar[i].path; //%%%
					nombre = montar[i].name;
					break;
				}
			}
		}
	}
	if (i == 31) {
		printf("ERROR: El ID no existe.\n");
		return 0;
	}

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	//VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	int j = 0;
	int existeLogica = 0;
	for (i = 0; i < 4; i++) { //Primaria/extendida

		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 8; j++) { //journalica
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				existeLogica = 1;
				break;
			}
		}
		if (existeLogica == 1) {
			break;
		}

	}
	if (i == 4 && existeLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	//CREA EL ARCHIVO
	superbloque sb;

	if (existeLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	} else {
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

	//printf("CrearArchivo");
	sb.magic = 61268;
	if (sb.magic == 61268) {

		char direccion[200];
		char auxDirecc[200];
		for (i = 0; i < 200; i++) {
			auxDirecc[i] = '\0';
		}
		strcpy(direccion, path);
		char nombre[50];
		int n = 0;
		for (i = 0; i < 200; i++) {
			nombre[n] = direccion[i];
			if (direccion[i] == '/') {
				auxDirecc[i] = direccion[i];
				char *aux = (char*) malloc(150);
				strcpy(aux, "mkdir ");
				strcat(aux, auxDirecc);
				//   printf("auxD=%s\n",auxDirecc);
				system(aux);
				free(aux);
				n = 0;
			}
			auxDirecc[i] = direccion[i];
			n++;
			if (direccion[i] == '\0') {
				break;
			}
		}

		char d[200];
		strcpy(d, auxDirecc);

		char* ext = NULL;
		ext = &d;
		char* nam = NULL;
		nam = &d;
		//printf("EEEE=%s\n",ext);
		int boolExt = 0;
		char* auxName;
		char* extImg;
		ext = strtok(nam, ".");
		//printf("Ext=%s\n",ext);
		auxName = ext;

		while (ext != NULL) {
			ext = strtok(NULL, ".");
			extImg = ext;
			if (ext != NULL) {
				if (strcmp(ext, "jpg") == 0 || strcmp(ext, "png") == 0) {
					boolExt = 1;
					break;
				}
			}
		}
		if (boolExt == 0) {
			printf("ERROR: La imagen no tiene extension.\n");
			return 0;
		}

		char *e = ".dot";
		char *dot = (char *) malloc(1 + strlen(auxName) + strlen(e));
		strcpy(dot, auxName);
		strcat(dot, e);

		FILE* reporte;
		reporte = fopen(dot, "w+");
		fprintf(reporte, "digraph tree{\n");
		fprintf(reporte, "rankdir = LR\n");
		fprintf(reporte,
				"node [shape = plaintext fontsize=15 fontname=\"%s\" randir =LR]; \n",
				"UBUNTU");

		fprintf(reporte,llenarTREE(ruta,"",sb.apuntadorAVD));
		fprintf(reporte,"\n}");

		fclose(reporte);

		char *r1 = "dot -Tjpg ";
		char *r2 = " -o ";
		char *ruta = (char*) malloc(
				1 + strlen(r1) + strlen(dot) + strlen(r2) + strlen(path));
		strcpy(ruta, r1);
		strcat(ruta, dot);
		strcat(ruta, r2);
		strcat(ruta, path);
		//	printf("RUTA= %s\n", ruta);
		char consola[300];
		strcpy(consola, "");
		strcat(consola, ruta);
		printf("%s\n", consola);
		system(consola);
		printf("-> Se creo el reporte TREE correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, auxDirecc);
		system(consola2);
		return 1;

	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}
}

char* llenarTREE(char* ruta, char* texto, char* posicion){


}


