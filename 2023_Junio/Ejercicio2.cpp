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
//  tesoro, vida
struct tSol{
    int botin;
    int vida;
    int curas;
    tSol(int t, int v, int p) : botin(t), vida(v), curas(p) {}
};

tSol mejor_recorrido(const BinTree<int>& tree){
    if(tree.empty()) return tSol(0,0,0);
    else if(tree.left().empty() && tree.right().empty()){
        if(tree.root() < 0) return tSol(0, -tree.root() +1, 0);
        else if(tree.root() > 0) return tSol(tree.root(), 0, 0);
        else return tSol(0, 0, 1);
    } else{
        tSol left = mejor_recorrido(tree.left());
        tSol right = mejor_recorrido(tree.right());
        tSol sol = {0,0,0};
        if(tree.root() > 0) sol = {tree.root(), 0, 0};
        else if(tree.root() < 0) sol = {0, -tree.root(), 0};
        else sol = {0, 0, tree.root()};

        tSol max = std::max(left, right, [](const tSol& a, const tSol& b){
            if(a.botin == b.botin) return a.vida - a.curas > b.vida - b.curas;
            return a.botin < b.botin;
        });

        sol.botin += max.botin;
        sol.curas += max.curas;
        sol.vida += max.vida;

        if(sol.curas > 0){
            sol.vida -= sol.curas;
            sol.curas = 0;
        }
        if(sol.vida == 0) sol.vida = 1;
        return sol;
    }
}


bool resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    if(arbol.empty()) return false;
    tSol sol = mejor_recorrido(arbol);
    cout << sol.botin << ' ';
    cout << sol.vida <<'\n';
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