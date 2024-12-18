#include <iostream>
#include <cstdlib>
using namespace std;

struct nodo {
    struct nodo *izq;
    int valor;
    int altura;
    int peso; 
    int equilibrio;
    struct nodo *der;
};


struct nodo *raiz, *aux , *aux2 = NULL;

// Función para calcular altura
int calcularAltura(nodo *n) {
   if (!n) return 0;
    int alturaIzq = calcularAltura(n->izq);
    int alturaDer = calcularAltura(n->der);
    return (alturaIzq > alturaDer ? alturaIzq : alturaDer) + 1;
}
//Funcion para calcular peso
int calcularPeso(nodo* n) {
    if (!n) return 0;
    return 1 + calcularPeso(n->izq) + calcularPeso(n->der);
}

// Función para calcular el factor de equilibrio de un nodo
int Equilibrio(nodo *n) {
    if (!n) return 0;
    return calcularAltura(n->izq) - calcularAltura(n->der);
}

// Rotación simple a la derecha
nodo* rotacionDerecha(nodo *y) {
     cout << "Realizando rotacion a la derecha en nodo con valor: " << y->valor << endl;
    nodo *x = y->izq;
    nodo *T2 = x->der;

    x->der = y;
    y->izq = T2;

    // Actualizar alturas
    y->altura = calcularAltura(y);
    x->altura = calcularAltura(x);

    return x;
}

// Rotación simple a la izquierda
nodo* rotacionIzquierda(nodo* x) {
    cout << "Realizando rotacion a la izquierda en nodo con valor: " << x->valor << endl;

    nodo* y = x->der;
    nodo* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    // Actualizar alturas
    x->altura =calcularAltura(x);
    y->altura =calcularAltura(y);

    return y;
}
 
 nodo* balancear(nodo *n){
    n->altura = calcularAltura(n);
    n->peso = calcularPeso(n);
    n->equilibrio = Equilibrio(n);


    // Rotaciones
    cout << "Balanceando nodo con valor: " << n->valor << " |  equilibrio: " << n->equilibrio << endl;
    if (n->equilibrio > 1 && n->valor < n->izq->valor) {
        return rotacionDerecha(n);
    }
    if (n->equilibrio < -1 && n->valor > n->der->valor) {
        return rotacionIzquierda(n);
    }
    if (n->equilibrio > 1 && aux->valor > n->izq->valor) {
        n->izq = rotacionIzquierda(n->izq);
        return rotacionDerecha(n);
    }
    if (n->equilibrio < -1 && aux->valor < n->der->valor) {
        n->der = rotacionDerecha(n->der);
        return rotacionIzquierda(n);
    }

    return n;
 }
 
 nodo* posicionar(nodo* raiz, nodo* nuevo) {
    if (!raiz) return nuevo;

    if (nuevo->valor < raiz->valor) {
        raiz->izq = posicionar(raiz->izq, nuevo);
    } else if (nuevo->valor > raiz->valor) {
        raiz->der = posicionar(raiz->der, nuevo);
    } else {
        cout << "Error: El valor " << nuevo->valor << " ya existe en el arbol." << endl;
        free(nuevo);
        return raiz; 
    }

    return balancear(raiz);
 }
// Insertar un nodo en el árbol AVL
int insertar() {
    aux = (struct nodo*)malloc(sizeof(struct nodo));
    cout << "Digite el valor del nodo: ";
    cin >> aux->valor;
    aux->izq = aux->der = NULL;
    aux->altura = 1;
    aux->peso = 1;

    if (!raiz) {
        raiz = aux;
    } else {
        raiz = posicionar(raiz, aux);
    }

    aux = NULL;
    
    return 0;
}


nodo* obtenerMinimo(nodo* nodoActual) {
    while (nodoActual->izq) {
        nodoActual = nodoActual->izq;
    }
    return nodoActual;
}

// Eliminar un nodo del árbol AVL
nodo* eliminarNodo(nodo* raiz, int valor) {
    if (!raiz){
         cout << "Error: El valor " << valor << " no existe en el arbol." << endl;
         return raiz;
    } 

    // Buscar el nodo a eliminar
    if (valor < raiz->valor) {
        raiz->izq = eliminarNodo(raiz->izq, valor);
    } else if (valor > raiz->valor) {
        raiz->der = eliminarNodo(raiz->der, valor);
    } else {
       
        if (!raiz->izq || !raiz->der) {
            aux2 = raiz->izq ? raiz->izq : raiz->der;
            if (!aux2) {
                aux2 = raiz;
                raiz = NULL;
            } else {
                // Copiar los datos del hijo en el nodo actual
                *raiz = *aux2;
            }
            free(aux2); // Liberar el nodo
        } else {
            // Caso con dos hijos: Encontrar el sucesor inorden
            aux2 = raiz->der; 
            while (aux2->izq) {
                aux2 = aux2->izq; 
            }
            raiz->valor = aux2->valor; // Reemplazar el valor
            raiz->der = eliminarNodo(raiz->der, aux2->valor); 
        }
    }

    if (!raiz) return raiz; 

    return balancear(raiz);
}

int eliminar() {
    int valor;
    cout << "Digite el valor del nodo a eliminar: ";
    cin >> valor;
    raiz = eliminarNodo(raiz, valor);
    return 0;
}
int recorrer(nodo* a) {
    if (!a) return 0;
    cout << "Valor: " << a->valor << " con altura: " << a->altura << " y peso: " << a->peso << endl;
    recorrer(a->izq);
    recorrer(a->der);
    return 0;
}
int mostrar() {
    if (raiz) recorrer(raiz);
    else cout << "El arbol esta vacio." << endl;
    return 0;
}



    int main() {
    int opcion;
    do {
        cout << "\n1. Insertar";
        cout << "\n2. Mostrar";
        cout << "\n3. Eliminar";
        cout << "\n4. Salir\n";
        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                eliminar();
                break;
            case 4:
            cout<<"SALIENDO DEL PROGRAMA...."<<endl;
            break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 4);

    return 0;
}