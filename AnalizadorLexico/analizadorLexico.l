%{
#include "analizadorLexico.h"  /* Incluye la definición de token y las declaraciones necesarias */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* Literales enteros (números) */
/* Decimal:
   decimal_lit = "0" | ( "1" … "9" ) [ [ "_" ] decimal_digits ]
   decimal_digits = decimal_digit { [ "_" ] decimal_digit } */
NONZERO         [1-9]
DECIMAL_DIGIT   {DIGITO}
DECIMAL_DIGITS  {DECIMAL_DIGIT}([_]{DECIMAL_DIGIT})*
decimal_lit     (0)|({NONZERO}(_?{DECIMAL_DIGITS})?)

/* Binary:
   binary_lit = "0" ( "b" | "B" ) [ "_" ] binary_digits */
BINARY_DIGIT    [01]
BINARY_DIGITS   {BINARY_DIGIT}([_]{BINARY_DIGIT})+
binary_lit      0[bB](_?{BINARY_DIGITS})

/* Octal:
   octal_lit = "0" [ "o" | "O" ] [ "_" ] octal_digits */
OCTAL_DIGIT     [0-7]
OCTAL_DIGITS    {OCTAL_DIGIT}([_]{OCTAL_DIGIT})+
octal_lit       0([oO])?(_?{OCTAL_DIGITS})

/* Hexadecimal:
   hex_lit = "0" ( "x" | "X" ) [ "_" ] hex_digits */
HEX_DIGIT       [0-9a-fA-F]
HEX_DIGITS      {HEX_DIGIT}([_]{HEX_DIGIT})+
hex_lit         0[xX](_?{HEX_DIGITS})

/* Literales flotantes */
/* Para exponentes decimales: */
DECIMAL_EXPONENT    ([eE][+\-]?{DECIMAL_DIGITS})
/* decimal_float_lit puede ser:
      1. {DECIMAL_DIGITS} "." [ {DECIMAL_DIGITS} ] [ DECIMAL_EXPONENT ]
   o  2. {DECIMAL_DIGITS} DECIMAL_EXPONENT
   o  3. "." {DECIMAL_DIGITS} [ DECIMAL_EXPONENT ] */
decimal_float_lit   (\
                         ({DECIMAL_DIGITS}"."({DECIMAL_DIGITS})?({DECIMAL_EXPONENT})?) \
                         |({DECIMAL_DIGITS}{DECIMAL_EXPONENT}) \
                         |("."{DECIMAL_DIGITS}({DECIMAL_EXPONENT})?)\
                        )
/* Para exponentes hexadecimales: */
HEX_EXPONENT        ([pP][+\-]?{DECIMAL_DIGITS})
/* hex_mantissa puede ser:
      1. [ "_" ] {HEX_DIGITS} "." [ {HEX_DIGITS} ]
   o  2. [ "_" ] {HEX_DIGITS}
   o  3. "." {HEX_DIGITS} */
hex_mantissa        (\
                         (_?{HEX_DIGITS}"."({HEX_DIGITS})?) \
                         |(_?{HEX_DIGITS}) \
                         |("."{HEX_DIGITS})\
                        )
/* hex_float_lit = "0" ( "x" | "X" ) hex_mantissa hex_exponent */
hex_float_lit       0[xX]{hex_mantissa}{HEX_EXPONENT}

/* El literal flotante completo es la unión de decimal y hexadecimal */
float_lit           ({decimal_float_lit}|{hex_float_lit})

/* Literales imaginarios */
/* imaginary_lit = (decimal_digits | int_lit | float_lit) "i" */
imaginary_lit  (({DECIMAL_DIGITS})|({decimal_lit})|({float_lit}))"i"

/* Literales de cadenas */
/* Interpreted string literal:
   interpreted_string_lit = "\"" { unicode_value | byte_value } "\"" */
interpreted_string_lit   \"([^\\"]|\\.)*\"
/* Raw string literal:
   raw_string_lit = "`" { unicode_char | newline } "`" */
raw_string_char  [^`]
raw_string_lit   \`({raw_string_char}|\n)*\/
/* Combinación de ambas */
string_lit       ({raw_string_lit}|{interpreted_string_lit})

/* ---------------------------------------------------------------- */
/* Fin de definición de macros */
/* ---------------------------------------------------------------- */

%%
/* -------------------------------------------------- */
/* 1. Palabras clave de Go, según definiciones.h      */
/* Estas reglas deben ir antes de la regla de {ID}      */
/* -------------------------------------------------- */
"break"          { return BREAK; }
"case"           { return CASE; }
"chan"           { return CHAN; }
"const"          { return CONST; }
"continue"       { return CONTINUE; }
"default"        { return DEFAULT; }
"defer"          { return DEFER; }
"else"           { return ELSE; }
"fallthrough"    { return FALLTHROUGH; }
"for"            { return FOR; }
"func"           { return FUNC; }
"go"             { return GO; }
"goto"           { return GOTO; }
"if"             { return IF; }
"import"         { return IMPORT; }
"interface"      { return INTERFACE; }
"map"            { return MAP; }
"package"        { return PACKAGE; }
"range"          { return RANGE; }
"return"         { return RETURN; }
"select"         { return SELECT; }
"struct"         { return STRUCT; }
"switch"         { return SWITCH; }
"type"           { return TYPE; }
"var"            { return VAR; }

/* -------------------------------------------------- */
/* 2. Literales numéricos                             */
/* -------------------------------------------------- */
/* Es importante colocar primero las reglas con prefijo para evitar solapamientos */
{binary_lit}      { yylval.str = strdup(yytext); return NUMERO; }
{hex_lit}         { yylval.str = strdup(yytext); return NUMERO; }
{octal_lit}       { yylval.str = strdup(yytext); return NUMERO; }
{decimal_lit}     { yylval.str = strdup(yytext); return NUMERO; }
{float_lit}       { yylval.str = strdup(yytext); return NUMERO; }
{imaginary_lit}   { yylval.str = strdup(yytext); return NUMERO; }

/* -------------------------------------------------- */
/* 3. Literales de cadenas                           */
/* -------------------------------------------------- */
{string_lit}      { yylval.str = strdup(yytext); return STRING; }

/* -------------------------------------------------- */
/* 4. Identificadores                                */
/* -------------------------------------------------- */
{ID}              { yylval.str = strdup(yytext); return ID; }

/* -------------------------------------------------- */
/* 5. Manejo de espacios y saltos de línea           */
/* -------------------------------------------------- */
[ \t]+             ;  /* Ignorar espacios y tabulaciones */
\n                 { num_linea++; }

/* -------------------------------------------------- */
/* 6. Cualquier otro carácter                         */
/* -------------------------------------------------- */
.                  { return yytext[0]; }
%%
/* Sección de código C adicional (después de las reglas) */
int yywrap(void) {
    return 1;
}

/* Función auxiliar para el analizador sintáctico */
int siguienteComponenteLexico(token *t) {
    int tok = yylex();
    if (tok == 0) {
        return 0;
    }
    t->identificador = tok;
    t->lexema = strdup(yytext);
    return 1;
}
