#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

typedef struct
{
    char id[32];
    int tipo; //1.Entero. 0.Cadena
    int entero;
    char cadena[255];
    int esConst; //1.True 0.False
} simbolo;

void inicializarTabla(); 
int indiceTabla(char* id);
char* retornarValorCad(char* id); 
int retornarValorInt(char* id); 
void escribirIntTabla(char* s, int valor, int esConst);
void escribirCadTabla(char* s, char* valor, int esConst);
int tipoVariable(char* s);
void cargarEntradas(char* p1); // leer ids
void imprimir(char* id);

#endif