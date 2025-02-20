#include <cassert>
#include <iostream>
#include <fstream>
#include "tPelicula.h"
#include <vector>
#include <algorithm>
using namespace std;

bool resuelveCaso() {
    int n;
    cin >> n;
    if(n == 0) return false;
    vector<tPelicula> listaPelis;
    tPelicula peli;
    for(int i = 0; i < n; i++){
        cin >> peli;
        peli.calcularHoraFin(peli);
        listaPelis.push_back(peli);
    }
    std::sort(listaPelis.begin(), listaPelis.end());
    for(int i = 0; i < n; i++){
        cout << listaPelis[i] << '\n';
    }
    cout << "---\n";
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
