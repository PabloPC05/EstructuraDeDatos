#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "bintree_2.h"
using namespace std;

bool resuelveCaso() {
    int num_nodos;
    cin >> num_nodos; 
    if(!cin) return false; 
    vector<int> recorridoPreorden;
    for(int i = 0; i < num_nodos; i++){
        int nodo;
        cin >> nodo;
        recorridoPreorden.push_back(nodo);
    }
    vector<int> recorridoInorder;
    for(int i = 0; i < num_nodos; i++){
        int nodo;
        cin >> nodo;
        recorridoInorder.push_back(nodo);
    }
    BinTree<int> arbol = BinTree<int>::reconstruir(recorridoPreorden, recorridoInorder);
    arbol.display(cout);
    cout << endl;
    return true;
}


int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while(resuelveCaso());
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}
    