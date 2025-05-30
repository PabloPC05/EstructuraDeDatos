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
    int sector;
    int max_sector;
};

tSol sector_max(const BinTree<char>& tree){
    if(tree.empty()) return {0,0};
    else if(tree.left().empty() && tree.right().empty()) return {tree.root() == 'V', tree.root() == 'V'};
    else {
        tSol left = sector_max(tree.left());
        tSol right = sector_max(tree.right());
        int sectorActual;
        if(tree.root() == 'V'){
            sectorActual = left.sector + right.sector + 1;
        } else{
            sectorActual = 0;
        }
        return {sectorActual, max(sectorActual, max(left.max_sector, right.max_sector))};
    }
}


bool resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    tSol result = sector_max(arbol);
    cout << result.max_sector << '\n';
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