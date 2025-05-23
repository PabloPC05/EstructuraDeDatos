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
// 0: Suma de los descendientes 
// 2: Numero de nodos intermedios
pair<int, int>  num_nodos_intermedios(const BinTree<int>& tree, const int& root){
    if(tree.empty()) return {0, 0};
    else if(tree.left().empty() && tree.right().empty()){
        if(tree.root() == 0 && root != 0) return {tree.root(), 1};
        else return {tree.root(),0};
    }else{
        pair<int, int> sol = {0, 0};
        auto left = num_nodos_intermedios(tree.left(), tree.root());
        auto right = num_nodos_intermedios(tree.right(), tree.root());
        sol.second = left.second + right.second; // Sumamos la cantidad de nodos intermedios
        sol.first = left.first + right.first + tree.root();   // Sumamos las sumas de los desendientes
        int op = abs(left.first - right.first) % root;
        if(op == tree.root()) sol.second++;
        return sol;
    }
} 

bool resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    if(arbol.empty()) cout << 0 << '\n';
    else{
        pair<int, int> sol = num_nodos_intermedios(arbol, arbol.root());
        cout << sol.second << '\n';
    }
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