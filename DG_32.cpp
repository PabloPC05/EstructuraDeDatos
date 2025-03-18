#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;


std::string maxString(int length, char maxChar) {
    std::string str;
    for(int i = 0; i < length; i++) {
      str.push_back(maxChar);
    }
    return str;
  }

bool resuelveCaso() {
    char type;
    cin >> type;
    if (!cin) return false;

    if (type == 'N') {
        // Árbol de enteros
        BinTree<int> arbol = read_tree<int>(cin);
        if (arbol.es_de_busqueda(INT_MIN, INT_MAX)) {
            cout << "SI\n";
        } else {
            cout << "NO\n";
        }
    } else {
        // Árbol de cadenas
        BinTree<string> arbol = read_tree<string>(cin);
        if (arbol.es_de_busqueda("", maxString(100, '\xFF'))) {
            cout << "SI\n";
        } else {
            cout << "NO\n";
        }
    }

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
    