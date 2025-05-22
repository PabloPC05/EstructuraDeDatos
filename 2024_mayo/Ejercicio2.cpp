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

// Primera componente:De parador a parador
// Segunda componente: De parador a root
pair<int, int> max_interes_ruta_aux(const BinTree<int>& montaya){
    pair<int, int> left = {0, 0}, right = {0, 0}, returnValue = {0, 0};
    if(!montaya.left().empty()) left = max_interes_ruta_aux(montaya.left());
    if(!montaya.right().empty()) right = max_interes_ruta_aux(montaya.right());
    returnValue.second = montaya.root() + max(left.second, right.second); // Camino con mejor valoracion desde un parador hasta la raiz 
    returnValue.first = max(montaya.root() + left.second + right.second, max(left.first, right.first)); // Camino con mejor valoracin desde un parador a otro parador
    return returnValue;
}

int max_interes_ruta(const BinTree<int>& montaya){
    return max_interes_ruta_aux(montaya).first;
}


bool resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    if(arbol.empty()) return false;
    cout << max_interes_ruta(arbol) <<'\n';
    return true;
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while(resuelveCaso());
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}