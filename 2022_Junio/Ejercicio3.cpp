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
#include <deque>
#include <unordered_set>
#include <map>
using namespace std;

using mesa = int;
using plato = std::string;

class restaurante {

    using t_pedido = list<pair<mesa, plato>>::iterator;
    unordered_map<mesa, map<plato, deque<t_pedido>>> mesas;
    list<pair<mesa, plato>> pedidos;

public:
    restaurante() {}

    void nueva_mesa(int num) { 
        if(mesas.count(num)) throw domain_error("Mesa ocupada");
        mesas.emplace(num, map<plato, deque<t_pedido>>());
    }

    void nuevo_pedido(int mesa, const std::string& plato) { 
        if(!mesas.count(mesa)) throw domain_error("Mesa vacía");
        pedidos.push_back({mesa, plato});
        mesas[mesa][plato].push_back(--pedidos.end());
    }

    void cancelar_pedido(int mesa, const std::string& plato) { 
        if(!mesas.count(mesa)) throw domain_error("Mesa vacía");
        if(mesas[mesa][plato].empty()) throw domain_error("Producto no pedido por la mesa");
        auto it = mesas[mesa][plato].back();
        mesas[mesa][plato].pop_back();
        pedidos.erase(it);
        if(mesas[mesa][plato].empty()){
            mesas[mesa].erase(plato);
        }
    }

    std::pair<int, std::string> servir() { 
        if(pedidos.empty()) throw domain_error("No hay pedidos pendientes");
        auto mesa_plato = pedidos.front();
        pedidos.pop_front();
        mesas[mesa_plato.first][mesa_plato.second].pop_front();
        if(mesas[mesa_plato.first][mesa_plato.second].empty()){
            mesas[mesa_plato.first].erase(mesa_plato.second);
        }
        return mesa_plato;
    }

    std::vector<std::string> que_falta(int mesa) const { 
        vector<string> result;
            for(const auto& plato : mesas.at(mesa)){
                result.push_back(plato.first);
            }
        return result;
    }   
};

// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso() {
    restaurante r;
    std::string op;
    std::cin >> op;

    if (!std::cin)return false;

    while (op != "FIN") {
        try {
            if (op == "nueva_mesa") {
                int num;
                std::cin >> num;
                r.nueva_mesa(num);
            }
            else if (op == "nuevo_pedido") {
                int mesa;
                std::string plato;
                std::cin >> mesa >> plato;
                r.nuevo_pedido(mesa, plato);
            }
            else if (op == "cancelar_pedido") {
                int mesa;
                std::string plato;
                std::cin >> mesa >> plato;
                r.cancelar_pedido(mesa, plato);
            }
            else if (op == "servir") {
                auto [mesa, plato] = r.servir();
                std::cout << plato << ' ' << mesa << '\n';
            }
            else if (op == "que_falta") {
                int mesa;
                std::cin >> mesa;
                std::vector<std::string> sol = r.que_falta(mesa);
                std::cout << "En la mesa " << mesa << " falta:\n";

                if (sol.size() > 0) {
                    std::cout << " " << sol[0] << '\n';

                    for (int i = 1; i < sol.size(); ++i)
                        std::cout << " " << sol[i] << '\n';
                }
            }
        }
        catch (std::domain_error &e) {
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