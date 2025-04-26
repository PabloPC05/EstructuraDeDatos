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

string toLower(std::string& input) {
    std::string result = input;
    for (char& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}


bool resuelveCaso() {
    int num_lineas; 
    cin >> num_lineas;
    if (num_lineas == 0) return false;
    map<string, vector<int>> palabras;
    cin.ignore(); // Ignorar el salto de línea después del número de líneas
    for(int i = 0; i < num_lineas; i++){
        string linea;
        getline(cin, linea);
        stringstream ss(linea);
        string palabra;
        while(ss >> palabra){
            if(palabra.size() <= 2) continue; // Ignorar palabras de longitud 1 o menos
            // Convertir a minúsculas
            palabra = toLower(palabra);
            auto& lineas = palabras[palabra];
            if (lineas.empty() || lineas.back() != i) { 
                lineas.push_back(i); 
            }
        }    
    }
    for(const auto& palabra : palabras){
        cout << palabra.first << " "; 
        for(int i = 0; i < palabra.second.size(); i++){
            cout << palabra.second[i] + 1 << ' ';
        }
        cout << '\n';
    }
    cout << "---\n";
    return true;
}


int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while(resuelveCaso());
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}
    