#include <iostream>
#include <stdio.h>
typedef int T;
using namespace std;
//
// Clase NodoBinario que será utilizada por la clase ArbolBinarioBusqueda.
//
class NodoBinario {
private:
    // Atributos y métodos privados.
    private:
		NodoBinario* HijoIzquierdo;
		NodoBinario* HijoDerecho;
		T datos;
public:
    // Método constructor que inicializa los atributos de la clase.
    NodoBinario(T datos, NodoBinario* hijoIzquierdo,
                NodoBinario* hijoDerecho);
    
    // Devuelve el hijo izquierdo de este nodo.
    NodoBinario* getHijoIzquierdo();
    
    // Establece a nodo como hijo izquierdo.
    void setHijoIzquierdo(NodoBinario* hijoIzquierdo);
    
    // Devuelve el hijo derecho de este nodo.
    NodoBinario* getHijoDerecho();
    
    // Establece a nodo como hijo derecho.
    void setHijoDerecho(NodoBinario* hijoDerecho);
    
    // Devuelve los datos almacenados en este nodo.
    T getDatos();
};

NodoBinario::NodoBinario(T datos,NodoBinario* HijoIzq, NodoBinario* HijoDer){
	HijoDerecho= HijoDer;
	HijoIzquierdo = HijoIzq;
	datos = datos;
}

NodoBinario* NodoBinario::getHijoDerecho(){
	return HijoDerecho;
}

NodoBinario* NodoBinario::getHijoIzquierdo(){
	return HijoIzquierdo;
}

void NodoBinario::setHijoDerecho(NodoBinario* HijoDer){
	HijoDerecho = HijoDer;
}

void NodoBinario::setHijoIzquierdo(NodoBinario* Hijoizq){
	HijoIzquierdo = Hijoizq;
}

T NodoBinario::getDatos(){
	return datos;
}

//
// Clase que representa de forma simplificada un árbol binario de búsqueda.
//

class ArbolBinarioBusqueda {
private:
    // Atributos y métodos privados.
    NodoBinario* raiz;
    NodoBinario* aux;
	int cont; 
public:
    // Método constructor que inicializa el atributo.
    ArbolBinarioBusqueda();
    
    
    // Método destructor para liberar la memoria reservada.
    ~ArbolBinarioBusqueda();
    
    
    // Busca a elem en este ABB. Devuelve el número de llamadas recursivas que realiza.
    int buscar(T elem);
    
    
    // Inserta a elem en este ABB y devuelve true. Si elem ya existe en el ABB,
    // no lo inserta y devuelve false.
    bool insertar(T elem);
	
	//es auxiliar para el metodo buscar, de forma recursiva
	int buscardato(T elem,NodoBinario* raiz);
	
};
//cosntructor
ArbolBinarioBusqueda::ArbolBinarioBusqueda(){
	raiz = NULL;
	aux = raiz;
}
	
//Destructor
ArbolBinarioBusqueda::~ArbolBinarioBusqueda(){
	
}
//funcion Buscar
int ArbolBinarioBusqueda::buscar(T elem){
	if(aux == NULL){
		cout<<"no hay ningun dato"<<endl;
	}else{
		if(aux->getDatos() == elem){
			return 0;
		}else if(elem < aux->getDatos()){
			return 1 + buscardato(elem,raiz->getHijoIzquierdo());
		}else{
			return 1 + buscardato(elem,raiz->getHijoDerecho());
		}
	}
}
//funcion Insertar
bool ArbolBinarioBusqueda::insertar(T elem){
	if(raiz == NULL){
		raiz = new  NodoBinario(elem,NULL,NULL);
		aux = raiz;
		return true;
	}
	else{
		int valor = aux->getDatos();
		if(valor == elem){
			aux = raiz;
			return false;
		}else if(valor < elem){
			if(aux->getHijoIzquierdo() == NULL ){
				NodoBinario* nuevo = new NodoBinario(elem,NULL,NULL);
				aux->setHijoIzquierdo(nuevo);
				aux = raiz;
				return true;
			}else{
				aux = aux->getHijoIzquierdo();
				return insertar(elem);
			}
		}else{
			if(aux->getHijoDerecho() == NULL){ 
				NodoBinario* nuevo = new NodoBinario(elem,NULL,NULL);
				aux->setHijoDerecho(nuevo);
				aux = raiz;
				return true;
			}else{
				aux = aux->getHijoDerecho();
				return insertar(elem);
			}
		}
	}
}
int ArbolBinarioBusqueda::buscardato(T elem,NodoBinario* raiz){
		if(aux == NULL){
			cout<<"no hay ningun dato"<<endl;
		}else{
			if(aux->getDatos() == elem){
				return 0;
			}else if(elem < aux->getDatos()){
				return 1 + buscardato(elem,raiz->getHijoIzquierdo());
			}else{
				return 1 + buscardato(elem,raiz->getHijoDerecho());
		}	
	}
}
