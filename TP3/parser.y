%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TS.h"

int yyerror(const char* s);     // alternativa de error
int yynerrs;                    // cantidad de errores sintacticos
int yylex();                    // analisis lexico alternativo sin void
extern int yynerrs;             // cantidad de errores sintacticos
extern int yylexerrs;           // cantidad de errores lexicos
extern FILE* yyin;              // archivo de entrada de extension .m
extern int yylineno;            // linea del error

%}

%union {
    int entero;
    char cadena[32];
}

%token INICIO FIN PUNTOYCOMA COMA 
%token LEER ESCRIBIR ASIGNACION
%token CONST TIPO_INT TIPO_STRING
%token PARENIZQUIERDO	PARENDERECHO
%token SUMA RESTA
%token <cadena> ID CONSTCADENA
%token <entero> CONSTNUM
%type <entero> expresion primaria

%left SUMA RESTA
%right ASIGNACION

%start programa  // Axioma

%%  // Reglas gramaticales

programa : 
    INICIO listaSentencias FIN  { if (yynerrs || yylexerrs) YYABORT; }
;

listaSentencias : 
    sentencia 
    | listaSentencias sentencia
;

sentencia :
    TIPO_INT ID PUNTOYCOMA                                     { if(indiceTabla($2) == -1) {escribirIntTabla($2, -1, 0);} else {yyerror("La variable ya existe");} }
    | TIPO_INT ID ASIGNACION expresion PUNTOYCOMA              { if(indiceTabla($2) == -1) {escribirIntTabla($2, $4, 0);} else {yyerror("La variable ya existe");}}
    | CONST TIPO_INT ID ASIGNACION expresion PUNTOYCOMA        { if(indiceTabla($3) == -1) {escribirIntTabla($3, $5, 1);} else {yyerror("La variable ya existe");}} 
    | TIPO_STRING ID PUNTOYCOMA                                { if(indiceTabla($2) == -1) {escribirCadTabla($2, "", 0);} else {yyerror("La variable ya existe");}}                                                     
    | TIPO_STRING ID ASIGNACION CONSTCADENA PUNTOYCOMA         { if(indiceTabla($2) == -1) {escribirCadTabla($2, $4, 0);} else {yyerror("La variable ya existe");}} 
    | CONST TIPO_STRING ID ASIGNACION CONSTCADENA PUNTOYCOMA   { if(indiceTabla($3) == -1) {escribirCadTabla($3, $5, 1);} else {yyerror("La variable ya existe");}} 
    
    | ID ASIGNACION expresion PUNTOYCOMA                        {if(indiceTabla($1) == -1) yyerror("La variable no fue declarada"); 
                                                                else if(tipoVariable($1) == 1) escribirIntTabla($1, $3, 0);
                                                                else yyerror("Se esperaba un string");}

    | ID ASIGNACION CONSTCADENA PUNTOYCOMA                      {if (indiceTabla($1) == -1) yyerror("La variable no fue declarada"); 
                                                                else if (tipoVariable($1) == 0) escribirCadTabla($1, $3, 0); 
                                                                else yyerror("Se esperaba un int");}

    | LEER PARENIZQUIERDO listaIdentificadores PARENDERECHO PUNTOYCOMA  
    | ESCRIBIR PARENIZQUIERDO listaExpresiones PARENDERECHO PUNTOYCOMA  
;

listaIdentificadores :
    ID                              { cargarEntradas($1); } 
    | listaIdentificadores COMA ID  { cargarEntradas($3); } 
;

listaExpresiones :
    expresion                           { printf("%d\n", $1); }
    | listaExpresiones COMA expresion   { printf("%d\n", $3); }
;

expresion :
    primaria                    { $$ = $1; }
    | expresion SUMA primaria   { $$ = $1 + $3; }
    | expresion RESTA primaria  { $$ = $1 - $3; }
;

primaria :
    ID { 
        if (tipoVariable($1) == 1) { //Si lee un int
            $$ = retornarValorInt($1); 
        }
        else if (tipoVariable($1) == 0) { //Si lee un string        
            printf("Cadena: %s ", retornarValorCad($1)); 
            $$ = 0;
        } else {
            yyerror("Variable no declarada");
            $$ = 0;
        }
    }
    | CONSTNUM                                 { $$ = $1; }
    | CONSTCADENA                              { printf("Cadena: %s ", $1);  $$ = 0;} 
    | PARENIZQUIERDO expresion PARENDERECHO    { $$ = $2; }
;

%%

int yylexerrs = 0;

int yyerror(const char* s) {
  extern int yylineno;  // Línea actual del analizador léxico
  extern char* yytext;  // Texto del token actual

  printf("Error en la linea %d %s.\n", yylineno, s);  
  //printf("Error Sintactico en la linea %d: token no valido '%s'.\n", yylineno, yytext);
  return 0;
}

// AGREGAR UN WHILE EN CASO DE VALOR ERRONEO
// REEMPLAZAR IF POR CASE
int main() {
  int opcion;
  printf("Seleccione entrada:\n 1. Archivo\n 2. Teclado\n");
  scanf("%d", &opcion);
  if (opcion == 1) { // Cargar un archivo
      char archivo[100];                  // Nombre del archivo
      printf("Ingrese el nombre del archivo: ");
      scanf("%s", &archivo);
      yyin = fopen(archivo, "r");
  } else
        yyin = stdin;
        
    inicializarTabla(); // Inicializa la tabla con todo en -1

    // Parser
    switch (yyparse()) {
        case 0: 
          printf("\nCompilado exitosamente\n");
          break;
        case 1: 
          printf("Error de compilacion\n");
          break;
        case 2: 
          printf("Memoria insuficiente\n");
          break;
    }
    printf("Cantidad de errores Lexicos: %i\n", yylexerrs);
    printf("Cantidad de errores Sintacticos: %i\n", yynerrs);

    return 0;
}