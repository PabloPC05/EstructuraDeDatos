#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "queue_linkedlist.h"
using namespace std;

bool resuelveCaso(){
    int num;
    cin >> num;
    if(num == 0) return false; 
    QueueLinkedList<int> cola; 
    
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
    