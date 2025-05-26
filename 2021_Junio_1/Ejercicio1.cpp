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
#include "ListLinkedDouble.h"
using namespace std;

bool resuelveCaso() {
    ListLinkedDouble<int> lista, aux;
    int elem;
    cin >> elem;
    while(elem != 0){
        lista.push_back(elem);
        cin >> elem;
    }
    cin >> elem;
    while(elem != 0){
        aux.push_back(elem);
        cin >> elem;
    }
    lista.unzip(aux);
    lista.display();
    cout << '\n';
    aux.display();
    cout << '\n';
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