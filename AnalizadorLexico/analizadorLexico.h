#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include "definiciones.h"  /* Aquí se definen los tokens (BREAK, CASE, NUMERO, STRING, ID, etc.) */

typedef struct {
    char *lexema;
    int identificador;
} token;

/* Función generada por Flex */
int yylex(void);

/* Función auxiliar para el analizador sintáctico */
int siguienteComponenteLexico(token *t);

#endif /* ANALIZADOR_LEXICO_H */
