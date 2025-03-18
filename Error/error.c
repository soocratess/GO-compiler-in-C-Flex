#include <stdio.h>

#define RED "\033[1;31m"
#define RESET "\033[0m"

/**
 * Muestra un error cuando se encuentra un carácter no reconocido en el análisis léxico.
 * @param caracter Carácter no reconocido.
 * @param linea Número de línea donde ocurre el error.
 */
void ERROR_CARACTER_NO_RECONOCIDO(char caracter, int linea) {
    printf(RED "Error línea %i: Caracter no reconocido '%c'.\n" RESET, linea, caracter);
}

/**
 * Muestra un error cuando un guion bajo ('_') sigue a un punto en un número flotante.
 * @param linea Número de línea donde ocurre el error.
 */
void ERROR_GUION_BAJO_DESPUES_DE_PUNTO(int linea) {
    printf(RED "Error línea %i: Un '_' no puede seguir a un '.' en un número flotante.\n" RESET, linea);
}

/**
 * Muestra un error cuando se encuentra un número mal formado en el análisis léxico.
 * @param linea Número de línea donde ocurre el error.
 * @param lexema Representación del número mal formado.
 */
void ERROR_NUMERO_MAL_FORMADO(int linea, const char *lexema) {
    printf(RED "Error línea %i: Número mal formado '%s'.\n" RESET, linea, lexema);
}

/**
 * Muestra un error cuando el exponente de un número flotante es inválido.
 * @param linea Número de línea donde ocurre el error.
 * @param lexema Número con exponente mal formado.
 */
void ERROR_EXPONENTE_INVALIDO(int linea, const char *lexema) {
    printf(RED "Error línea %i: Exponente mal formado en número '%s'.\n" RESET, linea, lexema);
}

/**
 * Muestra un error cuando se encuentra un estado no reconocido en el autómata de números.
 * @param linea Número de línea donde ocurre el error.
 * @param estado Estado inválido del autómata.
 */
void ERROR_ESTADO_NO_RECONOCIDO(int linea, int estado) {
    printf(RED "Error línea %i: Estado no reconocido en autómata de números: %d.\n" RESET, linea, estado);
}

/**
 * Muestra un error cuando un comentario de bloque no ha sido cerrado correctamente.
 * @param linea Número de línea donde ocurre el error.
 */
void ERROR_COMENTARIO_NO_CERRADO(int linea) {
    printf(RED "Error línea %i: Comentario de bloque no cerrado.\n" RESET, linea);
}

/**
 * Muestra un error cuando un identificador supera el límite de longitud permitido.
 * @param lexema Identificador demasiado largo.
 * @param linea Número de línea donde ocurre el error.
 */
void ERROR_IDENTIFICADOR_MUY_LARGO(const char *lexema, int linea) {
    printf(RED "Error línea %i: Identificador demasiado largo '%s'.\n" RESET, linea, lexema);
}

/**
 * Muestra un error cuando una cadena de texto no ha sido cerrada correctamente.
 * @param linea Número de línea donde ocurre el error.
 */
void ERROR_STRING_NO_CERRADO(int linea) {
    printf(RED "Error línea %i: Cadena de texto no cerrada.\n" RESET, linea);
}
