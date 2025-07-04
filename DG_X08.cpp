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

struct tSol{
    int max_depth;
    int completitud;
};

tSol completitud(const BinTree<char>& tree){
    if(tree.empty()) return {0, 1};
    else if(tree.left().empty() && tree.right().empty()){
         return {1,1};
    }
    tSol left = completitud(tree.left());
    tSol right = completitud(tree.right());
    int h = max(left.max_depth, right.max_depth) +1;
    if(left.completitud == -1 || right.completitud == -1) return {h, -1};

    else if(left.max_depth == right.max_depth && left.completitud == 1 && left.completitud == right.completitud) return {h, 1};

    else if((left.max_depth == right.max_depth + 1) && left.completitud >= 0 && right.completitud == 1) return {h, 0};

    else if((left.max_depth == right.max_depth) && left.completitud == 1 && right.completitud >= 0) return {h, 0};

    else return {h , -1};
}

bool resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    tSol result = completitud(arbol);
    if(result.completitud == 1) cout << "COMPLETO\n";
    else if(result.completitud == 0) cout << "SEMICOMPLETO\n";
    else cout << "NADA\n";
    return true;
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