%{
#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include "analizadorLexico.h"
#include "definiciones.h"
#include "TablaSimbolos/tablaSimbolos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Función alternativa a strdup */
char *my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup != NULL) {
        memcpy(dup, s, len);
    }
    return dup;
}

/* Puedes definir una macro para reemplazar strdup por my_strdup */
#define strdup my_strdup

extern char *yytext;
extern int yylex(void);

typedef struct {
    char *str;
} YYSTYPE;
YYSTYPE yylval;

int num_linea = 1;
%}


%option noyywrap

/* ---------------------- */
/* Definición de macros   */
/* ---------------------- */

/* Básicos */
DIGITO          [0-9]
LETRA           [a-zA-Z_]
ID              {LETRA}({LETRA}|{DIGITO})*

NONZERO         [1-9]
DECIMAL_DIGIT   {DIGITO}
DECIMAL_DIGITS  {DECIMAL_DIGIT}([_]{DECIMAL_DIGIT})*
decimal_lit     (0)|({NONZERO}(_?{DECIMAL_DIGITS})?)

BINARY_DIGIT    [01]
BINARY_DIGITS   {BINARY_DIGIT}([_]{BINARY_DIGIT})+
binary_lit      0[bB](_?{BINARY_DIGITS})

OCTAL_DIGIT     [0-7]
OCTAL_DIGITS    {OCTAL_DIGIT}([_]{OCTAL_DIGIT})+
octal_lit       0([oO])?(_?{OCTAL_DIGITS})

HEX_DIGIT       [0-9a-fA-F]
HEX_DIGITS      {HEX_DIGIT}([_]{HEX_DIGIT})+
hex_lit         0[xX](_?{HEX_DIGITS})

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


{binary_lit}      { yylval.str = strdup(yytext); return NUMERO; }
{hex_lit}         { yylval.str = strdup(yytext); return NUMERO; }
{octal_lit}       { yylval.str = strdup(yytext); return NUMERO; }
{decimal_lit}     { yylval.str = strdup(yytext); return NUMERO; }
{float_lit}       { yylval.str = strdup(yytext); return NUMERO; }
{imaginary_lit}   { yylval.str = strdup(yytext); return NUMERO; }
{string_lit}      { yylval.str = strdup(yytext); return STRING; }
{ID} {
    int simb = buscarElemento(yytext);
    yylval.str = strdup(yytext);
    return simb;
}

[ \t]+             ;
\n                 { num_linea++; }
.                  { return yytext[0]; }
<<EOF>>         {return FIN;}

%%

#undef yywrap
int yywrap(void) {
    return 1;
}

int siguienteComponenteLexico(token *t) {
    int tok = yylex();
    if (tok == 0)
        return 0;
    t->identificador = tok;
    t->lexema = strdup(yytext);
    return 1;
}
