#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <iostream>

#include "abb.h"

using namespace std;

// Clase para crear una serie de experimentos. Cada experimento genera un ABB de
// un tamaño fijo n de números enteros. Se buscan m números en el ABB y se registra
// la cantidad de llamadas recursivas realizadas. Al final, calcula el promedio y
// desviación estándar del número de llamadas recursivas.

class AppABB {
public:
    AppABB(int n, int factor, int m);
    ~AppABB();
    void iniciar();
    int* llamadas;
    float promedio;
    float desv;
    float tiempo;
    float aux;

private:
    int n;
    int maximo;
    int m;
    
    ArbolBinarioBusqueda generarArbol();
    float desvst();
};


AppABB::AppABB(int n, int factor, int m):n(n), maximo(n * factor), m(m) {
    llamadas = static_cast<int*>(malloc(m * sizeof(int)));
    promedio = 0.0;
    desv = 0.0;
    tiempo = 0.0;
    aux = 0.0;
    srand( (unsigned) time(NULL) );
}

// Método constructor que fija el tamaño del ABB (n), el valor máximo que
// almacenará el ABB y el número de búsquedas que realizará (m).

AppABB::~AppABB() {
    delete llamadas;
}

// Genera un ABB de tamaño n de números enteros aleatorios.

ArbolBinarioBusqueda AppABB::generarArbol() {
    ArbolBinarioBusqueda abb;
    for (int i = 1; i <= n; i++) {
        int num;
        do {
            // Se genera un número aleatorio entre 1 y máximo
            num = (rand() % maximo) + 1;
            
        // Se sigue intentando la inserción mientras ya exista
        // el número en el árbol.
        } while (!abb.insertar(num));
    }
    return abb;
}

// Calcula la desviación estándar del número de llamadas recursivas que se realizaron.

float AppABB::desvst() {
    float dif = 0.0;
    for (int i = 0; i < m; i++)
        dif += (llamadas[i] - promedio) * (llamadas[i] - promedio);
    return sqrt(dif / m);
}

// Ejecuta m veces una búsquede en un ABB de tamaño n.

void AppABB::iniciar() {
    promedio = 0.0;
    desv = 0.0;
    delete llamadas;
    llamadas = static_cast<int*>(malloc(m * sizeof(int)));
    ArbolBinarioBusqueda abb = generarArbol();
    for (int i = 1; i <= m; i++) {
        // Se genera un número aleatorio entre 1 y máximo
        int num = (rand() % maximo) + 1;
        cout << "Buscando: " << num << "\t";
        clock_t comienzo=clock();
        // Busca el número en el ABB y recupera la cantidad de llamadas
        // recursivas que se hicieron durante la búsqueda.
        llamadas[i-1] = abb.buscar(num);
        tiempo=(clock()-comienzo)/(float)CLOCKS_PER_SEC;
        aux= aux + tiempo;
        cout << "Llamadas recursivas: " << llamadas[i-1] << "\t";
        cout << "Tiempo de busqueda: " << tiempo << endl;
        promedio += llamadas[i-1];
    }
    
    promedio /= m;
    desv = desvst();
}


int main(int argc, char *argv[]) {
    if (argc == 3) {
        AppABB miApp(atoi(argv[1]), 10, atoi(argv[2]));
        miApp.iniciar();
        cout << "Resumen:" << endl;
        cout << "Promedio de llamadas recursivas: " << miApp.promedio << endl;
        cout << "Desviacion estandar: " << miApp.desv << endl;
        cout << "Tiempo que tardo en buscar: " << miApp.tiempo << endl;
        
    }
    else {
        cout << "Sintaxis: appabb <n> <m>" << endl;
        cout << "n: tamanio del arbol" << endl;
        cout << "m: cantidad de numeros a buscar" << endl;
    }
    
    return 0;
}

