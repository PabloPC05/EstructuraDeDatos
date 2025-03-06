#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;

void resuelveCaso(){
    char c; 
    cin >> c; 
    while(cin){
        if(c == 'N'){
            BinTree<int> arbol = read_tree<int>(cin); 
            cout << arbol.minimo() << endl; 
        }
        else if (c = 'P'){
            BinTree<string> arbol = read_tree<string>(cin); 
            cout << arbol.minimo() << endl; 
        }
        cin >> c;
    }
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    resuelveCaso();
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    
    return 0;
}
    