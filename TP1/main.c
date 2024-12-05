#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TERMINALES 3
#define MAX_NOTERMINALES 3
#define MAX_PRODUCCIONES 3
#define LONGITUD_PRODUCCION 6
#define MAX_CADENA 2048

//Estructura de la Gramatica
typedef struct gram{
    char noTerminales[MAX_NOTERMINALES];
    char terminales[MAX_TERMINALES];
    char producciones[MAX_PRODUCCIONES][LONGITUD_PRODUCCION];
    char axioma;
} gramatica;

// Retorna true si el axioma que nos pide ingresar se encuentra en el conjunto de NO terminales de la gramatica g
bool verificarAxioma(gramatica *g){
    char axioma;
    printf("Ingresa Axioma: ");
    scanf(" %c", &axioma);

    for (int i = 0; i < MAX_NOTERMINALES; i++){
        if (axioma == g->noTerminales[i]){
            printf("%s\n", "El axioma existe");
            g->axioma = axioma;
            return true;
        }
    }
    printf("%s\n", "El axioma NO existe.");
    return false;
}

// Retorna True si el valor ingresado es un NO Terminal de A-Z en ASCII
bool esNoTerminal(char posibleNoTerminal){
    return (posibleNoTerminal >= 'A' && posibleNoTerminal <= 'Z');
}

// Retorna True si el NO Terminal ingresado se encuentra dentro de la gramatica g
bool verificarNoTerminal(gramatica *g, char noTerminal){
    // Recorrer NO Terminales de la gramatica
    for (int i = 0; i < MAX_NOTERMINALES; i++){
        if (esNoTerminal(noTerminal) && noTerminal == g->noTerminales[i])
            return true;
    }
    return false;
}

// Retorna True si el valor ingresado es un Terminal de a-z en ASCII
bool esTerminal(char posibleTerminal){
    return (posibleTerminal >= 'a' && posibleTerminal <= 'z');
}

// Retorna True si el Terminal ingresado se encuentra dentro de la gramatica g
bool verificarTerminal(gramatica *g, char terminal){
    // Recorrer Terminales de la gramatica
    for (int i = 0; i < MAX_TERMINALES; i++){
        if (esTerminal(terminal) && terminal == g->terminales[i])
            return true;
    }
    return false;
}

//Ingresamos Terminales la gramatica g
void ingresarTerminales(gramatica *g){
    char terminal;
    int i = 0;

    while (i < MAX_TERMINALES){
        printf("Ingrese terminal #%i: ", i + 1);
        scanf(" %c", &terminal);

        // El usuario debe ingresar terminales no repetidos y caracteres validos
        if (!verificarTerminal(g, terminal) && esTerminal(terminal)){
            g->terminales[i] = terminal;
            i++;
        }else{
            printf("Caracter no valido (a-z). Intente nuevamente.\n");
        }
    }
    printf("Terminales ingresados:\n");
    for (int i = 0; i < MAX_TERMINALES; i++)
        printf("%c\n", g->terminales[i]);
}

//Ingresamos NO Terminales a la gramatica g
void ingresarNoTerminales(gramatica *g){
    char noterminal;
    int i = 0;

    while (i < MAX_NOTERMINALES){
        printf("Ingrese No Terminal #%i: ", i + 1);
        scanf(" %c", &noterminal);

        // El usuario debe ingresar NoTerminales no repetidos y caracteres validos
        if (!verificarNoTerminal(g, noterminal) && esNoTerminal(noterminal)){
            g->noTerminales[i] = noterminal;
            i++;
        }else {
            printf("Caracter no valido (A-Z). Intente nuevamente.\n");
        }
    }

    printf("No Terminales ingresados:\n");
    for (int i = 0; i < MAX_NOTERMINALES; i++){
        printf("%c\n", g->noTerminales[i]);
    }
}

bool esRegularPorIzquierda(gramatica *g, int fila, int columna) {
    //Si del lado derecho arranca por un NO Terminal, debe seguirle un terminal
   if (verificarNoTerminal(g, g->producciones[fila][columna])){
        if (verificarTerminal(g, g->producciones[fila][columna + 1])){
                return true;
        }
    }
    else if (verificarTerminal(g, g->producciones[fila][columna])){
        if(g->producciones[fila][columna + 1] == '\0'){
                return true;
        }
    }

    return false;
}

// verifica si la produccion en una fila de la tabla de producciones de la gramatica g es regular a derecha
bool esRegularPorDerecha(gramatica *g, int fila, int columna) {
    // si del lado derecho arranca por un Terminal
   if (verificarTerminal(g, g->producciones[fila][columna])){
        if (verificarNoTerminal(g, g->producciones[fila][columna + 1]) || g->producciones[fila][columna + 1] == '\0'){
            return true;
        }
    }

    return false;
}

// retorna true si se mantiene la misma linealidad en todas las producciones
bool verificarLinealidad(gramatica *g, int fila){
    //analizamos la columna 3 porque es donde arranca el lado derecho de la produccion
    int columna =3;
    if (esRegularPorDerecha(g,0,columna)){
        for(int i = fila ; i > 0  ; i--){
            if(!esRegularPorDerecha(g,i,columna)){
                return false;
            }
        }
    }
    else if(esRegularPorIzquierda(g,0,columna)){
        for(int i = fila ; i > 0  ; i--){
            if(!esRegularPorIzquierda(g,i,columna)){
                return false;
            }
        }
    }

    return true;
}

// retorna true si arranca por un NO Terminal y mantiene la misma linealidad con las demas producciones
bool verificarProduccion(gramatica *g, int fila){

    // El primer elemento (i=0) de la produccion debe ser un NoTerminal siempre
    if (!verificarNoTerminal(g, g->producciones[fila][0])){
        printf("Debe comenzar con un NoTerminal que pertenezca a la gramatica. Vuelva a ingresar.\n");
        return false;
    }

    if (g->producciones[fila][1] != '-' || g->producciones[fila][2] != '>'){
        printf("Esta mal puesta la flecha. Vuelva a ingresar.\n");
        return false;
    }

    if(!verificarNoTerminal(g, g->producciones[fila][3]) && !verificarTerminal(g, g->producciones[fila][3])){
        printf("Produccion invalida. Vuelva a ingresar.\n");
        return false;
    }

    if(verificarNoTerminal(g, g->producciones[fila][3]) && !verificarTerminal(g, g->producciones[fila][4])){
        printf("Produccion invalida. Vuelva a ingresar.\n");
        return false;
    }

    if(verificarTerminal(g, g->producciones[fila][3]) && verificarTerminal(g, g->producciones[fila][4])){
        printf("Produccion invalida. Vuelva a ingresar.\n");
        return false;
    }

    if(!verificarLinealidad(g, fila)){
        printf("No cumple la linealidad. Vuelva a ingresar.\n");
        return false;
    }

    return true;
}

//Ingresamos producciones la gramatica g
void ingresarProduccion(gramatica *g){
    printf("%s\n", "La primer produccion que ingrese debe ser de la forma X->xX o X->Xx, si lo hace de la forma X->x el programa entendera que la gramatica es regular a DERECHA, en cualquier otro caso le pedira que vuelva a ingresar la produccion \n");
    for (int fila = 0; fila < MAX_PRODUCCIONES; fila++){
        bool produccionValida = false;
        while (!produccionValida){
            printf("Ingrese la produccion entera: ");
            scanf("%s", g->producciones[fila]);

            // Verificamos que la produccion sea regular.
            if (verificarProduccion(g, fila))
                produccionValida = true;
        }
    }

    printf("Producciones ingresadas:\n");
    for (int fila = 0; fila < MAX_PRODUCCIONES; fila++){
        printf("Produccion %i: %s\n", fila + 1, g->producciones[fila]);
    }
}

// Devuelve el indice de una fila aleatoria que empieze por el NO terminal que le pasamos
int seleccionarAleatorio(gramatica *g, char noterminal){
    int indice[MAX_PRODUCCIONES];
    int cantidad = 0;

    for (int i = 0; i < MAX_PRODUCCIONES; i++){
        // Buscar posiciones de los noterminales para elegir
        if (g->producciones[i][0] == noterminal){
            indice[cantidad] = i;
            cantidad++;
        }
    }

    int randomIndice = rand() % cantidad;

    // Retorna fila aleatoria de la matriz producciones
    return indice[randomIndice];
}

// Genera una palabra del lenguaje que cumpla con la gramatica g
void derivacion(gramatica *g) {
    char cadenaDerivacion[MAX_CADENA];
    int longitudCadena = 1;

    //Comenzamos siempre por el Axioma
    cadenaDerivacion[0] = g->axioma;
    cadenaDerivacion[1] = '\0';
    printf("Cadena inicial: %c\n", cadenaDerivacion[0]);

    while (true) {
        bool derived = false;

        for (int i = 0; i < longitudCadena; i++) {
            //Verificamos que haya noTerminal
            if (verificarNoTerminal(g, cadenaDerivacion[i])) {

                //Elegir produccion random que tenga ese noTerminal
                int fila = seleccionarAleatorio(g, cadenaDerivacion[i]); //aca el seleccionar aleatoria no tendria que estar dentro del for para que no se itere siempre la misma opcion
                printf("Aplicando produccion: %s\n", g->producciones[fila]);

                char nuevaCadena[MAX_CADENA];
                int j = 0;
                
                //Este for copia la cadena de derivacion pero omite el NoTerminal actual
                for (int k = 0; k < i; k++) {
                    nuevaCadena[j++] = cadenaDerivacion[k];
                }

                for (int k = 3; g->producciones[fila][k] != '\0'; k++) {
                    //Tomar lado derecho de la produccion
                    nuevaCadena[j++] = g->producciones[fila][k];
                }

                //caracteres luego del no-terminal
                for (int k = i + 1; k < longitudCadena; k++) {
                    nuevaCadena[j++] = cadenaDerivacion[k];
                }
                nuevaCadena[j] = '\0';

                //Reemplazar caracteres
                strcpy(cadenaDerivacion, nuevaCadena);
                longitudCadena = strlen(cadenaDerivacion);
                printf("Cadena derivada: %s\n", cadenaDerivacion);

                derived = true;
                break;
            }
        }

        if (!derived) break;
    }

    printf("Cadena final derivada: %s\n", cadenaDerivacion);
}

void iniciarGramatica(gramatica *g){
    ingresarNoTerminales(g);
    ingresarTerminales(g);
    while (verificarAxioma(g) == false);
    ingresarProduccion(g);

   int flag = 1;
    do{
        derivacion(g);
        printf("\nPresione:\n1. Para derivar otra vez\n0. Salir\n");
        scanf("%d", &flag);
    } while (flag == 1);
}

int main(){
    srand(time(NULL));
    gramatica g = {{0}};
    iniciarGramatica(&g);
    return 0;
}
