/*********************************************************************** *
 * Prepara el resto de tus asignaturas y aprueba todos los exámenes
 * finales con PROXUS!
 *
 * Todos los SPEEDRUNS disponibles:
 * https://www.proxusacademy.com
 *
 * Creado por PROXUS Academy
 ***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>
#include <queue>
#include <set>
#include <map>
using namespace std;

using plaga = std::string;
using sector = string;

class hospital {


};

// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso() {
    hospital h;
    std::string op;
    std::cin >> op;

    if (!std::cin)return false;

    while (op != "FIN") {
        try {

        } catch (std::domain_error &e) {
            std::cout << "ERROR: " << e.what() << "\n";
        }
        std::cin >> op;
    }
    std::cout << "---\n";
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
    system("PAUSE");

#endif
    return 0;
}