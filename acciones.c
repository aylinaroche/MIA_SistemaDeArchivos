#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "acciones.h"
#include "estructuras.h"
#include <math.h>
# include <setjmp.h>

char* ruta = NULL;
char* size = NULL;
char* unit = NULL;
char* path = NULL;
char* type = NULL;
char* fit = NULL;
char* dele = NULL;
char* name = NULL;
char* add = NULL;
char* id = NULL;
int boolCrearDisco = 1;
int varLetra = 0;
int boolK = 0;
int boolM = 0;
int boolH = 0;
int boolI = 0;
char* nDirectorio = NULL;
char* fs = NULL;
char* usuario = NULL;
char* password = NULL;
char* grupo = NULL;
char* p = NULL;
char* cont = NULL;
char* ugo = NULL;
char* R = NULL;
int boolR = 0;
char* filen = NULL;
int rf = 0;
char* dest = NULL;
char* iddest = NULL;
char* perm = NULL;
char* user = NULL;
char* file1 = NULL;
char* file2 = NULL;
char* file3 = NULL;
char* allocation = NULL;

int boolLogin = 0;
char* usrLogin = NULL;
int correcto = 1;
int boolEditar = 0;
int contadorUsuario = 0;
int contadorGrupo = 0;
char* contenidoUsers = NULL;

char caracter[1000];
char* inst = NULL;
char* contadorU = NULL;
char* tipoU = NULL;
char* grupoU = NULL;
char* nombreU = NULL;
char* passU = NULL;
int con = 1;
char* contEliminar = NULL;
char *tex1 = NULL;
char *tex2 = NULL;
char *tex3 = NULL;
char *tex4 = NULL;
char *tex5 = NULL;
char *tex6 = NULL;
char *tex7 = NULL;
char *tex8 = NULL;
atrib atrUsuario[50];
atrib atribUsuario[50];
int contadorM;

void limpiarVariables() {
	size = NULL;
	unit = NULL;
	path = NULL;
	type = NULL;
	fit = NULL;
	dele = NULL;
	name = NULL;
	add = NULL;
	id = NULL;
	boolK = 0;
	boolM = 0;
	boolH = 0;
	boolI = 0;
	nDirectorio = NULL;
	usuario = NULL;
	password = NULL;
	grupo = NULL;
	p = NULL;
	cont = NULL;
	ugo = NULL;
	boolR = 0;
	rf = 0;
	dest = NULL;
	iddest = NULL;
	perm = NULL;
	user = NULL;
	file1 = NULL;
	file2 = NULL;
	file3 = NULL;
	allocation = NULL;
	ruta = NULL;
	//contadorM = 0;
//	boolEditar=0;
}

void metodoPrueba() {
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

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		//return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	superbloque sb = crearBloque();
	char ajuste;

	int posicion;
	posicion = structDisco.part[i].start;
	ajuste = structDisco.part[i].fit;
	fseek(archivo, structDisco.part[i].start, SEEK_SET);
	fread(&sb, sizeof(superbloque), 1, archivo);

	printf("Magicos = %d\n", sb.magic);
}

void atributoDisco(char* coman) {
//printf("atributo disco %s\n",coman);
	char* token1 = tolower(coman);
	char* com = coman;
	//printf("T1 = %s\n",token1);
	token1 = strtok(com, "=");
	//printf("T1 = %s\n",token1);
	if (token1 != NULL) {
		if (strcasecmp(token1, "-tamanio") == 0
				|| strcasecmp(token1, "–tamanio") == 0
				|| strcasecmp(token1, "+tamanio") == 0) { //Verifica cada atributo
			token1 = strtok(NULL, ">");
			size = token1;
		} else if (strcasecmp(token1, "+unit") == 0) {
			token1 = strtok(NULL, ">");
			unit = token1;
		} else if (strcasecmp(token1, "-path") == 0
				|| strcasecmp(token1, "–path") == 0
				|| strcasecmp(token1, "+path") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			path = token1;
		} else if (strcasecmp(token1, "-ruta") == 0
				|| strcasecmp(token1, "–ruta") == 0
				|| strcasecmp(token1, "+ruta") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			ruta = token1;
			//printf("token1 = %s",token1);
		} else if (strcasecmp(token1, "+tipo") == 0 ||strcasecmp(token1, "+type") == 0) {
			token1 = strtok(NULL, ">");
			type = token1;
		} else if (strcasecmp(token1, "+fit") == 0) {
			token1 = strtok(NULL, ">");
			fit = token1;
		} else if (strcasecmp(token1, "+delete") == 0) {
			token1 = strtok(NULL, ">");
			dele = token1;
		} else if (strcasecmp(token1, "-nombre") == 0
				|| strcasecmp(token1, "–nombre") == 0) {
			token1 = strtok(NULL, ">");
			//printf("tok1 = %s\n",token1);
			char nombre[200];
			strcpy(nombre, token1);
			if (nombre[0] == '"') {
				int i = 0;
				while (nombre[i + 1] != '"') { //Le quita las comillas
					nombre[i] = nombre[i + 1];
					if (nombre[i] == ' ') {
						nombre[i] = '_';
					}
					i++;
				}
				nombre[i] = '\0';
				nombre[i + 1] = '\0';
			}
			//   printf("tok1 = %s\n",token1);
			strcpy(token1, nombre);
			name = token1;
		} else if (strcasecmp(token1, "+add") == 0) {
			token1 = strtok(NULL, ">");
			add = token1;
		} else if (strcasecmp(token1, "-id") == 0
				|| strcasecmp(token1, "–id") == 0) {
			token1 = strtok(NULL, ">");
			id = token1;
		} else if (strcasecmp(token1, "-id1") == 0
				|| strcasecmp(token1, "-id2") == 0
				|| strcasecmp(token1, "-id3") == 0
				|| strcasecmp(token1, "-id4") == 0
				|| strcasecmp(token1, "-id5") == 0
				|| strcasecmp(token1, "-id6") == 0
				|| strcasecmp(token1, "-id7") == 0
				|| strcasecmp(token1, "-id8") == 0) {

			token1 = strtok(NULL, ">");
			id = token1;

		} else if (boolExec == 1) { //********* MMM
			token1 = strtok(NULL, ">");
			printf("token1=%s\n", token1);
			char direccion[200];
			strcpy(direccion, token1);

			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			path = token1;

		} else if (strcasecmp(token1, "+k") == 0) {
			boolK = 1;
		} else if (strcasecmp(token1, "+m") == 0) {
			boolM = 1;
		} else if (strcasecmp(token1, "+h") == 0
				|| strcasecmp(token1, "-h") == 0
				|| strcasecmp(token1, "–h") == 0) {
			boolH = 1;
		} else if (strcasecmp(token1, "+i") == 0) {
			boolI = 1;
		} else if (strcasecmp(token1, "+n") == 0) {
			token1 = strtok(NULL, ">");
			nDirectorio = token1;
		} else if (strcasecmp(token1, "+fs") == 0) {
			token1 = strtok(NULL, ">");
			fs = token1;
		} else if (strcasecmp(token1, "-usr") == 0
				|| strcasecmp(token1, "–usr") == 0) {
			token1 = strtok(NULL, ">");
			usuario = token1;
		} else if (strcasecmp(token1, "-pwd") == 0
				|| strcasecmp(token1, "–pwd") == 0) {
			token1 = strtok(NULL, ">");
			password = token1;
		} else if (strcasecmp(token1, "-grp") == 0
				|| strcasecmp(token1, "–grp") == 0) {
			token1 = strtok(NULL, ">");
			grupo = token1;
		} else if (strcasecmp(token1, "-ugo") == 0
				|| strcasecmp(token1, "–ugo") == 0) {
			token1 = strtok(NULL, ">");
			ugo = token1;
		} else if (strcasecmp(token1, "+r") == 0) {
			boolR = 1;
		} else if (strcasecmp(token1, "+p") == 0
				|| strcasecmp(token1, "-p") == 0
				|| strcasecmp(token1, "–p") == 0) {
			p = "p";
		} else if (strcasecmp(token1, "+cont") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			cont = token1;
		} else if (strcasecmp(token1, "+rf") == 0) {
			rf = 1;
		} else if (strcasecmp(token1, "-dest") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			dest = token1;
		} else if (strcasecmp(token1, "-iddest") == 0) {
			token1 = strtok(NULL, ">");
			iddest = token1;
		} else if (strcasecmp(token1, "+perm") == 0) {
			token1 = strtok(NULL, ">");
			perm = token1;
		} else if (strcasecmp(token1, "+user") == 0) {
			token1 = strtok(NULL, ">");
			user = token1;
		} else if (strcasecmp(token1, "-file1") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			file1 = token1;

		} else if (strcasecmp(token1, "-file2") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			file2 = token1;

		} else if (strcasecmp(token1, "-file3") == 0) {
			token1 = strtok(NULL, ">");
			char direccion[200];
			strcpy(direccion, token1);
			if (direccion[0] == '"') {
				int i = 0;
				while (direccion[i + 1] != '"') { //Le quita las comillas
					direccion[i] = direccion[i + 1];
					if (direccion[i] == ' ') {
						direccion[i] = '_';
					}
					i++;
				}
				direccion[i] = '\0';
				direccion[i + 1] = '\0';
			}
			strcpy(token1, direccion);
			file3 = token1;

		} else if (strcasecmp(token1, "+allocation") == 0) {
			token1 = strtok(NULL, ">");
			allocation = token1;
		} else {
			printf("ERROR: El atributo \"%s\" es incorrecto.\n", token1);
		}

	}
}

void mostrarMontadas() {
	int i;
	if (contadorM == 0) {
		printf("-> No existe ningua particion montada.\n");
	}
	//printf("contadorM = %d\n", contadorM);
	for (i = 0; i < 5; i++) {
		printf("M%d= id=>%s  -path=>%s  -nombre=>%s \n", i, montar[i].vdID,
				montar[i].path, montar[i].name);
	}
}

void crearDisco() {
	boolCrearDisco = 1;
	if (size == NULL || path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (size > 0) {
			int d = crearArchivoBinario(size, path, name);
			if (d == 0) {
				printf(
						"-> Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else {
			printf("ERROR: El tamanio es incorrecto.\n");
		}
	}
}

int crearArchivoBinario(char* size, char* path, char* name) {
	int unidad = 0;
	int tam = atoi(size);

//COMPROBAR POSIBLES ERRORES
	if (tam < 8) {
		printf("ERROR: El tamanio minimo para un disco es de 8Mb.\n");
		boolCrearDisco = 0;
		return 0;
	} else {
		int b = multiploDeOcho(tam);
		if (b == 0) {
			printf("ERROR: El tamanio no es multiplo de 8.\n");
			boolCrearDisco = 0;
			return 0;
		}
	}

	char* ext = NULL;
	ext = name;
	int boolExt = 0;

	ext = strtok(name, ".");
	while (ext != NULL) {
		ext = strtok(NULL, ".");
		if (ext != NULL) {
			if (strcasecmp(ext, "dsk") == 0) {
				boolExt = 1;
			}
		}
	}
	if (boolExt == 0) {
		printf("ERROR: El nombre no tiene extension.\n");
		boolCrearDisco = 0;
		return 0;
	}
/////////////////////////////////////////////////////////////////

	if (boolCrearDisco == 1) {
		char direcc[200];
		char direcc2[200];
		int i = 0;
		for (i = 0; i < 200; i++) {
			direcc2[i] = '\0';
		}
		strcat(name, ".dsk");
		strcat(path, name);
		// printf("PATH = %s\n",path);
		strcpy(direcc, path);

		for (i = 0; i < 200; i++) {
			if (direcc[i] == '/') {
				direcc2[i] = direcc[i];
				char *aux = (char*) malloc(200);
				strcpy(aux, "mkdir ");
				strcat(aux, direcc2);
				//	printf("Ruta de Archivo: %s\n", aux);
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

		mbr structDisco;
		structDisco.fecha = time(0);
		int as = aleatorio();
		structDisco.signature = as;
		i = 0;
		for (i = 0; i < 4; i++) {
			structDisco.part[i].size = 0;
			structDisco.part[i].auxiliar = 0;
			structDisco.part[i].start = 0;
			structDisco.part[i].fit = '0';
			structDisco.part[i].status = '0';
			structDisco.part[i].type = '0';
			int j = 0;
			for (j = 0; j < 20; j++) {
				structDisco.part[i].exten[j].status = '0';
				structDisco.part[i].exten[j].fit = '0';
				structDisco.part[i].exten[j].next = 0;
				structDisco.part[i].exten[j].size = 0;
				structDisco.part[i].exten[j].auxiliar = 0;
				structDisco.part[i].exten[j].start = 0;
			}
		}
		char buffer[1024];
		i = 0;
		for (i = 0; i < 1024; i++) {
			buffer[i] = '0';
		}

		FILE *disco;
		//printf("P = %s\n",path);
		disco = fopen(path, "wb+");
		if (disco) {
		} else {
			printf("ERROR: Al crear archivo.\n");
			return 0;
		}

		//MegaBytes
		structDisco.size = tam * 1024 * 1024;
		tam = tam * 1024;
		i = 0;

		for (i = 0; i < tam; i++) {
			fwrite(&buffer, 1024, 1, disco);
		}
		//printf("SIZE = %d\n",sizeof(mbr));

		fseek(disco, 0, SEEK_SET);
		fwrite(&structDisco, sizeof(mbr), 1, disco);
		fclose(disco);
		printf("-> Se creo el disco correctamente.\n");

		return 1;
	}
	return 1;
}

int multiploDeOcho(int tam) {
	int i = 0;
	for (i = 8; i < 300; i = i + 8) {
		if (i == tam) {
			return 1;
		}
	}
	return 0;
}

void imprimirDatos() {
	printf("DATOS:\n");
	printf("  unit = %s\n", unit);
	printf("  size = %s\n", size);
	printf("  path = %s\n", path);
	printf("  name = %s\n", name);
	printf("  type = %s\n", type);
	printf("  add = %s\n", add);
	printf("  delete = %s\n", dele);
	printf("  fit = %s\n", fit);
	printf("  id = %s\n", id);
	printf("  K = %d\n", boolK);
	printf("  M = %d\n", boolM);
	printf("  H = %d\n", boolH);
	printf("  I = %d\n", boolI);
	printf("  n = %s\n", nDirectorio);
	printf("  usr = %s\n", usuario);
	printf("  pwd = %s\n", password);
	printf("  grp = %s\n", grupo);
	printf("  p = %s\n", p);
	printf("  cont = %s\n", cont);
	printf("  ugo = %s\n", ugo);
	printf("  R = %s\n", R);
	printf("  rf = %d\n", rf);
}

int eliminarDisco() {
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	} else {
		char com[5];
		printf("-> ¿Desea continuar? [S/n]: \n");
		fgets(com, 5, stdin);
		if (com[0] == 's' || com[0] == 'S') {
			char* aux;
			aux = (char*) malloc(160);
			strcpy(aux, "rm ");
			strcat(aux, path);
			system(aux);
			printf("-> Disco eliminado con exito.\n");
		} else {
			printf("-> No se elimino el disco.\n");
		}
	}
	return 1;
}

void adminParticion() {
	//Atributos opcionales
	if (unit == NULL) {
		unit = "k"; //kilobytes
	}
	if (type == NULL) {
		type = "p"; //primaria
	}
	if (fit == NULL) {
		fit = "wf"; //peor ajuste
	}

	//Atributos obligatorios
	if (add == NULL && dele == NULL) {
		if (path == NULL || size == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = crearParticion(path, name, size, unit, type, fit);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	} else if (dele == NULL) {
		if (path == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = agregarParticion(add, unit, path, name);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	} else if (add == NULL) {
		if (path == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = eliminarParticion(dele, path, name);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	} else {
		if (path == NULL || name == NULL) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		} else {
			int d = agregarParticion(add, unit, path, name);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		}
	}
}

int crearParticion(char* path, char* name, char* size, char* unit, char* type,
		char* fit) {
	int tam = atoi(size);
	int libre = 0;

	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);
	int tipo = 0;
	char ajuste[5];

//VERIFICAR EL TIPO
	if (strcasecmp(type, "P\n") == 0 || strcasecmp(type, "p") == 0
			|| strcasecmp(type, "p\r") == 0) { //primaria
		tipo = 1;
	} else if (strcasecmp(type, "L\n") == 0 || strcasecmp(type, "l") == 0
			|| strcasecmp(type, "l\r") == 0) { //logica
		tipo = 2;
		//printf("tipo 2\n");
	} else if (strcasecmp(type, "E\n") == 0 || strcasecmp(type, "e") == 0
			|| strcasecmp(type, "e\r") == 0) { //extendida
		tipo = 3;
	} else {
		printf("ERROR: Tipo de particion incorrecta.%s**\n", type);

		return 0;
	}

	//VERIFICAR LA UNIDAD

	int bytes = 0;
	if (strcasecmp(unit, "b") == 0 || strcasecmp(unit, "b\n") == 0
			|| strcasecmp(unit, "b\r") == 0) { //Kilobyte -> 1024 bytes
		if (tam < 2097152) { //2 *1024 *1024
			printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
			return 0;
		} else {
			bytes = tam;
		}

	} else if (strcasecmp(unit, "k") == 0 || strcasecmp(unit, "k\n") == 0
			|| strcasecmp(unit, "k\r") == 0) { //byte -> 8bits
		if (tam < 2048) { //2 * 1024
			printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
			return 0;
		} else {
			bytes = tam * 1024;
		}
	} else if (strcasecmp(unit, "m") == 0 || strcasecmp(unit, "m\n") == 0
			|| strcasecmp(unit, "m\r") == 0) { //megabyte -> 1024 Kb
		if (tam < 2) {
			printf("ERROR: El tamanio minimo para una particion es 2Mb\n");
			return 0;
		} else {
			bytes = tam * 1024 * 1024;
		}
	} else {
		printf("ERROR: La unidad no existe.%s**\n", unit);
		return 0;
	}

//VERIFICAR AJUSTE
	if (strcasecmp(fit, "BF\n") == 0 || strcasecmp(fit, "bf") == 0
			|| strcasecmp(fit, "bF") == 0 || strcasecmp(fit, "bf\r") == 0) {
		strcpy(ajuste, "B");
	} else if (strcasecmp(fit, "FF\n") == 0 || strcasecmp(fit, "ff") == 0
			|| strcasecmp(fit, "fF") == 0 || strcasecmp(fit, "Ff\r") == 0) {
		strcpy(ajuste, "F");
	} else if (strcasecmp(fit, "WF\n") == 0 || strcasecmp(fit, "wf") == 0
			|| strcasecmp(fit, "wF") == 0 || strcasecmp(fit, "Wf\r") == 0) {
		strcpy(ajuste, "W");
	} else {
		printf("ERROR: No existe el ajuste indicado.%s**\n", fit);
		return 0;
	}
	int i = 0;
	for (i = 0; i < 4; i++) {
		if (strcasecmp(name, structDisco.part[i].name) == 0) {
			printf("ERROR: Ya existe el nombre.\n");
			return 0;
		}
	}
//Limpiar
	/*for (i = 0; i < 4; i++) {
	 if (structDisco.part[i].type != 'e' && structDisco.part[i].type != 'p'
	 && structDisco.part[i].type != 'l') {
	 printf("Es diferente = %c\n", structDisco.part[i].type);
	 structDisco.part[i].status = '0';
	 structDisco.part[i].type = 'l';
	 }
	 }*/
//VERIFICAR NOMBRE REPETIDO
	if (tipo == 1) { //primaria
		for (i = 0; i < 4; i++) {
			///  printf("Primaria= %s\n",structDisco.part[i].name);
			if (strcasecmp(name, structDisco.part[i].name) == 0) {
				printf("ERROR: Ya existe el nombre.\n");
				return 0;
			}
		}
	} else if (tipo == 3) { //extendida
		for (i = 0; i < 4; i++) {
			//  printf("Extendida= %s\n",structDisco.part[i].name);
			if (structDisco.part[i].type == 'E'
					|| structDisco.part[i].type == 'e'
					|| strcasecmp(name, structDisco.part[i].name) == 0) {
				printf("ERROR: Ya existe una particion extendida.\n");
				return 0;
			}
		}
	} else {
		for (i = 0; i < 4; i++) {
			if (structDisco.part[i].type == 'E'
					|| structDisco.part[i].type == 'e') {
				int j = 0;
				for (j = 0; j < 20; j++) {
					if (strcasecmp(name, structDisco.part[i].exten[j].name)
							== 0) {
						printf("ERROR: Ya existe el nombre.\n");
						return 0;
					}
				}
				break;
			}
		}
		if (i == 4) {
			printf("ERROR: No existe una particion extendida.\n");
			return 0;
		}
	}
	//VERIFICAR EL TAMANIO DE LA PARTICION Y LA CANTIDAD DE PARTICIONES
	int particion = 0;
	int contParticion = 0;
	for (i = 0; i < 4; i++) {
		if (structDisco.part[i].status == '1') {
			//printf("No = %d , Tipo = %c\n", contParticion + 1,structDisco.part[i].type);
			particion = particion + structDisco.part[i].size;
			contParticion++;
		}
	}
	if (contParticion == 4 && tipo != 2) {
		printf("ERROR: Ya existen 4 particiones. %d\n", tipo);
		return 0;
	}

//VERIFICAR TAMANIO DE PARTICION
	libre = structDisco.size - particion;
	int esp = 0; //espacio

	if (tipo == 1 || tipo == 3) { // Si la particion es primaria o extendida
		if (libre < bytes) {
			printf("ERROR: No hay tamaño disponible1.\n");
			return 0;
		}

//ASINGAR TIPO, AJUSTE, TAMANIO
		for (i = 0; i < 4; i++) {
			if (structDisco.part[i].status == '0') {
				if (structDisco.part[i].size == 0
						|| bytes < structDisco.part[i].size) {
					if (ajuste[0] == 'F') {
						structDisco.part[i].fit = 'F';
					} else if (ajuste[0] == 'B') {
						structDisco.part[i].fit = 'B';
					} else {
						structDisco.part[i].fit = 'W';
					}
					strcpy(structDisco.part[i].name, name);
					//printf("Asignacion ==  %s\n",structDisco.part[i].name);
					structDisco.part[i].size = bytes;
					structDisco.part[i].auxiliar = bytes;
					if (i == 0) {
						//printf("Size of=%d\n",sizeof(mbr));
						structDisco.part[i].start = sizeof(mbr) + 1;
						esp = 1;
					} else {
						structDisco.part[i].start =
								structDisco.part[i - 1].start
										+ structDisco.part[i - 1].size;
						esp = 1;
					}
					structDisco.part[i].status = '1';

					if (strcasecmp(type, "E") == 0
							|| strcasecmp(type, "e") == 0) {
						structDisco.part[i].type = 'e';
					} else {
						structDisco.part[i].type = 'p';
					}
					esp = 1;
					break;
				}
			}
		}
	} else { //Si la particion es logica
		for (i = 0; i < 4; i++) {
			if (structDisco.part[i].type == 'E'
					|| structDisco.part[i].type == 'e') { //Si existe una extendida antes
				int j = 0;
				for (j = 0; j < 20; j++) {
					int j = 0;
					int espa = 0; //suma de todas las particiones extendidas
					for (j = 0; j < 20; j++) {
						espa = espa + structDisco.part[i].exten[j].size;
					}
					espa = structDisco.part[i].auxiliar - espa;
					if (espa < bytes) {
						printf("ERROR: No hay tamaño disponible2.\n");
						return 0;
					}

					if (structDisco.part[i].exten[j].status == '0') {
						if (structDisco.part[i].exten[j].size == 0
								|| bytes < structDisco.part[i].exten[j].size) {

							if (ajuste[0] == 'F') { //Primer ajuste
								structDisco.part[i].exten[j].fit = 'F';
							} else if (ajuste[0] == 'B') { //Mejor Ajuste
								structDisco.part[i].exten[j].fit = 'B';
							} else {
								structDisco.part[i].exten[j].fit = 'W'; //Peor ajuste
							}
							strcpy(structDisco.part[i].exten[j].name, name);
							structDisco.part[i].exten[j].size = bytes;
							structDisco.part[i].exten[j].auxiliar = bytes;

							if (j == 0) { //
								structDisco.part[i].exten[j].start =
										structDisco.part[i].start + 1;
								structDisco.part[i].exten[j].next = -1;
								esp = 1;
							} else {
								structDisco.part[i].exten[j].start =
										structDisco.part[i].exten[j - 1].start
												+ structDisco.part[i].exten[j
														- 1].size;
								structDisco.part[i].exten[j - 1].next =
										structDisco.part[i].exten[j - 1].start
												+ structDisco.part[i].exten[j
														- 1].size;
								esp = 1;
							}

							structDisco.part[i].exten[j].status = '1';
							esp = 1;
							break;
						}
					}
				}
			}
		}
	}
	if (esp == 0) {
		printf("ERROR: Espacio insuficiente.");
		return 0;
	}

	fseek(archivo, 0, SEEK_SET);
	//printf("Size2 = %d\n",sizeof(mbr));
	fwrite(&structDisco, sizeof(mbr), 1, archivo);
	fclose(archivo);
	printf("-> Se creo la particion correctamente.\n");
	return 1;

}

int agregarParticion(char* add, char* unit, char* path, char* name) {

	int tam = atoi(add);

//VERIFICA SI EL DISCO EXISTE
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICA LA UNIDAD DEL DISCO
	int bytes = 0;
	if (strcasecmp(unit, "k") == 0 || strcasecmp(unit, "K") == 0) {
		bytes = tam * 1024;
	} else if (strcasecmp(unit, "m") == 0 || strcasecmp(unit, "M") == 0) {
		bytes = tam * 1024 * 1024;
	} else if (strcasecmp(unit, "b") == 0 || strcasecmp(unit, "B") == 0) {
		bytes = tam;
	} else {
		printf("ERROR: Unidad incorrecta.\n");
		return 0;
	}
	int i = 0, j = 0;
	int esLogica = 0;

//VERIFICA SI EL NOMBRE EXISTE
	for (i = 0; i < 4; i++) {
		if (strcasecmp(name, structDisco.part[i].name) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(name, structDisco.part[i].exten[j].name) == 0) {
				esLogica = 1;
				break;
			}
		}
		if (esLogica > 0) {
			break;
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: El nombre indicado no existe.\n");
		return 0;
	}

//VERIFICAR SI EL ESPACIO ES SUFICIENTE
	if (esLogica > 0) {
		if (bytes > 0) {
			if (j < 20) { //j depende de donde encontro el nombre
				printf("j = %d\n", j);
				if (structDisco.part[i].exten[j + 1].start != 0) { //Si no es la primer particion
					int siguiente = structDisco.part[i].exten[j].start
							+ structDisco.part[i].exten[j].auxiliar;
					int anterior = structDisco.part[i].exten[j + 1].start;

					int resta = anterior - siguiente;

					if (resta < bytes) {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
					structDisco.part[i].exten[j].auxiliar =
							structDisco.part[i].exten[j].auxiliar + bytes;

					if (structDisco.part[i].exten[j].auxiliar
							> structDisco.part[i].exten[j].size) {
						structDisco.part[i].exten[j].size =
								structDisco.part[i].exten[j].size
										+ (structDisco.part[i].exten[j].auxiliar
												- structDisco.part[i].exten[j].size);
					}

				} else { //Si es la primer particion

					int j = 0;
					int suma = 0;
					for (j = 0; j < 20; j++) {
						suma = suma + structDisco.part[i].exten[j].size;
					}
					int resta = structDisco.part[i].auxiliar - suma;
					if (resta < bytes) {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
					structDisco.part[i].exten[j].auxiliar =
							structDisco.part[i].exten[j].auxiliar + bytes;
					if (structDisco.part[i].exten[j].auxiliar
							> structDisco.part[i].exten[j].size) {
						structDisco.part[i].exten[j].size =
								structDisco.part[i].exten[j].size
										+ (structDisco.part[i].exten[j].auxiliar
												- structDisco.part[i].exten[j].size);
					}
				}
			} else { //Si es la primera particion
				int j = 0;
				int suma = 0;
				for (j = 0; j < 20; j++) {
					suma = suma + structDisco.part[i].exten[j].size;
				}
				int resta = structDisco.part[i].auxiliar - suma;
				if (resta < bytes) {
					printf("ERROR: No hay espacio disponible.\n");
					return 0;
				}
				structDisco.part[i].exten[j].auxiliar =
						structDisco.part[i].exten[j].auxiliar + bytes;
				if (structDisco.part[i].exten[j].auxiliar
						> structDisco.part[i].exten[j].size) {
					structDisco.part[i].exten[j].size =
							structDisco.part[i].exten[j].size
									+ (structDisco.part[i].exten[j].auxiliar
											- structDisco.part[i].exten[j].size);
				}

			}
		} else { //Si los bytes son 0
			if (j < 20) {
				if (structDisco.part[i].exten[j + 1].start != 0) { //Si no es la primer particion
					int resta = structDisco.part[i].exten[j].auxiliar + bytes;
					if (resta > 0) {
						structDisco.part[i].exten[j].auxiliar = resta;
					} else {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
				} else { //Si es la primer particion
					int resta = bytes + structDisco.part[i].exten[j].auxiliar;
					if (resta > 0) {
						structDisco.part[i].exten[j].auxiliar = resta;
						structDisco.part[i].exten[j].size = resta;
					} else {
						printf("ERROR: No hay espacio disponible.\n");
						return 0;
					}
				}
			} else {
				int resta = bytes + structDisco.part[i].exten[j].auxiliar;
				if (resta > 0) {
					structDisco.part[i].exten[j].auxiliar = resta;
					structDisco.part[i].exten[j].size = resta;
				} else {
					printf("ERROR: No hay espacio disponible.\n");
					return 0;
				}
			}
		}
	} else {
		if (bytes > 0) {
			if (i < 3) {
				if (structDisco.part[i + 1].start != 0) {
					int siguiente = structDisco.part[i].auxiliar
							+ structDisco.part[i].start;
					int anterior = structDisco.part[i + 1].start;
					int resta = anterior - siguiente;
					if (resta < bytes) {
						printf("No hay espacio disponible.\n");
						return 0;
					}
					structDisco.part[i].auxiliar = structDisco.part[i].auxiliar
							+ bytes;
					if (structDisco.part[i].auxiliar
							> structDisco.part[i].size) {
						structDisco.part[i].size = structDisco.part[i].size
								+ (structDisco.part[i].auxiliar
										- structDisco.part[i].size);
					}
				} else {
					int k = 0;
					int suma = 0;
					for (k = 0; k < 4; k++) {
						suma = suma + structDisco.part[k].size;
					}
					int resta = structDisco.size - suma;
					if (resta < bytes) {
						printf("No hay espacio disponible.\n");
						return 0;
					}
					structDisco.part[i].auxiliar = structDisco.part[i].auxiliar
							+ bytes;
					if (structDisco.part[i].auxiliar
							> structDisco.part[i].size) {
						structDisco.part[i].size = structDisco.part[i].size
								+ (structDisco.part[i].auxiliar
										- structDisco.part[i].size);
					}
				}
			} else {
				int k = 0;
				int suma = 0;
				for (k = 0; k < 4; k++) {
					suma = suma + structDisco.part[k].size;
				}
				int resta = structDisco.size - suma;
				if (resta < bytes) {
					printf("No hay espacio disponible.\n");
					return 0;
				}
				structDisco.part[i].auxiliar = structDisco.part[i].auxiliar
						+ bytes;
				if (structDisco.part[i].auxiliar > structDisco.part[i].size) {
					structDisco.part[i].size = structDisco.part[i].size
							+ (structDisco.part[i].auxiliar
									- structDisco.part[i].size);
				}
			}
		} else {
			if (i < 3) {
				if (structDisco.part[i + 1].start != 0) {
					int resta = bytes + structDisco.part[i].auxiliar;
					int k = 0;
					int sumadora = 0;
					for (k = 0; k < 8; k++) {
						if (structDisco.part[i].exten[k].size > 0) {
							sumadora = sumadora
									+ structDisco.part[i].exten[k].size;
						}
					}
					if (resta > sumadora) {
						structDisco.part[i].auxiliar = resta;
					} else {
						printf("No hay espacio para borrar ");
						return 0;
					}
				} else {
					int resta = bytes + structDisco.part[i].auxiliar;
					int k = 0;
					int sumadora = 0;
					for (k = 0; k < 8; k++) {
						sumadora = sumadora + structDisco.part[i].exten[k].size;
					}
					if (resta > sumadora) {
						structDisco.part[i].auxiliar = resta;
						structDisco.part[i].size = resta;
					} else {
						printf("No hay espacio para disponible.\n");
						return 0;
					}
				}
			} else {
				int resta = bytes + structDisco.part[i].auxiliar;
				int k = 0;
				int sumadora = 0;
				for (k = 0; k < 8; k++) {
					sumadora = sumadora + structDisco.part[i].exten[k].size;
				}
				if (resta > sumadora) {
					structDisco.part[i].auxiliar = resta;
					structDisco.part[i].size = resta;
				} else {
					printf("No hay espacio disponible.\n");
					return 0;
				}
			}
		}
	}
//*****************************************************
	fseek(archivo, 0, SEEK_SET);
	fwrite(&structDisco, sizeof(mbr), 1, archivo);
	fclose(archivo);
	printf("-> Se realizo la modificacion correctamente.\n");
	return 1;
}

int eliminarParticion(char* dele, char* path, char* name) {

//VERIFICA SI EXISTE EL DISCO
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco.\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	int esLogica = 0;
	int tipoDelete = 0;
	int i = 0;
	int j = 0;

//VERIFICA TIPO DE ELIMINAR
	if (strcasecmp(dele, "full") == 0) {
		tipoDelete = 1;
	} else if (strcasecmp(dele, "fast") == 0) {
		tipoDelete = 2;
	} else {
		printf("ERROR: Tipo de Delete incorrecto.\n");
		return 0;
	}

//VERIFICA SI EL NOMBRE EXISTE
	for (i = 0; i < 4; i++) {
		if (strcasecmp(structDisco.part[i].name, name) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, name) == 0) {
				esLogica = 1;
				break;
			}
		}
		if (esLogica == 1) {
			break;
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre.\n");
		return 0;
	}

//SI EXISTE...

	if (esLogica == 1) {
		//si hay extendida
		if (j < 20) { //i , j lugar donde encontro la particion
			//LIMPIAR VARIABLES
			if (structDisco.part[i].exten[j + 1].status != '0') {
				structDisco.part[i].exten[j].status = '0';
				strcpy(structDisco.part[i].exten[j].name, " ");
			} else {
				structDisco.part[i].exten[j].status = '0';
				structDisco.part[i].exten[j].start = 0;
				structDisco.part[i].exten[j].size = 0;
				structDisco.part[i].exten[j].auxiliar = 0;
				strcpy(structDisco.part[i].exten[j].name, " ");
			}
		} else { //Si no hay extendida
			structDisco.part[i].exten[j].status = '0';
			structDisco.part[i].exten[j].start = 0;
			structDisco.part[i].exten[j].size = 0;
			structDisco.part[i].exten[j].auxiliar = 0;
			strcpy(structDisco.part[i].exten[j].name, " ");
		}
	} else { // Si no existe
		if (i < 3) {
			if (structDisco.part[i + 1].status != '0') {
				if (structDisco.part[i].type == 'e'
						|| structDisco.part[i].type == 'E') {
					int k = 0;
					structDisco.part[i].type = '0'; //+
					for (k = 0; k < 20; k++) {
						structDisco.part[i].exten[k].status = '0';
						structDisco.part[i].exten[k].start = 0;
						structDisco.part[i].exten[k].size = 0;
						structDisco.part[i].exten[k].auxiliar = 0;
						strcpy(structDisco.part[i].exten[k].name, " ");
					}
				}
				structDisco.part[i].status = '0';
				structDisco.part[i].type = '0';
				strcpy(structDisco.part[i].name, " ");
			} else {
				if (structDisco.part[i].type == 'e'
						|| structDisco.part[i].type == 'E') {
					int k = 0;
					structDisco.part[i].type = '0'; //+
					for (k = 0; k < 20; k++) {
						structDisco.part[i].exten[k].status = '0';
						structDisco.part[i].exten[k].start = 0;
						structDisco.part[i].exten[k].size = 0;
						structDisco.part[i].exten[k].auxiliar = 0;
						strcpy(structDisco.part[i].exten[k].name, " ");
					}
				}
				structDisco.part[i].status = '0';
				structDisco.part[i].start = 0;
				structDisco.part[i].size = 0;
				structDisco.part[i].auxiliar = 0;
				structDisco.part[i].type = '0';
				strcpy(structDisco.part[i].name, " ");
			}
		} else {
			if (structDisco.part[i].type == 'e'
					|| structDisco.part[i].type == 'E') {
				int k = 0;
				for (k = 0; k < 8; k++) {
					structDisco.part[i].exten[k].status = '0';
					structDisco.part[i].exten[k].start = 0;
					structDisco.part[i].exten[k].size = 0;
					structDisco.part[i].exten[k].auxiliar = 0;
					strcpy(structDisco.part[i].exten[k].name, " ");
				}
			}
			structDisco.part[i].status = '0';
			structDisco.part[i].start = 0;
			structDisco.part[i].size = 0;
			structDisco.part[i].auxiliar = 0;
			structDisco.part[i].type = '0';
			strcpy(structDisco.part[i].name, " ");
		}
	}
	fseek(archivo, 0, SEEK_SET);
	fwrite(&structDisco, sizeof(mbr), 1, archivo);
	fclose(archivo);
	printf("-> Se elimino correctamente.\n");
	return 1;
}

void montarP() {
	if (path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio = %s.\n", name);
	} else {
		//	printf("else\n");
		int d = montarParticion(path, name);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int montarParticion(char* path, char* name) {
	FILE* archivo;
	archivo = fopen(path, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

//VERIFICA SI EL NOMBRE DE LA PARTICION EXISTE
	int boolExten = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < 4; i++) {
		//printf("%s * * * %s\n",structDisco.part[i].name,name);
		if (strcasecmp(structDisco.part[i].name, name) == 0) {
			break;
		}
		for (j = 0; j < 20; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, name) == 0) {
				//printf("%s * * * %s\n", structDisco.part[i].exten[j].name,
				//			name);

				boolExten = 1;
				break;
			}
			if (boolExten == 1) {
				break;
			}
		}
	}
	if (i == 4 && boolExten == 0) {
		printf("ERROR: No existe el nombre de la particion.\n");
		fclose(archivo);
		return 0;
	}
	//VERIFICAR SI EL PATH Y LA PARTICION YA ESTA REGISTRADO
	int pop = 0;
	for (pop = 0; pop < 31; pop++) {

		if (strcasecmp(montar[pop].path, path) == 0
				&& strcasecmp(montar[pop].name, name) == 0) {
			if (montar[pop].estado == 1) {
				printf("-> La particion ya esta montada:: %s\n",
						montar[pop].vdID);
			} else {
			}
			fclose(archivo);
			return 0;
		}
	}
	int a = 0, c = 0;
	int v = 0, boolExistePath = 0;

	for (a = 0; a < 31; a++) {
		if (strcasecmp(montar[a].path, path) == 0) {
			c++;
			boolExistePath = 1;
			v = montar[a].var;
		} else {
		}
	}

	if (boolExistePath == 1) {
		for (a = 0; a < 31; a++) {
			if (montar[a].uso == 0) {
				break;
			}
		}
		int cont = 0;
		for (pop = 0; pop < 31; pop++) {
			if (path != NULL) {
				if (strcasecmp(montar[pop].path, path) == 0) {
					cont++;
				}
			}
		}

		montar[a].estado = 1;
		montar[a].uso = '1';
		strcpy(montar[a].path, path);
		strcpy(montar[a].name, name);
		int p;
		p = montar[a].part;
		p = p + 1;
		montar[a].part++;
		char *letra = letraDisco(v);
		char n = p + '0';
		//	printf("n =%c",n);
		char *num = numeroMontar(cont);
		//sprintf(num, "%d", p);
		char *str = (char *) malloc(1 + strlen(letra) + strlen(num));
		strcpy(str, letra);
		strcat(str, num);
		montar[a].vdID = str;
		montar[a].var = v;
		printf("-> Se monto la particion con id::%s correctamente.\n", str);

	} else {
		for (a = 0; a < 31; a++) {
			if (montar[a].uso == 0) {
				break;
			}
		}
		varLetra++;
		v = varLetra;
		montar[a].estado = 1;
		montar[a].uso = '1';
		//	printf("path = %s\n",path);
		strcpy(montar[a].path, path);
		montar[a].var = v;
		montar[a].part = 1;
		strcpy(montar[a].name, name);
		//printf("varLetra =%d\n",varLetra);

		char *letra = letraDisco(varLetra);
		char *num = "1";
		char *str = (char *) malloc(1 + strlen(letra) + strlen(num));
		strcpy(str, letra);
		strcat(str, num);
		montar[a].vdID = str;
		printf("-> Se monto la particion con id::%s correctamente.\n", str);
		contadorM = contadorM + 1;
	}
	/*
	 //VERIFICAR SI EL NOMBRE COINCIDE CON LA PARTICION
	 int j = 0;
	 int existeLogica = 0;
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
	 printf("MAGIC = %d\n", sb.magic);
	 sb.mountCount = 5;
	 */
	fclose(archivo);

	return 1;
}

char *numeroMontar(int num) {
	char *numero;
	switch (num) {
	case 0:
		numero = "1";
		break;

	case 1:
		numero = "2";
		break;
	case 2:
		numero = "3";
		break;
	case 3:
		numero = "4";
		break;
	case 4:
		numero = "5";
		break;
	case 5:
		numero = "6";
		break;
	case 6:
		numero = "7";
		break;
	case 7:
		numero = "8";
		break;
	case 8:
		numero = "9";
		break;
	case 9:
		numero = "10";
		break;
	case 10:
		numero = "11";
		break;
	case 11:
		numero = "12";
		break;
	case 12:
		numero = "13";
		break;
	}
	return numero;
}

char *letraDisco(int varLetra) {
	char *letra;

	switch (varLetra) {
	case 0:
		letra = "vd";
		break;
	case 1:
		letra = "vda";
		break;
	case 2:
		letra = "vdb";
		break;
	case 3:
		letra = "vdc";
		break;
	case 4:
		letra = "vdd";
		break;
	case 5:
		letra = "vde";
		break;
	case 6:
		letra = "vdf";
		break;
	case 7:
		letra = "vdg";
		break;
	case 8:
		letra = "vdh";
		break;
	case 9:
		letra = "vdi";
		break;
	case 10:
		letra = "vdj";
		break;
	case 11:
		letra = "vdk";
		break;
	case 12:
		letra = "vdl";
		break;
	}

	return letra;
}

void desmontar() {
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = desmontarParticion(id);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
	metodoPrueba();
}

int desmontarParticion(char* id) {
	//printf("ID=%s\n", id);
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n", montar[i].vdID, id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				printf("igual\n");
				if (montar[i].estado == 1) {
					montar[i].estado = 0;
					montar[i].vdID = NULL;
					printf("-> Se ha desmontado la particion correctamente.\n");
					contadorM = contadorM - 1;
					return 1;
				}
			}
		}
	}
	printf("ERROR: El ID no existe.\n");
	return 0;

}

int aleatorio() {
	srand(time(NULL));
	int test = rand() % 20;

	return test;
}

void script() {
	if (path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = ejecutarScript(path);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int ejecutarScript(char *path) {
	//printf("P=%s\n",path);
	FILE* archivo;
	char caracter[1000];
	archivo = fopen(path, "r+");
	if (archivo == NULL) {
		printf("ERROR: No existe el archivo.\n");
		return 0;
	} else {
		int j = 0;
		for (j = 0; j < 1000; j++) {
			caracter[j] = '\0';
		}
		int i = 0;
		while (feof(archivo) == 0) { // *feof* hasta que se acabe el archivo
			caracter[i] = fgetc(archivo); // *fgetc* lee lineapor linea
			printf(&caracter[i]);
			//caracter[i]= tolower(caracter[i]);
			if (caracter[i] == '\n') {
				//printf("\n");
				char com[1000];
				char com2[1000];
				caracter[i] = '\0';
				strcpy(com, caracter);
				strcpy(com2, com);
				char *comando = NULL;
				comando = strtok(com, " ");
				char *atr;
				if (comando != NULL) {
					atr = com2;
					//	printf("ATR=%s\n",comando);
					verificarComando(comando, atr);
				}

				for (j = 0; j < 1000; j++) {
					caracter[j] = '\0';
				}
				printf("\n");
				i = 0;
			} else if (caracter[i] == '\\') {
				caracter[i] = ' ';
			} else {
				i++;
			}
		}
	}

}

void espacioLibre() {
	if (path == NULL) {
		path = "/"; //kilobytes
	}
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = verEspacioLibre(id, path, boolK, boolM, boolH, boolI);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int verEspacioLibre(char* id, char* path, int K, int M, int H, int I) {
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

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	return 1;
}

void espacioUsado() {
	//Atributos opcionales
	if (nDirectorio == NULL) {
		nDirectorio = "1"; //kilobytes
	}
	if (path == NULL || boolH == 0) {
		path = "/"; //kilobytes
	}
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = verEspacioUsado(id, path, nDirectorio, boolH);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int verEspacioUsado(char *id, char *path, char* n, int boolH) {
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

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	if (archivo == NULL) {
		printf("ERROR: No existe el disco\n");
		return 0;
	}
	mbr structDisco;
	fseek(archivo, 0, SEEK_SET);
	fread(&structDisco, sizeof(mbr), 1, archivo);

	return 1;
}

void formatear() {
	//Atributos opcionales
	if (type == NULL) {
		type = "full"; //kilobytes
	}
	if (unit == NULL) {
		unit = "k"; //kilobytes
	}
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		fflush(NULL);
		int d = formatearDisco(id, type, add, unit, fs);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		} else {
			setbuf(stdin, NULL);
			fflush(NULL);
			crearArchivoParticion(id, "/home/users.txt", "si", "16384",
					"/home/aylin/users.txt");
			boolEditar = 1;
			fflush(NULL);
			//crearGrupoDisco(id,"root");
			//crearUsuarioDisco(id,"root","201404368","root");
			//crearArchivoParticion(id, "/home/users.txt", "si", "16384", "/home/aylin/users.txt");
			//"/home/aylin/usuarios.txt"
		}

	}
}

int formatearDisco(char* id, char* type, char* add, char* unit, char* fs) {

	if (strcasecmp(type, "full") == 0 || strcasecmp(type, "fast") == 0) {
	} else {
		printf("ERROR: Tipo no existe.\n");
		return 0;
	}
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
		//printf("COMPARAR Mkfs:: %s - %s\n",structDisco.part[i].name,nombre);
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 10; j++) { //journalica
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
	//printf("N1:: %s\n",structDisco.part[i].name);

	superbloque sb;
	int pos = 0;
	int n = 0;
	int tam = 0;
	if (existeLogica == 1) { //Si la particion es journalica
		n = structDisco.part[i].exten[j].auxiliar - sizeof(superbloque);
		int m = (6 + sizeof(avd) + sizeof(detalle) + sizeof(inodo)
				+ 4 * sizeof(datos) + sizeof(journal));
		int nn = n / m;
		tam = floor(nn);
		printf("tam1== %d\n", tam);
		pos = tam;
		sb.nombre = name;
		sb.arbolVirtualCount = tam;
		sb.detalleDirectorioCount = tam * 2;
		sb.inodosCount = tam;
		sb.bloquesCount = tam * 3;
		sb.freeArbolCount = tam - 1;
		sb.freeDetalleDirectorioCount = (tam * 2) - 1;
		sb.freeBloquesCount = tam - 1;
		sb.freeInodosCount = (tam * 3) - 10;
		sb.DateCreacion = time(0);
		sb.DateMontaje = time(0);
		sb.mountCount = 0;
		sb.magic = 201404368;  //0xEF53
		sb.inodoSize = sizeof(inodo);
		sb.bloqueSize = sizeof(datos);
		sb.arbolDirectorioSize = sizeof(avd);
		sb.detalleDirectorioSize = sizeof(detalle);
		sb.apuntadorLog = sb.apuntadorBloques + sizeof(datos);
		sb.apuntadorBitArbolDirectorio = structDisco.part[i].exten[j].start
				+ sizeof(superbloque);
		sb.apuntadorAVD = structDisco.part[i].exten[j].start
				+ sizeof(superbloque) + tam;
		sb.apuntadorBitDetalleDirectorio = structDisco.part[i].exten[j].start
				+ sizeof(superbloque) + tam + sizeof(avd);
		sb.apuntadorDetalleDirectorio = sb.apuntadorBitDetalleDirectorio + tam;
		sb.apuntadorBitTablaInodo = sb.apuntadorDetalleDirectorio
				+ sizeof(detalle);
		sb.apuntadorTablaInodo = sb.apuntadorBitTablaInodo + tam;
		sb.apuntadorBitmapInodo = sb.apuntadorTablaInodo + sizeof(inodo);
		sb.apuntadorCopia = sb.apuntadorLog + sizeof(journal);
		sb.firstFreeBitArbol = 1;
		sb.firstFreeBitDetalleDirectorio = 1;
		sb.firstFreeBitTablaInodo = 1;
		sb.firstFreeBitBloque = 1;

		fseek(archivo, structDisco.part[i].exten[j].start, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);
		fseek(archivo, sb.apuntadorCopia, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);

	} else {
		n = 2 * structDisco.part[i].auxiliar - sizeof(superbloque);
		int m = (6 + sizeof(avd) + sizeof(detalle) + sizeof(inodo)
				+ 4 * sizeof(datos) + sizeof(journal));
		int nn = n / m;
		tam = floor(nn);
		printf("tam1== %d\n", tam);

		pos = tam;
		sb.nombre = name;
		sb.arbolVirtualCount = tam;
		sb.detalleDirectorioCount = tam * 2;
		sb.inodosCount = tam;
		sb.bloquesCount = tam * 3;
		sb.freeArbolCount = tam - 1;
		sb.freeDetalleDirectorioCount = (tam * 2) - 1;
		sb.freeBloquesCount = tam - 1;
		sb.freeInodosCount = (tam * 3) - 10;
		sb.DateCreacion = time(0);
		sb.DateMontaje = time(0);
		sb.mountCount = 0;
		sb.magic = 201404368;  //0xEF53
		sb.inodoSize = sizeof(inodo);
		sb.bloqueSize = sizeof(datos);
		sb.arbolDirectorioSize = sizeof(avd);
		sb.detalleDirectorioSize = sizeof(detalle);
		sb.apuntadorLog = sb.apuntadorBloques + sizeof(datos);
		sb.apuntadorBitArbolDirectorio = structDisco.part[i].start
				+ sizeof(superbloque);
		sb.apuntadorAVD = structDisco.part[i].start + sizeof(superbloque) + tam;
		sb.apuntadorBitDetalleDirectorio = structDisco.part[i].start
				+ sizeof(superbloque) + tam + sizeof(avd);
		sb.apuntadorDetalleDirectorio = sb.apuntadorBitDetalleDirectorio + tam;
		sb.apuntadorBitTablaInodo = sb.apuntadorDetalleDirectorio
				+ sizeof(detalle);
		sb.apuntadorTablaInodo = sb.apuntadorBitTablaInodo + tam;
		sb.apuntadorBitmapInodo = sb.apuntadorTablaInodo + sizeof(inodo);
		sb.apuntadorCopia = sb.apuntadorLog + sizeof(journal);
		sb.firstFreeBitArbol = 2;
		sb.firstFreeBitDetalleDirectorio = 1;
		sb.firstFreeBitTablaInodo = 1;
		sb.firstFreeBitBloque = 1;
		fseek(archivo, structDisco.part[i].start, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);
		fseek(archivo, sb.apuntadorCopia, SEEK_SET);
		fwrite(&sb, sizeof(superbloque), 1, archivo);

	}
	printf("-> Se ha dado formato a la particion correctamente.\n");

	char bitm = '0';
	char bitm1 = '1';
	fseek(archivo, sb.apuntadorBitArbolDirectorio, SEEK_SET);
	fwrite(&bitm1, 1, 1, archivo);
	int io = 0;
	for (io = 0; io < (pos) - 1; io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	fseek(archivo, sb.apuntadorBitDetalleDirectorio, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	fseek(archivo, sb.apuntadorBitTablaInodo, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	fseek(archivo, sb.apuntadorBitmapInodo, SEEK_SET);
	for (io = 0; io < (pos); io++) {
		fwrite(&bitm, 1, 1, archivo);
	}

	avd insertar;
	insertar.apuntadorAVD = -1;
	insertar.directorio = 0;
	strcpy(insertar.name, "/");
	int ip = 0;
	for (ip = 0; ip < 4; ip++) {
		insertar.subDirectorios[ip] = 0;
	}
	fseek(archivo, sb.apuntadorAVD, SEEK_SET);
	fwrite(&insertar, sizeof(avd), 1, archivo);

//CAMBIOS EN EL JOURNALING
	journal bitacora;

	bitacora.operacion = 1;
	bitacora.tipo = 0;
	bitacora.fecha = time(0);
	if (usrLogin != NULL) {
		//	strcpy(bitacora.usuario,usrLogin);
	}
	//strcpy(bitacora.permiso,"664");
	strcpy(bitacora.nombre, "Formatear");
	strcpy(bitacora.contenido, "Formatear");
	fseek(archivo, sb.apuntadorLog, SEEK_SET); //**
	fwrite(&bitacora, sizeof(journal), 1, archivo);

	fclose(archivo);
	//printf("N4:: %s\n",structDisco.part[i].name);
	//printf("M5:: %s\n",montar[i].name);
	//printf("MM= %d\n",sb.magic);
	strcpy(structDisco.part[i].name, montar[i].name);
	return 1;
}

void crearArchivo() {
	if (id == NULL || path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = crearArchivoParticion(id, path, p, size, cont);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int crearArchivoParticion(char* id, char* path, char* p, char* size, char* cont) {
	char* ruta;
	char* nombre;
	int i = 0;
	//printf("MAKE FILE");
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//		printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
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
	fflush(NULL);
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
		//printf("Comparar= *%s* - *%s*\n",montar[i].name,nombre);
		if (strcasecmp(structDisco.part[i].name, nombre) == 0
				|| strcmp(nombre, structDisco.part[i].name) == 0) {
			//printf("eureka\n");
			break;
		}
		for (j = 0; j < 10; j++) { //journalica
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
		printf("ERROR: No existe el nombre indicado (CAP).\n");
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

	FILE* archivoCont;
	archivoCont = fopen(cont, "r");
	int existeCont = 1;

	if (cont == NULL) {
		existeCont = 0;
	} else if (archivoCont == NULL) {
		printf("ERROR: No existe ruta de cont.\n");
		return 0;
	}

	int tamanio;
	if (existeCont > 0) {
		fseek(archivoCont, 0, SEEK_END);
		tamanio = ftell(archivoCont);
	} else {
		tamanio = atoi(size);
	}

	if (tamanio < 0) {
		printf("ERROR: El tamanio es incorrecto.\n");
		return 0;
	}
	printf("MAGIC = %d\n", sb.magic);
	sb.magic = 201404368;
	if (sb.magic == 201404368) {
		fseek(archivo, sb.apuntadorAVD, SEEK_SET);
		avd ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);

		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') {
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
		char* rutaC;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			p = "si";
			rutaC = strtok(crear, "/");
		} else {
			rutaC = strtok(verificar, "/");
			//p="no";
		}
		//	p  ="si";

		fclose(archivo);
		int informacion = 0;
		int datos = 0;

		correcto = 1; //**
		//	printf("crearCarpeta\n");//XXX
		setbuf(stdin, NULL);
		informacion = crearCarpeta(ruta, sb, ap, rutaC, p, ajuste, posicion,
				sb.apuntadorAVD);

		if (correcto > 0) {
			rutaC = strtok(verificar2, "/");
			//posicion = inicio & apuntador =atras
			//		printf("buscarArchivo\n");//XXX
			setbuf(stdin, NULL);
			fflush(NULL);
			datos = buscarArchivo(ruta, sb, ap, rutaC, ajuste, posicion,
					sb.apuntadorAVD);

			if (datos > 0) {
				rutaC = strtok(crear, "/");
				//verificar si ruta es igual a NULO
				while ((strstr(rutaC, ".") == 0x0 || strstr(rutaC, ".") == ""
						|| strstr(rutaC, ".") == NULL) && rutaC != NULL) {
					rutaC = strtok(NULL, "/");
					//		printf("rutaC= %s\n",rutaC);
					if (rutaC == NULL || rutaC == 0x0) {
						break;
					}
				}
				char leer[tamanio];
				fflush(NULL);
				if (archivoCont != NULL) {
					fseek(archivoCont, 0, SEEK_SET);
					fread(&leer, tamanio, 1, archivoCont);
				} else {
					printf("Sin contenido.\n");
					int r, c = 0;
					for (r = 0; r < tamanio; r++) {
						leer[r] = (char) (c + 48);
						c++;
						if (c > 9) {
							c = 0;
						}
					}
				}
				fflush(NULL);
				//		printf("archivoCont ==  %s*\n",leer);
				printf("-> Se ha creado el archivo correctamente.\n");
				char contenido[100];

				if (archivoCont != NULL || archivoCont != 0x0) {
					setbuf(stdin, NULL);
					fflush(NULL);
					agregarContenido(datos, sb, ruta, rutaC, ajuste, leer,
							tamanio);
					//cambiarPermiso(datos,sb,ruta, rutaC, "664","0");
					fflush(NULL);
					//printf("Contenido = %s\n",contenido);
					if (size == 0x0 || size == NULL) {
						strcat(contenido, "-cont:");
						strcat(contenido, cont);
					} else {
						strcat(contenido, "-size:");
						strcat(contenido, size);
					}
					//bitacora(sb.apuntadorJournal, 1, path, contenido, sb, ruta);
				} else {
					printf("else\n");
					//contenido[0]= 'n';
				}
				//	printf("Contenido = %s\n",contenido);

			} else {
				printf("ERROR: No se ha podido crear el archivo.\n");
			}
		}
	} else {
		printf("ERROR: No se ha formateado la particion.\n");
	}
	return 1;
}

int agregarContenido(int posicion, superbloque super, char* ruta, char* name,
		char ajuste, char* contenido, int size) {

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	fflush(NULL);
	int i = 0, k = 0;
	int j = 0;
	for (i = 0; i < 3; i++) {
		//	int n = c.contenido[i].inodo;
		//char* print =c.contenido[i].name;
		//printf("nombre = %s\n",print);
		if (carp.archivos[i].inodo > 1) {
			if (strcasecmp(carp.archivos[i].name, name) == 0) {
				if (boolEditar == 0) {
					printf("ERROR: El nombre ya existe.\n");
					return 0;
				} else {
				}
				break;
			}
			k++;

		} else {
			j = i;
		}
	}
	if (k > 4) {
		if (carp.detalle > 0) {
			fclose(archivo);
			setbuf(stdin, NULL);
			fflush(NULL);
			return agregarContenido(carp.detalle, super, ruta, name, ajuste,
					contenido, size);
		} else {
			detalle carp;
			carp.detalle = 0;
			int a = 0;
			for (a = 0; a < 3; a++) {
				carp.archivos[a].inodo = -1;
			}
			int posicion = 0;
			fclose(archivo);
			setbuf(stdin, NULL);
			if (ajuste == 'w') {
				posicion = peorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitDetalleDirectorio, 1);
			} else if (ajuste == 'f') {
				posicion = primerAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitDetalleDirectorio, 1);
			} else {
				posicion = mejorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitDetalleDirectorio, 1);
			}
			FILE* disco;
			disco = fopen(ruta, "rb+");

			carp.detalle = super.apuntadorDetalleDirectorio
					+ 100 * posicion * sizeof(detalle);
			fseek(disco, posicion, SEEK_SET);
			fwrite(&carp, sizeof(detalle), 1, disco);

			fseek(disco,
					super.apuntadorDetalleDirectorio
							+ 100 * posicion * sizeof(detalle), SEEK_SET);
			fwrite(&carp, sizeof(detalle), 1, disco);
			fclose(disco);
			setbuf(stdin, NULL);
			return agregarContenido(carp.detalle, super, ruta, name, ajuste,
					contenido, size);
			fflush(NULL);
		}
	} else {
		strcpy(carp.archivos[j].name, name);

		int pos = 0;
		setbuf(stdin, NULL);
		fclose(archivo);
		if (ajuste == 'w') {
			pos = peorAjuste(super.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		} else if (ajuste == 'f') {
			pos = primerAjuste(super.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		} else {
			pos = mejorAjuste(super.arbolVirtualCount, ruta,
					super.apuntadorBitTablaInodo, 1);
		}
		FILE* disco;
		disco = fopen(ruta, "rb+");
		carp.archivos[j].inodo = super.apuntadorTablaInodo
				+ 100 * pos * sizeof(inodo);
		fseek(disco, posicion, SEEK_SET);
		fwrite(&carp, sizeof(detalle), 1, disco);
		fclose(disco);

		inodo ino;
		ino.noAsignados = pos;
		ino.size = size;

		int aux = size / 25;

		if (size % 25) {
			aux++;
		}

		datos arch;
		char conten[200];
		strcpy(conten, contenido);
		int l, m = 0;
		int pos2 = 0;
		if (aux < 5) {

			ino.noInodo = size / 25;
			if (size % 25 > 0) {
				ino.noInodo++;
			}
			ino.indirecto = 0;
			setbuf(stdin, NULL);
			for (l = 0; l < ino.noInodo; l++) {
				if (ajuste == 'w') {
					pos2 = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos2 = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else {
					pos2 = mejorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(ruta, "rb+");
				for (m = 0; m < 25; m++) {
					arch.contenido[m] = conten[l * 25 + m];
				}
				ino.bloques[l] = super.apuntadorBloques
						+ 100 * pos2 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos2 * sizeof(datos),
						SEEK_SET);
				fwrite(&arch, sizeof(datos), 1, disco);
				fclose(disco);
			}
		} else {
			ino.noInodo = 4;
			setbuf(stdin, NULL);
			for (l = 0; l < 4; l++) {
				if (ajuste == 'w') {
					pos2 = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos2 = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitDetalleDirectorio, 1);
				} else {
					pos2 = mejorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(ruta, "rb+");
				for (m = 0; m < 25; m++) {
					arch.contenido[m] = conten[l * 25 + m];
				}
				ino.bloques[l] = super.apuntadorBloques
						+ 100 * pos2 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos2 * sizeof(datos),
						SEEK_SET);
				fwrite(&arch, sizeof(datos), 1, disco);
				fclose(disco);
			}
			int pos3 = 0;
			setbuf(stdin, NULL);
			if (ajuste == 'w') {
				pos3 = peorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			} else if (ajuste == 'f') {
				pos3 = primerAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			} else {
				pos3 = mejorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitTablaInodo, 1);
			}
			inodo ino2;
			ino2.noAsignados = pos3;
			ino2.size = size;
			ino2.indirecto = 0;
			ino2.noInodo = (size - 100) / 25;
			if ((size - 100) % 25 > 0) {
				ino2.noInodo++;
			}
			if (ino2.noInodo > 4) {
				ino2.noInodo = 4;
			}
			int pos4 = 0;
			setbuf(stdin, NULL);
			for (l = 0; l < ino2.noInodo; l++) {
				if (ajuste == 'w') {
					pos4 = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else if (ajuste == 'f') {
					pos4 = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				} else {
					pos4 = mejorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitmapInodo, 1);
				}
				FILE* disco;
				disco = fopen(ruta, "rb+");
				int m = 0;
				for (m = 0; m < 25; m++) {
					arch.contenido[m] = conten[l * 25 + m + 100];
				}
				ino2.bloques[l] = super.apuntadorBloques
						+ 100 * pos4 * sizeof(datos);
				fseek(disco,
						super.apuntadorBloques + 100 * pos4 * sizeof(datos),
						SEEK_SET);
				fwrite(&arch, sizeof(datos), 1, disco);
				fclose(disco);
			}

			disco = fopen(ruta, "rb+");
			ino.indirecto = super.apuntadorDetalleDirectorio
					+ 100 * pos3 * sizeof(inodo);
			fseek(disco,
					super.apuntadorDetalleDirectorio
							+ 100 * pos3 * sizeof(inodo), SEEK_SET);
			fwrite(&ino2, sizeof(inodo), 1, disco);
			fclose(disco);
		}
		disco = fopen(ruta, "rb+");
		fseek(disco, super.apuntadorTablaInodo + 100 * pos * sizeof(inodo),
		SEEK_SET);
		fwrite(&ino, sizeof(inodo), 1, disco);
		fclose(disco);
		fflush(NULL);
		printf("-> Se agrego el archivo correctamente.\n");
	}
}

int crearCarpeta(char* ruta, superbloque super, avd apun, char* path, char* p,
		char ajuste, int inicio, int atras) {
//	printf("p == %s\n",p);
	char* patito = path;

	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd ap;
//	int m = super.apuntador;
	//printf("m= %d\n", m);
	if (atras > 800000000) {
		return 0;
	}
	fseek(archivo, atras, SEEK_SET);
	fread(&apun, sizeof(avd), 1, archivo);
	int i = 0, x = 0, w = 0, qw = 0;

	for (i = 0; i < 6; i++) {
		//	printf("sub carpeta =%d\n",apun.subCarpetas[i]);
		if (apun.subDirectorios[i] > 0) {	//Si ya existe la carpeta
			fseek(archivo, apun.subDirectorios[i], SEEK_SET);
			fread(&ap, sizeof(ap), 1, archivo);
			if (strcasecmp(ap.name, path) == 0) {
				break;
			}
		} else if (x == 0) {
			x = 1;
			w = i;
			qw++;
		} else {
			qw++;
		}
	}
	//printf("i = %d\n",i);
	if (i < 6) {
		path = strtok(NULL, "/");
		//	printf("path=%s\n", path);
		if (path != NULL && path != 0x0) {
			fclose(archivo);
			crearCarpeta(ruta, super, ap, path, p, ajuste, inicio,
					apun.subDirectorios[i]);
		} else {
			//	printf("NULO\n");
//			correcto=0;
			return 1;
		}
	} else if (i > 5 && x > 0) {
		if (p != NULL) {
			int pos = 0;
			fclose(archivo);
			if (ajuste == 'w') {
				pos = peorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitArbolDirectorio, 1);
			} else if (ajuste == 'f') {
				pos = primerAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitArbolDirectorio, 1);
			} else {
				pos = mejorAjuste(super.arbolVirtualCount, ruta,
						super.apuntadorBitArbolDirectorio, 1);
			}
			FILE* archivo;
			archivo = fopen(ruta, "rb+");
			ap.apuntadorAVD = -1;
			ap.directorio = 0;

			strcpy(ap.name, path);
			int au = 0;
			for (au = 0; au < 4; au++) {
				ap.subDirectorios[au] = -1;
			}

			apun.subDirectorios[w] = super.apuntadorAVD
					+ 100 * pos * sizeof(avd);
			fseek(archivo, atras, SEEK_SET);
			fwrite(&apun, sizeof(avd), 1, archivo);

			fseek(archivo, super.apuntadorAVD + 100 * pos * sizeof(avd),
			SEEK_SET);
			fwrite(&ap, sizeof(avd), 1, archivo);
			path = strtok(NULL, "/");
			fclose(archivo);
			if (path != NULL) {
				//printf("hola\n");
				crearCarpeta(ruta, super, apun, path, p, ajuste, inicio,
						apun.subDirectorios[w]);
			} else {
				printf("-> Se creo la carpeta correctamente. %s\n", patito);
				return 1;
			}
		} else {
			correcto = 0;
			printf("*ERROR: La ruta indicada no existe.\n");
			return 0;
		}
	} else if (i > 5 && x < 1) {
		//printf("apun == %d\n",apun.apuntador);

		if (apun.apuntadorAVD < 0) {
			if (p != NULL) {
				int pos = 0;
				fclose(archivo);
				if (ajuste == 'w') {
					pos = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitArbolDirectorio, 1);
				} else if (ajuste == 'f') {
					pos = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitArbolDirectorio, 1);
				} else {
					pos = mejorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitArbolDirectorio, 1);
				}
				FILE* disco;
				disco = fopen(ruta, "rb+");

				ap.apuntadorAVD = -1;
				ap.directorio = 0;

				strcpy(ap.name, apun.name);
				int aux = 0;
				for (aux = 0; aux < 6; aux++) {
					ap.subDirectorios[aux] = -1;
				}
				apun.apuntadorAVD = super.apuntadorAVD
						+ 100 * pos * sizeof(avd);

				fseek(disco, atras, SEEK_SET);
				fwrite(&apun, sizeof(avd), 1, disco);

				fseek(disco, super.apuntadorAVD + 100 * pos * sizeof(avd),
				SEEK_SET);
				fwrite(&ap, sizeof(avd), 1, disco);
				//crear aqui
				if (path != NULL) {
					fclose(disco); //XXX
					crearCarpeta(ruta, super, ap, path, p, ajuste, inicio,
							apun.apuntadorAVD);
				}
			} else {
				correcto = 0;
				printf("/ERROR: La ruta indicada no existe.\n");
				return 0;
			}
		} else {
			fclose(archivo);
			crearCarpeta(ruta, super, apun, path, p, ajuste, inicio,
					apun.apuntadorAVD);
		}
	} else {
		correcto = 0;
		printf("ERROR: No se ha podido crear la carpeta.\n");
		return 0;
	}

	return 1;

}

void mostrarContenido() {
	int cont = 0;
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (file1 != NULL) {
			int d = mostrarContenidoArchivo(id, file1);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
			cont++;
		}
		if (file2 != NULL) {
			int d = mostrarContenidoArchivo(id, file2);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
			cont++;
		}
		if (file3 != NULL) {
			int d = mostrarContenidoArchivo(id, file3);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
			cont++;
		}
		if (cont == 0) {
			printf("ERROR: Falta un atributo obligatorio.\n");
		}
	}
}

int mostrarContenidoArchivo(char* id, char* filen) {
//	printf("filen= %s\n",filen);
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
		int datos;
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

				//	bitacora(sb.apuntadorJournal, 2, filen, "", sb, ruta);
			}
		} else {
			printf("ERROR: La ruta no existe.\n");
		}
	} else {
		printf("ERROR: La particion no esta formateada.\n");
	}
	return 1;
}

int buscarArchivo(char* ruta, superbloque super, avd ap, char* path,
		char ajuste, int inicio, int atras) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd ap2;
	//printf("apuntador = %d\n", super.apuntadorAVD);
	fseek(archivo, atras, SEEK_SET);
	fread(&ap, sizeof(avd), 1, archivo);
	int i = 0, x = 0, qw = 0;

	for (i = 0; i < 4; i++) {
		printf("sub = %d, ", ap.subDirectorios[i]);
		if (ap.subDirectorios[i] > 0) {
			fseek(archivo, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(avd), 1, archivo);
			if (strcasecmp(ap2.name, path) == 0) {
				break;
			}
		} else if (x == 0) {
			x = 1;
			qw++;
		} else {
			qw++;
		}
	}
	printf("i = %d\n", i);
	if (i < 4) {
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(archivo);
			//printf("return1\n");
			return buscarArchivo(ruta, super, ap2, path, ajuste, inicio,
					ap.subDirectorios[i]);
		} else {
			if (ap2.directorio > 0) {
				fclose(archivo);
				return ap2.directorio;
			} else {
				detalle c;
				c.detalle = 0;
				int uy = 0;
				for (uy = 0; uy < 5; uy++) {
					c.archivos[uy].inodo = -1;
				}
				int pos = 0;
				fclose(archivo);
				if (ajuste == 'w') {
					pos = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitDetalleDirectorio, 1);
				} else if (ajuste == 'f') {
					pos = primerAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitDetalleDirectorio, 1);
				} else {
					pos = peorAjuste(super.arbolVirtualCount, ruta,
							super.apuntadorBitDetalleDirectorio, 1);
				}
				FILE* archivo;
				archivo = fopen(ruta, "rb+");

				ap2.directorio = super.apuntadorDetalleDirectorio
						+ 100 * pos * sizeof(detalle);
				fseek(archivo, ap.subDirectorios[i], SEEK_SET);
				fwrite(&ap2, sizeof(avd), 1, archivo);
				fclose(archivo);

				archivo = fopen(ruta, "rb+");
				fseek(archivo,
						super.apuntadorDetalleDirectorio
								+ 100 * pos * sizeof(detalle), SEEK_SET);
				fwrite(&c, sizeof(detalle), 1, archivo);
				fclose(archivo);
				return ap2.directorio;
			}
		}
	} else {
		//	printf("apuntador = %d\n", ap.apuntador);

		if (ap.apuntadorAVD < 1) {
			printf("ERROR: No existe carpeta \n");
			return 0;
		} else {
			fclose(archivo);
			return buscarArchivo(ruta, super, ap, path, ajuste, inicio,
					ap.apuntadorAVD);
		}
	}

}

void remover() {
	if (id == NULL || path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = removerArchivo(id, path, rf);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int removerArchivo(char* id, char* path, int rf) {
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				//	 printf("igual\n");
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
	superbloque sb = crearBloque();
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
	printf("M= %d\n", sb.magic);
	if (sb.magic == 201404368) {
		fseek(archivo, sb.apuntadorAVD, SEEK_SET);
		avd ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);

		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') {
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

		char* ruta1;
		char* ruta2;
		char auxPath[100];
		strcpy(auxPath, path);
		a = 0; //nuevas variables
		b = 0;
		for (a = 0; a < 100; a++) {
			if (auxPath[a] == '.') {
				b++;
			}
		}
		fclose(archivo);

		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		ruta2 = strtok(crear, ".");

		int datos = 0;

		if (b < 1) {
			ruta1 = strtok(crear, "/");
			printf("Eliminar Carpeta.\n");
			eliminarCarpeta(ruta, sb, ruta1, sb.apuntadorAVD);
			//bitacora(sb.apuntadorLog, 3, path, " ", sb, ruta); ///****
		} else {
			ruta1 = strtok(verificar2, "/");

			printf("Buscar Archivo.\n");
			datos = buscarArchivo(ruta, sb, ap, ruta1, ajuste, posicion,
					sb.apuntadorAVD);
			if (datos > 0) {
				ruta1 = strtok(path, "/");
				//retorna un puntero - strstr
				while ((strstr(ruta1, ".") == 0x0 || strstr(ruta1, ".") == ""
						|| strstr(ruta1, ".") == NULL) && ruta1 != NULL
						&& ruta1 != 0x0) {
					ruta1 = strtok(NULL, "/");
					if (ruta1 == NULL) {
						break;
					}
				}
				if (ruta1 != NULL) {
					printf("Eliminar Archivo.\n");
					eliminarArchivo(datos, sb, ruta, ruta1);
					//	bitacora(sb.apuntadorJournal, 3, auxPath, " ", sb, ruta);
				}
			} else {
				printf("ERROR: No existe la ruta indicada.\n");
			}
		}
	} else {
		printf("ERROR: La particion no ha sido formateada.\n");
	}

	return 1;
}

int eliminarCarpeta(char* ruta, superbloque super, char* path, int posicion) {
	FILE* disco;
	disco = fopen(ruta, "rb+");
	avd ap2, ap;
	fseek(disco, posicion, SEEK_SET);
	fread(&ap, sizeof(avd), 1, disco);

	int i = 0;
	for (i = 0; i < 4; i++) {
		if (ap.subDirectorios[i] > 0) {
			fseek(disco, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, disco);
			if (strcasecmp(ap2.name, path) == 0) {
				break;
			}
		}
	}
	printf("i= %d\n", i);
	if (i < 4) {
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(disco);
			return 1; //eliminarCarpeta(ruta, super, path, ap.subDirectorios[i]);
		} else {
			int c = ap.subDirectorios[i];
			ap.subDirectorios[i] = -1;
			fseek(disco, posicion, SEEK_SET);
			fwrite(&ap, sizeof(avd), 1, disco);
			int pos = (c - super.apuntadorAVD) / (100 * sizeof(avd));

			char ok = '0';
			/*fseek(disco, super.apuntadorBitArbolDirectorio, SEEK_SET);
			 fwrite(&ok, 1, 1, disco);
			 */ //fclose(disco);
			printf("-> Se elimino la carpeta correctamente.\n");
			return eliminarCarpetaCompleta(ruta, super, c);
		}
	} else {
		if (ap.apuntadorAVD < 1) {
			printf("ERROR: No existe la carpeta especificada.\n");
			return 0;
		} else {
			fclose(disco);
			return eliminarCarpeta(ruta, super, path, ap.apuntadorAVD);
		}

	}
	return 1;
}

int eliminarCarpetaCompleta(char*ruta, superbloque super, int posicion) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd ap2, ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(avd), 1, archivo);

	int i = 0;

	for (i = 0; i < 6; i++) {
		// int m=ap.subCarpetas[i];

		if (ap.subDirectorios[i] > 0) {
			int c = ap.subDirectorios[i];
			ap.subDirectorios[i] = -1;
			fseek(archivo, posicion, SEEK_SET);
			fwrite(&ap, sizeof(avd), 1, archivo);
			int pos = (c - super.apuntadorAVD) / (100 * sizeof(avd));

			char ok = '0';
			fseek(archivo, super.apuntadorBitArbolDirectorio + pos, SEEK_SET);
			fwrite(&ok, 1, 1, archivo);
			fclose(archivo);
			printf("eliminar com\n");
			eliminarCarpetaCompleta(ruta, super, c);
		}
	}

	if (ap.apuntadorAVD > 0) {
		archivo = fopen(ruta, "rb+");
		int c = ap.apuntadorAVD;
		ap.apuntadorAVD = -1;
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&ap, sizeof(avd), 1, archivo);
		int pos = (c - super.apuntadorAVD) / (100 * sizeof(avd));
		char ok = '0';
		fseek(archivo, super.apuntadorBitArbolDirectorio + pos, SEEK_SET);
		fwrite(&ok, 1, 1, archivo);
		fclose(archivo);
		printf("eliminarC\n");
		//eliminarCarpetaCompleta(ruta, super, c);
	}
	if (ap.directorio > 50) {
		archivo = fopen(ruta, "rb+");
		int c = ap.directorio;
		ap.directorio = 0;
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&ap, sizeof(avd), 1, archivo);
		int pos = (c - super.apuntadorDetalleDirectorio)
				/ (100 * sizeof(detalle));
		char yeah = '0';
		fseek(archivo, super.apuntadorBitDetalleDirectorio + pos, SEEK_SET);
		fwrite(&yeah, 1, 1, archivo);
		fclose(archivo);
	}
}

int eliminarArchivo(int posicion, superbloque super, char* ruta, char* name) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	int contenidoInodo;
	char* contenidoNombre;

	for (i = 0; i < 5; i++) {
		contenidoInodo = carp.archivos[i].inodo;
		contenidoNombre = carp.archivos[i].name;
		if (carp.archivos[i].inodo > 1) {
			if (strcasecmp(carp.archivos[i].name, name) == 0) {
				break;
			}
		}
	}
	char v = '0';
	if (i < 5) {
		carp.archivos[i].inodo = -1;
		strcpy(carp.archivos[i].name, "");
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&carp, sizeof(detalle), 1, archivo);

		inodo ino;
		fseek(archivo, contenidoInodo, SEEK_SET);
		fread(&ino, sizeof(ino), 1, archivo);

		int cont = ino.noAsignados;
		ino.noAsignados = -1;
		fseek(archivo, super.apuntadorBitTablaInodo + cont, SEEK_SET);
		fwrite(&v, 1, 1, archivo);
		fseek(archivo, contenidoInodo, SEEK_SET);
		fwrite(&ino, sizeof(ino), 1, archivo);

		int j = 0;
		for (j = 0; j < ino.noInodo; j++) {
			//	  int mou=ino.bloque[j];
			//  int cl=super.inicioTablaBloque;
			int popo = (ino.bloques[j] - super.apuntadorBloques)
					/ (100 * sizeof(datos));
			fseek(archivo, super.apuntadorBitmapInodo + popo, SEEK_SET);
			fwrite(&v, 1, 1, archivo);
		}
		// int most =conx.indirecto;
		inodo inodo2;
		if (ino.indirecto > 0) {

			fseek(archivo, ino.indirecto, SEEK_SET);
			fread(&inodo2, sizeof(inodo), 1, archivo);
			cont = inodo2.noAsignados;
			inodo2.noAsignados = -1;
			fseek(archivo, super.apuntadorBitTablaInodo + cont, SEEK_SET);
			fwrite(&v, 1, 1, archivo);

			for (j = 0; j < inodo2.noInodo; j++) {
				int aux = (inodo2.bloques[j] - super.apuntadorBloques)
						/ (100 * sizeof(datos));
				fseek(archivo, super.apuntadorBitmapInodo + aux, SEEK_SET);
				fwrite(&v, 1, 1, archivo);
			}
			fseek(archivo, ino.indirecto, SEEK_SET);
			fwrite(&inodo2, sizeof(inodo), 1, archivo);
		}
		fclose(archivo);
		printf("-> Se ha eliminado el archivo correctamente.\n");
		return 1;

	} else {
		if (carp.detalle > 0) {
			fclose(archivo);
			//   int om=carp.d;
			return eliminarArchivo(carp.detalle, super, ruta, name);
		} else {
			fclose(archivo);
			printf("ERROR: No se ha encontrado el archivo.\n");
			return 0;
		}
	}
}

int primerAjuste(int bloque, char* ruta, int inicio, int arch) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	int sig = 0;
	char leer;
	fseek(archivo, inicio, SEEK_SET);

	int i = 0;
	int posicion = 0;
	for (i = 0; i < bloque; i++) {
		fread(&leer, 1, 1, archivo);
		if (leer == '0') {			//Si es vacio
			sig++;
		} else {
			sig = 0;
		}
		if (sig == arch) {
			posicion = (i - (sig - 1));
			break;
		}
	}
	fseek(archivo, inicio + posicion, SEEK_SET);
	leer = '1';
	fwrite(&leer, 1, 1, archivo);
	fclose(archivo);
	return posicion;
}

int mejorAjuste(int bloque, char* ruta, int inicio, int arch) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	int posicion = 0;
	int sig = 0;
	int i = 0;
	int menor = bloque;
	char leer;
	fseek(archivo, inicio, SEEK_SET);
	for (i = 0; i < bloque; i++) {
		fread(&leer, 1, 1, archivo);
		if (leer == '0') {
			sig++;
		} else {
			if (menor > sig && sig != 0) {
				menor = sig;
				if (menor >= arch || menor == arch) {
					posicion = i - menor;
				}
			} else if (menor == bloque) {
				posicion = i + 1;
			}
			sig = 0;
		}

	}
	fseek(archivo, inicio + posicion, SEEK_SET);
	leer = '1';
	fwrite(&leer, 1, 1, archivo);
	fclose(archivo);
	return posicion;

}

int peorAjuste(int bloque, char* ruta, int inicio, int arch) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	int posicion = 0;
	int sig = 0;
	int i = 0;
	int mayor = 0;
	int aux = 0;
	char leer;
	fseek(archivo, inicio, SEEK_SET);
	for (i = 0; i < bloque; i++) {
		fread(&leer, 1, 1, archivo);
		if (leer == '0') {
			sig++;

		} else {
			aux = i + 1;
			if (mayor < sig) {
				mayor = sig;
				if (mayor >= arch || mayor == arch) {
					posicion = i - mayor;
				}
			} else if (mayor == 0) {
				posicion = i + 1;
			}
			sig = 0;

		}

		if (sig >= archivo) {
			if (aux == 0) {
				posicion = 0;
			} else {
				posicion = aux;
			}
		}

	}
	fseek(archivo, inicio + posicion, SEEK_SET);
	leer = '1';
	fwrite(&leer, 1, 1, archivo);
	fclose(archivo);
	return posicion;
}

void copiar() {
//Error raiz archivo
	if (id == NULL || path == NULL || dest == NULL || iddest == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = copiarArchivo(id, path, dest, iddest);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		} else {
			printf("-> Se ha copiado el archivo correctamente.\n");
		}
	}

}

int copiarArchivo(char* id, char* path, char* dest, char* iddest) {
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
	superbloque sb = crearBloque();
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
		strcpy(crear, path);
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
		char* ruta1;
		char* ruta2;
		char auxPath[100];
		strcpy(auxPath, path);
		a = 0; //nuevas variables
		b = 0;
		for (a = 0; a < 100; a++) {
			if (auxPath[a] == '.') {
				b++;
			}
		}
		fclose(archivo);
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		ruta2 = strtok(crear, ".");

		int datos = 0;
		if (b < 1) {
			ruta1 = strtok(crear, "/");
			//printf("copiar\n");
			copiarCarpeta(ruta, sb, ruta1, sb.apuntadorAVD, dest, iddest);

			bitacora(sb.apuntadorLog, 3, path, " ", sb, ruta); ///****
		} else {
			printf("buscar\n");
			ruta1 = strtok(verificar2, "/");
			datos = buscarArchivo(ruta, sb, ap, ruta1, posicion, ajuste,
					sb.apuntadorAVD);
			if (datos > 0) {
				ruta1 = strtok(path, "/");
				//retorna un puntero - strstr
				while ((strstr(ruta1, ".") == 0x0 || strstr(ruta1, ".") == ""
						|| strstr(ruta1, ".") == NULL) && ruta1 != NULL
						&& ruta1 != 0x0) {
					ruta1 = strtok(NULL, "/");
				}
				if (ruta1 != NULL) {
					char mensaje[200];
					int j = 0;
					for (j = 0; j < 200; j++) {
						mensaje[j] = '\0';
					}
					strcpy(mensaje,
							contenidoArchivo(" ", datos, sb, ruta, ruta1));
					FILE* reporte;
					reporte = fopen("/home/aylin/auxContenido.txt", "w+");
					fprintf(reporte, mensaje);
					fclose(reporte);
					char auxRuta[100];
					for (j = 0; j < 100; j++) {
						auxRuta[j] = '\0';
					}
					strcat(auxRuta, dest);
					strcat(auxRuta, "/");
					strcat(auxRuta, ruta1);
					printf("crear\n");
					crearArchivoParticion(iddest, auxRuta, NULL, NULL,
							"/home/aylin/auxContenido.txt");
				}
			} else {
				printf("ERROR: No existe la ruta indicada.\n");
				return 0;
			}
		}
	} else {
		printf("ERROR: La particion no ha sido formateada.\n");
		return 0;
	}
	return 1;
}

int copiarCarpeta(char* ruta, superbloque super, char* path, int posicion,
		char* dest, char* iddest) {
	FILE* disco;
	disco = fopen(ruta, "rb+");
	avd ap, ap2;

	fseek(disco, posicion, SEEK_SET);
	fread(&ap, sizeof(avd), 1, disco);
	// char* n=ap.name;
	int i = 0;
	for (i = 0; i < 6; i++) {
		//int n=ap.subdirectorios[i];
		if (ap.subDirectorios[i] > 50) {
			fseek(disco, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, disco);
			//char* m=ap2.puntero;

			if (strcasecmp(ap2.name, path) == 0) {
				break;
			}
		}
	}
	if (i < 6) {
		char* copia = path;
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(disco);
			return copiarCarpeta(ruta, super, path, ap.subDirectorios[i], dest,
					iddest);
		} else {
			int sub = ap.subDirectorios[i];
			//printf("else\n");
			printf("-> Se copio la carpeta correctamente.\n");
			fclose(disco);
			return copiarRaizCarpeta(ruta, super, sub, iddest, dest);
		}
	} else {
		if (ap.apuntadorAVD < 1) {
			printf("ERROR: No existe la carpeta.\n");
			return 0;
		} else {
			fclose(disco);
			return copiarCarpeta(ruta, super, path, ap.apuntadorAVD, dest,
					iddest);
		}
	}
}

int copiarRaizCarpeta(char* ruta, superbloque super, int posicion, char* iddest,
		char* dest) {
//	printf("raizCarpeta\n");
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(avd), 1, archivo);

	int i = 0;
	int j = 0;

	char llenar[80];
	for (j = 0; j < 80; j++) {
		llenar[j] = '\0';
	}
	strcpy(llenar, dest);
	strcat(llenar, "/");
	strcat(llenar, ap.name);
	fclose(archivo);
	crearCopia(iddest, llenar, NULL);
	printf("holi\n");

	for (i = 0; i < 4; i++) {
		//int n=con.subdirectorios[i];
		if (ap.subDirectorios[i] > 0) {
			int sub = ap.subDirectorios[i];
			copiarRaizCarpeta(ruta, super, sub, iddest, llenar);
		}
	}
	//int lol = ap.apuntadorAVD;
	//printf("lol = %d = %d\n",ap.apuntadorAVD, ap.directorio);
	if (ap.apuntadorAVD > 0) {
		copiarRaizCarpeta(ruta, super, ap.apuntadorAVD, iddest, dest);
	}
	if (ap.directorio > 0) {
		copiarRaizArchivo(ruta, super, ap.directorio, iddest, llenar);
	}
	//printf("casi\n");
	return 1;
}

int crearCopia(char* id, char* path, char* p) {
	//printf("crearCopia\n");
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
		for (j = 0; j < 20; j++) {
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
		strcpy(crear, path);
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
		char* ruta1;
		strcpy(verificar2, verificar);
		if (verificar[0] == '\0') {
			p = "si";
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		fclose(archivo);

		int datos;
		correcto = 1;
		if (p == NULL) {
			//		printf("p=NULL\n");
			datos = crearCarpeta(ruta, sb, ap, ruta1, p, ajuste, posicion,
					sb.apuntadorAVD);
			ruta1 = strtok(crear, "/");
			if (correcto > 0) {
//				printf("correctooooo= %d\n", correcto);

				datos = crearCarpeta(ruta, sb, ap, ruta1, "si", ajuste,
						posicion, sb.apuntadorAVD);
				//		printf("murio\n");

			}
		} else {
			//	printf("p!=NULL\n");
			ruta1 = strtok(crear, "/");
			datos = crearCarpeta(ruta, sb, ap, ruta1, p, ajuste, posicion,
					sb.apuntadorAVD);
		}
		bitacora(sb.apuntadorLog, 6, path, " ", sb, ruta);
	} else {
		printf("ERROR: No se ha formateado la particion.");
	}
	return 1;
}

int copiarRaizArchivo(char* ruta, superbloque super, int posicion, char* iddest,
		char* dest) {
	//printf("raizArchivo\n");
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;

	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	int j = 0;

	fclose(archivo);
	for (i = 0; i < 3; i++) {
		//	printf("FOR = %d\n", carp.archivos[i].inodo);
		if (carp.archivos[i].inodo > 50) {
			char mensaje[200];
			for (j = 0; j < 200; j++) {
				mensaje[j] = '\0';
			}
			//	printf("contenido\n");
			strcpy(mensaje,
					contenidoArchivo(" ", posicion, super, ruta,
							carp.archivos[i].name));
			FILE* reporte;
			reporte = fopen("/home/aylin/archivoAux.txt", "w+");
			fprintf(reporte, mensaje);
			fclose(reporte);
			char aux[100];
			for (j = 0; j < 100; j++) {
				aux[j] = '\0';
			}
			strcpy(aux, dest);
			strcat(aux, "/");
			strcat(aux, carp.archivos[i].name);
			char* enviado = aux;
			//printf("crear\n");
			crearArchivoParticion(iddest, enviado, NULL, NULL,
					"/home/aylin/archivoAux.txt");
			//printf("fin crearr\n");
		}
	}
	//printf("carpeta = %d\n", carp.detalle);
	if (carp.detalle > 50) {
		copiarRaizArchivo(ruta, super, carp.detalle, iddest, dest);
	}
	return 1;
}

char* contenidoArchivo(char* contenido, int posicion, superbloque super,
		char* ruta, char* name) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	for (i = 0; i < 5; i++) {
		// char* m =carp.archivos[i].name;
		if (carp.archivos[i].inodo > 1) {
			if (strcasecmp(carp.archivos[i].name, name) == 0) {
				break;
			}
		}
	}
	if (i < 5) {
		//se supone que obtiene el contenido
		inodo ino;
		fseek(archivo, carp.archivos[i].inodo, SEEK_SET);
		fread(&ino, sizeof(inodo), 1, archivo);
		if (ino.size > 100) {
			int i = 0;
			char texto[200];
			for (i = 0; i < 200; i++) {
				texto[i] = '\0';
			}
			if (ino.noInodo > 4) {
				ino.noInodo = 4;
			}
			setbuf(stdin, NULL);
			for (i = 0; i < ino.noInodo; i++) {
				datos arch;
				fseek(archivo, ino.bloques[i], SEEK_SET);
				fread(&arch, sizeof(datos), 1, archivo);
				//char *ar=arch.contenido;
				strcat(texto, arch.contenido);
				contenido = &texto;
			}
			inodo ino2;
			fseek(archivo, ino.indirecto, SEEK_SET);
			fread(&ino2, sizeof(inodo), 1, archivo);
			if (ino2.noInodo > 4) {
				ino2.noInodo = 4;
			}
			for (i = 0; i < ino2.noInodo; i++) {
				datos arch;
				fseek(archivo, ino2.bloques[i], SEEK_SET);
				fread(&arch, sizeof(datos), 1, archivo);
				//char *ar=arch.contenido;
				strcat(texto, arch.contenido);
				setbuf(stdin, NULL);
				contenido = &texto;
			}
			fclose(archivo);
			return contenido;

		} else {
			char texto[200];
			int i = 0;
			for (i = 0; i < ino.noInodo; i++) {
				datos arch;
				fseek(archivo, ino.bloques[i], SEEK_SET);
				fread(&arch, sizeof(datos), 1, archivo);
				//   char *ar=arch.contenido;
				strcat(texto, arch.contenido);
				setbuf(stdin, NULL);
				contenido = &texto;
				if (i > 3) {
					break;
				}
			}
			fclose(archivo);
			return contenido;
		}
	} else {
		if (carp.detalle > 0) {
			fclose(archivo);
			setbuf(stdin, NULL);
			return contenidoArchivo(contenido, carp.detalle, super, ruta, name);
		} else {
			printf("ERROR: El archivo no existe.\n");
			return "";
		}
	}
}

void renombrar() {
	if (id == NULL || path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = renombrarArchivo(id, path, name);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int renombrarArchivo(char* id, char* path, char* name) {
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
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
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
		strcpy(crear, path);
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
		////////////////////////////////////////
		char* ruta1;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		fclose(archivo);
		int datos;
		ruta1 = strtok(verificar2, "/");

		datos = buscarArchivo(ruta, sb, ap, ruta1, ajuste, posicion,
				sb.apuntadorAVD);

		if (datos > 0) {
			ruta1 = strtok(crear, "/");
			while ((strstr(ruta1, ".") == 0x0 || strstr(ruta1, ".") == ""
					|| strstr(ruta1, ".") == NULL) && ruta1 != NULL) {
				ruta1 = strtok(NULL, "/");
			}
			if (ruta1 != NULL) {
				cambiarNombre(datos, sb, ruta, ruta1, name);

				char contenido[100];
				strcat(contenido, "-name:");
				strcat(contenido, name);
				//bitacora(sb.apuntadorLog, 5, path, contenido, sb, ruta);
				return 1;
			}
		} else {
			printf("ERROR: No existe la ruta indicada.\n");
			return 0;
		}
	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}
}

int cambiarNombre(int posicion, superbloque super, char* ruta, char* nombre,
		char* nombreNuevo) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	for (i = 0; i < 5; i++) {
		if (carp.archivos[i].inodo > 1) {
			if (strcasecmp(carp.archivos[i].name, nombre) == 0) {
				break;
			}
		}
	}
	if (i < 5) {
		strcpy(carp.archivos[i].name, nombreNuevo);
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&carp, sizeof(detalle), 1, archivo);
		fclose(archivo);
		printf("-> Se ha cambiado el nombre correctamente.\n");
		return 1;
	} else {
		if (carp.detalle > 0) {
			fclose(archivo);
			return cambiarNombre(carp.detalle, super, ruta, nombre, nombreNuevo);
		} else {
			printf("ERROR: no existe documento");
			return 0;
		}
	}
}

void encontrar() {
	//printf("enc");
	if (id == NULL || path == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = encontrarArchivo(id, path, name, perm, user);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int encontrarArchivo(char* id, char* path, char* name, char* perm, char* user) {
	//printf("encont");
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
	//	printf("t");
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
	//printf("r");
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
		strcpy(crear, path);
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
		char* ruta1;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		fclose(archivo);

		char aux[10];
		char aux2[10];
		int k = 0;
		for (k = 0; k < 10; k++) {
			aux[k] = '\0';
			aux2[k] = '\0';
		}
		strcpy(aux, name);
		k = 1;
		if (aux[0] == '"') {
			while (aux[k] != '"') {
				aux2[k - 1] = aux[k];
				k++;
			}
		} else {
			strcpy(aux2, aux);
		}
		if (strcasecmp(path, "/") == 0) {
			//	 printf("if\n");
			return 0;
			buscarRaizCarpeta(ruta, sb, sb.apuntadorAVD, aux2, 0);
		} else {
			//		 printf("else\n");
			buscarCarpeta(ruta, ruta1, sb, sb.apuntadorAVD, aux2, 0);
		}

	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}

}

char* buscarCarpeta(char* ruta, char* path, superbloque super, int posicion,
		char* mensaje, int espacio) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd ap, ap2;
	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(avd), 1, archivo);

	//char* n=con.name;
	int i = 0;
	int j = 0;
	for (j = 0; j < espacio; j++) {
		printf(" ");
	}
	printf("|_%s\n", ap.name);

	char nombre[50];
	strcpy(nombre, ap.name);
	if (nombre[0] == '0' || nombre[15] == '0') {
		return "";
	}

	for (i = 0; i < 4; i++) {
		//int sc=ap.subCarpetas[i];
		if (ap.subDirectorios[i] > 50) {
			fseek(archivo, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, archivo);

			if (strcasecmp(ap2.name, path) == 0) {
				break;
			}
		}
	}
	if (i < 4) {
		path = strtok(NULL, "/");
		if (path != NULL && path != 0x0) {
			fclose(archivo);
			return buscarCarpeta(ruta, path, super, ap.subDirectorios[i],
					mensaje, espacio + 2);
		} else {
			int a = ap.subDirectorios[i];
			fclose(archivo);
			return buscarRaizCarpeta(ruta, super, a, mensaje, espacio + 2);
		}
	} else {
		if (ap.apuntadorAVD < 1) {
			printf("ERROR: No existe la carpeta indicada.\n");
			return "";
		} else {
			fclose(archivo);
			int p = ap.apuntadorAVD;
			return buscarCarpeta(ruta, path, super, p, mensaje, espacio);
		}
	}
	return "";
}

int buscarRaizCarpeta(char* ruta, superbloque super, int posicion,
		char* mensaje, int espacio) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	avd ap2, ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(avd), 1, archivo);
	//   char* n=ap.puntero;
	//  printf("nombre = %s\n",n);
	int i = 0;
	int j = 0;

	for (j = 0; j < espacio; j++) {
		printf(" ");
	}
	printf("|_%s\n", ap.name);
	fclose(archivo);
	for (i = 0; i < 4; i++) {

		if (ap.subDirectorios[i] > 500) {
			archivo = fopen(ruta, "rb+");
			fseek(archivo, ap.subDirectorios[i], SEEK_SET);
			fread(&ap2, sizeof(ap2), 1, archivo);
			fclose(archivo);
			buscarRaizCarpeta(ruta, super, ap.subDirectorios[i], mensaje,
					espacio + 2);
		}
	}
	if (ap.directorio > 100) {
		buscarRaizArchivo(ruta, super, ap.directorio, mensaje, espacio + 2);
	}
	if (ap.apuntadorAVD > 100) {
		buscarRaizCarpeta(ruta, super, ap.apuntadorAVD, mensaje, espacio);
	}
}

int buscarRaizArchivo(char* ruta, superbloque super, int posicion,
		char* mensaje, int espacio) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle ap2, ap;

	fseek(archivo, posicion, SEEK_SET);
	fread(&ap, sizeof(detalle), 1, archivo);
	int i = 0;
	int x = 0;
	int j = 0;

	fclose(archivo);
	for (i = 0; i < 3; i++) {
		if (ap.archivos[i].inodo > 50) {
			char aux[10];
			char aux2[16];
			for (j = 0; j < 10; j++) {
				aux[j] = '\0';
			}
			for (j = 0; j < 16; j++) {
				aux2[j] = '\0';
			}
			strcpy(aux2, ap.archivos[i].name);
			strcpy(aux, mensaje);

			if (aux[0] == '?' && aux[1] == '\0') {
				if (aux2[1] == '\0') {
					for (j = 0; j < espacio; j++) {
						printf(" ");
					}
					printf("|_");
					printf(ap.archivos[i].name);
					printf("\n");
				}
			} else if (aux[0] == '*' && aux[1] == '\0') {
				for (j = 0; j < espacio; j++) {
					printf(" ");
				}
				printf("|_%s\n", ap.archivos[i].name);
				//printf("\n");
			} else {
				j = 0;
				x = 0;
				while (aux[j] != '\0') {
					if (aux[j] == '?') {
						if (aux[j + 1] == aux2[x + 1]) {
							j++;
							x++;
						} else {
							break;
						}
					} else if (aux[j] == '*') {
						j++;
						while (aux[j] != aux2[x] && '\0' != aux2[x]) {
							x++;
						}
					} else if (aux[j] == aux2[x]) {
						j++;
						x++;
					} else {
						break;
					}
				}
				if (aux[j] == '\0') {
					int h;
					for (h = 0; h < espacio; h++) {
						printf(" ");
					}
					printf("|_%s\n", ap.archivos[i].name);
				}
			}
		}
	}
}

void crearDirectorio() {
	if (id == NULL || path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = crearDirectorioArchivo(id, path, p);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int crearDirectorioArchivo(char* id, char* path, char* p) {
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
		strcpy(crear, path);
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

		int datos;
		correcto = 1;
		if (p == NULL) {
			datos = crearCarpeta(ruta, sb, ap, ruta2, p, ajuste, posicion,
					sb.apuntadorAVD);
			ruta2 = strtok(crear, "/");
			if (correcto > 0) {
				datos = crearCarpeta(ruta, sb, ap, ruta2, "si", ajuste,
						posicion, sb.apuntadorAVD);
			}
		} else {
			ruta2 = strtok(crear, "/");
			datos = crearCarpeta(ruta, sb, ap, ruta2, p, ajuste, posicion,
					sb.apuntadorAVD);
		}
		//bitacora(sb.apuntadorLog, 6, path, " ", sb, ruta);

	} else {
		printf("No ha formateado la particion");
	}
}

void editar() {
	if (id == NULL || path == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		boolEditar = 1;
		int d = crearArchivoParticion(id, path, "si", size, cont);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

void mover() {
	if (id == NULL || path == NULL || dest == NULL || iddest == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		boolEditar = 1;
		int d = moverArchivo(id, path, dest, iddest);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}

}

int moverArchivo(char* id, char* path, char* dest, char* iddest) {
	printf("-> Copiar\n");
	int a = copiarArchivo(id, path, dest, iddest);
	printf("-> Eliminar\n");
	int b = removerArchivo(id, path, 0);
	if (a == 1 && b == 1) {
		return 1;
	} else {
		return 0;
	}
}

void logg() {
	boolLogin = 1;
	usrLogin = "root";
}

void login() {
	if (usuario == NULL || password == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		logg();
		//int d = loginUsuario(usuario, password);
		int d = iniciarSesion(usuario, password);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int loginUsuario(char* usuario, char* password) {
	//printf("ll\n");
	int o = obtenerArchivoUsers(id);
	if (o == 1) {
		int con2 = 1;
		FILE* archivoUsuario;
		archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "r+b");
		//char buffer[1000];
		char *atributos;
		if (archivoUsuario == NULL) {
			printf("ERROR: No existe el archivo Users.\n");
			return 0;
		} else {
			atributos = contenidoUsers;
			printf("BUFFER::\n%s\n", atributos);
			char atr[200];
			strcpy(atr, atributos);
			int j;
			for (j = 0; j < 200; j++) {
				if (atr[j] == '\\') {
					atr[j] = ' ';
				}
			}
			strcpy(atributos, atr);
			char aux[100];
			char *auxInst = NULL;
			strcpy(aux, atributos);
			inst = strtok(atributos, "\n");
			printf("i = %s\n", inst);
			auxInst = inst;
			atrUsuario[con2].atributos = auxInst;
			con2++;
			while (inst != NULL) {
				inst = strtok(NULL, "\n");
				//		printf("j= %s\n",inst);
				atrUsuario[con2].atributos = inst;
				con2++;
			}
			int i;
			for (i = 1; i < con2 - 1; i++) {
				//			printf("atr = %s\n",atrUsuario[i].atributos);
				if (atrUsuario[i].atributos != NULL) {
					int v = verificarLogin(atrUsuario[i].atributos, usuario,
							password);
					if (v > 0) {
						usrLogin = malloc(1 + strlen(usuario));
						strcpy(usrLogin, usuario);
						boolLogin = 1;
						return 1;
					}
				}
			}
			fclose(archivoUsuario);
			printf("ERROR: Usuario o password incorrectos.\n");
			return 0;

		}
		return 1;

	} else {
		printf("ERROR: No se ha iniciado sesion.\n");
		return 0;
	}

}

int verificarLogin(char* atributos, char* usuario, char* password) {
	printf("atributos = %s\n", atributos);
	char* instruc = NULL;
	con = 1;
	char atr[200];
	strcpy(atr, atributos);
	int j;
	for (j = 0; j < 200; j++) {
		if (atr[j] == '\\') {
			atr[j] = ' ';
		}
	}
	strcpy(atributos, atr);
	char aux[100];

	strcpy(aux, atributos);
	instruc = strtok(atributos, ",");
	contadorU = instruc;
	while (instruc != NULL) {
		instruc = strtok(NULL, ",");
		//	printf("j = %s\n",instruc);
		if (instruc != NULL) {
			switch (con) {
			case 1:
				tipoU = instruc;
				break;
			case 2:
				grupoU = instruc;
				break;
			case 3:
				nombreU = instruc;
				break;
			case 4:
				passU = instruc;
				break;
			}
			con++;
		}
	}
	/*****************/
	if (strcasecmp(tipoU, "U") == 0) {
		printf("U:: %s - %s\n", nombreU, usuario);
		if (strcasecmp(nombreU, usuario) == 0) {
			printf("P:: %s - %s\n", passU, password);
			if (strcasecmp(passU, password) == 0) {
				if (strcasecmp(contadorU, "0") == 0) {
					printf("-> El usuario ha sido eliminado.\n");
					return 0;
				} else {
					printf("-> El usuario %s se ha logeado exitosamente.\n",
							usuario);
					return 1;
				}
			}
		}
	}
	return 0;
}

int iniciarSesion(char* usuario, char* password) {
//	printf("filen= %s\n",filen);
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, "vda1") == 0) {
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
	superbloque sb = crearBloque();
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
		strcpy(crear, "/home/users.txt");
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
		int datos;
		ruta2 = strtok(verificar2, "/");
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

				//	bitacora(sb.apuntadorJournal, 2, filen, "", sb, ruta);
			}
		} else {
			printf("ERROR: La ruta no existe.\n");
		}
	} else {
		printf("ERROR: La particion no esta formateada.\n");
	}
	return 1;
}

void logout() {
	if (boolLogin == 1) { //Alguien journaleado
		printf("-> Ha cerrado sesion correctamente.\n");
		boolLogin = 0;
		usrLogin = NULL;
	} else {
		printf("ERROR: No existe ningun usuario journaleado.\n");
	}
}

void crearGrupo() {
	if (id == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (boolLogin == 1) {
			printf("usr =%s*\n", usrLogin);
			if (strcasecmp(usrLogin, "root") == 0) {
				int d = crearGrupoDisco(id, name);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}
			} else {
				printf("ERROR: Solo el usuario ROOT puede realizar cambios.\n");
			}
		} else {
			printf("bool = %d\n", boolLogin);
			printf("ERROR: Debe iniciar sesion como usuario ROOT.\n");
		}

	}
}

int crearGrupoDisco(char* id, char* name) {
	int o = obtenerArchivoUsers(id);
	if (o == 1) {
		contadorGrupo += 1;
//		printf("CONTENIDO = %s\n",contenidoUsers);
		FILE* archivoUsuario;
		archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "w+");
		fprintf(archivoUsuario, "%d,G,%s\n", contadorGrupo, name);
		fprintf(archivoUsuario, "%s", contenidoUsers);
		fclose(archivoUsuario);

		boolEditar = 1;
		int d = crearArchivoParticion(id, "/home/users.txt", "si", size,
				"/home/aylin/usersTemporal.txt");
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
		return 1;

	} else {
		printf("ERROR: No se pudo agregar el Grupo. Intentelo de nuevo.\n");
		return 0;
	}
}

void eliminarGrupo() {
	if (id == NULL || name == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (boolLogin == 1) {
			if (strcasecmp(usrLogin, "root") == 0) {
				int d = eliminarGrupoDisco(id, name);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}
			} else {
				printf("ERROR: Solo el usuario ROOT puede realizar cambios.\n");
			}
		} else {
			printf("ERROR: Debe iniciar sesion como usuario ROOT.\n");
		}

	}
}

int eliminarGrupoDisco(char* id, char* usuario) {

	int o = obtenerArchivoUsers(id);
	if (o == 1) {
		int con2 = 1;
		char* contenido = NULL;
		FILE* archivoUsuario;
		archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "w+");

		char *atributos;
		if (archivoUsuario == NULL) {
			printf("ERROR: No existe el archivo Users.\n");
			return 0;
		} else {
			remove("/home/aylin/usersTemporal.txt"); // Eliminamos el archivo

			atributos = contenidoUsers;
			char atr[200];
			strcpy(atr, atributos);
			int j;
			for (j = 0; j < 200; j++) {
				if (atr[j] == '\\') {
					atr[j] = ' ';
				}
			}
			strcpy(atributos, atr);
			char aux[100];
			char *auxInst = NULL;
			strcpy(aux, atributos);
			inst = strtok(atributos, "\n");

			auxInst = inst;
			atrUsuario[con2].atributos = auxInst;
			atribUsuario[con2].atributos = auxInst;
			con2++;
			while (inst != NULL) {
				inst = strtok(NULL, "\n");
				atrUsuario[con2].atributos = inst;
				atribUsuario[con2].atributos = inst;
				con2++;
			}
			int i;
			for (i = 1; i < con2; i++) {
				if (atrUsuario[i].atributos != NULL) {
					int v = eliminarG(atrUsuario[i].atributos, usuario);
					printf("v= %d\n", v);
				}
			}
			//printf("archivo\n");
			fclose(archivoUsuario);
			return 1;
		}
		return 1;

	} else {
		printf("ERROR: No se ha iniciado sesion.\n");
		return 0;
	}
}

int eliminarG(char* atributos, char* grupo) {
	FILE* archivoUsuario;
	archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "a+b");
	char* contenido = "";
	//char* conten = ",";
	char* c1;
	char* c2;
	char* c3;
	char* c4;

	char* instruc = NULL;
	con = 1;
	char atr[200];
	strcpy(atr, atributos);
	int j;
	for (j = 0; j < 200; j++) {
		if (atr[j] == '\\') {
			atr[j] = ' ';
		}
	}
	strcpy(atributos, atr);
	char aux[100];

	strcpy(aux, atributos);
	instruc = strtok(atributos, ",");
	contadorU = instruc;
	printf("k = %s\n", instruc);
	while (instruc != NULL) {
		instruc = strtok(NULL, ",");
		if (instruc != NULL) {
			printf("j = %s\n", instruc);

			switch (con) {
			printf("switch %d\n", con);
		case 1:
			tipoU = instruc;
			c1 = (char *) malloc(1 + strlen(",") + strlen(tipoU));
			strcpy(c1, ",");
			strcat(c1, tipoU);
			break;
		case 2:
			grupoU = instruc;
			c2 = (char *) malloc(1 + strlen(c1) + strlen(",") + strlen(grupoU));
			strcat(c2, c1);
			strcat(c2, ",");
			strcat(c2, grupoU);
			break;
		case 3:
			nombreU = instruc;
			c3 = (char *) malloc(
					1 + strlen(c2) + strlen(",") + strlen(nombreU));
			strcat(c3, c2);
			strcat(c3, ",");
			strcat(c3, nombreU);
			break;
		case 4:
			passU = instruc;
			c4 = (char *) malloc(1 + strlen(c3) + strlen(",") + strlen(passU));
			strcat(c4, c3);
			strcpy(c4, ",");
			strcat(c4, passU);

			break;
			}
			con++;
		}
	}
//printf("holi\n");
	/*****************/
	if (strcasecmp(tipoU, "G") == 0) {
		//	printf("U:: %s - %s\n",grupoU,grupo);
		if (strcasecmp(grupoU, grupo) == 0) {
			//	printf("C:: %s - \n",contadorU);
			contenido = "0";
			char* conten = (char *) malloc(1 + strlen("0") + strlen(c2));
			strcpy(conten, "0");
			strcat(conten, c2);
			fprintf(archivoUsuario, "%s\n", conten);
			fclose(archivoUsuario);

			if (strcasecmp(contadorU, "0") == 0) {
				printf("-> El usuario ya esta eliminado.\n");
				return 0;
			} else {
				printf("-> El grupo %s se ha eliminado correctamente.\n",
						grupo);
				return 1;
			}
		} else {
			char* conten = (char *) malloc(1 + strlen(contadorU) + strlen(c2));
			strcpy(conten, contadorU);
			strcat(conten, c2);
			fprintf(archivoUsuario, "%s\n", conten);
			fclose(archivoUsuario);
		}
	} else {
		//contenido =contadorU;
		char* conten = (char *) malloc(1 + strlen(contadorU) + strlen(c4));
		strcpy(conten, contadorU);
		strcat(conten, c4);
		fprintf(archivoUsuario, "%s\n", conten);
		fclose(archivoUsuario);

	}
	return 0;
}

char* cambiarEliminado(char* atributos) {
	char* contenido = NULL;
	char* instruc = NULL;
	con = 1;
	char atr[200];
	strcpy(atr, atributos);
	int j;
	for (j = 0; j < 200; j++) {
		if (atr[j] == '\\') {
			atr[j] = ' ';
		}
	}
	strcpy(atributos, atr);
	char aux[100];

	strcpy(aux, atributos);
	instruc = strtok(atributos, ",");
	contadorU = instruc;
	strcpy(contenido, "0,");
	while (instruc != NULL) {
		instruc = strtok(NULL, ",");
		//	printf("j = %s\n",instruc);
		if (instruc != NULL) {
			switch (con) {
			case 1:
				tipoU = instruc;
				strcat(contenido, tipoU);
				break;
			case 2:
				grupoU = instruc;
				strcat(contenido, ",");
				strcat(contenido, grupoU);
				break;
			case 3:
				nombreU = instruc;
				strcat(contenido, ",");
				strcat(contenido, nombreU);
				break;
			case 4:
				passU = instruc;
				strcat(contenido, ",");
				strcat(contenido, passU);
				break;
			}
			con++;
		}
	}
	return contenido;
}

void crearUsuario() {
	if (id == NULL || name == NULL || password == NULL || grupo == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (boolLogin == 1) {
			if (strcasecmp(usrLogin, "root") == 0) {
				int d = crearUsuarioDisco(id, name, password, grupo);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}
			} else {
				printf("ERROR: Solo el usuario ROOT puede realizar cambios.\n");
			}
		} else {
			printf("bool = %d\n", boolLogin);
			printf("ERROR: Debe iniciar sesion como usuario ROOT.\n");
		}
	}
}

int crearUsuarioDisco(char* id, char* usuario, char* password, char* grupo) {
	int o = obtenerArchivoUsers(id);
	if (o == 1) {
		contadorUsuario += 1;
//		printf("CONTENIDO = %s\n",contenidoUsers);
		FILE* archivoUsuario;
		archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "a+");
		int v = verificarGrupo(grupo);
		if (v > 0) {
			fprintf(archivoUsuario, "\n%d,U,%s,%s,%s", contadorUsuario, grupo,
					usuario, password);
		}
		//	fprintf(archivoUsuario,"%s",contenidoUsers);
		fclose(archivoUsuario);

		boolEditar = 1;
		int d = crearArchivoParticion(id, "/home/users.txt", "si", size,
				"/home/aylin/usersTemporal.txt");
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
		return 1;

	} else {
		printf("ERROR: No se pudo agregar el Usuario. Intentelo de nuevo.\n");
		return 0;
	}
}

int verificarGrupo(char* grupo) {
	int con2 = 1;
	FILE* archivoUsuario;
	archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "r+b");

	char *atributos;
	if (archivoUsuario == NULL) {
		printf("ERROR: No existe el archivo Users.\n");
		return 0;
	} else {
		atributos = contenidoUsers;
//		printf("BUFFER::\n%s\n",atributos);

		char atr[200];
		strcpy(atr, atributos);
		int j;
		for (j = 0; j < 200; j++) {
			if (atr[j] == '\\') {
				atr[j] = ' ';
			}
		}
		strcpy(atributos, atr);
		char aux[100];
		char *auxInst = NULL;
		strcpy(aux, atributos);
		inst = strtok(atributos, "\n");
		//printf("i = %s\n",inst);
		auxInst = inst;
		atrUsuario[con2].atributos = auxInst;
		con2++;
		while (inst != NULL) {
			inst = strtok(NULL, "\n");
			//auxInst = inst;
			//	printf("ii = %s\n",inst);
			atrUsuario[con2].atributos = inst;
			con2++;
		}
		int i;
		for (i = 1; i < con2; i++) {
			//	printf("atr = %s\n",atrUsuario[i].atributos);
			if (atrUsuario[i].atributos != NULL) {
				int v = verificar(atrUsuario[i].atributos, grupo);
				if (v > 0) {
					return 1;
				}
			}
		}
		fclose(archivoUsuario);
		printf("ERROR: No se ha encontrado el grupo.\n");
		return 0;

	}

	return 1;
}

int verificar(char* atributos, char* grupo) {
	con = 1;
	char* instruc = NULL;
	char atr[200];
	strcpy(atr, atributos);
	int j;
	for (j = 0; j < 200; j++) {
		if (atr[j] == '\\') {
			atr[j] = ' ';
		}
	}
	strcpy(atributos, atr);
	char aux[100];
	strcpy(aux, atributos);
	instruc = strtok(atributos, ",");
	contadorU = instruc;
	while (instruc != NULL) {
		instruc = strtok(NULL, ",");

		//	printf("i = %s\n",auxInst);
		if (instruc != NULL) {
			switch (con) {
			case 1:
				tipoU = instruc;
				break;
			case 2:
				grupoU = instruc;
				break;
			case 3:
				nombreU = instruc;
				break;
			case 4:
				passU = instruc;
				break;
			}
			con++;
		}
	}
	/*****************/
	if (strcasecmp(tipoU, "G") == 0) {
		//	printf("%s - %s\n",grupoU,grupo);
		if (strcasecmp(grupoU, grupo) == 0) {
			if (strcasecmp(contadorU, "0") == 0) {
				printf("-> El usuario ha sido eliminado.\n");
				return 0;
			} else {
				printf("-> Se ha encontrado el grupo.\n");
				return 1;
			}
		}
	}
	return 0;
}

void eliminarUsuario() {
	if (id == NULL || usuario == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (boolLogin == 1) {
			if (strcasecmp(usrLogin, "root") == 0) {
				int d = eliminarUsuarioDisco(id, usuario);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}
			} else {
				printf("ERROR: Solo el usuario ROOT puede realizar cambios.\n");
			}
		} else {
			printf("ERROR: Debe iniciar sesion como usuario ROOT.\n");
		}

	}
}

int eliminarUsuarioDisco(char* id, char* usuario) {
	int o = obtenerArchivoUsers(id);
	if (o == 1) {
		int con2 = 1;
		char* contenido = NULL;
		FILE* archivoUsuario;
		archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "w+");

		char *atributos;
		if (archivoUsuario == NULL) {
			printf("ERROR: No existe el archivo Users.\n");
			return 0;
		} else {
			remove("/home/aylin/usersTemporal.txt"); // Eliminamos el archivo

			atributos = contenidoUsers;
			char atr[200];
			strcpy(atr, atributos);
			int j;
			for (j = 0; j < 200; j++) {
				if (atr[j] == '\\') {
					atr[j] = ' ';
				}
			}
			strcpy(atributos, atr);
			char aux[100];
			char *auxInst = NULL;
			strcpy(aux, atributos);
			inst = strtok(atributos, "\n");

			auxInst = inst;
			atrUsuario[con2].atributos = auxInst;
			atribUsuario[con2].atributos = auxInst;
			con2++;
			while (inst != NULL) {
				inst = strtok(NULL, "\n");
				atrUsuario[con2].atributos = inst;
				atribUsuario[con2].atributos = inst;
				con2++;
			}
			int i;
			for (i = 1; i < con2; i++) {
				if (atrUsuario[i].atributos != NULL) {
					int v = eliminarU(atrUsuario[i].atributos, usuario);
					printf("v= %d\n", v);
				}
			}
			//printf("archivo\n");
			fclose(archivoUsuario);
			return 1;
		}
		return 1;

	} else {
		printf("ERROR: No se ha iniciado sesion.\n");
		return 0;
	}

}

int eliminarU(char* atributos, char* usuario) {
	FILE* archivoUsuario;
	archivoUsuario = fopen("/home/aylin/usersTemporal.txt", "a+b");
	char* c1;
	char* c2;
	char* c3;
	char* c4;

	char* instruc = NULL;
	con = 1;
	char atr[200];
	strcpy(atr, atributos);
	int j;
	for (j = 0; j < 200; j++) {
		if (atr[j] == '\\') {
			atr[j] = ' ';
		}
	}
	strcpy(atributos, atr);
	char aux[100];

	strcpy(aux, atributos);
	instruc = strtok(atributos, ",");
	contadorU = instruc;
	printf("k = %s\n", instruc);
	while (instruc != NULL) {
		instruc = strtok(NULL, ",");
		if (instruc != NULL) {
			printf("j = %s\n", instruc);

			switch (con) {
			printf("switch %d\n", con);
		case 1:
			tipoU = instruc;
			c1 = (char *) malloc(1 + strlen(",") + strlen(tipoU));
			strcpy(c1, ",");
			strcat(c1, tipoU);
			break;
		case 2:
			grupoU = instruc;
			c2 = (char *) malloc(1 + strlen(c1) + strlen(",") + strlen(grupoU));
			strcat(c2, c1);
			strcat(c2, ",");
			strcat(c2, grupoU);
			break;
		case 3:
			nombreU = instruc;
			c3 = (char *) malloc(
					1 + strlen(c2) + strlen(",") + strlen(nombreU));
			strcat(c3, c2);
			strcat(c3, ",");
			strcat(c3, nombreU);
			break;
		case 4:
			passU = instruc;
			c4 = (char *) malloc(1 + strlen(c3) + strlen(",") + strlen(passU));
			strcat(c4, c3);
			strcpy(c4, ",");
			strcat(c4, passU);

			break;
			}
			con++;
		}
	}
	if (strcasecmp(tipoU, "U") == 0) {
		//	printf("U:: %s - %s\n",grupoU,grupo);
		if (strcasecmp(nombreU, usuario) == 0) {
			//	printf("C:: %s - \n",contadorU);
			char* conten = (char *) malloc(1 + strlen("0") + strlen(c4));
			strcpy(conten, "0");
			strcat(conten, c4);
			fprintf(archivoUsuario, "%s\n", conten);
			fclose(archivoUsuario);

			if (strcasecmp(contadorU, "0") == 0) {
				printf("-> El usuario ya esta eliminado.\n");
				return 0;
			} else {
				printf("-> El grupo %s se ha eliminado correctamente.\n",
						nombreU);
				return 1;
			}
		} else {
			char* conten = (char *) malloc(1 + strlen(contadorU) + strlen(c4));
			strcpy(conten, contadorU);
			strcat(conten, c4);
			fprintf(archivoUsuario, "%s\n", conten);
			fclose(archivoUsuario);
		}
	} else {
		//contenido =contadorU;
		char* conten = (char *) malloc(1 + strlen(contadorU) + strlen(c2));
		strcpy(conten, contadorU);
		strcat(conten, c2);
		fprintf(archivoUsuario, "%s\n", conten);
		fclose(archivoUsuario);

	}
	return 0;
}

int obtenerArchivoUsers(char* id) {
	//	printf("filen= %s\n",filen);
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
		//printf("N:: %s - %s\n", structDisco.part[i].name, nombre);
		if (strcasecmp(structDisco.part[i].name, nombre) == 0) {
			break;
		}
		for (j = 0; j < 10; j++) {
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
				esLogica = 1;
				break;
			}
			if (esLogica == 1) {
				break;
			}
		}
	}
	if (i == 4 && esLogica == 0) {
		printf("ERROR: No existe el nombre indicado (ObtenerUsuarios).\n");
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
		strcpy(crear, "/home/users.txt");
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
		int datos;
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
				printf("* * * * * *\n");
				//			//		printf("contenidoArchivo.\n");
				char* con = contenidoArchivo(" ", datos, sb, ruta, ruta2);
				strcpy(mensaje, con);
				contenidoUsers = con;
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

void permiso() {
	if (id == NULL || path == NULL || ugo == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = permisoArchivo(id, path, ugo, R);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int permisoArchivo(char* id, char* path, char* ugo, char* R) {
	printf("permiso\n");
	int r = rangoPermiso(ugo);
	if (r == 0) {
		return 0;
	}
	printf("rango\n");
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
			if (strcasecmp(structDisco.part[i].exten[j].name, nombre) == 0) {
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
		strcpy(crear, path);
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
		////////////////////////////////////////
		char* ruta1;
		strcpy(verificar, verificar2);
		if (verificar[0] == '\0') {
			ruta1 = strtok(crear, "/");
		} else {
			ruta1 = strtok(verificar, "/");
		}
		fclose(archivo);
		int datos;
		ruta1 = strtok(verificar2, "/");
		printf("buscar\n");
		datos = buscarArchivo(ruta, sb, ap, ruta1, ajuste, posicion,
				sb.apuntadorAVD);
		printf("BB\n");
		if (datos > 0) {
			ruta1 = strtok(crear, "/");
			while ((strstr(ruta1, ".") == 0x0 || strstr(ruta1, ".") == ""
					|| strstr(ruta1, ".") == NULL) && ruta1 != NULL) {
				ruta1 = strtok(NULL, "/");
			}
			if (ruta1 != NULL) {
				printf("cambiar\n");
				cambiarPermiso(datos, sb, ruta, ruta1, ugo, 1);

				char contenido[100];
				strcat(contenido, "-name:");
				strcat(contenido, name);
				//bitacora(sb.apuntadorJournal,5,path,contenido,sb,ruta);
				return 1;
			}
		} else {
			printf("ERROR: No existe la ruta indicada.\n");
			return 0;
		}
	} else {
		printf("ERROR: No se ha formateado la particion.\n");
		return 0;
	}
}

int cambiarPermiso(int posicion, superbloque super, char* ruta, char* nombre,
		char* permiso, int opcion) {
	FILE* archivo;
	archivo = fopen(ruta, "rb+");
	detalle carp;
	fseek(archivo, posicion, SEEK_SET);
	fread(&carp, sizeof(detalle), 1, archivo);
	int i = 0;
	for (i = 0; i < 3; i++) {
		if (carp.archivos[i].inodo > 1) {
			if (opcion == 0) { //Agregar
				if (strcasecmp(carp.archivos[i].ino.permisos, permiso) == 0) {
					break;
				}
			} else { //Modificar
				if (strcasecmp(carp.archivos[i].ino.permisos, permiso) == 0) {
					break;
				}
			}
		}
	}
	if (i < 3) {
		if (opcion == 0) { //Agregar
			strcpy(carp.archivos[i].ino.permisos, permiso);
			strcpy(carp.archivos[i].ino.uID, usrLogin);
		} else { //Modificar
			strcpy(carp.archivos[i].ino.permisos, permiso);
		}
		fseek(archivo, posicion, SEEK_SET);
		fwrite(&carp, sizeof(detalle), 1, archivo);
		fclose(archivo);
		printf("-> Se ha cambiado los permisos correctamente.\n");
		return 1;
	} else {
		if (carp.detalle > 0) {
			fclose(archivo);
			return cambiarPermiso(carp.detalle, super, ruta, nombre, permiso,
					opcion);
		} else {
			printf("ERROR: no existe documento");
			return 0;
		}
	}

}

int rangoPermiso(char* ugo) {
	char perm[10];
	strcpy(perm, ugo);
	//perm[3] = ugo;
	printf("copy =%s\n", ugo);
	int i;
	for (i = 0; i < 3; i++) {
		//printf("char = %c\n",perm[i]);

		if (perm[i] == '0' || perm[i] == '1' || perm[i] == '2' || perm[i] == '3'
				|| perm[i] == '4' || perm[i] == '5' || perm[i] == '6'
				|| perm[i] == '7') {

		} else {
			printf("ERROR: Permiso %c invalido.\n", perm[i]);
			return 0;
		}
	}
	return 1;
}

int bitacora(int posicion, int operacion, char* nombre, char* contenido,
		superbloque super, char* ruta) {
	printf("Bitacora = (%d, %d, %s, %s, %s )\n", posicion, operacion, nombre,
			contenido, ruta);

	FILE* disco;
	disco = fopen(ruta, "rb+");
	journal bitacora;
	fseek(disco, posicion, SEEK_SET);
	fread(&bitacora, sizeof(journal), 1, disco);

	int a = 1;
	int b = posicion;
	int i = 0;
//	printf("tipo = %d\n",bitacora.tipo);
	while (bitacora.tipo > 0) { //Si es carpeta
		//for(i=0;i<15;i++){
		//	printf("tipo = %d\n",bitacora.tipo);
		b = bitacora.tipo;
		fseek(disco, bitacora.tipo, SEEK_SET);
		fread(&bitacora, sizeof(journal), 1, disco);
		a++;
	}
	//printf("* * * * * * *\n");
	bitacora.tipo = super.apuntadorLog + 100 * a * sizeof(journal);
	fseek(disco, b, SEEK_SET);
	fwrite(&bitacora, sizeof(journal), 1, disco);

	journal bita;
	bita.operacion = operacion;
	//strcpy(bita.usuario, usrLogin);
	strcpy(bita.nombre, nombre);
	strcpy(bita.contenido, contenido);
	bita.fecha = time(0);
	bita.tipo = 0;
	fseek(disco, bitacora.tipo, SEEK_SET);
	fwrite(&bita, sizeof(journal), 1, disco);

	fclose(disco);
	return 1;
}

void generarReporte() {

	if (path == NULL || name == NULL || id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		if (strcasecmp(name, "mbr") == 0 || strcasecmp(name, "mbr\n") == 0) {
			//printf("entro");
			int d = reporteMBR(id, name, path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "disk") == 0
				|| strcasecmp(name, "disk\n") == 0) {
			int d = reporteDISK(id, name, path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "inode") == 0
				|| strcasecmp(name, "inode\n") == 0) {
			int d = reporteINODO(id, name, path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "bitacora") == 0
				|| strcasecmp(name, "bitacora\n") == 0) {
			int d = reporteBITACORA(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "bm_arbdir") == 0
				|| strcasecmp(name, "bm_arbdir\n") == 0) {
			int d = reporteBITMAP_ARBOL(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "bm_detdir") == 0
				|| strcasecmp(name, "bm_detdir\n") == 0) {
			int d = reporteBITMAP_DETALLE(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "bm_inode") == 0
				|| strcasecmp(name, "bm_inode\n") == 0) {
			int d = reporteBITMAP_INODO(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "bm_block") == 0
				|| strcasecmp(name, "Bm_block\n") == 0) {
			int d = reporteBITMAP_BLOQUE(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "tree") == 0
				|| strcasecmp(name, "tree\n") == 0) {
			int d = reporteTREE(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "sb") == 0
				|| strcasecmp(name, "sb\n") == 0) {
			int d = reporteSB(name, path, id);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else if (strcasecmp(name, "file") == 0
				|| strcasecmp(name, "file\n") == 0) {
			//printf("HOLIWI = %s\n",ruta);
			if (ruta != NULL) {
				int d = reporteFILE(name, path, id, ruta);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}
			} else {
				printf("Falta el atributo ruta.\n");
			}
		} else if (strcasecmp(name, "tree_file") == 0
				|| strcasecmp(name, "tree_file\n") == 0) {
			if (ruta != NULL) {

				int d = reporteTREE_F(id, name, path, ruta);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}
			} else {
				printf("Falta el atributo ruta.\n");
			}
		} else if (strcasecmp(name, "tree_directorio") == 0
				|| strcasecmp(name, "tree_directorio") == 0) {
			if (ruta != NULL) {

				int d = reporteTREE_DIRECTORIO(id, name, path, ruta);
				if (d == 0) {
					printf(
							"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
				}
			} else {
				printf("Falta el atributo ruta.\n");
			}
		} else if (strcasecmp(name, "directorio") == 0
				|| strcasecmp(name, "directorio") == 0) {
			int d = reporteDIRECTORIO(id, name, path);
			if (d == 0) {
				printf(
						"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
			}
		} else {
			printf("name = %s\n", name);
			printf("x\n");
		}
	}
}

superbloque crearBloque() {
	superbloque sb;

	//sb.nombre = "";
	sb.arbolVirtualCount = 0;
	//sb.detalleDirectorioCount =0;
	sb.inodosCount = 0;
	sb.bloquesCount = 0;
	//sb.freeArbolCount = 0;
	//sb.freeDetalleDirectorioCount =0;
	sb.freeBloquesCount = 0;
	sb.freeInodosCount = 0;
	sb.DateCreacion = time(0);
	sb.DateMontaje = time(0);
	sb.mountCount = 0;
	sb.magic = 0;
	sb.inodoSize = 0;
	sb.bloqueSize = 0;
	//sb.arbolDirectorioSize = 0;
	//sb.detalleDirectorioSize = 0;
	sb.apuntadorLog = 0;
	sb.apuntadorBitArbolDirectorio = 0;
	sb.apuntadorAVD = 0;
	sb.apuntadorBitDetalleDirectorio = 0;
	sb.apuntadorDetalleDirectorio = 0;
	sb.apuntadorBitTablaInodo = 0;
	sb.apuntadorTablaInodo = 0;
	sb.apuntadorBitmapInodo = 0;
	sb.apuntadorCopia = 0;
	//sb.firstFreeBitArbol = 0;
	//sb.firstFreeBitDetalleDirectorio =0;
	sb.firstFreeBitTablaInodo = 0;
	sb.firstFreeBitBloque = 0;

	return sb;
}

void loss(){
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = systemLoss(id);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int systemLoss(char* id){
	char* ruta;
	char* nombre;
	int i = 0;
	for (i = 0; i < 31; i++) {
		if (montar[i].vdID != NULL) {
			//	printf("NOT NULL -> %s-%s-\n",montar[i].vdID,id);
			if (strcasecmp(montar[i].vdID, id) == 0) {
				//	 printf("igual\n");
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
	superbloque sb = crearBloque();
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
	printf("M= %d\n", sb.magic);
	if (sb.magic == 201404368) {
		fseek(archivo, sb.apuntadorAVD, SEEK_SET);
		avd ap;
		fread(&ap, sizeof(ap), 1, archivo);

		char crear[100];
		char verificar[100];
		char verificar2[100];
		strcpy(crear, path);

		int b, a = 0;
		for (a = 0; a < 100; a++) {
			if (crear[a] != '\0') {
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
	}

}

void recovery(){
	if (id == NULL) {
		printf("ERROR: Falta un atributo obligatorio.\n");
	} else {
		int d = systemRecovey(id);
		if (d == 0) {
			printf(
					"Se han encontrado errores en el comando. No se ha podido ejecutar correctamente.\n");
		}
	}
}

int systemRecovey(char* id){
