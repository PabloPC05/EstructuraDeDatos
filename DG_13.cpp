    #include <cassert>
    #include <iostream>
    #include <fstream>
    #include "list_linked_double.h"
    using namespace std;

    void resuelveCaso(){
        int indice, n;
        ListLinkedDouble lista, other;
        cin >> n;
        // Leemos la primera lista
        while(n != 0){
            lista.push_back(n);
            cin >> n;
        }
        cin >> n; 
        while(n != 0){
            other.push_back(n);
            cin >> n;
        }
        lista.unzip(other);
        lista.display();
        cout << endl;
        other.display();
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
        