#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

const string funciones[] = {"nuevo", "quitar", "consultar", "cuantos_con_puntos"}; // Funciones que se pueden llamar


class CarnetPuntos{
    private: 
        unordered_map<string, int> conductor_puntos;
        vector<int> puntos_conductores;
    public:
        CarnetPuntos() : conductor_puntos(), puntos_conductores(16, 0){}
        void nuevo(const string& nombre){ // Aáde un nuevo conductor identificado por su DNi y si el coductor ya existe lanza la excepcion domain_error con mensaje "Conductor duplicado"
            if(conductor_puntos.count(nombre)){
                throw domain_error("Conductor duplicado");
            }
            conductor_puntos[nombre] = 15;
            puntos_conductores[15]++;
        }

        void quitar(const string& dni, const int& puntos){
            auto it = conductor_puntos.find(dni);
            if(it == conductor_puntos.end()){
                throw domain_error("Conductor inexistente");
            }
            int& pts = it->second;
            puntos_conductores[pts]--; // Se decrementa el contador de conductores con esos puntos
            pts = max(0, pts - puntos); // Se le quitan los puntos al conductor
            puntos_conductores[pts]++; // Se incrementa el contador de conductores con esos puntos
        }

        int consultar(const string& dni) const{
            auto it = conductor_puntos.find(dni);
            if(it == conductor_puntos.end()){
                throw domain_error("Conductor inexistente");
            }
            return it->second; 
        }

        int cuantos_con_puntos(const int& puntos) const{
            if(puntos < 0 || puntos > 15){
                throw domain_error("Puntos no validos");
            }
            return puntos_conductores[puntos]; // Se devuelve el contador de conductores con esos puntos
        }
};

bool resuelveCaso(){
    string funcion; 
    cin >> funcion; 
    if(!std::cin) return false; // Fin de la entrada
    CarnetPuntos sistema;
    while(funcion != "FIN"){    
        try {
            if (funcion == "nuevo") {
                std::string dni;
                std::cin >> dni;
                sistema.nuevo(dni);
            } else if (funcion == "quitar") {
                std::string dni;
                int puntos;
                std::cin >> dni >> puntos;
                sistema.quitar(dni, puntos);
            } else if (funcion == "consultar") {
                std::string dni;
                std::cin >> dni;
                int puntos = sistema.consultar(dni);
                std::cout << "Puntos de " << dni << ": " << puntos << '\n';
            } else if (funcion == "cuantos_con_puntos") {
                int puntos;
                std::cin >> puntos;
                int num_conductores = sistema.cuantos_con_puntos(puntos);
                std::cout << "Con " << puntos << " puntos hay " << num_conductores << '\n';
            }
        } catch (const std::domain_error& e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        cin >> funcion;
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