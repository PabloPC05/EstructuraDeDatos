#include <cassert>
#include <iostream>
#include "tHora.h"
#include <vector>
using namespace std;

int busquedaBinaria(const vector<tHora>& horarios, const tHora& consulta) {
    int izquierda = 0, derecha = horarios.size() - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (horarios[medio] < consulta) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    if (izquierda < horarios.size()) {
        return izquierda;
    } else {
        return -1;
    }
}

bool resuelveCaso() {
    int nTrenes, nConsultas;
    cin >> nTrenes >> nConsultas;
    if (nTrenes == 0 && nConsultas == 0) {
        return false;
    }
    vector<tHora> trenes;
    trenes.clear();
    for (int i = 0; i < nTrenes; i++) {
        tHora h;
        cin >> h;
        trenes.push_back(h);
    }

    for (int i = 0; i < nConsultas; i++) {
        tHora h;
        cin >> h;
        int indice = busquedaBinaria(trenes, h);
        if(indice == -1 ) cout << "NO\n";
        else cout << trenes[indice] << '\n';   
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
