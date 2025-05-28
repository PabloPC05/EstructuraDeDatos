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
    char c;
    in >> c;
    if (!in) return BinTree<int>(); // Fin de entrada
    if (c == '.') return BinTree<int>();
    // Si es '*', creamos nodo con valor 1 (o el valor que quieras)
    BinTree<int> iz = leerArbol(in);
    BinTree<int> dr = leerArbol(in);
    return BinTree<int>(iz, 1, dr);
}

struct tSol{
    bool es_diestro;
    int suma;
};

tSol es_zurdo(const BinTree<int>& tree){
    if(tree.empty()) return {true, 0};
    else if(tree.left().empty() && tree.right().empty()){
        return {true, 1};
    } else{
        tSol left = es_zurdo(tree.left());
        tSol right = es_zurdo(tree.right());
        tSol result;
        result.es_diestro = left.es_diestro && right.es_diestro && (left.suma + right.suma)/2 < left.suma;
        result.suma = left.suma + right.suma + 1;
        return result;
    }
}

void resuelveCaso() {
    BinTree<int> arbol = leerArbol(cin);
    tSol result = es_zurdo(arbol);
    if(result.es_diestro) cout << "SI\n";
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