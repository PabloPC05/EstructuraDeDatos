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

class Tienda {
    private:
        unordered_map<string, int> producto_cantidades; 
        unordered_map<string, list<tDia>> producto_fecha;
        unordered_map<string, list<string>> producto_lista_espera;
    public: 
        list<string> adquirir(const string& cod, const tDia& fecha, const int& cant) {
            list<string> atendidos;
            int disponibles = cant;
        
            // Atiende a los clientes en espera
            while (disponibles > 0 && !producto_lista_espera[cod].empty()) {
                atendidos.push_back(producto_lista_espera[cod].front());
                producto_lista_espera[cod].pop_front();
                disponibles--;
            }
        
            // Si sobran unidades, se guardan en el almacén
            if (disponibles > 0) {
                producto_cantidades[cod] += disponibles;
                for (int i = 0; i < disponibles; ++i) {
                    producto_fecha[cod].push_back(fecha);
                }
            }
        
            return atendidos;
        }

        pair<bool, tDia> vender(const string& cod, const string& cliente){
            if(producto_cantidades.count(cod) && producto_cantidades.at(cod) > 0){    // Si hay stock suficiente para comprar 
                return {true, producto_fecha.at(cod).back()};
            } else{
                producto_lista_espera[cod].push_back(cliente);
                //producto_lista_espera.at(cod).push_back(cliente); // Añadimos al cliente al final dela lista de espera
                return {false, tDia()}; // Return a default-constructed tDia object
            }
        }

        int cuantos(const string& cod){
            if(producto_cantidades.count(cod)) return producto_cantidades.at(cod);
            return 0;
        }

        bool hay_esperando(const string& cod){
            return producto_lista_espera.count(cod) && !producto_lista_espera.at(cod).empty(); 
        }
};

bool resuelveCaso() {
    if(!cin) return false; 
    Tienda tienda;
    string orden;
    string linea; 
    while(getline(cin, linea)){
        istringstream ss(linea);
        ss >> orden;
        ss.ignore();
        if(orden == "FIN") break;
        if(orden == "adquirir"){
            string prod;
            tDia fecha;
            int cant;
            ss >> prod >> fecha >> cant;
            list<string> list = tienda.adquirir(prod, fecha, cant);
            cout << "PRODUCTO ADQUIRIDO ";
            for(string s : list){
                cout << s << " ";
            }
            cout <<'\n';
        } else if(orden == "vender"){
            string prod;
            string cliente;
            ss >> prod >> cliente; 
            auto result = tienda.vender(prod, cliente);
            if(result.first){
                cout << "VENDIDO "<< result.second << '\n';
            } else{
                cout << "EN ESPERA\n"; 
            }
        } else if(orden == "cuantos"){
            string prod;
            ss >> prod; 
            cout << tienda.cuantos(prod) << '\n';
        } else if(orden == "hay_esperando"){
            string prod;
            ss >> prod; 
            if(tienda.hay_esperando(prod)) cout << "SI\n"; 
            else cout<< "NO\n"; 
        }
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