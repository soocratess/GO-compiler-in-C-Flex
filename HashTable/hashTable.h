#ifndef hashTable_H
#define hashTable_H

// --------------------- ESTRUCTURAS --------------------- //

// Estructura para almacenar tokens
typedef struct token{
    int identificador;  // Código numérico del token
    char *lexema;       // Representación textual del token
    struct token *next; // Lista enlazada para gestionar colisiones
}token;

// Cada posición en la tabla apunta a la cabeza de una lista enlazada de tokens (doble puntero)
typedef token **hashTable;

// --------------------- FUNCIONES --------------------- //


/**
 * @brief Crea e inicializa una tabla de hash con un tamaño específico.
 * @param tabla Puntero a la tabla de hash.
 * @param tamanho Tamaño de la tabla de hash.
 * @return Código de éxito o error.
 */
int crearHashTable(hashTable *tabla, int tamanho);

/**
 * @brief Libera los recursos asociados con la tabla de hash.
 * @param tabla Puntero a la tabla de hash a destruir.
 * @return Código de éxito o error.
 */
int destruirHashTable(hashTable *tabla);

/**
 * @brief Ajusta el tamaño de la tabla de hash para optimizar el rendimiento.
 * @param tabla Puntero a la tabla de hash.
 * @param tamanho Nuevo tamaño de la tabla.
 * @return Código de éxito o error.
 */
int ajustarTamanhoHashTable(hashTable *tabla, int tamanho);

/**
 * @brief Inserta un token en la tabla de hash.
 * @param tabla Puntero a la tabla de hash.
 * @param lexema Lexema del token a insertar.
 * @param identificador Identificador del token.
 * @return Código de éxito o error.
 */
int insertarToken(hashTable *tabla, char *lexema, int identificador);

/**
 * @brief Elimina un token de la tabla de hash.
 * @param tabla Puntero a la tabla de hash.
 * @param lexema Lexema del token a eliminar.
 * @return Código de éxito o error.
 */
int eliminarToken(hashTable *tabla, char *lexema);

/**
 * @brief Busca un token en la tabla de hash.
 * @param tabla Tabla de hash.
 * @param lexema Lexema del token a buscar.
 * @return Identificador del token o error si no se encuentra.
 */
int buscarToken(hashTable tabla, char *lexema);

/**
 * @brief Modifica el identificador de un token en la tabla de hash.
 * @param tabla Puntero a la tabla de hash.
 * @param lexema Lexema del token a modificar.
 * @param identificador Nuevo identificador del token.
 * @return Código de éxito o error.
 */
int modificarToken(hashTable *tabla, char *lexema, int identificador);

/**
 * @brief Imprime el contenido de la tabla de hash para depuración.
 * @param tabla Tabla de hash a imprimir.
 */
void imprimirHashTable(hashTable tabla);

/**
 * @brief Devuelve la cantidad de elementos almacenados en la tabla de hash.
 * @return Número total de elementos en la tabla.
 */
int cantidadElementosHashTable();

/**
 * @brief Devuelve el tamaño actual de la tabla de hash.
 * @return Tamaño de la tabla de hash.
 */
int tamanhoHashTable();

#endif // hashTable_H