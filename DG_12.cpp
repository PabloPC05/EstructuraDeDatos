#include <cassert>
#include <iostream>
#include <fstream>
#include "list_linked_double.h"
using namespace std;

void resuelveCaso(){
    int indice, n;
    ListLinkedDouble lista;
    cin >> n;
    while(n != 0){
        lista.push_back(n);
        cin >> n;
    }
    cin >> indice;
    lista.partition(indice);
    lista.display();
    cout << endl;
    lista.display_reverse();    
    cout << '\n';
}

int main() {
    #ifndef DOMJUDGE
      std::ifstream in("casos.txt");
      auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
        int numCasos;
        cin >> numCasos; 
       while (numCasos--) resuelveCaso();
    
    #ifndef DOMJUDGE
      std::cin.rdbuf(cinbuf);
      // Descomentar si se necesita
      // system("PAUSE");
    #endif
    
       return 0;
}
    