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

// Primera coordenada es el numero representante de la seccion
// Segunda coordenada es la cantidad de numeros de la sección
pair<int, int> seccion_mayor_aux(const BinTree<int>& tree){
    pair<int, int> left, right; 
    if(tree.left().empty() && tree.right().empty()){ // Caso Base: Hojas
         return {tree.root(), 1};
    }

    // Casos de recursividad
    if(!tree.left().empty()) left = seccion_mayor_aux(tree.left());
    if(!tree.right().empty()) right = seccion_mayor_aux(tree.right());

    if(left.first == right.first && left.first == tree.root()) return {left.first, left.second + right.second + 1};
    else if(tree.root() == left.first && left.second + 1 >= right.second){
            return {left.first, left.second+1};
    } else if(tree.root() == right.first && right.second + 1 >= left.second){
            return {right.first, right.second+1};
    } else if(left.second > right.second) return left;
    else if (left.second < right.second) return right;
    else return {tree.root(), 1};
}

int seccion_mayor(const BinTree<int>& tree){
    return seccion_mayor_aux(tree).second;
}

bool resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    if(arbol.empty()) return false;
    cout << seccion_mayor(arbol) <<'\n';
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