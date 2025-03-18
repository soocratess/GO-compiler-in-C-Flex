#include "hashTable.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// --------------------- CONSTANTES Y VARIABLES --------------------- //

#define primoFuncionHash 33 // Número primo recomendado

#define ERROR_GENERAL -1
#define EXITO 0


int TAMANHO_TABLA;
int NUMERO_ELEMENTOS;

// --------------------- FUNCIONES PRIVADAS --------------------- //
/**
 * Calcula el valor hash de una cadena utilizando el algoritmo DJB2 modificado.
 * Emplea una combinación de multiplicación y XOR para distribuir los valores.
 * @param string Cadena de caracteres a procesar.
 * @return Valor hash ajustado al tamaño de la tabla hash.
 */
unsigned int hash(char *string) {
    if (!string) return 0;  // Manejo de NULL

    unsigned int hash = 5381;  // Mejor valor inicial (DJB2)

    // Guardar la longitud antes del bucle para evitar múltiples llamadas a strlen()
    size_t len = strlen(string);
    for (size_t i = 0; i < len; i++) {
        hash = (hash * primoFuncionHash) ^ string[i];  // Multiplicación + XOR
    }

    return hash % TAMANHO_TABLA;  // Ajuste al tamaño de la tabla hash
}

/**
 * Duplica una cadena de caracteres asignando memoria dinámica.
 * @param s Cadena original a duplicar.
 * @return Puntero a la nueva cadena duplicada, o NULL si falla la asignación.
 */
char *_my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup) {
        memcpy(dup, s, len);
    }
    return dup;
}
// --------------------- FUNCIONES PÚBLICAS --------------------- //

/**
 * Crea e inicializa una tabla de hash con tamaño dinámico.
 * Reserva memoria para la estructura y establece los valores iniciales.
 * @param tabla Puntero a la tabla de hash a inicializar.
 * @param size Tamaño inicial de la tabla de hash.
 * @return Código de éxito o error en caso de fallo en la asignación de memoria.
 */
int crearHashTable(hashTable *tabla, int size){

    *tabla = (token **) malloc (sizeof(token*) * size);

    if (*tabla == NULL) {
        perror("Fallo a la hora de asignar memoria para la tabla de hash\n");
        return ERROR_GENERAL;
    }

    for (int i = 0; i < size; i++){
        (*tabla)[i] = NULL;
    }

    TAMANHO_TABLA = size;
    NUMERO_ELEMENTOS = 0;

    return EXITO;
}



/**
 * Libera los recursos asociados con la tabla de hash.
 * Recorre la tabla y libera cada token almacenado, incluyendo su lista enlazada.
 * @param tabla Puntero a la tabla de hash a destruir.
 * @return Código de éxito o error si la tabla no existe.
 */
int destruirHashTable(hashTable *tabla){

    if(tabla == NULL){
        printf("ERROR: La tabla no existe\n");
        return ERROR_GENERAL;
    }
    for (int i = 0; i < TAMANHO_TABLA; i++) {
        if ((*tabla)[i] != NULL) {

            // Para cada elemento de la tabla hay una lista enlazada de tokens
            token *actual = (*tabla)[i];

            while (actual != NULL) {
                token *siguiente = actual->next;

                free(actual->lexema); // Libera el lexema del token

                free(actual); // Libera el token

                actual = siguiente;

            }
        }
    }

    free(*tabla);
    *tabla = NULL;

    return EXITO;
}

/**
 * Ajusta el tamaño de la tabla de hash para mantener un rendimiento óptimo.
 * Crea una nueva tabla con el tamaño especificado y reubica los elementos existentes.
 * @param tabla Puntero a la tabla de hash a redimensionar.
 * @param newSize Nuevo tamaño de la tabla de hash.
 * @return Código de éxito o error si falla la asignación de memoria.
 */
int ajustarTamanhoHashTable(hashTable *tabla, int newSize) {

    // Paso 1: Crear una nueva tabla de hash del nuevo tamaño que sera nuestra nueva tabla

    hashTable nuevaTabla = malloc (sizeof(token *) * newSize);

    if (nuevaTabla == NULL) {
        printf("ERROR: Fallo al asignar nueva tabla de hash\n");
        return ERROR_GENERAL;
    }

    for (int i = 0; i < newSize; i++) {
        nuevaTabla[i] = NULL;
    }

    // Paso 2: Rehashear e insertar cada token de la tabla antigua en la nueva tabla

    int oldSize = TAMANHO_TABLA;
    TAMANHO_TABLA = newSize;

    for (int i = 0; i < oldSize; i++) {

        token *actual = (*tabla)[i];

        while (actual != NULL) {
            // Guarda el próximo token antes de modificar el actual
            token *siguiente = actual->next;

            // Calcula el nuevo índice para el token actual basado en el nuevo tamaño de tabla
            int nuevoIndice = hash(actual->lexema);

            // Inserta el token en la nueva tabla (al principio de la lista en ese índice)
            actual->next = nuevaTabla[nuevoIndice];
            nuevaTabla[nuevoIndice] = actual;

            // Avanza al siguiente token en la lista original
            actual = siguiente;
        }
    }

    // No se liberan los elementos, solo la tabla antigua
    free(*tabla);

    *tabla = nuevaTabla;
    TAMANHO_TABLA = newSize;

    return EXITO;
}

/**
 * Imprime el contenido actual de la tabla de hash para depuración.
 * Recorre cada índice de la tabla e imprime los tokens almacenados en listas enlazadas.
 * @param tabla Tabla de hash a imprimir.
 */
void imprimirHashTable(hashTable tabla) {
    printf("\nSTART\n");


    for (int index = 0; index < TAMANHO_TABLA; index++) {
        printf("%d\t", index);
        if (tabla[index] == NULL) {
            printf("---\n"); // Indica que no hay token en esta posición
        }

        else {
            // Recorre la lista enlazada en esta posición de la tabla
            token *actual = tabla[index];
            while (actual != NULL) {
                printf("( %s | %d ) -> ", actual->lexema, actual->identificador);
                actual = actual->next;
            }
            printf("\n");
        }
    }

    printf("END\n");
}

/**
 * Inserta un nuevo token en la tabla de hash.
 * Usa encadenamiento para manejar colisiones y redimensiona la tabla si es necesario.
 * @param tabla Puntero a la tabla de hash donde se insertará el token.
 * @param lexema Cadena de caracteres que representa el lexema del token.
 * @param identificador Identificador asociado al lexema.
 * @return Código de éxito o error si falla la asignación de memoria.
 */
int insertarToken(hashTable *tabla, char *lexema, int identificador){

    if (tabla == NULL) return ERROR_GENERAL;

    int index = hash(lexema);

    token *nuevoToken = (token *) malloc (sizeof(token));

    if (nuevoToken == NULL) return ERROR_GENERAL;

    // Implementamos el encadenamiento en tablas hash (mas eficiente) debido a las restricciones
    // del sistema
    nuevoToken->lexema = _my_strdup(lexema);
    nuevoToken->identificador = identificador;
    nuevoToken->next = NULL;

    // Si hay colisión, insertamos el nuevo token al principio de la lista enlazada
    if ((*tabla)[index] == NULL) {
        (*tabla)[index] = nuevoToken;
    } else {
        nuevoToken->next = (*tabla)[index];
        (*tabla)[index] = nuevoToken;
    }

    NUMERO_ELEMENTOS++;

    // Redimensionamos la tabla si el factor de carga supera 0.75
    if(NUMERO_ELEMENTOS/TAMANHO_TABLA > 0.75){
        ajustarTamanhoHashTable(tabla, TAMANHO_TABLA * 2);
    }

    return EXITO;
}

/**
 * Busca un token en la tabla de hash por su lexema.
 * Si el token existe, devuelve su identificador; en caso contrario, retorna un código de error.
 * @param tabla Tabla de hash en la que se buscará el lexema.
 * @param lexema Cadena de caracteres a buscar.
 * @return Identificador del token si se encuentra, o un código de error si no existe.
 */
int buscarToken(hashTable tabla, char *lexema) {

    int index = hash(lexema);

    token *actual = tabla[index];

    // Recorremos la lista enlazada en la posición de la tabla
    while (actual != NULL) {
        if (strcmp(actual->lexema, lexema) == 0) {
            return actual->identificador;
        }

        actual = actual->next;
    }

    return ERROR_GENERAL;
}

/**
 * Elimina un token de la tabla de hash si existe.
 * Ajusta la lista enlazada en caso de colisión y libera la memoria del token.
 * @param tabla Puntero a la tabla de hash.
 * @param lexema Cadena de caracteres que representa el token a eliminar.
 * @return Código de éxito si se elimina correctamente, o un código de error si no se encuentra.
 */
int eliminarToken(hashTable *tabla, char *lexema) {

    int index = hash(lexema);

    token *actual = (*tabla)[index];
    token *anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->lexema, lexema) == 0) {
            if (anterior == NULL) {
                (*tabla)[index] = actual->next;
            } else {
                anterior->next = actual->next;
            }

            free(actual->lexema);
            free(actual);

            return ERROR_GENERAL;
        }

        anterior = actual;
        actual = actual->next;
    }

    return EXITO;
}

/**
 * Modifica el identificador de un token existente en la tabla de hash.
 * Elimina el token previo e inserta uno nuevo con el identificador actualizado.
 * @param tabla Puntero a la tabla de hash.
 * @param lexema Cadena de caracteres que representa el token a modificar.
 * @param identificador Nuevo identificador a asignar.
 * @return Código de éxito si la operación se realiza correctamente, o un código de error si el token no existe.
 */
int modificarToken(hashTable *tabla, char * lexema, int identificador){

    int identificadorAux = buscarToken(*tabla, lexema);

    if(identificadorAux == 0) return ERROR_GENERAL;
    else {

        eliminarToken(tabla, lexema);

        insertarToken(tabla, lexema, identificador);
        
        return EXITO;
    } 
}

/**
 * Devuelve la cantidad actual de elementos almacenados en la tabla de hash.
 * @return Número total de elementos en la tabla.
 */
int cantidadElementosHashTable() {
    return NUMERO_ELEMENTOS;
}

/**
 * Devuelve el tamaño actual de la tabla de hash.
 * @return Tamaño total de la tabla de hash.
 */
int tamanhoHashTable() {
    return TAMANHO_TABLA;
}