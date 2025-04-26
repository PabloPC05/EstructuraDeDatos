#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <climits>
#include <vector>
#include <string>
using namespace std;

enum Estado {
    CORRECTO = 1,
    INCORRECTO = -1
};

Estado convertirEstado(const string& estado) {
    if (estado == "CORRECTO") return CORRECTO;
    else return INCORRECTO;
}

bool resuelveCaso() {
    int num_alumnos; 
    cin >> num_alumnos; 
    if (num_alumnos == 0) return false;
    std::map<std::string, int> alumnos;
    for(int i = 0; i < num_alumnos; i++){
        string nombre; 
        string estado;
        char ch;
        cin >> ch; // Leer el primer caracter
        while (ch != '\n' ) {
            nombre += ch;
            cin.get(ch); // Leer el siguiente caracter
        }
        cin >> estado;
        auto it = alumnos.find(nombre);
        if(it != alumnos.end()){ // Si el alumno ya existe
            Estado estadoActual = convertirEstado(estado);
            if(estadoActual + it->second == 0) alumnos.erase(it); // Si el alumno no se le puede calificar
            else{
                alumnos[nombre] = estadoActual + it->second; // Si el alumno ya tiene un estado, se suma
            }
        }
        else{ // Si el alumno no existe en el mapa
            Estado estadoActual = convertirEstado(estado);
            alumnos[nombre] = estadoActual; // Si el alumno no existe, se añade
        }
    }
    // Imprimir los alumnos
    for(auto alumno : alumnos){
        cout << alumno.first << ", " << alumno.second << '\n';
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
    