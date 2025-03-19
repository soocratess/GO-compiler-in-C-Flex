%{
/* ------------------ */
/*   Funciones en C   */
/* ------------------ */

#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include "analizadorLexico.h"
#include "definiciones.h"
#include "TablaSimbolos/tablaSimbolos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *yytext;
extern int yylex(void);

typedef struct {
    char *str;
} YYSTYPE;
YYSTYPE yylval;

int num_linea = 1;
%}
/* ------------------------ */
/*  Definición de patrones  */
/* ------------------------ */

%option noyywrap

/* Básicos */
DIGITO          [0-9]
LETRA           [a-zA-Z_]
ID              {LETRA}({LETRA}|{DIGITO})*

NONZERO         [1-9]
DECIMAL_DIGIT   {DIGITO}
DECIMAL_DIGITS  {DECIMAL_DIGIT}+([_]{DECIMAL_DIGIT}+)*
decimal_lit     (0)|({NONZERO}(_?{DECIMAL_DIGITS})?)

BINARY_DIGIT    [01]
BINARY_DIGITS   {BINARY_DIGIT}+([_]{BINARY_DIGIT}+)*
binary_lit      0[bB]{BINARY_DIGITS}

OCTAL_DIGIT     [0-7]
OCTAL_DIGITS    {OCTAL_DIGIT}+([_]{OCTAL_DIGIT}+)*
octal_lit       0([oO])?{OCTAL_DIGITS}

HEX_DIGIT       [0-9a-fA-F]
HEX_DIGITS      {HEX_DIGIT}+([_]{HEX_DIGIT}+)*
hex_lit         0[xX]{HEX_DIGITS}

DECIMAL_EXPONENT    ([eE][+\-]?{DECIMAL_DIGITS})
decimal_float_lit   (({DECIMAL_DIGITS}"."({DECIMAL_DIGITS})?({DECIMAL_EXPONENT})?)|({DECIMAL_DIGITS}{DECIMAL_EXPONENT})|("."{DECIMAL_DIGITS}({DECIMAL_EXPONENT})?))
HEX_EXPONENT        ([pP][+\-]?{DECIMAL_DIGITS})
hex_mantissa        ((_?{HEX_DIGITS}"."({HEX_DIGITS})?)|(_?{HEX_DIGITS})|("."{HEX_DIGITS}))
hex_float_lit       0[xX]{hex_mantissa}{HEX_EXPONENT}
float_lit           ({decimal_float_lit}|{hex_float_lit})

imaginary_lit  (({DECIMAL_DIGITS})|({decimal_lit})|({float_lit}))"i"

BACKTICK       "`"
interpreted_string_lit   \"([^\\"]|\\.)*\"
raw_string_lit           {BACKTICK}([^`]|\n)*{BACKTICK}
string_lit               ({raw_string_lit}|{interpreted_string_lit})

%%

"//".*             { /* Comentario de línea: se ignora */ }
"/*"([^*]|\*+[^*/])*\*+"/" {
    int i, nl = 0;
    for (i = 0; i < yyleng; i++) {
         if (yytext[i] == '\n') nl++;
    }
    num_linea += nl;
    /* No se retorna token; se ignora el comentario */
}

"+="        { return OPERADOR; }
"&="        { return OPERADOR; }
"&&"        { return OPERADOR; }
"=="        { return OPERADOR; }
"!="        { return OPERADOR; }
"+"         { return yytext[0]; }
"&"         { return yytext[0]; }
"("         { return yytext[0]; }
")"         { return yytext[0]; }
"-="        { return OPERADOR; }
"|="        { return OPERADOR; }
"||"        { return OPERADOR; }
"<="        { return OPERADOR; }
"-"         { return yytext[0]; }
"|"         { return yytext[0]; }
"<"         { return yytext[0]; }
"["         { return yytext[0]; }
"*="        { return OPERADOR; }
"^="        { return OPERADOR; }
"<-"        { return OPERADOR; }
">="        { return OPERADOR; }
"*"         { return yytext[0]; }
"^"         { return yytext[0]; }
">"         { return yytext[0]; }
"{"         { return yytext[0]; }
"<<"        { return OPERADOR; }
"/="        { return OPERADOR; }
"<<="       { return OPERADOR; }
"++"        { return OPERADOR; }
":="        { return OPERADOR; }
"/"         { return yytext[0]; }
"="         { return yytext[0]; }
","         { return yytext[0]; }
";"         { return yytext[0]; }
">>"        { return OPERADOR; }
"%="        { return OPERADOR; }
">>="       { return OPERADOR; }
"--"        { return OPERADOR; }
"..."       { return OPERADOR; }
"!"         { return yytext[0]; }
"."         { return yytext[0]; }
":"         { return yytext[0]; }
"%"         { return yytext[0]; }
"&^="       { return OPERADOR; }
"&^"        { return OPERADOR; }
"~"         { return yytext[0]; }


{binary_lit}      { return NUMERO; }
{hex_lit}         { return NUMERO; }
{octal_lit}       { return NUMERO; }
{decimal_lit}     { return NUMERO; }
{float_lit}       { return NUMERO; }
{imaginary_lit}   { return NUMERO; }
{string_lit}      { return STRING; }
{ID} { int simb = buscarElemento(yytext); return simb; }

[ \t]+             ;
\n                 { num_linea++; }
.                  { return yytext[0]; }
<<EOF>>         {return FIN;}

%%

/* ------------------ */
/*   Funciones en C   */
/* ------------------ */

#undef yywrap
int yywrap(void) {
    return 1;
}

/* Función para obtener el siguiente componente léxico */
int siguienteComponenteLexico(token *t) {
    int tok = yylex();
    if (tok == 0)
        return 0;
    t->identificador = tok;
    t->lexema = strdup(yytext);
    return 1;
}

/* Función para cargar un archivo */
void abrirArchivo(char *nombreArchivo) {
        yyin = fopen(nombreArchivo, "r");
    if (yyin == NULL) {
        perror("fopen");
        exit(1);
    }
}

/* Función para cerrar un archivo */
void cerrarArchivo() {
    if (yyin != NULL) {
        fclose(yyin); 
        yyin = NULL; 
    }
    yylex_destroy();
}
