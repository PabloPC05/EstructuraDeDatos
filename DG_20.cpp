#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include "tDia.h"

using namespace std;

struct tAccidenteAereo{
    tDia fecha; 
    int numVictimas;
};

bool resuelveCaso() {
    int numFechas; 
    cin >> numFechas;
    if (!cin) return false;

    stack<tAccidenteAereo> accidentes;

    for (int i = 0; i < numFechas; i++) {
        tAccidenteAereo accidente;
        cin >> accidente.fecha >> accidente.numVictimas;

        // Eliminamos de la pila todos los elementos con menos o igual víctimas
        while (!accidentes.empty() && accidentes.top().numVictimas <= accidente.numVictimas) {
            accidentes.pop();
        }

        // Si la pila aún tiene elementos, imprimimos la fecha del más cercano con más víctimas
        if (!accidentes.empty()) {
            cout << accidentes.top().fecha << endl;
        } else {
            cout << "NO HAY" << endl;
        }

        // Insertamos el accidente actual en la pila
        accidentes.push(accidente);
    }

    cout << "---" << endl;
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
    