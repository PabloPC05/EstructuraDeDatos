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
    int long_camino;
    int long_camino_max;
};

tSol long_camino_pares_max(const BinTree<int>& tree){
    if(tree.empty()) return {0,0};
    else if(tree.left().empty() && tree.right().empty()){ // Si es una hoja
        return {tree.root() % 2 == 0, tree.root() % 2 == 0};
    } else{
        tSol left = long_camino_pares_max(tree.left());
        tSol right = long_camino_pares_max(tree.right());
        tSol result;
        if(tree.root() % 2 == 0){
            result.long_camino = max(left.long_camino, right.long_camino) + 1; // Tomamos el maximo camino desde una hoja hasta una raiz
            result.long_camino_max = max(right.long_camino_max, max(left.long_camino_max, (tree.root() % 2 == 0) + left.long_camino + right.long_camino));
        }
        else{
             result.long_camino = 0;
             result.long_camino_max = max(right.long_camino_max,left.long_camino_max);
            }
        
        return result;
    }
}

void resuelveCaso() {
    BinTree<int> arbol = leerArbol(cin);
    tSol result = long_camino_pares_max(arbol);
    cout << result.long_camino_max << '\n';
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