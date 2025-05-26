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
    int profundidad_max;
    int nodo_max;
    int suma;
    bool hay_nodo_cuadrado;
};

tSol nodo_cuadrado_mayor_prof_aux(const BinTree<int>& tree, const int& depth){
    if(tree.empty()) return {0, 0, 0};
    /*else if(tree.left().empty() && tree.right().empty()){ // es una hoja
        return {0, 0, tree.root()};
    }*/else{ // Caso General
        tSol left = nodo_cuadrado_mayor_prof_aux(tree.left(), depth+1);
        tSol right = nodo_cuadrado_mayor_prof_aux(tree.right(), depth+1);
        tSol result = max(left, right, [](const tSol& a, const tSol& b){
            return a.profundidad_max < b.profundidad_max;
        });
        result.suma = left.suma + right.suma + tree.root();
        result.hay_nodo_cuadrado = left.hay_nodo_cuadrado || right.hay_nodo_cuadrado;
        bool es_cuadrado = tree.root() == left.suma + right.suma;
        if(es_cuadrado){
            if(depth > result.profundidad_max){
                result.profundidad_max = depth;
                result.nodo_max = tree.root();
            }
            result.hay_nodo_cuadrado = true;
        }
        return result;
    }
}

int nodo_cuadrado_mayor_prof(const BinTree<int> & tree){
    int i = 0; 
    tSol result = nodo_cuadrado_mayor_prof_aux(tree, i);
    if(result.hay_nodo_cuadrado) return result.nodo_max;
    else return -1;

}

void resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    cout << nodo_cuadrado_mayor_prof(arbol) << '\n';
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