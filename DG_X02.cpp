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
    int ronda;
    int numPartidos;
    bool presente;
};

tSol partidos_totales(const BinTree<int>& tree, const int&K){
    if(tree.empty()) return {0,0,0};
    else if(tree.left().empty() && tree.right().empty()) return {0, 0, (tree.root() == 1)};
    else {
        tSol left = partidos_totales(tree.left(), K);
        tSol right = partidos_totales(tree.right(), K);
        tSol result = {left.ronda + 1, left.numPartidos + right.numPartidos, (left.presente || right.presente)};
        if(left.ronda >= K) return result;
        if(left.presente && right.presente){     // Si ambos jugadores están presentes
            result.numPartidos += 1;
        }
        return result;
    }
}


bool resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    int K;
    cin >> K;
    tSol result = partidos_totales(arbol, K);
    cout << result.numPartidos << '\n';
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