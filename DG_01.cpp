#include <cassert>
#include <iostream>
#include <fstream>
#include "tHorarioTrenes.h"
using namespace std;

bool resuelveCaso() {
    int nTrenes, nConsultas;
    cin >> nTrenes >> nConsultas;
    if (nTrenes == 0 && nConsultas == 0) {
        return false;
    }
    tHorarioTrenes trenes;
    inicia(trenes);
    for (int i = 0; i < nTrenes; i++) {
        tHora h;
        cin >> h;
        inserta(trenes, h);
    }
    for (int i = 0; i < nConsultas; i++) {
        tHora h, sig;
        cin >> h;
        if (busca(trenes, h, sig))
            cout << sig << '\n';
        else
            cout << "NO\n";
    }
    cout << "---\n";
    return true;
}

int main() {
    #ifndef DOMJUDGE
      std::ifstream in("casos.txt");
      auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while (resuelveCaso()); // Ejecutar hasta que `0 0` termine la ejecución
    #ifndef DOMJUDGE
      std::cin.rdbuf(cinbuf);
    #endif
    return 0;
}
