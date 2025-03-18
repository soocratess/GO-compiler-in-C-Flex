#include <stdio.h>
#include <stdlib.h>

#include "TablaSimbolos/tablaSimbolos.h"
#include "AnalizadorLexico/analizadorLexico.h"
#include "AnalizadorSintactico/analizadorSintactico.h"
#include "Error/error.h"

extern FILE *yyin;  /* Declaración externa para la variable de entrada del lexer */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No se ha proporcionado el archivo de entrada.\n");
        return EXIT_FAILURE;
    }

    /* Abre el archivo de entrada y lo asigna a yyin para que el lexer lo lea */
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    /* Inicializa y muestra la tabla de símbolos antes del análisis */
    crearTablaSimbolos();
    imprimirTablaSimbolos();

    /* Inicia el análisis léxico y sintáctico */
    iniciarAnalisis();

    /* Muestra la tabla de símbolos después del análisis */
    imprimirTablaSimbolos();

    /* Libera los recursos de la tabla de símbolos */
    destruirTablaSimbolos();

    fclose(yyin);
    return EXIT_SUCCESS;
}
