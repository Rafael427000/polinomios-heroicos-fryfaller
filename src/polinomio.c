#include "polinomio.h"

Nodo* crearNodo(float coef, int exp) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo) {
        nuevo->termino.coeficiente = coef;
        nuevo->termino.exponente = exp;
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
    }
    return nuevo;
}

void insertarNodoOrdenado(Polinomio* p, Nodo* nuevo) {
    if (!p->cabeza) {
        p->cabeza = p->cola = nuevo;
        return;
    }
    Nodo* actual = p->cabeza;
    while (actual && actual->termino.exponente > nuevo->termino.exponente) {
        actual = actual->siguiente;
    }
    if (!actual) {
        nuevo->anterior = p->cola;
        p->cola->siguiente = nuevo;
        p->cola = nuevo;
    } else if (actual == p->cabeza) {
        nuevo->siguiente = p->cabeza;
        p->cabeza->anterior = nuevo;
        p->cabeza = nuevo;
    } else {
        nuevo->siguiente = actual;
        nuevo->anterior = actual->anterior;
        actual->anterior->siguiente = nuevo;
        actual->anterior = nuevo;
    }
}

void eliminarNodo(Polinomio* p, int exp) {
    Nodo* actual = p->cabeza;
    while (actual) {
        if (actual->termino.exponente == exp) {
            if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
            else p->cabeza = actual->siguiente;
            if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
            else p->cola = actual->anterior;
            free(actual);
            return;
        }
        actual = actual->siguiente;
    }
}

Polinomio* crearPolinomio() {
    Polinomio* p = (Polinomio*)malloc(sizeof(Polinomio));
    p->cabeza = p->cola = NULL;
    return p;
}

void insertarTermino(Polinomio* p, float coef, int exp) {
    if (coef == 0) return;
    Nodo* actual = p->cabeza;
    while (actual) {
        if (actual->termino.exponente == exp) {
            actual->termino.coeficiente += coef;
            if (fabs(actual->termino.coeficiente) < 0.0001) eliminarNodo(p, exp);
            return;
        }
        actual = actual->siguiente;
    }
    insertarNodoOrdenado(p, crearNodo(coef, exp));
}

float evaluarPolinomio(Polinomio* p, float x) {
    float res = 0;
    for (Nodo* n = p->cabeza; n; n = n->siguiente)
        res += n->termino.coeficiente * pow(x, n->termino.exponente);
    return res;
}

Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* res = crearPolinomio();
    for (Nodo* n = p1->cabeza; n; n = n->siguiente) insertarTermino(res, n->termino.coeficiente, n->termino.exponente);
    for (Nodo* n = p2->cabeza; n; n = n->siguiente) insertarTermino(res, n->termino.coeficiente, n->termino.exponente);
    return res;
}

Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* res = crearPolinomio();
    for (Nodo* n1 = p1->cabeza; n1; n1 = n1->siguiente)
        for (Nodo* n2 = p2->cabeza; n2; n2 = n2->siguiente)
            insertarTermino(res, n1->termino.coeficiente * n2->termino.coeficiente, n1->termino.exponente + n2->termino.exponente);
    return res;
}

char* polinomioToString(Polinomio* p) {
    if (!p->cabeza) return strdup("0");
    char* b = (char*)malloc(1024); b[0] = '\0';
    for (Nodo* n = p->cabeza; n; n = n->siguiente) {
        char s[100]; float c = n->termino.coeficiente; int e = n->termino.exponente;
        if (c > 0 && n != p->cabeza) strcat(b, "+");
        if (c == -1 && e != 0) strcat(b, "-");
        else if (c != 1 || e == 0) { sprintf(s, "%.0f", c); strcat(b, s); }
        if (e > 0) strcat(b, "x");
        if (e > 1) { sprintf(s, "^%d", e); strcat(b, s); }
    }
    return b;
}

void destruirPolinomio(Polinomio* p) {
    Nodo* n = p->cabeza;
    while (n) { Nodo* t = n->siguiente; free(n); n = t; }
    free(p);
}
