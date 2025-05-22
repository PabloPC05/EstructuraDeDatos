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
#include "ListLinkedDouble.h"
using namespace std;


bool resuelveCaso() {
    int numElem;
    cin >> numElem;
    if(numElem == -1) return false;
    ListLinkedDouble<char> lista;
    while(numElem--){
        char c;
        cin >> c;
        lista.push_back(c);
    }
    ListLinkedDouble<char> duplicados = lista.quitar_duplicados();
    lista.display();
    cout << '\n';
    duplicados.display();
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