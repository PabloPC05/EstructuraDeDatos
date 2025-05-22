#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set> 
#include <unordered_map>
#include <queue>
#include <stack>
#include <stdexcept>
#include <list>
#include <algorithm>
#include "tDia.h"
using namespace std;

struct tAccidenteAereo{
    tDia fecha;
    int numVictimas;
};


void resuelveCaso() {

    int numCasos; 
    cin >> numCasos;

    stack<tAccidenteAereo> accidentesAereos;

    for(int i = 0; i < numCasos; i++){
        tDia fecha;
        int victimas;
        cin >> fecha >> victimas;
        bool hay = false;
        while(!accidentesAereos.empty() && accidentesAereos.top().numVictimas <= victimas){ // Mientrasno esté vacío y no hayamos encontrado lo que buscamos
            accidentesAereos.pop();
        }
        if(!accidentesAereos.empty()){
            cout << accidentesAereos.top().fecha<< '\n';
        } else{
            cout << "NO HAY\n";
        }
        accidentesAereos.push({fecha, victimas});
    }
    cout << "---\n";
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    resuelveCaso();
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}