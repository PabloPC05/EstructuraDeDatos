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
#include "list_linked_single.h"
using namespace std;


bool resuelveCaso() {
    int numElem;
    cin >> numElem;
    if(!cin) return false;
    ListLinkedSingle<int> lista;
    while(numElem--){
        int n;
        cin >> n;
        lista.push_back(n);
    }
    lista.buble_sort();
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