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
#include <unordered_set>
using namespace std;

using jugador = std::string;
using region = string;
using caballeros = int;

class hospital {
    private:
        set<region> en_disputa;
        unordered_map<region, unordered_map<jugador, caballeros>> regiones;
        unordered_map<jugador, int> puntuaciones;
        unordered_map<region, pair<jugador, caballeros>> predominantes;


    public:
        void anyadir_jugador(const jugador& j){
            if(puntuaciones.count(j)) throw domain_error("Jugador existente");
            puntuaciones[j] = 0;
        }

        void colocar_caballero(const jugador& j, const region& r){
            if(!puntuaciones.count(j)) throw domain_error("Jugador no existente");
            regiones[r][j]++;
            if(!predominantes.count(r)){
                predominantes[r] = make_pair(j, 1);
                puntuaciones[j]++;
            }else{
                auto& jugador_pred = predominantes[r];
                if(jugador_pred.second < regiones[r][j]){ // El jugador que ha colocado el caballero es el nuevo predominante, por lo tanto su puntuacion tambien aumenta y la del anterior diminuye
                    if(en_disputa.count(r)){ // Si laregion estaba en disputa
                        predominantes[r] = make_pair(j, regiones[r][j]);
                        puntuaciones[j]++;
                    } else{
                        puntuaciones[jugador_pred.first]--;
                        jugador_pred.first = j;
                        jugador_pred.second = regiones[r][j];
                        puntuaciones[j]++;
                    }

                } else if(jugador_pred.second == regiones[r][j]){
                    puntuaciones[jugador_pred.first]--;
                    predominantes[r] = make_pair("", 0);
                    en_disputa.insert(r);
                }
            }
        }

        int puntuacion(const jugador& j){
            return puntuaciones.at(j);
        }

        vector<string> regiones_en_disputa(){
            vector<region> result;
            for(const region& r : en_disputa) result.push_back(r);
            return result;
        }

        void expulsar_caballeros(const region& r){
            if(!predominantes.count(r)) throw domain_error("Region vacia");
            auto ex_predominante = predominantes[r];
            puntuaciones[ex_predominante.first]--;
            predominantes.erase(r);
            for(auto& [jugador, caballeros] : regiones.at(r)){
                caballeros = 0;
            }
        }
};

// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso() {
    hospital h;
    std::string op;
    std::cin >> op;

    if (!std::cin) return false;

    while (op != "FIN") {
        try {
            if (op == "anyadir_jugador") {
                std::string j;
                std::cin >> j;
                h.anyadir_jugador(j);
            } else if (op == "colocar_caballero") {
                std::string j, r;
                std::cin >> j >> r;
                h.colocar_caballero(j, r);
            } else if (op == "puntuacion") {
                std::string j;
                std::cin >> j;
                int p = h.puntuacion(j);
                std::cout << "Puntuacion de " << j << ": " << p << "\n";
            } else if (op == "regiones_en_disputa") {
                std::vector<std::string> regiones = h.regiones_en_disputa();
                std::cout << "Regiones en disputa:\n";
                for (const auto& r : regiones) {
                    std::cout << r << "\n";
                }
            } else if (op == "expulsar_caballeros") {
                std::string r;
                std::cin >> r;
                h.expulsar_caballeros(r);
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