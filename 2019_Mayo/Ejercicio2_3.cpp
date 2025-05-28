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

class Outlet {
    private:
        unordered_map<string, int> producto_cantidad;
        unordered_map<string, list<string>> producto_lista_espera;
        unordered_map<string, unordered_map<string, list<string>::iterator>> cliente_producto_iterador;
        map<string, int> producto_ventas;

    public: 
        void an_oferta(const string& producto, const int& num_unidades){
            if(num_unidades <= 0){
                throw out_of_range("Unidades negativas");
            }
            auto it = producto_cantidad.find(producto);
            if(it != producto_cantidad.end()){ // si el prducto ya existía
                throw domain_error("Producto ya existente");
            }
            producto_cantidad[producto] = num_unidades;
        }

        void pon_en_espera(const string& cliente, const string& producto){
            if(!producto_cantidad.count(producto)){
                throw domain_error("El producto no está en oferta");
            }
            if(cliente_producto_iterador.count(cliente) && cliente_producto_iterador[cliente].count(producto)) return;
            producto_lista_espera[producto].push_back(cliente);
            auto it = --producto_lista_espera[producto].end();
            cliente_producto_iterador[cliente][producto] = it;
        }

        void cancela_espera(const string& cliente, const string& producto){
            if (!cliente_producto_iterador.count(cliente) || !cliente_producto_iterador[cliente].count(producto)) return;
            auto it = cliente_producto_iterador[cliente][producto];
            producto_lista_espera[producto].erase(it);
            cliente_producto_iterador[cliente].erase(producto);
            if (cliente_producto_iterador[cliente].empty()) {
                cliente_producto_iterador.erase(cliente);
            }
        }

        int num_en_espera(const string& producto){
            return producto_lista_espera[producto].size();
        }

        void venta(const string& producto, const int& num_unidades){
            if(!producto_cantidad.count(producto) || producto_lista_espera.at(producto).empty() || producto_cantidad[producto] < num_unidades){
                throw domain_error("Error en la venta de un prodcto");
            }

            string cliente = producto_lista_espera[producto].front();
            producto_lista_espera[producto].pop_front();
            cliente_producto_iterador[cliente].erase(producto);
            if (cliente_producto_iterador[cliente].empty()) cliente_producto_iterador.erase(cliente);

            producto_cantidad[producto] -= num_unidades;
            producto_ventas[producto] += num_unidades;

            if (producto_cantidad[producto] == 0) {
                // Elimina toda la oferta del producto
                // Limpia los iteradores de los clientes que estaban en la lista de espera
                for (const string& c : producto_lista_espera[producto]) {
                    cliente_producto_iterador[c].erase(producto);
                    if (cliente_producto_iterador[c].empty())
                        cliente_producto_iterador.erase(c);
                }
                producto_cantidad.erase(producto);
                producto_lista_espera.erase(producto);
            }
        }

        string primero_en_espera(const string& producto) const{
            if(!producto_cantidad.count(producto) || producto_lista_espera.at(producto).empty()){
                throw domain_error("Error en la lista de espera");
            }
            return producto_lista_espera.at(producto).front();
        }

        list<pair<string, int>> lista_ventas() const {
            list<pair<string, int>> list;
            for(const auto& par : producto_ventas){
                list.push_back(par);
            }
            return list;
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