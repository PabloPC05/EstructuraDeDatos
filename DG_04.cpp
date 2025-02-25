#include <iostream>
#include <vector>
#include <fstream>
#include "multiconjunto.h"
using namespace std;


bool resuelveCaso() {
    int M;
    cin >> M;
    if (M == 0) return false;

    vector<int> secuencia(M), intento(M);
    Multiconjunto conteo_secreta;
    
    for (int i = 0; i < M; i++) {
        cin >> secuencia[i];
        conteo_secreta.anyadir(secuencia[i]);
    }
    
    for (int i = 0; i < M; i++) {
        cin >> intento[i];
    }
    
    vector<char> resultado(M, '.');
    
    for (int i = 0; i < M; i++) {
        if (intento[i] == secuencia[i]) {
            resultado[i] = '#';
            conteo_secreta.eliminar(intento[i]);
        }
    }
    
    for (int i = 0; i < M; i++) {
        if (resultado[i] == '.' && conteo_secreta.eliminar(intento[i])) {
            resultado[i] = 'O';
        }
    }
    
    for (char c : resultado) cout << c;
    cout << endl;
    
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
    #endif
    return 0;
}