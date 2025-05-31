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
    int max_altura_completo;
    int altura_completo;
};

tSol completitud(const BinTree<char>& tree){
    if(tree.empty()) return {0, 0};
    else if(tree.left().empty() && tree.right().empty()) return {1,1};
    tSol left = completitud(tree.left());
    tSol right = completitud(tree.right());
    tSol result = {0,0};
    if(left.altura_completo == right.altura_completo){
        result.altura_completo = right.altura_completo + 1;
    } else{
        result.altura_completo = min(left.altura_completo, right.altura_completo) + 1;
    }
    result.max_altura_completo = max({left.max_altura_completo, right.max_altura_completo, result.altura_completo});
    return result;
}

bool resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    tSol result = completitud(arbol);
    cout << result.max_altura_completo << '\n';
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