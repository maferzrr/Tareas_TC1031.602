#ifndef FUNCIONES
#define FUNCIONES

#include <iostream>

class Funciones{

    public:
    int sumaIterativa(int n);
    int sumaRecursiva(int n);
    int sumaDirecta(int n);

};

int Funciones::sumaIterativa(int n){
    if (n < 0) return 0;
    int resultado = 0;
    for (int i = 0; i <= n; i++){
        resultado += i;
    }
    return resultado;
}
int Funciones::sumaRecursiva(int n){
	if (n == 0) {
		return 0;
        } else {
		    return n + sumaRecursiva(n - 1);
	}
}
int Funciones::sumaDirecta(int n){
    return n * (n + 1) / 2;
}

#endif