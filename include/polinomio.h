##include "../include/polinomio.h"

/* --- Funciones de Lista --- */

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
    if (!p || !nuevo) return;

    if (!p->cabeza) {
        p->cabeza = p->cola = nuevo;
        return;
    }

    Nodo* actual = p->cabeza;
    while (actual && actual->termino.exponente > nuevo->termino.exponente) {
        actual = actual->siguiente;
    }

    if (!actual) { // Insertar al final
        nuevo->anterior = p->cola;
        p->cola->siguiente = nuevo;
        p->cola = nuevo;
    } else if (actual == p->cabeza) { // Insertar al inicio
        nuevo->siguiente = p->cabeza;
        p->cabeza->anterior = nuevo;
        p->cabeza = nuevo;
    } else { // Insertar en medio
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

/* --- Funciones de Polinomio --- */

Polinomio* crearPolinomio() {
    Polinomio* p = (Polinomio*)malloc(sizeof(Polinomio));
    if (p) {
        p->cabeza = NULL;
        p->cola = NULL;
    }
    return p;
}

void insertarTermino(Polinomio* p, float coef, int exp) {
    if (coef == 0) return;

    // Buscar si ya existe el exponente para simplificar
    Nodo* actual = p->cabeza;
    while (actual) {
        if (actual->termino.exponente == exp) {
            actual->termino.coeficiente += coef;
            if (fabs(actual->termino.coeficiente) < 0.0001) {
                eliminarNodo(p, exp);
            }
            return;
        }
        actual = actual->siguiente;
    }

    // Si no existe, crear e insertar ordenado
    insertarNodoOrdenado(p, crearNodo(coef, exp));
}

float evaluarPolinomio(Polinomio* p, float x) {
    float resultado = 0;
    Nodo* actual = p->cabeza;
    while (actual) {
        resultado += actual->termino.coeficiente * pow(x, actual->termino.exponente);
        actual = actual->siguiente;
    }
    return resultado;
}

Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* res = crearPolinomio();
    Nodo* aux = p1->cabeza;
    while (aux) {
        insertarTermino(res, aux->termino.coeficiente, aux->termino.exponente);
        aux = aux->siguiente;
    }
    aux = p2->cabeza;
    while (aux) {
        insertarTermino(res, aux->termino.coeficiente, aux->termino.exponente);
        aux = aux->siguiente;
    }
    return res;
}

Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* res = crearPolinomio();
    for (Nodo* n1 = p1->cabeza; n1; n1 = n1->siguiente) {
        for (Nodo* n2 = p2->cabeza; n2; n2 = n2->siguiente) {
            insertarTermino(res, n1->termino.coeficiente * n2->termino.coeficiente, 
                            n1->termino.exponente + n2->termino.exponente);
        }
    }
    return res;
}

char* polinomioToString(Polinomio* p) {
    if (!p || !p->cabeza) return strdup("0");
    char* buffer = (char*)malloc(1024);
    buffer[0] = '\0';
    Nodo* n = p->cabeza;
    while (n) {
        char temp[100];
        float c = n->termino.coeficiente;
        int e = n->termino.exponente;

        if (c > 0 && n != p->cabeza) strcat(buffer, "+");
        
        if (c == -1 && e != 0) strcat(buffer, "-");
        else if (c != 1 || e == 0) {
            sprintf(temp, "%.0f", c);
            strcat(buffer, temp);
        }

        if (e > 0) strcat(buffer, "x");
        if (e > 1) {
            sprintf(temp, "^%d", e);
            strcat(buffer, temp);
        }
        n = n->siguiente;
    }
    return buffer;
}

void destruirPolinomio(Polinomio* p) {
    if (!p) return;
    Nodo* actual = p->cabeza;
    while (actual) {
        Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    free(p);
}
