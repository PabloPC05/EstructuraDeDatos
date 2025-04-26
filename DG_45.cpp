#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "MapHash.h"
using namespace std;

bool resuelveCaso() {

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