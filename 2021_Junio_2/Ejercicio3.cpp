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
using plantas = int;

class hospital {
    private:
        unordered_map<sector, plantas> sectores;
        unordered_map<sector, map<plaga, plantas>> plagas_map;
        vector<pair<sector, plaga>> a_fumigar;
    public:
        void alta(const sector& id, const plantas& n){
            sectores[id] += n;
        }

        void datos(const sector& id, const plaga& p, const plantas& n){
            if(!sectores.count(id)) throw domain_error("Sector no existente");
            if(n > sectores[id]) throw domain_error("Numero de plantas incorrecto");
            plagas_map[id][p] = n;
            if(plagas_map[id][p] >= sectores[id]/4) a_fumigar.push_back(make_pair(id, p));
        }

        vector<pair<sector,plaga>> fumigar(){
            vector<pair<sector,plaga>> result = a_fumigar;
            for(auto [sector, plaga] : a_fumigar){
                plagas_map[sector][plaga] = 0;
            }
            a_fumigar.clear();
            return result;
        }

        vector<pair<plaga,plantas>> plagas(const sector& id){
            if(!sectores.count(id)) throw domain_error("Sector no existente");
            vector<pair<plaga,plantas>> result;
            for(auto [plaga, plantas] : plagas_map[id]){
                result.push_back(make_pair(plaga, plantas));
            }
            return result;
        }

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
            if(op == "alta"){
                sector id;
                plantas n;
                cin >> id >> n;
                h.alta(id, n);
            } else if(op == "datos"){
                sector id;
                plaga p;
                plantas n;
                cin >> id >> p >> n;
                h.datos(id, p, n);
            } else if(op == "fumigar"){
                auto result = h.fumigar();
                for(auto [sector, plaga] : result){
                    cout << "Fumigar la plaga " << plaga << " del sector " << sector << '\n';
                }
            } else if(op == "plagas"){
                sector id;
                cin >> id;
                vector<pair<plaga,plantas>> result = h.plagas(id);
                cout << "Plagas del sector " << id << " : ";
                for(const auto& [plaga, plantas] : result){
                    cout << plaga << " " << plantas << " ";
                }
                cout << '\n';
            }
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