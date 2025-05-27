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
    int num_ceros;
    bool codificada;
};

tSol bien_codificada(const BinTree<int>& arbol){
    if(arbol.empty()) return {0, true};
    else if(arbol.left().empty() && arbol.right().empty()){
        return {arbol.root() == 0, true};
    } else{
        tSol left = bien_codificada(arbol.left());
        tSol right = bien_codificada(arbol.right());
        tSol result;
        result.codificada = abs(left.num_ceros - right.num_ceros) <= 1 && left.codificada && right.codificada;
        result.num_ceros = (left.num_ceros + right.num_ceros) + (arbol.root() == 0);
        return result;
    }
}

void resuelveCaso() {
    BinTree<int> arbol = leerArbol(cin);
    tSol b = bien_codificada(arbol);
    if(b.codificada) cout << "SI\n";
    else cout << "NO\n";
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