#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "list_linked_double.h"
using namespace std;

bool resuelveCaso(){
    int elem; 
    ListLinkedDouble<int> l;
    cin >> elem;
    while(elem != 0){
        l.push_back(elem);
        cin >> elem;
    }
    auto it = l.rbegin();
    while(it != l.rend()){
        cout << it.elem() << " ";
        it.advance();
    }
    cout << endl;
    return true;
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos;
    cin >> numCasos;
    while (numCasos--){
        resuelveCaso();
    }    
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
    #endif
    
    return 0;
}
    