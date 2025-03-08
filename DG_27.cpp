#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;



/*
* La implementacion de esta función se basa en que recorremos, por ejemlo toda la rama izquierda y para calcular el maximo de excursionistas
* llamamos a la funcion derecha y calculamos el maximo de las dos
*/
pair<int, int> resolver(BinTree<int> const& t) {
    if (t.empty()) return {0, 0}; // Árbol vacío

    // Llamadas recursivas a las sub-rutas izquierda y derecha
    pair<int, int> left = resolver(t.left());
    pair<int, int> right = resolver(t.right());

    // Máximo número de excursionistas rescatados en una ruta
    int maxRescatados = max(left.second, right.second) + t.root();

    // Contar los equipos de rescate
    int equipos = left.first + right.first;
    if (t.root() > 0 && left.second == 0 && right.second == 0) {
        equipos++; // Se necesita un nuevo equipo de rescate
    }

    return {equipos, maxRescatados};
}



void resuelveCaso(){
    BinTree<int> t = read_tree<int>(cin);
    pair<int, int> sol = resolver(t);
    cout << sol.first << " " << sol.second << endl;
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos;
    cin >> numCasos;
    while(numCasos--){ resuelveCaso();}
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    
    return 0;
}
    