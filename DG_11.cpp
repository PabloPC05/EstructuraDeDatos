#include <cassert>
#include <iostream>
#include <fstream>
#include "list_linked_double.h"
using namespace std;

void resuelveCaso(){
    int n;
    ListLinkedDouble lista_1;
    cin >> n;
    for(int i = 0; i < n; i++){
        int elem;
        cin >> elem;
        lista_1.push_back(elem);
    }
    cin >> n; 
    ListLinkedDouble lista_2;
    for(int i = 0; i < n; i++){
        int elem;
        cin >> elem;
        lista_2.push_back(elem);
    }
    lista_1.zip(lista_2);
    lista_1.display();
    cout << endl;
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
    