#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;

void resuelveCaso(){
    BinTree<int> arbol = read_tree<int>(cin);
    if(arbol.es_estable()){
        cout << "SI" << endl;
    }else{
        cout << "NO" << endl;
    }
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
    