#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set> 
#include <unordered_map>
#include <queue>
#include <stack>
#include <stdexcept>
#include <list>
#include <algorithm>
#include <list>
#include "list_linked_single.h"
using namespace std;

bool resuelveCaso() {
    ListLinkedSingle<int> lista;
    int numElems, pivote;
    cin >> numElems >> pivote;
    if(!cin) return false;
    while(numElems--){
        int elem;
        cin >> elem;
        lista.push_back(elem);
    }
    lista.partition(pivote);
    lista.display();
    cout << '\n';
    return true;
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