#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "TS.h"

simbolo TS[50]; //Tabla

void inicializarTabla() {
    for (int i = 0; i < 50; i++) {
        TS[i].entero = -1;
        strcpy(TS[i].cadena, "");
        strcpy(TS[i].id, "");
    }
}

int indiceTabla(char* id) {
    for (int i = 0; i < 50; i++) {
        if (strcmp(TS[i].id, id) == 0) return i;
    }
    return -1;
}

int retornarValorInt(char* id) {
    int i = indiceTabla(id);
    if (i >= 0 && TS[i].tipo == 1) {
        return TS[i].entero;
    }
    printf("Error: '%s' no está definido o no es un entero.\n", id);
    return 0; // Devuelve un valor por defecto si hay un error
}

char* retornarValorCad(char* id) {
    int i = indiceTabla(id);
    if (i >= 0 && TS[i].tipo == 0) {
        return TS[i].cadena;
    }
    printf("Error: '%s' no está definido o no es una cadena.\n", id);
    return NULL; // Devuelve NULL si hay un error
}

void escribirIntTabla(char* id, int valor, int esConst){
    int ind = indiceTabla(id);
    if (ind == -1) { // No está en la TS
        int i = 0;
        for (i; i < 50 && TS[i].entero != -1; i++); // busca la primera entrada vacía 
        if (i >= 50) { printf("No hay más espacio en la TS.\n"); return;} 
        sprintf(TS[i].id, "%s", (char*)id); 
        TS[i].entero = valor; 
        TS[i].tipo = 1; //Int es tipo1
        TS[i].esConst = esConst;
        sprintf(TS[i].id, "%s", id); 
        //printf("Se asigno %i al nuevo ID: %s\n", valor, id);
    } else if(TS[ind].esConst == 1){
        printf("NO es posible cambiar el valor de '%s' a %i porque es una constante\n", id, valor);
    } else { //Si ya esta en la TS
        TS[ind].entero = valor; 
        TS[ind].tipo = 1;
        //printf("Se asigno %i al ID: %s\n", valor, id);
    } 
}

void escribirCadTabla(char* id, char* valor, int esConst){
    int ind = indiceTabla(id);
    if (ind == -1) { // No está en la TS
        int i = 0;
        for (i; i < 50 && strcmp(TS[i].cadena, "") != 0; i++); // busca la primera entrada vacía 
        if (i >= 50) { printf("No hay más espacio en la TS.\n"); return; } 
        sprintf(TS[i].id, "%s", (char*)id); 
        sprintf(TS[i].cadena, "%s", (char*)valor); 
        TS[i].tipo = 0;
        TS[i].esConst = esConst;
        sprintf(TS[i].id, "%s", id); 
        //printf("Se asigno %s al nuevo ID: %s\n", valor, id);
    } else if(TS[ind].esConst == 1){
        printf("NO es posible cambiar el valor de %s a %s porque es una constante\n", id, valor);
    } else { //Si ya esta en la TS y no es Const
        strcpy(TS[ind].cadena, (char*)valor); 
        TS[ind].tipo = 0;
        //printf("Se asigno %s al ID: %s\n", valor, id);
    } 
}

int tipoVariable(char* s) { 
    int i = indiceTabla(s);
    if (i != -1){ return TS[i].tipo;}
    return -1;
}

static int numerico(char* s){
    for(int i=0; i<strlen(s); i++)
        if (!isdigit(s[i])) return -1;
    return atoi(s);
}

void cargarEntradas(char* p1) {
    int valor;
    char temp[50];
    printf("Ingresa el valor de %s: ", p1);
    fscanf(stdin, "%s", temp);

    if ((valor = numerico(temp)) != -1) {
        escribirIntTabla(p1, valor, 1); // Pasar el valor como entero
    } else {
        escribirCadTabla(p1, temp, 0); // Pasar la cadena directamente
    }
}

void imprimir(char* id) {
    int i = indiceTabla(id);
    if (i >= 0) {
        if (TS[i].tipo == 1) {
            printf("Entero: %d\n", TS[i].entero);
        } else if (TS[i].tipo == 0) {
            printf("Cadena: %s\n", TS[i].cadena);
        } else {
            printf("Error: Tipo no reconocido para '%s'.\n", id);
        }
    } else {
        printf("Error: Variable '%s' no encontrada.\n", id);
    }
}
