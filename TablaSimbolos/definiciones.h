#ifndef DEFINICIONES_H
#define DEFINICIONES_H

// Palabras clave de Go (asignadas desde 300 en adelante)
#define BREAK        300
#define CASE         301
#define CHAN         302
#define CONST        303
#define CONTINUE     304
#define DEFAULT      305
#define DEFER        306
#define ELSE         307
#define FALLTHROUGH  308
#define FOR          309
#define FUNC         310
#define GO           311
#define GOTO         312
#define IF           313
#define IMPORT       314
#define INTERFACE    315
#define MAP          316
#define PACKAGE      317
#define RANGE        318
#define RETURN       319
#define SELECT       320
#define STRUCT       321
#define SWITCH       322
#define TYPE         323
#define VAR          324

// Tipos de enteros sin signo
#define UINT8        325
#define UINT16       326
#define UINT32       327
#define UINT64       328

// Tipos de enteros con signo
#define INT8         329
#define INT16        330
#define INT32        331
#define INT64        332

// Tipos de punto flotante
#define FLOAT32      333
#define FLOAT64      334

// Tipos de números complejos
#define COMPLEX64    335
#define COMPLEX128   336

// Aliases de tipos
#define BYTE         337
#define RUNE         338

// Tipos de enteros dependientes de la implementación
#define UINT         339
#define INT          340
#define UINTPTR      341

// Otros tokens léxicos
#define ID           342  // Identificadores (nombres de variables, funciones, etc.)
#define NUMERO       343  // Números enteros y flotantes
#define STRING       344  // Cadenas de texto
#define OPERADOR     345  // Operadores (+, -, *, /, etc.)
#define DELIMITADOR  346  // Delimitadores como {}, (), [], ;
#define COMENTARIO   347  // Comentarios (// y /* ... */)
#define FIN          EOF  // Fin del archivo

#endif // DEFINICIONES_H
