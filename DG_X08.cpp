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


int completitud(const BinTree<char>& tree, const int& depth){
    if(tree.empty()) return {false, 0};
    else if(tree.left().empty() && tree.right().empty()) return {1, 1 };
    int left = completitud(tree.left(), depth + 1);
    int right = completitud(tree.right(), depth + 1);
    int result;
    if(left.depth == right.depth) result.completitud = 1;
    else if(left.depth > right.depth) result.completitud = 0;
    else result.completitud = -1;
    result.depth = 
}

bool resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    if(arbol.empty()) return false;
    cout << max_interes_ruta(arbol) <<'\n';
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