#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <list>
#include <algorithm>
#include <deque>
#include <unordered_set>

using namespace std;

class Ferrovistan {
    private:
    // lineas[linea_1] = map<posicion, estacion>
    unordered_map<string, map<int, string>> lineas;
    // estaciones[Chamartin] = unordered_map<linea, posicion>
    unordered_map<string, map<string, int>> estaciones;
        
    public:     
        void nueva_linea(const string& nombre){
            if(lineas.count(nombre)) throw invalid_argument("Linea existente");
            lineas[nombre] = {};
        }

        void nueva_estacion(const string& linea, const string& nombre, int posicion){
            auto it = lineas.find(linea);
            if(!lineas.count(linea)) throw domain_error("Linea no existente");
            if(estaciones[nombre].count(linea)) throw domain_error("Estacion duplicada en linea");
            if(lineas[linea].count(posicion)) throw domain_error("Posicion ocupada");
            lineas[linea][posicion] = nombre;
            estaciones[nombre][linea] = posicion;
        }

        void eliminar_estacion(const string& estacion){
            if(!estaciones.count(estacion)) throw invalid_argument("Estacion no existente");
            for(const auto [linea, posicion] : estaciones[estacion]){   // Eliminamos en cada unade las lineas a las que llega la estacion 
                lineas[linea].erase(posicion);
            }
            estaciones.erase(estacion);
        }

        vector<string> lineas_de(const string& estacion) const{
            if(!estaciones.count(estacion)) throw invalid_argument("Estacion no existente");
            vector<string> result;
            auto mEstacion = estaciones.at(estacion);
            for(const auto [linea, posicion] : mEstacion){
                result.push_back(linea);
            }
            return result;
        }

        string proxima_estacion(const string& linea, const string& estacion) const{
            if(!lineas.count(linea)) throw domain_error("Linea no existente");
            if(!estaciones.count(estacion) || !estaciones.at(estacion).count(linea)) throw domain_error("Estacion no existente");
            int posicion_estacion = estaciones.at(estacion).at(linea);
            auto& mLinea = lineas.at(linea);
            auto it = mLinea.upper_bound(posicion_estacion);            
            if(it == mLinea.end()) throw domain_error("Fin de trayecto");
            return it->second;
        }

};

bool resuelveCaso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  Ferrovistan ferrovistan;


  while (operacion != "FIN") {
    try {
        if(operacion == "nueva_linea"){
            string linea;
            cin >> linea;
            ferrovistan.nueva_linea(linea);
        } else if(operacion == "nueva_estacion"){
            string linea, estacion;
            int pos; 
            cin >> linea >> estacion >> pos;
            ferrovistan.nueva_estacion(linea, estacion, pos);
        } else if(operacion == "eliminar_estacion"){
            string estacion;
            cin >> estacion;
            ferrovistan.eliminar_estacion(estacion);
        } else if(operacion == "lineas_de"){
            string estacion;
            cin >> estacion;
            vector<string> result = ferrovistan.lineas_de(estacion);
            cout << "Lineas de " << estacion << ": ";
            for(const string linea : result) cout << linea << ' ';
            cout << '\n';
        } else if(operacion == "proxima_estacion"){
            string linea, estacion;
            cin >> linea >> estacion;
            cout << ferrovistan.proxima_estacion(linea, estacion) <<'\n';
        }
    } catch (exception &e) {
      cout << "ERROR: " << e.what() << "\n";
    }
    cin >> operacion;
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