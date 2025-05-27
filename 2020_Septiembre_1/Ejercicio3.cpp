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
#include <unordered_set>
using namespace std;


struct infoEquipo{
    list<string> ciclistas;
    int puntuacion;
    int top3;
};

struct infoCiclista{
    string equipo;
    int puntuacion;
    list<string>::iterator it;
};

bool resuelveCaso() {
    int numEquipos;
    cin >> numEquipos;
    if(!cin) return false;
    map<string, infoEquipo> equipos;
    unordered_map<string, infoCiclista> ciclistas;
    unordered_map<int, set<string>> descalificaciones;
    pair<string, int> ganador = make_pair("", INT_MAX);
    // Leeemos los datos al inicio
    while(numEquipos--){
        string equipo;
        cin >> equipo;
        int numCiclista;
        cin >> numCiclista;
        while(numCiclista--){
            string ciclista;
            cin >> ciclista;
            equipos[equipo].ciclistas.push_back(ciclista);
            ciclistas[ciclista].equipo = equipo;
            ciclistas[ciclista].it = --equipos[equipo].ciclistas.end();
        }
    }
    int numEtapas;
    cin >> numEtapas;
    for(int i = 0; i < numEtapas; i++){
        // Reiniciamos contador
		for (auto &it : equipos) {
			it.second.top3 = 0;
		}
        int numCiclistas, limite;
        cin >> numCiclistas >> limite;
        for(int j = 0; j < numCiclistas; j++){
            string ciclista;
            int tiempo;
            cin >> ciclista >> tiempo;
            string equipo = ciclistas[ciclista].equipo;
            if(i == numEtapas -1){  // Cuando sea la última ultima etapa calculamos el jugador ganador
                int tiempoAux = ciclistas[ciclista].puntuacion + tiempo;
                if (j == 0) {
					ganador.first = ciclista;
                    ganador.second = tiempoAux;
                }
                if(tiempoAux < ganador.second){ // Si encontramos un tiempo aun menor que otro
                    ganador.first = ciclista;
                    ganador.second = tiempoAux;
                }
            }
            if(tiempo > limite){ // Si el tiempo del jugador es mayor del límite ha de ser descalificado 
                descalificaciones[i+1].insert(ciclista);
                auto it = ciclistas[ciclista].it;
                equipos[equipo].ciclistas.erase(it); // Lo elimnamos del equipo
                ciclistas.erase(ciclista);
            } else{
                auto& it = equipos[equipo];
                if(it.top3 < 3){
                    it.top3++;
                    it.puntuacion += tiempo;
                }
                ciclistas[ciclista].puntuacion += tiempo;
            }
        }
    }
	// MOSTRAMOS RESULTADOR

	bool valid = false;
	for (auto it : equipos) {
		if (it.second.ciclistas.size() > 2) {
			valid = true;
			cout << it.first << " " << it.second.puntuacion << endl;
		}
	}

	if (!valid) cout << "CALIFICACION VACIA" << endl;
	cout << endl;

	// 2
	cout << ganador.second << " " << ganador.first << endl << endl;

	// 3
	for (int i = 0; i < numEtapas; i++) {
		cout << i + 1;
		for (auto &it : descalificaciones[i + 1]) {
			cout << " " << it;
		}
		cout << endl;
	}
	cout << "---" << endl;

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