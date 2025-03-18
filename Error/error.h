
#ifndef ERROR_H
#define ERROR_H

/**
 * @file error.h
 * @brief Declaraciones de funciones para el manejo de errores en el análisis léxico y sintáctico.
 */

/**
 * Muestra un error cuando el lexema está en el buffer.
 */
void ERROR_LEXEMA_EN_BUFFER(); // SistemaEntrada

/**
 * Muestra un error por un carácter no reconocido.
 * @param caracter El carácter no reconocido.
 * @param linea La línea en la que ocurre el error.
 */
void ERROR_CARACTER_NO_RECONOCIDO(char caracter, int linea);

/**
 * Muestra un error cuando un guion bajo sigue a un punto en un número flotante.
 * @param linea La línea donde ocurre el error.
 */
void ERROR_GUION_BAJO_DESPUES_DE_PUNTO(int linea);

/**
 * Muestra un error por un número mal formado.
 * @param linea La línea donde ocurre el error.
 * @param lexema El número mal formado.
 */
void ERROR_NUMERO_MAL_FORMADO(int linea, const char *lexema);

/**
 * Muestra un error por un exponente inválido en un número flotante.
 * @param linea La línea donde ocurre el error.
 * @param lexema El número con exponente inválido.
 */
void ERROR_EXPONENTE_INVALIDO(int linea, const char *lexema);

/**
 * Muestra un error cuando se encuentra un estado no reconocido en el autómata.
 * @param linea La línea donde ocurre el error.
 * @param estado El estado no reconocido.
 */
void ERROR_ESTADO_NO_RECONOCIDO(int linea, int estado);

/**
 * Muestra un error por un comentario de bloque no cerrado.
 * @param linea La línea donde ocurre el error.
 */
void ERROR_COMENTARIO_NO_CERRADO(int linea);

/**
 * Muestra un error cuando un identificador es demasiado largo.
 * @param lexema El identificador demasiado largo.
 * @param linea La línea donde ocurre el error.
 */
void ERROR_IDENTIFICADOR_MUY_LARGO(const char *lexema, int linea);

/**
 * Muestra un error por una cadena de texto no cerrada.
 * @param linea La línea donde ocurre el error.
 */
void ERROR_STRING_NO_CERRADO(int linea);


#endif //ERROR_H
