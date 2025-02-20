#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "tTeatro.h"

using namespace std;

bool resuelveCaso() {
    int N, Q;
    cin >> N >> Q;
    if (N == 0 || Q == 0) return false;
    Teatro teatro;
    vector<char> resultados(N, '.');
    for (int i = 0; i < N; ++i) {
        int inicio, fin;
        string nombre;
        cin >> inicio >> fin >> nombre;
        if (!teatro.nueva_reserva(inicio, fin, nombre)) {
            cout << 'X';
        }
        else{
            cout << '.'; 
        }
    }
    cout << endl; 
    for (int i = 0; i < Q; ++i) {
        int num_butaca;
        cin >> num_butaca;
        cout << teatro.nombre_reserva(num_butaca) << endl;
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
    #endif
    return 0;
}