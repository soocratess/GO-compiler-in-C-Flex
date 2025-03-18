#include "analizadorSintactico.h"
#include "TablaSimbolos/definiciones.h"
#include <stdio.h>
#include <stdlib.h>

#include <AnalizadorLexico/analizadorLexico.h>

/**
 * Imprime un componente léxico en la consola.
 * Muestra el lexema y su identificador en formato tabular.
 * @param t Componente léxico a imprimir.
 */
void imprimirComponenteLexico(token t){
    printf("%-40s %-10d\n", t.lexema, t.identificador);
}

/**
 * Inicia el análisis léxico del código fuente.
 * Solicita e imprime componentes léxicos hasta alcanzar el fin del archivo.
 * Gestiona la liberación de memoria para los lexemas dinámicos.
 */
void iniciarAnalisis(){
    token t;

    printf("\n\n");
    printf("%-40s %-10s\n", "Lexema", "Identificador");
    printf("---------------------------------------- ----------\n");

    // Solicitamos componentes léxicos al analizador léxico hasta que reciba FIN.
    do {
        printf("---------------------------------------- ----------\n");

        // Se solicita el siguiente componente léxico.
        int liberarMemoria = siguienteComponenteLexico(&t);
        
        // Si no se ha llegado al final del fichero, se imprime el componente léxico.
        if (t.identificador != FIN) imprimirComponenteLexico(t);
        
        // Se libera la memoria del lexema si se ha solicitado.
        if (liberarMemoria) {free(t.lexema);}
    } while (t.identificador != FIN);

    printf("\n\n");
}