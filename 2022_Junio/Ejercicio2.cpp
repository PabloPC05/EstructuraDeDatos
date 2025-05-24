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

pair<BinTree<int>,int> acumula_aux(const BinTree<int>& arbol){
    if(arbol.empty()) return {{}, 0};
    else if(arbol.left().empty() && arbol.right().empty()){
        return {{arbol.root()}, arbol.root()};
    } else{
        auto left = acumula_aux(arbol.left());
        auto right = acumula_aux(arbol.right());

        return {{left.first, left.second + right.second, right.first}, left.second + right.second};
    }
}


BinTree<int> acumula(const BinTree<int>& arbol){
    return acumula_aux(arbol).first;
}

void resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    BinTree<int> result = acumula(arbol);
    cout << result << '\n';
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