#include <stdio.h>
#include <stdlib.h>

#include "TablaSimbolos/tablaSimbolos.h"
#include "AnalizadorLexico/analizadorLexico.h"
#include "AnalizadorSintactico/analizadorSintactico.h"
#include "SistemaEntrada/sistemaEntrada.h"
#include "Error/error.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Verifica si se ha pasado el archivo como argumento
        fprintf(stderr, "Error: No se ha proporcionado el archivo de entrada.\n");
        return EXIT_FAILURE;
    }

    // Obtiene el nombre del archivo desde el primer argumento
    char *archivoEntrada = argv[1];

    // Crea el sistema de entrada usando el archivo proporcionado
    crearSistemaEntrada(archivoEntrada);
    crearTablaSimbolos();
    imprimirTablaSimbolos();

    // Inicia el análisis léxico y sintáctico
    iniciarAnalisis();

    // Imprime la tabla de símbolos después del análisis
    imprimirTablaSimbolos();
    
    // Libera los recursos
    destruirTablaSimbolos();
    destruirSistemaEntrada();

    return EXIT_SUCCESS;
}
