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
    int num_nodos;
    int suma;
};

tSol num_nodos_acumulativos(const BinTree<int>& tree){
    if(tree.empty()) return {0, 0};
    else if(tree.left().empty() && tree.right().empty()){
        if(tree.root() == 0) return {1, tree.root()};
        else return {0, tree.root()};
    } else{
        tSol left = num_nodos_acumulativos(tree.left());
        tSol right = num_nodos_acumulativos(tree.right());
        tSol result;
        result.num_nodos = left.num_nodos + right.num_nodos;
        result.suma = left.suma + right.suma;
        if(result.suma == tree.root()) result.num_nodos++;
        result.suma += tree.root();
        return result;
    }
}

void resuelveCaso() {
    BinTree<int> arbol = leerArbol(cin);
    tSol result = num_nodos_acumulativos(arbol);
    cout << result.num_nodos << '\n';
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