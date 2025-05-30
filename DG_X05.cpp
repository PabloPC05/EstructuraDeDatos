#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct Problema {
    bool resuelto = false;
    int intentosIncorrectos = 0;
    int tiempoCorrecto = 0;
};

struct Equipo {
    string nombre;
    int problemasResueltos = 0;
    int tiempoTotal = 0;
    unordered_map<string, Problema> problemas;
};

// criterio de ordenacion
bool comparar(const Equipo& a, const Equipo& b) {
    if(a.problemasResueltos != b.problemasResueltos)
        return a.problemasResueltos > b.problemasResueltos;
    if(a.tiempoTotal != b.tiempoTotal)
        return a.tiempoTotal < b.tiempoTotal;
    return a.nombre < b.nombre;
}

void resolverCaso() {
    unordered_map<string, Equipo> equipos;
    string equipo, problema, veredicto;
    int minutos;

    while(cin >> equipo && equipo != "FIN") {
        cin >> problema >> minutos >> veredicto;
        auto& eq = equipos[equipo];
        eq.nombre = equipo;
        auto& prob = eq.problemas[problema];

        if(!prob.resuelto) {
            if(veredicto == "AC") {
                prob.resuelto = true;
                prob.tiempoCorrecto = minutos;
                eq.problemasResueltos++;
                eq.tiempoTotal += minutos + 20 * prob.intentosIncorrectos;
            } else {
                prob.intentosIncorrectos++;
            }
        }
    }

    // Pasamos a vector para ordenar
    vector<Equipo> resultado;
    for(auto& p : equipos) resultado.push_back(p.second);

    sort(resultado.begin(), resultado.end(), comparar);

    // salida del ranking
    for(auto& eq : resultado) {
        cout << eq.nombre << " " << eq.problemasResueltos << " " << eq.tiempoTotal << '\n';
    }
    cout << "---\n";
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while(resolverCaso()) ;
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}
