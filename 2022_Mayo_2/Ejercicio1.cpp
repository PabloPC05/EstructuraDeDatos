//******************************************************
// IMPORTANTE
// NOMBRE Y APELLIDOS DEL ALUMNO:
// USUARIO DEL JUEZ DE ESTE EXAMEN:
// LABORATORIO Y PUESTO:
//******************************************************

#include <iostream>
#include <fstream>

#include "bintree.h"
using namespace std;

// maximo camino 
// numero de pares
pair<int, int> caminoPares_aux(const bintree<int>& a){
    if(a.empty()) return {0,0};
    else{
        auto left = caminoPares_aux(a.left());
        auto right = caminoPares_aux(a.right());
        int esPar = (a.root() % 2 == 0);
        pair<int, int> maximo = {0,0};
        maximo.first = max(left.first + right.second + esPar, max(left.first, left.second));
        maximo.second = max(left.first, right.second) + esPar;
        return maximo;
    }
}


int caminoPares (bintree<int> const& a) {
    return caminoPares_aux(a).second;
}

// No modificar el código a partir de aqui.
// Entrada y salida de datos
void resuelveCaso(){
    bintree<int> a = leerArbol(-1);
    std::cout << caminoPares(a) << '\n';
}

int main() {
    
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif
    
    int numCasos = 1;   std::cin >> numCasos; std::cin.ignore();    
    for (int i = 0; i < numCasos; ++i) resuelveCaso();
    
    
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    
    return 0;
}
