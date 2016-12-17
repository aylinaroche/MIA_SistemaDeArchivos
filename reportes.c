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

int reporteDISK(char* id, char* name, char* path) {
//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	int boolIgual = 0;
	int i = 0;
	for (i = 0; i < 30; i++) {
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

	//CREA EL REPORTE
	int par = 0;
	FILE* report = fopen(dot, "w+");
	fprintf(report,
			"digraph particiones{\nrankdir=TB;\ncolor=blue;\n node[shape = record, color = cyan];\nsubgraph cluster{\n");
	fprintf(report, "label=\"%s\"", direcc);
	fprintf(report, "\nnode8[label=\"MBR");
	int j = 3;
	for (j = 0; j < 4; j++) {
		printf("EstadoDisk = %c\n", structDisco.part[j].status);
		if (structDisco.part[j].status == '1'
				&& (structDisco.part[j].type == 'P'
						|| structDisco.part[j].type == 'p')) {
			fprintf(report, "|PRIMARIA\n %s \n  %d",structDisco.part[j].name, structDisco.part[j].size);
			par++;

		} else if (structDisco.part[j].status == '0') {	//&& structDisco.part[j].size!=0){
			fprintf(report, "|LIBRE");
			par++;
		} else if (structDisco.part[j].status == '1'
				&& (structDisco.part[j].type == 'E'
						|| structDisco.part[j].type == 'e')) {
			fprintf(report, "|{EXTENDIDA|{");
			int i;
			for (i = 0; i < 20; i++) {
				//printf("EstadoLogica = %c\n", structDisco.part[j].exten[i].status);
				if (structDisco.part[j].exten[i].status == '1') {
					printf("entro logica\n");
					fprintf(report, "Logica|");
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

	char *r1 = "dot -Tpng ";
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
			"{%s}"
					"|* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
					"|{NOMBRE | VALOR}"
					"|{MBR_tamanio:| %d }"
					"|{ MBR_fecha:| %s }"
					"|{ MBR_disk_signature: | %d }"
					"", direcc, structDisco.size, fecha, structDisco.signature);
	int a = 0;
	for (a = 0; a < 4; a++) {
		if (structDisco.part[a].status == '1') {
			printf("TIPO = %c\n", structDisco.part[a].type);
			fprintf(report,
					"|{PART_status_%d: | %c}"
							"| { PART_type_%d: | %c}"
							"|{ PART_fit_%d : | %c}"
							"| { PART_start_%d :| %d}"
							"|{ PART_size_%d:| %d }"
							"|{ PART_name_%d :| %s}"
							"| * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
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
			for (i = 0; i < 20; i++) {
				if (structDisco.part[a].exten[i].status == '1') {
					ii++;
					fprintf(report, "Particion%d[label=\"", ii);
					fprintf(report, "{EBR_%d}\n"
							"|{PART_status_%d: | %c}"
							"|{ PART_fit_%d : | %c}"
							"| { PART_start_%d :| %d}"
							"|{ PART_size_%d:| %d }"
							"|{ PART_next_%d:| %d }"
							"|{ PART_name_L%d :| %s} ", ii, ii,
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

	char *r1 = "dot -Tpng ";
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

int reporteBITACORA(char* name, char* path, char* id) {
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
	sb.magic = 201404368;
	if (sb.magic == 201404368) {
		fseek(archivo, sb.apuntadorLog, SEEK_SET);
		journal bitacora;
		fread(&bitacora, sizeof(bitacora), 1, archivo);

		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		//strcat(name, ".txt");
		//printf("name=%s\n",name);
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

		printf("-> Se creo el reporte BITACORA correctamente.\n");
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
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

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
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

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

int reporteBITMAP_ARBOL(char* name, char* path, char* id) {
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
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

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

int reporteBITMAP_DETALLE(char* name, char* path, char* id) {
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
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

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
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

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

		fprintf(reporte, "{%s}|{NOMBRE | VALOR}|", "REPORTE SB");
		fprintf(reporte, "{ sb_nombre_hd: | %s }|", ruta);
		fprintf(reporte, "{ sb_arbol_virtual_count: | %d }|",
				sb.arbolVirtualCount);
		fprintf(reporte, "{ sb_detalle_directorio_count: | %d }|",
				sb.detalleDirectorioCount);
		fprintf(reporte, "{ sb_inodos_count: | %d }|", sb.inodosCount);
		fprintf(reporte, "{ sb_bloques_count: | %d }|", sb.bloquesCount);
		fprintf(reporte, "{ sb_arbol_virtual_free: | %d }|", sb.freeArbolCount);
		fprintf(reporte, "{ sb_detalle_directorio_free: | %d }|",
				sb.freeDetalleDirectorioCount);
		fprintf(reporte, "{ sb_inodos_free: | %d }|", sb.freeInodosCount);
		fprintf(reporte, "{ sb_bloques_free: | %d }|", sb.freeBloquesCount);
		fprintf(reporte, "{ sb_date_creacion: | %s }|", fecha);
		fprintf(reporte, "{ sb_date_ultimo_montaje: | %s }|", fecha2);
		fprintf(reporte, "{ sb_montajes_count: | %d }|", 1);
		fprintf(reporte, "{ sb_ap_bitmap_arbol_directorio:| %d }|",
				sb.apuntadorBitArbolDirectorio);
		fprintf(reporte, "{ sb_ap_arbol_directorio:| %d }|", sb.apuntadorAVD);
		fprintf(reporte, "{ sb_ap_bitmap_detalle_directorio:| %d }|",
				sb.apuntadorBitDetalleDirectorio);
		fprintf(reporte, "{ sb_ap_detalle_directorio:| %d }|",
				sb.apuntadorDetalleDirectorio);
		fprintf(reporte, "{ sb_ap_bitmap_tabla_inodo:| %d }|",
				sb.apuntadorBitTablaInodo);
		fprintf(reporte, "{ sb_ap_tabla_inodo:| %d }|", sb.apuntadorTablaInodo);
		fprintf(reporte, "{ sb_ap_bitmap_bloques:| %d }|",
				sb.apuntadorBitmapInodo);
		fprintf(reporte, "{ sb_ap_bloques:| %d }|", sb.apuntadorBloques);
		fprintf(reporte, "{ sb_ap_log:| %d }|", sb.apuntadorLog);
		fprintf(reporte, "{ sb_size_struct_arbol_directorio:| %d }|",
				sb.arbolDirectorioSize);
		fprintf(reporte, "{ sb_size_struct_detalle_directorio:| %d }|",
				sb.detalleDirectorioSize);
		fprintf(reporte, "{ sb_size_struct_inodo: | %d }|", sb.inodoSize);
		fprintf(reporte, "{ sb_size_struct_bloque: | %d }|", sb.bloqueSize);
		fprintf(reporte, "{ sb_first_free_bit_arbol_directorio:| %d }|",
				sb.firstFreeBitArbol);
		fprintf(reporte, "{ sb_first_free_bit_detalle_directorio:| %d }|",
				sb.firstFreeBitDetalleDirectorio);
		fprintf(reporte, "{ sb_first_free_bit_tabla_inodo: | %d }|",
				sb.firstFreeBitTablaInodo);
		fprintf(reporte, "{ sb_first_free_bit_bloques: | %d }|",
				sb.firstFreeBitBloque);
		fprintf(reporte, "{ sb_magic_num:| %d }|", sb.magic);

		fclose(archivo);
		fprintf(reporte, "\"];\n}");

		fclose(reporte);

		char *r1 = "dot -Tpng ";
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
	sb.magic = 201404368;
	if (sb.magic == 201404368) {

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

		//fprintf(reporte, llenarTREE(ruta, "", sb.apuntadorAVD));
		fprintf(reporte, "\n}");

		fclose(reporte);

		char *r1 = "dot -Tpng ";
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

int llenarTREE(char* ruta, char* texto, char* posicion) {
	char* s = "";
	return 0;
}

int reporteFILE(char* name, char* path, char* id, char* filen) {
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

//VERIFICAR LA PARTICION
	i = 0;
	int j = 0;
	int esLogica = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 8; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, name) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre indicado.\n");
		return 0;
	}
	superbloque sb;
	char ajuste;
	int posicion;
	if (esLogica == 1) {
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

	if (sb.magic == 201404368) {
		fseek(archivo, sb.apuntadorAVD, SEEK_SET);
		avd ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, filen);
		//printf("crear = %s\n",filen);
		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') { //Hasta que llegue al final
				verificar[a] = crear[a];
				verificar2[a] = crear[a];
			} else {
				for (b = a; b >= 0; b--) {
					if (verificar[b] != '/') {
						verificar[b] = '\0';
						verificar2[b] = '\0';
					} else {
						verificar[b] = '\0';
						verificar2[b] = '\0';
						break;
					}
				}
				break;
			}
		}
		char* ruta2;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta2 = strtok(crear, "/");
		} else {
			ruta2 = strtok(verificar, "/");
		}
		fclose(archivo);
		int datos = 0;
		ruta2 = strtok(verificar2, "/");
		//	printf("buscarArchivo\n");
		//	printf("ruta::%s, ruta2::%s\n",ruta,ruta2);
		datos = buscarArchivo(ruta, sb, ap, ruta2, ajuste, posicion,
				sb.apuntadorAVD);

		if (datos > 0) {
			ruta2 = strtok(crear, "/");
			while ((strstr(ruta2, ".") == 0x0 || strstr(ruta2, ".") == ""
					|| strstr(ruta2, ".") == NULL) && ruta2 != NULL) {
				ruta2 = strtok(NULL, "/");
			}
			if (ruta2 != NULL) {
				char mensaje[200];
				//		printf("contenidoArchivo.\n");
				strcpy(mensaje, contenidoArchivo(" ", datos, sb, ruta, ruta2));
				printf("* * * * * * * * * * * * * * * * * * * * * *\n%s\n",
						mensaje);

//////////////////////////////////////////////////////

				char direcc[200];
				char direcc2[200];
				int i = 0;
				for (i = 0; i < 200; i++) {
					direcc2[i] = '\0';
				}
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

				FILE* reporte;
				reporte = fopen(path, "w+");
				fprintf(reporte, "Reporte FILES: %s\n\n", ruta);
				fprintf(reporte, "%s", mensaje);
				fclose(reporte);

				printf("-> Se creo el reporte FILE correctamente.\n");
				char consola[300];
				strcpy(consola, "");
				strcat(consola, "xdg-open ");
				strcat(consola, direcc2);
				system(consola);
				return 1;

			}
		} else {
			printf("ERROR: La ruta no existe.\n");
		}
	} else {
		printf("ERROR: La particion no esta formateada.\n");
	}
	return 1;
}

int reporteDIRECTORIO(char* id, char* name, char* path) {
	//printf("\nID = %s\n",id);

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	char* nombres;
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
					nombres = montar[i].name;
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

//VERIFICA EL NOMBRE DE LA PARTICION
	int esLogica = 0;
	i = 0;
	int j = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombres) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombres) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: El nombre no existe.\n");
		return 0;
	}

	superbloque sb;
	if (esLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);

	} else {
		//int mos = structDisco.part[i].start;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

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
//VERIFICA LA EXTENSION DEL ARCHIVO
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


//VERIFICA SI SE HA FORMATEADO LA PARTICION
	//sb.magic = 201404368;
	if (sb.magic == 201404368) {

//CREA EL REPORTE
		FILE* report;
		report = fopen(dot, "w+");
		fprintf(report, "digraph directorio{\n");
		fprintf(report, "rankdir = LR;\n");
		fprintf(report,
				"node [shape = record, fontsize=12,fontname=\"%s\", color=orange, height = 0.7]; ",
				"UBUNTU");

		fprintf(report, completarDIRECTORIO(direcc, "", sb.apuntadorAVD));

		fprintf(report, "\n}");
		fclose(report);


		char *r1 = "dot -Tpng ";
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
		printf("-> Se creo el reporte DIRECTORIO correctamente.\n");
		char consola2[300];
		strcpy(consola2, "");
		strcat(consola2, "xdg-open ");
		strcat(consola2, auxDirecc);
		system(consola2);
	} else {
		printf("ERROR: No se ha formateado la particion.\n");
	}
	return 1;
}

char* completarDIRECTORIO(char* ruta, char* mensaje, int posicion) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd arbol;
	fseek(archivo, posicion, SEEK_SET);
	fread(&arbol, sizeof(avd), 1, archivo);
	fclose(archivo);
	char cadena[10000];
	char dato[25];
	sprintf(dato, "%d", posicion);
	strcpy(cadena, "node");
	strcat(cadena, dato);
	strcat(cadena, " [label=\" {<f0> ");
	strcat(cadena, arbol.name);
	strcat(cadena, "}|{<p0>|<p1>|<p2>|<p3>|<p4>|<p5>|<p6>|<p7>} \"]; \n");
	strcat(cadena, mensaje);
	int i = 0;

	for (i = 0; i < 6; i++) {
		//int mostrar2=con.subdirectorio[i];
		if (arbol.subDirectorios[i] > 500) {
			avd arbol2;
			archivo = fopen(ruta, "rb+");
			fseek(archivo, arbol.subDirectorios[i], SEEK_SET);
			fread(&arbol2, sizeof(avd), 1, archivo);
			char numero[25];
			char directorio[25];
			sprintf(numero, "%d", i);
			sprintf(directorio, "%d", arbol.subDirectorios[i]);
			strcat(cadena, " node");
			strcat(cadena, dato);
			strcat(cadena, ":p");
			strcat(cadena, numero);
			strcat(cadena, " -> node");
			strcat(cadena, directorio);
			strcat(cadena, ":f0;");
			fclose(archivo);
			strcat(cadena,
					completarDIRECTORIO(ruta, " ", arbol.subDirectorios[i]));

		}
	}
	if (arbol.apuntadorAVD > 0) {
		avd arbol3;
		archivo = fopen(ruta, "rb+");
		fseek(archivo, arbol.apuntadorAVD, SEEK_SET);
		fread(&arbol3, sizeof(avd), 1, archivo);
		fclose(archivo);
		char p[100];
		strcpy(p, arbol3.name);
		if (strcasecmp(arbol3.name, arbol.name) == 0) {
			char aux[25];
			char apunt[25];
			sprintf(aux, "%d", arbol.apuntadorAVD);
			sprintf(apunt, "%d", arbol.apuntadorAVD);
			strcat(cadena, " node");
			strcat(cadena, dato);
			strcat(cadena, ":p7");
			strcat(cadena, " -> node");
			strcat(cadena, apunt);
			strcat(cadena, ":f0;");

			strcat(cadena,
				completarDIRECTORIO(ruta, " ", arbol.apuntadorAVD));
		}
	}
	return cadena;
}

int reporteTREE_DIRECTORIO(char* id, char* name, char* path, char* ruta) {
	//printf("\nID = %s\n",id);

//VERIFICA SI EL EL ID EXISTE
	char* direcc;
	char* nombres;
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
					nombres = montar[i].name;
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

	int esLogica = 0;
	i = 0;
	int ii = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, nombres) == 0) {
			break;
		}
		for (ii = 0; ii < 20; ii++) {
			if (strcasecmp(structDisco.part[i].exten[ii].name, nombres) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("No Existe el nombre");
		return 0;
	}

	superbloque sb;
	if (esLogica == 1) {
		fseek(archivo, structDisco.part[i].exten[ii].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);

	} else {
		//int mos = structDisco.part[i].start;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fread(&sb, sizeof(superbloque), 1, archivo);
	}

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

	sb.magic = 201404368;
	if (sb.magic == 201404368) {
		char* path2;
		char path3[100];
		strcpy(path3, ruta);
		char* path1 = strtok(path3, "/");
		avd con;
		int info3;
		info3 = buscarArchivo(direcc, sb, con, path1, "w", 0, sb.apuntadorAVD);
		if (info3 > 10) {

//CREA EL REPORTE
			FILE* report;
			report = fopen(dot, "w+");
			fprintf(report, "digraph directorio{\n");
			fprintf(report, "rankdir = LR;\n");
			fprintf(report,
					"node [shape = record, fontsize=12,fontname=\"%s\", color=orange, height = 0.7]; ",
					"UBUNTU");
			char* path1;
			path1 = strtok(ruta, "/");
			printf("d= %s, a=%d, p=%s\n", direcc, sb.apuntadorAVD, path1);
			fprintf(report,
					completarTreeD1(direcc, "", sb.apuntadorAVD, path1));
			fprintf(report, completarTreeD2(direcc, "", info3));

			fprintf(report, "\n}");
			fclose(report);

			char *r1 = "dot -Tpng ";
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
			printf("-> Se creo el reporte TREE_DIRECTORIO correctamente.\n");
			char consola2[300];
			strcpy(consola2, "");
			strcat(consola2, "xdg-open ");
			strcat(consola2, auxDirecc);
			system(consola2);
		} else {

			printf("No existe direccion");
		}
	} else {
		printf("No se ha formateado");
	}
	return 1;
}

char* completarTreeD1(char* ruta, char* mensaje, int posicion, char*path) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd arbol;
	avd arbol2;
	char* path2 = path;
	fseek(archivo, posicion, SEEK_SET);
	fread(&arbol, sizeof(avd), 1, archivo);

	char cadena[10000];
	char dato[25];
	sprintf(dato, "%d", posicion);
	strcpy(cadena, "node");
	strcat(cadena, dato);
	strcat(cadena, " [label=\" {<f0> ");
	strcat(cadena, arbol.name);
	strcat(cadena, "}|{<p0>|<p1>|<p2>|<p3>|<p4>|<p5>|<p6>|<p7>} \"]; \n");
	strcat(cadena, mensaje);
	int i = 0;

	for (i = 0; i < 6; i++) {
//		int mostrar2 = con.subDirectorios[i];
		if (arbol.subDirectorios[i] > 0) {
			fseek(archivo, arbol.subDirectorios[i], SEEK_SET);
			fread(&arbol2, sizeof(avd), 1, archivo);
			if (strcasecmp(arbol2.name, path) == 0) {
				break;
			}
		}
	}
	fclose(archivo);
	if (i < 6) {

		path = strtok(NULL, "/");

		char cosas2[25];
		char cosas3[25];
		sprintf(cosas2, "%d", i);
		sprintf(cosas3, "%d", arbol.subDirectorios[i]);
		strcat(cadena, " node");
		strcat(cadena, dato);
		strcat(cadena, ":p");
		strcat(cadena, cosas2);
		strcat(cadena, " -> node");
		strcat(cadena, cosas3);
		strcat(cadena, ":f0;");

		if (path != NULL && path != 0x0) {
			strcat(cadena,
					completarTreeD1(ruta, " ", arbol.subDirectorios[i], path));
		} else {

			char cosas[25];
			sprintf(cosas, "%d", arbol.subDirectorios[i]);
			strcat(cadena, " node");
			strcat(cadena, cosas);
			strcat(cadena, " [label=\" {<f0> ");
			strcat(cadena, path2);
			strcat(cadena,
					"}|{<p0>|<p1>|<p2>|<p3>|<p4>|<p5>|<p6>|<p7>} \"]; \n");

			char cosas2[25];
			char cosas3[25];
			sprintf(cosas2, "%d", arbol2.directorio);
			sprintf(cosas3, "%d", arbol.subDirectorios[i]);
			strcat(cadena, " node");
			strcat(cadena, cosas3);
			strcat(cadena, ":p6");
			strcat(cadena, " -> node");
			strcat(cadena, cosas2);
			strcat(cadena, ":f0;");
		}
		//	int loool = con.apuntadorAVD;
	} else if (arbol.apuntadorAVD > 0) {
		char cosas2[25];
		char cosas3[25];
		sprintf(cosas2, "%d", arbol.apuntadorAVD);
		sprintf(cosas3, "%d", arbol.apuntadorAVD);
		strcat(cadena, " node");
		strcat(cadena, dato);
		strcat(cadena, ":p7");
		strcat(cadena, " -> node");
		strcat(cadena, cosas3);
		strcat(cadena, ":f0;");

		strcat(cadena,
				completarTreeD1(ruta, " ", arbol.apuntadorAVD, path));
	}

	return cadena;
}

char* completarTreeD2(char*ruta, char* mensaje, int posicion) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	char cadena[10000];
	char dato[25];
	sprintf(dato, "%d", posicion);
	strcpy(cadena, "node");
	strcat(cadena, dato);
	strcat(cadena, " [label=\" {<f0> nombre} ");
	int i = 0;

	for (i = 0; i < 5; i++) {

		if (carp.archivos[i].inodo > 1) {
			strcat(cadena, "|{");
			strcat(cadena, carp.archivos[i].name);
			strcat(cadena, "}");
		}
	}
	strcat(cadena, "\"]; \n");
	fclose(archivo);
	if (carp.detalle > 0) {
		char dato1[25];
		char dato2[25];
		sprintf(dato1, "%d", i);
		sprintf(dato2, "%d", carp.detalle);
		strcat(cadena, " node");
		strcat(cadena, dato);
		strcat(cadena, " -> node");
		strcat(cadena, dato2);
		strcat(cadena, ";");
		strcat(cadena, completarTreeD2(ruta, " ", carp.detalle));
	}
	return cadena;
}

