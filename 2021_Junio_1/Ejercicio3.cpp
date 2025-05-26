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
using namespace std;

using medico = std::string;
using paciente = string;

class hospital {
    private:
        unordered_map<medico, list<paciente>> medicos;
        unordered_map<paciente, set<medico>> pacientes;
        unordered_map<paciente, unordered_map<medico, list<paciente>::iterator>> iteradores;

    public:
    void altaMedico(const medico& medico){
        if(medicos.count(medico)) throw domain_error("Medico existente");
        medicos.emplace(medico, list<paciente>());
    }

    void pedirConsulta(const paciente& paciente, const medico& medico){
        if(!medicos.count(medico)) throw domain_error("Medico inexistente");
        if(pacientes[paciente].count(medico)) throw domain_error("Paciente ya esperando");
        medicos[medico].push_back(paciente);
        iteradores[paciente][medico] = --medicos[medico].end();
        pacientes[paciente].insert(medico);
    }

    paciente siguientePaciente(const medico& medico){
        if(!medicos.count(medico)) throw domain_error("Medico inexistente");
        if(medicos[medico].empty()) throw domain_error("Medico sin pacientes");
        return medicos[medico].front();
    }

    void atenderConsulta(const medico& medico){
        if(!medicos.count(medico)) throw domain_error("Medico inexistente");
        if(medicos[medico].empty()) throw domain_error("Medico sin pacientes");
        paciente paciente = medicos[medico].front();
        medicos[medico].pop_front();
        iteradores[paciente].erase(medico);
        pacientes[paciente].erase(medico);
    }

    vector<medico> abandonarConsulta(const paciente& paciente){
        if(pacientes[paciente].empty()) throw domain_error("Paciente inexistente");
        vector<medico> result;
        set<medico> medicos_del_paciente = pacientes.at(paciente);
        for(const medico& medico : medicos_del_paciente){ // Por cada uno de los pacientes del paciente
            result.push_back(medico);
            auto it = iteradores[paciente][medico];
            medicos[medico].erase(it);
        }
        return result;
    }

};

// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso() {
    hospital h;
    std::string op;
    std::cin >> op;

    if (!std::cin)return false;

    while (op != "FIN") {
        try {
            if(op == "altaMedico"){
                medico med;
                cin >> med;
                h.altaMedico(med);
            } else if(op == "pedirConsulta"){
                paciente pa;
                medico med;
                cin >> pa >> med;
                h.pedirConsulta(pa, med);
            } else if(op == "siguientePaciente"){
                medico med;
                cin >> med;
                paciente paciente = h.siguientePaciente(med);
                cout << paciente << '\n';
            } else if(op == "abandonarConsulta"){
                paciente paciente;
                cin >> paciente;
                vector<string> result = h.abandonarConsulta(paciente);
                cout << "Medicos abandonados: ";
                for(const medico& med : result) cout << med << ' ';
                cout << '\n';
            } else if(op == "atenderConsulta"){
                medico med;
                cin >> med;
                h.atenderConsulta(med);
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