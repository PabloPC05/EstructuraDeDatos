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
    bool es_diestro;
    int suma;
};

tSol es_diestro(const BinTree<int>& tree){
    if(tree.empty()) return {true, 0};
    else if(tree.left().empty() && tree.right().empty()){
        return {true, tree.root()};
    } else{
        tSol left = es_diestro(tree.left());
        tSol right = es_diestro(tree.right());
        tSol result;
        result.es_diestro = left.es_diestro && right.es_diestro && right.suma > left.suma;
        result.suma = left.suma + right.suma + tree.root();
        return result;
    }
}

void resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    tSol result = es_diestro(arbol);
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