#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

/**
 * @brief Crea e inicializa la tabla de símbolos.
 * @return Código de éxito o error.
 */
int crearTablaSimbolos();

/**
 * @brief Libera los recursos asociados con la tabla de símbolos.
 * @return Código de éxito o error.
 */
int destruirTablaSimbolos();

/**
 * @brief Imprime el contenido de la tabla de símbolos para depuración.
 */
void imprimirTablaSimbolos();

/**
 * @brief Busca un elemento en la tabla de símbolos por su lexema.
 * @param lexema Lexema del elemento a buscar.
 * @return Identificador del elemento encontrado o un error si no se encuentra.
 */
int buscarElemento(char *lexema);


#endif //TABLA_SIMBOLOS_H

