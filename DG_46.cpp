#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

bool isAllUpper(const string& str) {
    for (const char& c : str) {
        if (!isupper(c)) return false;
    }
    return true;
}

bool resuelveCaso() {
    unordered_map<string, string> alumnos_deportes;
    unordered_map<string, int> deportes_contados;
    string str; 
    // Leeemos el deporte
    cin >> str;
    if(!cin) return false;
    while(str != "_FIN_"){
        deportes_contados[str] = 0; // Inicializamos el contador a 0
        string deporte = str; // Guardamos el deporte
        // Leemos los alumnos de ese deporte
        cin >> str;
        while(!isAllUpper(str) && str != "_FIN_") { // Mientras no sea un nombre de deporte y no sea _FIN_
            auto it = alumnos_deportes.find(str); // Buscamos si el alumno ya tiene un deporte asignado
            if(it == alumnos_deportes.end()) { // Si no tiene un deporte asignado
                alumnos_deportes[str] = deporte; // Asignamos el deporte al alumno
                deportes_contados[deporte]++; // Aumentamos el contador de deportes
            } else if(it->second != deporte && it->second != "ELIMINADA") { // Si tiene un deporte asignado diferente al actual, lo eliminamos de ambos deportes
                deportes_contados[it->second]--; // Disminuimos el contador del otro deporte
                alumnos_deportes[str] = "ELIMINADA";
            } // El ultimo caso que queda es que el alumno ya tiene un deporte asignado, que por descarte, ha de ser el actual, por lo que no se hace nada
            // Tambien cubre el caso de que el alumno ya haya sido eliminado, por lo que no se hace nada
            cin >> str; // Leemos el siguiente alumno
        }
    }

    vector<pair<string, int>> deportes_ordenados(deportes_contados.begin(), deportes_contados.end());
    sort(deportes_ordenados.begin(), deportes_ordenados.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first; // si hay empate, ordenar por nombre de deporte
    });


    // Imprimimos los resultados
    for(const auto& [deporte, cantidad] : deportes_ordenados) {
        cout << deporte << " " << cantidad << '\n';
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