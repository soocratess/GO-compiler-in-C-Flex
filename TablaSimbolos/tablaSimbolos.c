#include "tablaSimbolos.h"
#include "definiciones.h"
#include "../HashTable/hashTable.h"
#include <stdio.h>


#define TAMANHO_INICIAL 64 // Añadimos espacio extra para minimizar cantidad de redimensiones

hashTable tabla = NULL;

/**
 * Crea e inicializa la tabla de símbolos del lenguaje.
 * Define las palabras reservadas y tipos de datos predefinidos.
 * Inserta estos tokens en una tabla hash para su rápida identificación.
 * @return 0 si la tabla se creó correctamente, -1 en caso de error.
 */
int crearTablaSimbolos(){

    // Palabras reservadas (keywords) del lenguaje y tipos de datos predefinidos
    char *keywords[TAMANHO_INICIAL] = {
        "break", "case", "chan", "const", "continue",
        "default", "defer", "else", "fallthrough", "for",
        "func", "go", "goto", "if", "import",
        "interface", "map", "package", "range", "return",
        "select", "struct", "switch", "type", "var",

        // Tipos de enteros sin signo
        "uint8", "uint16", "uint32", "uint64",

        // Tipos de enteros con signo
        "int8", "int16", "int32", "int64",

        // Tipos de punto flotante
        "float32", "float64",

        // Tipos de números complejos
        "complex64", "complex128",

        // Aliases de tipos
        "byte", "rune",

        // Tipos de enteros dependientes de la implementación
        "uint", "int", "uintptr",

        NULL
    };


    // Inicializamos la tabla de hash
    if (crearHashTable(&tabla, TAMANHO_INICIAL) == -1) {
        printf("Error al inicializar la tabla de hash\n");
        return -1;
    }

    // Insertamos las palabras reservadas en la tabla de hash
    for (int i = 0; keywords[i] != NULL; i++) {
        if (insertarToken(&tabla, keywords[i], i + 300) == -1) {
            printf("Error al insertar el token %s en la tabla de hash\n", keywords[i]);
        }
    }
    return 0;
}

/**
 * Libera los recursos asociados a la tabla de símbolos.
 * Llama a la función encargada de destruir la tabla hash.
 * @return Resultado de la operación de destrucción.
 */
int destruirTablaSimbolos(){
    return destruirHashTable(&tabla);
}

/**
 * Imprime el contenido de la tabla de símbolos.
 * Llama a la función encargada de recorrer e imprimir la tabla hash.
 */
void imprimirTablaSimbolos(){
    imprimirHashTable(tabla);
}

/**
 * Busca un lexema en la tabla de símbolos.
 * Si no se encuentra, lo inserta como un identificador (ID).
 * @param lexema Cadena de caracteres a buscar en la tabla.
 * @return Código asociado al lexema si existe, o ID si se inserta como nuevo.
 */
int buscarElemento(char *lexema){
    int busqueda = buscarToken(tabla, lexema);

    if (busqueda == -1) { // No se encontró el token
        insertarToken(&tabla, lexema,ID); // Insertamos el token como un identificador
        return ID;
    }
    return busqueda;
}


