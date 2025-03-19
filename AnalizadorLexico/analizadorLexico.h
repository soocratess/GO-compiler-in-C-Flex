#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include "TablaSimbolos/definiciones.h"  /* Aquí se definen los tokens (BREAK, CASE, NUMERO, STRING, ID, etc.) */
#include "HashTable/hashTable.h"         /* Aquí se define la tabla de símbolos */

/* Función generada por Flex */
int yylex(void);

/* Función auxiliar para el analizador sintáctico */
int siguienteComponenteLexico(token *t);

/* Funciones auxiliares para el manejo de archivos */
void abrirArchivo(char *nombreArchivo);
void cerrarArchivo();


#endif /* ANALIZADOR_LEXICO_H */
