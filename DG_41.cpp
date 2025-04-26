#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <climits>
#include <vector>
#include <string>
using namespace std;

void resuelveCaso() {
    map<string, string> diccionario_antiguo; 
    map<string, string> diccionario_nuevo;
    string antiguo, nuevo; 
    getline(cin, antiguo); // Leemos la primera línea
    getline(cin, nuevo); // Leemos la segunda línea
    stringstream ss(antiguo), ss2(nuevo);
    string clave, valor;

    while(ss >> clave >> valor) diccionario_antiguo[clave] = valor;
    while(ss2 >> clave >> valor) diccionario_nuevo[clave] = valor; 

    vector<string> claves_nuevas, claves_eliminadas, claves_modificadas;

    for (const auto& par : diccionario_nuevo) { // Para cada una de las claves del nuevo diccionario
        auto it = diccionario_antiguo.find(par.first); 
        if (it == diccionario_antiguo.end()) { // Si no está en el antiguo, es una nueva clave
            claves_nuevas.push_back(par.first); 
        } else if (it->second != par.second) {  // Si si está en el antiguo pero su valor es diferente, es una clave modificada
            claves_modificadas.push_back(par.first); 
        }

    }
    for (const auto& par : diccionario_antiguo) { // Para cada una de las claves del antiguo diccionario
        if (diccionario_nuevo.find(par.first) == diccionario_nuevo.end()) { // Si no está en el nuevo, es una clave eliminada
            claves_eliminadas.push_back(par.first); 
        }
    }
    if(claves_nuevas.empty() && claves_modificadas.empty() && claves_eliminadas.empty()) { // Si no hay cambios, no imprimimos nada
        cout << "Sin cambios\n---\n"; 
        return; 
    }
    if(!claves_nuevas.empty()){
        cout << '+'; 
        for(const auto& clave : claves_nuevas) { // Imprimimos las claves nuevas
            cout << ' ' << clave; 
        }
        cout << '\n';
    }
    if(!claves_eliminadas.empty()){
        cout << '-'; 
        for(const auto& clave : claves_eliminadas) { // Imprimimos las claves eliminadas
            cout << ' ' << clave; 
        }
        cout << '\n';
    }
    if(!claves_modificadas.empty()){
        cout << '*'; 
        for(const auto& clave : claves_modificadas) { // Imprimimos las claves modificadas
            cout << ' ' << clave; 
        }
        cout << '\n';
    }
    cout << "---\n";
}


int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos; 
    cin >> numCasos; 
    cin.ignore(); // Limpiamos el buffer de entrada
    while(numCasos--) resuelveCaso();
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}