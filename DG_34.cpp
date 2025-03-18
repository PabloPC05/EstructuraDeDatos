#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;

void resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    vector<int> resultado = arbol.perfil();
    for (int i = 0; i < resultado.size(); i++) {
        cout << resultado[i] << " ";
    }
    cout << endl;
}


int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos;
    cin >> numCasos;
    while(numCasos--){ resuelveCaso();}
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}
    