#include <stdio.h>
#include "polinomio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Termino {
    float coeficiente;
    int exponente;
} Term;

typedef struct Nodo {
    Term termino;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* cabeza;
    Nodo* cola;
} Polinomio;
