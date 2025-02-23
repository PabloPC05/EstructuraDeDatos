#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "list_linked_double.h"
using namespace std;

bool resuelveCaso(){
    int num_alumnos, saltos; 
    cin >> num_alumnos >> saltos; 
    if(num_alumnos == 0 && saltos == 0) return false; 
    ListLinkedDouble<int> alumnos; 
    for(int i = 1; i <= num_alumnos; i++){
        alumnos.push_back(i);
    }
    cout << alumnos.eliminarSaltando(saltos) << endl;
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
    