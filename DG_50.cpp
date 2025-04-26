#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <list>
using namespace std;

const string funciones[] = {"nuevo", "quitar", "consultar", "cuantos_con_puntos"}; // Funciones que se pueden llamar


class CarnetPuntos{
    private: 
        unordered_map<string, int> conductor_puntos;
        vector<int> num_conductores_con_puntos;
        unordered_map<int, list<string>> lista_conductores_por_puntos; 
        unordered_map<string, list<string>::iterator> posicion_en_lista; 
        
    public: 
        CarnetPuntos() : num_conductores_con_puntos(16, 0) { // Inicializa el vector de contadores de conductores con puntos
            for(int i = 0; i <= 15; ++i) {
                lista_conductores_por_puntos[i] = list<string>(); // Inicializa la lista de conductores por puntos
            }
        }
        
        void nuevo(const string& dni){
            if(conductor_puntos.count(dni)) throw domain_error("Conductor duplicado");
            conductor_puntos[dni] = 15; // Se añade el nuevo conductor con 15 puntos
            num_conductores_con_puntos[15]++; // Se incrementa el número de conductores con 15 puntos
            lista_conductores_por_puntos[15].push_front(dni); 
            posicion_en_lista[dni] = lista_conductores_por_puntos[15].begin(); 
        }

        void quitar(const string& dni, const int& puntos){
            auto it = conductor_puntos.find(dni);
            if(it == conductor_puntos.end()) throw domain_error("Conductor inexistente");
            int nuevos_puntos = max(0, it->second - puntos);
            if(nuevos_puntos == it->second) return; // Si los nuevos puntos son iguales a los actuales, no se hace nada
            int& pts = it->second;
            num_conductores_con_puntos[pts]--;
            lista_conductores_por_puntos[pts].erase(posicion_en_lista[dni]); 
            num_conductores_con_puntos[nuevos_puntos]++; 
            lista_conductores_por_puntos[nuevos_puntos].push_front(dni); // Se añade el dni a la lista de conductores con esos puntos
            posicion_en_lista[dni] = lista_conductores_por_puntos[nuevos_puntos].begin(); 
            pts = nuevos_puntos; 
        }

        void recuperar(const string& dni, const int& puntos){
            auto it = conductor_puntos.find(dni);
            if(it == conductor_puntos.end()) throw domain_error("Conductor inexistente");
            int nuevos_puntos = min(15, it->second + puntos);
            if(nuevos_puntos == it->second) return; 
            int& pts = it->second;
            num_conductores_con_puntos[pts]--;
            lista_conductores_por_puntos[pts].erase(posicion_en_lista[dni]); 
            num_conductores_con_puntos[nuevos_puntos]++;   
            lista_conductores_por_puntos[nuevos_puntos].push_front(dni); 
            posicion_en_lista[dni] = lista_conductores_por_puntos[nuevos_puntos].begin(); 
            pts = nuevos_puntos; 
        }

        int consultar(const string& dni) const {
            auto it = conductor_puntos.find(dni);
            if(it == conductor_puntos.end()) throw domain_error("Conductor inexistente");
            return it->second; // Se devuelve el número de puntos del conductor
        }

        int cuantos_con_puntos(const int& puntos) const {
            if(puntos < 0 || puntos > 15) throw domain_error("Puntos no validos");
            return num_conductores_con_puntos[puntos];
        }

        const list<string>& lista_por_puntos(const int& puntos) const {
            if(puntos < 0 || puntos > 15) throw domain_error("Puntos no validos");
            return lista_conductores_por_puntos.at(puntos); 
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
            } else if(funcion == "lista_por_puntos") {
                int puntos; 
                cin >> puntos; 
                auto lista = sistema.lista_por_puntos(puntos);
                cout << "Tienen " << puntos << " puntos: ";
                for(const auto& dni : lista) {
                    cout << dni << " ";
                }
                cout << '\n';
            } else if(funcion == "recuperar") {
                std::string dni;
                int puntos;
                std::cin >> dni >> puntos;
                sistema.recuperar(dni, puntos);
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