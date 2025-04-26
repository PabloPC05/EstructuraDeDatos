#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <climits>
#include <vector>
#include <string>
#include "bintree_2.h"
using namespace std;

bool resuelveCaso() {
    int numOperaciones;
    cin >> numOperaciones;
    

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