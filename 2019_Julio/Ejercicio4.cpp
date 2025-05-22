#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set> 
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <list>
#include <algorithm>
#include "tDia.h"
using namespace std;

class GestorSurtidores {
    private:
        unordered_map<string, unordered_map<string, int>> surtidor_combustible_cantidad;
        unordered_map<string, list<string>> surtidor_vehiculos_en_espera;
        unordered_map<string, list<string>::iterator> vehiculo_iterador; 
        unordered_map<string, string> vehiculo_surtidor;


    public: 
        void an_surtidor(const string& id_surtidor) {
            // Si el surtidor ya existe, lanzamos excepción
            if (surtidor_combustible_cantidad.count(id_surtidor))
                throw domain_error("ESurtidorDuplicado");
            // Creamos la entrada para el surtidor en ambos mapas
            surtidor_combustible_cantidad[id_surtidor] = unordered_map<string, int>();
            surtidor_vehiculos_en_espera[id_surtidor] = list<string>();
        }

        void carga(const string& id_surtidor, const string& tipo_combustible, const int& num_litros){
            auto it = surtidor_combustible_cantidad.find(id_surtidor);
            if(it == surtidor_combustible_cantidad.end()){
                throw domain_error("El surtidor no existe");
            }
            it->second[tipo_combustible] = num_litros;
        }

        void pon_en_espera(const string& id_vehiculo, const string& id_surtidor){
            auto it = surtidor_vehiculos_en_espera.find(id_surtidor);
            if(it == surtidor_vehiculos_en_espera.end()){
                throw domain_error("El surtidor no existe");
            }
            auto it_insertado = it->second.insert(it->second.end(), id_vehiculo);
            vehiculo_iterador[id_vehiculo] = it_insertado;
            vehiculo_surtidor[id_vehiculo] = id_surtidor;
        }

        pair<string, int> vende(const string& id_surtidor, const string& tipo_combustible, const int& num_litros){
            if(num_litros <= 0 ||
                !surtidor_combustible_cantidad.count(id_surtidor) || 
                surtidor_combustible_cantidad[id_surtidor][tipo_combustible] < num_litros ||
                surtidor_vehiculos_en_espera[id_surtidor].empty()){
                throw domain_error("Error en la venta");
            }
            string vehicle = surtidor_vehiculos_en_espera[id_surtidor].front();
            abandona(vehicle);
            surtidor_combustible_cantidad[id_surtidor][tipo_combustible] -= num_litros;
            return {vehicle, surtidor_combustible_cantidad[id_surtidor][tipo_combustible]};
        }

    void abandona(const string& id_vehiculo) {
        if(vehiculo_surtidor.count(id_vehiculo)){ // Si el vehiculo está en la lista de espera
            string id_surtidor = vehiculo_surtidor[id_vehiculo];
            auto it = vehiculo_iterador[id_vehiculo];
            surtidor_vehiculos_en_espera[id_surtidor].erase(it); // Lo eliminamos de la lista de espera
            vehiculo_surtidor.erase(id_vehiculo); // Lo eliminamos de la lista
            vehiculo_iterador.erase(id_vehiculo); // lo eliminamos del mapa de iteradores
        }   
    }
};

bool resuelveCaso() {

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