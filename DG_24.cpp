#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;

// El coste de las tres funciones es O(n) lineal con respecto al numero de nodos del arbol, 
// por lo que por las propiedades aritméticas de los costes asintóticos
// O(n) + O(n) + O(n) ~~ O(n) 
void resuelveCaso(){
    BinTree<char> tree = read_tree<char>(std::cin);
    cout << tree.num_nodes() << " " << tree.num_leaves() << " " << tree.height() << endl;
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos;
    cin >> numCasos;
    while (numCasos--){
        resuelveCaso();
    }    
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
    #endif
    
    return 0;
}
    