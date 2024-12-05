%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"  //Incluir los tokens definidos en Bison

int yyerror(char *s); //Funcion de error
int yylex();
int yylineno=1;   // Linea inicial
int yylexerrs;  // Contador de errores lexicos
%}

ID          [a-zA-Z_][a-zA-Z0-9_]*
CONSTNUM    [0-9]+
CONSTCADENA \"[^\"]*\"

%%
"inicio"                {return INICIO;}
"fin"                   {return FIN;}
"leer"                  {return LEER;}
"escribir"              {return ESCRIBIR;}
"const"                 {return CONST;}
"int"                   {return TIPO_INT;}
"string"                {return TIPO_STRING;}
"("                     {return PARENIZQUIERDO;}
")"                     {return PARENDERECHO;}  
";"                     {return PUNTOYCOMA;}
"+"                     {return SUMA;}
"-"                     {return RESTA;} 
":="                    {return ASIGNACION;}
","                     {return COMA;}        
{ID}                    { strcpy(yylval.cadena, yytext); return ID; } 
{CONSTNUM}              { yylval.entero = atoi(yytext); return CONSTNUM; }
{CONSTCADENA}           { strcpy(yylval.cadena, yytext); return CONSTCADENA; }
\n                      {yylineno++;}
[ \t]                   ; //ignora los espacios
.                       {printf("Error lexico en la linea %d caracter '%s' invalido.\n", yylineno, yytext); yylexerrs++; } 
%%

int yywrap(void) { 
    return 1; 
} 
