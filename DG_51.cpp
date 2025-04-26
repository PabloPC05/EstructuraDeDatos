#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <utility>
#include <limits>
#include <fstream>

using namespace std;

enum class Direccion { Norte, Sur, Este, Oeste };

class Desierto {
private:
    // Mantenimiento básico
    std::map<std::string, std::pair<int,int>> nombre_a_pos;
    std::map<std::pair<int,int>, std::string> pos_a_nombre;

    // Índices por columna (x) y por fila (y)
    std::unordered_map<int, std::map<int, std::string>> torres_por_x;
    std::unordered_map<int, std::map<int, std::string>> torres_por_y;

public:
    void anyadir_torre(const std::string &nombre, int x, int y) {
        if (nombre_a_pos.count(nombre))
            throw std::domain_error("Torre ya existente");
        if (pos_a_nombre.count({x,y}))
            throw std::domain_error("Posicion ocupada");

        nombre_a_pos[nombre] = {x,y};
        pos_a_nombre[{x,y}] = nombre;
        torres_por_x[x][y] = nombre;
        torres_por_y[y][x] = nombre;
    }

    void eliminar_torre(const std::string &nombre) {
        auto it = nombre_a_pos.find(nombre);
        if (it == nombre_a_pos.end())
            throw std::domain_error("Torre no existente");

        int x = it->second.first, y = it->second.second;
        nombre_a_pos.erase(it);
        pos_a_nombre.erase({x,y});
        torres_por_x[x].erase(y);
        if (torres_por_x[x].empty()) torres_por_x.erase(x);
        torres_por_y[y].erase(x);
        if (torres_por_y[y].empty()) torres_por_y.erase(y);
    }

    std::pair<int,int> posicion(const std::string &nombre) const {
        auto it = nombre_a_pos.find(nombre);
        if (it == nombre_a_pos.end())
            throw std::domain_error("Torre no existente");
        return it->second;
    }

    std::pair<bool,std::string> torre_en_posicion(int x, int y) const {
        auto it = pos_a_nombre.find({x,y});
        if (it == pos_a_nombre.end())
            return {false, ""};
        return {true, it->second};
    }

    std::string torre_mas_cercana(const std::string &nombre, Direccion dir) const {
        auto it = nombre_a_pos.find(nombre);
        if (it == nombre_a_pos.end())
            throw std::domain_error("Torre no existente");

        int x = it->second.first, y = it->second.second;
        const auto &col = torres_por_x.at(x);
        const auto &fil = torres_por_y.at(y);
        std::string resultado;
        
        switch (dir) {
            case Direccion::Norte: {
                // misma x, y2 > y → buscar primer y2 > y
                auto iter = col.upper_bound(y);
                if (iter == col.end()) break;
                resultado = iter->second;
                break;
            }
            case Direccion::Sur: {
                // misma x, y2 < y → buscar primer y2 >= y y retroceder
                auto iter = col.lower_bound(y); // 
                if (iter == col.begin()) break;
                --iter;
                resultado = iter->second;
                break;
            }
            case Direccion::Este: {
                // misma y, x2 > x
                auto iter = fil.upper_bound(x);
                if (iter == fil.end()) break;
                resultado = iter->second;
                break;
            }
            case Direccion::Oeste: {
                // misma y, x2 < x
                auto iter = fil.lower_bound(x);
                if (iter == fil.begin()) break;
                --iter;
                resultado = iter->second;
                break;
            }
        }
        if (resultado.empty())
            throw std::domain_error("No hay torres en esa direccion");
        return resultado;
    }
};


bool resuelveCaso(){
    string orden; 
    cin >> orden; 
    if(!cin) return false; 
    Desierto desierto;
    while(orden != "FIN"){
        try{
            if(orden == "anyadir_torre"){
                string nombre; 
                int x, y; 
                cin >> nombre >> x >> y; 
                desierto.anyadir_torre(nombre, x, y); 
            } else if(orden == "eliminar_torre"){
                string nombre; 
                cin >> nombre; 
                desierto.eliminar_torre(nombre); 
            } else if(orden == "posicion"){
                string nombre; 
                cin >> nombre; 
                auto posicion = desierto.posicion(nombre); 
                cout << posicion.first << " " << posicion.second << '\n';
            } else if(orden == "torre_en_posicion"){
                int x, y; 
                cin >> x >> y; 
                auto torre = desierto.torre_en_posicion(x, y); 
                if(torre.first) cout << "SI " << torre.second << '\n'; 
                else cout << "NO\n";
            } else if(orden == "torre_mas_cercana"){
                string nombre;
                string dir; 
                cin >> nombre >> dir; 
                Direccion direccion;
                if(dir == "Norte") direccion = Direccion::Norte; 
                else if(dir == "Sur") direccion = Direccion::Sur; 
                else if(dir == "Este") direccion = Direccion::Este; 
                else if(dir == "Oeste") direccion = Direccion::Oeste;
                string torre = desierto.torre_mas_cercana(nombre, direccion);
                cout << torre << '\n';
            }
        } catch(domain_error& e){
            cout << e.what() << endl; 
        }
        cin >> orden;
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