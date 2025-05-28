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

BinTree<int> leerArbol(istream& in) {
    int val;
    in >> val;
    if (val == -1) return BinTree<int>();
    BinTree<int> iz = leerArbol(in);
    BinTree<int> dr = leerArbol(in);
    return BinTree<int>(iz, val, dr);
}


struct tSol{
    int num_pares;
    bool es_pareado;
};

tSol num_nodos_acumulativos(const BinTree<int>& tree){
    if(tree.empty()) return {0, true};
    else if(tree.left().empty() && tree.right().empty()){
        return {tree.root() % 2 == 0, true};
    } else{
        tSol left = num_nodos_acumulativos(tree.left());
        tSol right = num_nodos_acumulativos(tree.right());
        tSol result;
        result.es_pareado = left.es_pareado && right.es_pareado && abs(left.num_pares - right.num_pares) <= 1;
        result.num_pares = left.num_pares + right.num_pares + (tree.root()%2==0);
        return result;
    }
}

void resuelveCaso() {
    BinTree<int> arbol = leerArbol(cin);
    tSol result = num_nodos_acumulativos(arbol);
    if(result.es_pareado) cout << "SI\n";
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