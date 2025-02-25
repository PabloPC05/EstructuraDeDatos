#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "dequeue.h"
using namespace std;
using deque = Dequeue<char>;

bool resuelveCaso(){
    int numSobrinos; 
    cin >> numSobrinos; 
    if(!cin) return false; 
    
    return true; 
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while (resuelveCaso());
    
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
    #endif
    
    return 0;
}
    