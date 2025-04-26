#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

class ConteoVotos{
    private: 
        struct tEstado{
            int num_compromisarios; 
            unordered_map<string, int> votos_partidos; // <nombre_partido, num_votos>
            string partido_ganador; // Nombre del partido ganador
            tEstado() : num_compromisarios(0), votos_partidos() {} // Constructor por defecto
            tEstado(int num_compromisarios) : num_compromisarios(num_compromisarios), votos_partidos() {}
        };
        unordered_map<string, tEstado> estados; // <nombre_estado, tEstado>
        unordered_map<string, int> partidos_compromisarios_totales;
    public: 
        ConteoVotos() : estados(){} // Constructor por defecto

        void nuevo_estado(const string& nombre, const int& num_compromisarios){
            if(!estados.count(nombre)){ // Si no lo hemos encontrdo 
                estados[nombre] = tEstado(num_compromisarios); // Lo añadimos
            }
            else throw domain_error("Estado ya existente");
        }

        // Al sumar votos de un partido en un estado actualizamos el maximo de cada estado
        void sumar_votos(const string& estado, const string& partido, const int& num_votos){
            auto it = estados.find(estado); // Buscamos el estado
            if(it != estados.end()){ // Si lo hemos encontrado
                tEstado& estado_actual = it->second; // Tomamos el estado actual
                estado_actual.votos_partidos[partido] += num_votos; // Sumamos los votos al partido
                if(estado_actual.partido_ganador.empty() || estado_actual.votos_partidos[partido] > estado_actual.votos_partidos[estado_actual.partido_ganador]){ // Si el partido es el nuevo ganador
                    if(!estado_actual.partido_ganador.empty()){ 
                        partidos_compromisarios_totales[estado_actual.partido_ganador] -= estado_actual.num_compromisarios; 
                        if(partidos_compromisarios_totales[estado_actual.partido_ganador] == 0) partidos_compromisarios_totales.erase(estado_actual.partido_ganador);
                    }
                    estado_actual.partido_ganador = partido; // Actualizamos el partido ganador
                    partidos_compromisarios_totales[partido] += estado_actual.num_compromisarios; // Sumamos los compromisarios al partido ganador
                }
            }
            else throw domain_error("Estado no encontrado"); // Si no lo hemos encontrado, lanzamos la excepcion
        }

        string ganador_en(const string &estado) const{ // Devuelve el partido ganador en un estado
            auto it = estados.find(estado); // Buscamos el estado
            if(it == estados.end()) throw domain_error("Estado no encontrado"); // Si no lo hemos encontrado, lanzamos la excepcion
            string partido_ganador = it->second.partido_ganador; // Tomamos el partido ganador
            return partido_ganador; // Devolvemos el partido ganador
        }

        vector<pair<string, int>> resultados() const{
            vector<pair<string, int>> resultados(partidos_compromisarios_totales.begin(), partidos_compromisarios_totales.end()); // Creamos un vector de resultados
            sort(resultados.begin(), resultados.end()); 
            return resultados; // Devolvemos el vector de resultados ordenado por nombre de partido
        }
};


bool resuelveCaso(){
    string orden; 
    cin >> orden; 
    if(!std::cin) return false; // Fin de la entrada
    ConteoVotos conteo; // Se crea el conteo de votos
    while(orden != "FIN"){
        try{
            if(orden == "nuevo_estado"){
                string nombre_estado; 
                int num_compromisarios; 
                cin >> nombre_estado >> num_compromisarios; // Leemos el nombre del estado y el numero de compromisarios
                conteo.nuevo_estado(nombre_estado, num_compromisarios); // Añadimos el nuevo estado
            }
            else if(orden == "sumar_votos"){
                string nombre_estado, nombre_partido; 
                int num_votos; 
                cin >> nombre_estado >> nombre_partido >> num_votos; // Leemos el nombre del estado, el nombre del partido y el numero de votos
                conteo.sumar_votos(nombre_estado, nombre_partido, num_votos); // Sumamos los votos al partido
            }
            else if(orden == "ganador_en"){
                string nombre_estado; 
                cin >> nombre_estado; 
                string ganador = conteo.ganador_en(nombre_estado); // Tomamos el partido ganador de un estado
                cout << "Ganador en " << nombre_estado << ": " << ganador << '\n';
            }
            else if(orden == "resultados"){
                vector<pair<string, int>> resultados = conteo.resultados();
                for(const auto& [partido, num_compromisarios] : resultados){ // Por cada partido
                    cout << partido << " " << num_compromisarios << '\n'; // Imprimimos el partido y el numero de compromisarios
                }
            }

        } catch (const domain_error& e){
            cout << e.what() << '\n';
        }
        cin >> orden; // Leemos la proxima orden
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