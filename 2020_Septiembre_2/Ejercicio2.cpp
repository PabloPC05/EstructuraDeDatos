#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set> 
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <stack>
#include "BinTree.h"
using namespace std;

// Lee un árbol binario de ceros y unos en preorden, usando -1 para árbol vacío.
BinTree<int> leerArbol(std::istream& in) {
    int dato;
    if (!(in >> dato)) return BinTree<int>(); // Fin de entrada
    if (dato == -1) return BinTree<int>();
    BinTree<int> izq = leerArbol(in);
    BinTree<int> der = leerArbol(in);
    return BinTree<int>(izq, dato, der);
}

struct tSol{
    int suma;
    int suma_maxima;
};

tSol suma_maxima(const BinTree<int>& arbol){
    if(arbol.empty()) return {0,0};
    else if(arbol.left().empty() && arbol.right().empty()){
         return {arbol.root(), arbol.root()};
    }
    else{
        tSol left = suma_maxima(arbol.left());
        tSol right = suma_maxima(arbol.right());
        tSol resultado;
        resultado.suma = max(left.suma, right.suma) + arbol.root();
        resultado.suma_maxima = std::max(left.suma_maxima, std::max(right.suma_maxima, left.suma + right.suma + arbol.root()));
        return resultado;
    }
}

void resuelveCaso() {
    BinTree<int> arbol = leerArbol(cin);
    tSol b = suma_maxima(arbol);
    cout << b.suma_maxima << '\n';
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos; 
    cin >> numCasos;
    while(numCasos--) resuelveCaso();
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}