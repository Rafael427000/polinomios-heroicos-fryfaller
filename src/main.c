#include "polinomio.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("--- PROYECTO POLINOMIOS: TAD LISTA DOBLEMENTE LIGADA ---\n");
    printf("Facultad de Ingenieria - UNAM\n\n");

    // 1. Creacion de polinomios
    Polinomio* p1 = crearPolinomio();
    Polinomio* p2 = crearPolinomio();

    // 2. Insercion de terminos (segun ejemplos de la practica)
    // P1 = 3x^2 + 2x + 1
    insertarTermino(p1, 3, 2);
    insertarTermino(p1, 2, 1);
    insertarTermino(p1, 1, 0);

    // P2 = x^2 + 4
    insertarTermino(p2, 1, 2);
    insertarTermino(p2, 4, 0);

    printf("P1: %s\n", polinomioToString(p1));
    printf("P2: %s\n", polinomioToString(p2));

    // 3. Suma
    Polinomio* pSuma = sumarPolinomios(p1, p2);
    char* resSuma = polinomioToString(pSuma);
    printf("Suma (P1 + P2): %s\n", resSuma);
    free(resSuma);

    // 4. Multiplicacion
    Polinomio* pMult = multiplicarPolinomios(p1, p2);
    char* resMult = polinomioToString(pMult);
    printf("Multiplicacion (P1 * P2): %s\n", resMult);
    free(resMult);

    // 5. Evaluacion
    float x = 2.0;
    printf("Evaluacion de P1 cuando x = %.1f: %.2f\n", x, evaluarPolinomio(p1, x));

    // 6. Limpieza de memoria
    destruirPolinomio(p1);
    destruirPolinomio(p2);
    destruirPolinomio(pSuma);
    destruirPolinomio(pMult);

    printf("\nEjecucion terminada exitosamente.\n");
    return 0;
}
