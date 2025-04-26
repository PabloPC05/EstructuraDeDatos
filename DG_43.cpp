#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <string>
#include <vector>
using namespace std;

void resuelveCaso() {
    int numCapitulos; 
    cin >> numCapitulos;
    // La clave es el capitulo y cuando fue la última vez que se emitio
    vector<int> capitulos(numCapitulos);
    for(int i = 0; i < numCapitulos; i++){
        cin >> capitulos[i];  // Leemos los capitulos
    }
    unordered_map<int, int> ultimaVez;  // Mapa para almacenar los capitulos y la última vez que se emitieron
    int i = 0, inicio_ventana = 0, max = INT_MIN; // Ventana de capitulos y el maximo
    for(const int& capitulo : capitulos){
        if(ultimaVez.find(capitulo) != ultimaVez.end() && ultimaVez[capitulo] >= inicio_ventana){ // Si el capitulo ya se emitió y la última vez que se emitió es mayor o igual al inicio de la ventana
            inicio_ventana = ultimaVez[capitulo] + 1; // Guardamos el nuevo inicio de la ventana
        }
        ultimaVez[capitulo] = i; // Guardamos la última vez que se emitió el capitulo
        int longitud_ventana = i - inicio_ventana + 1; // Longitud de la ventana
        max = std::max(max, longitud_ventana); // Actualizamos el maximo
        i++; // Aumentamos el indice
    }
    cout << max << '\n';
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos;
    cin >> numCasos;
    while(numCasos--) resuelveCaso();
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}