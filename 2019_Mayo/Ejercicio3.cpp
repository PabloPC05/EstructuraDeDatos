#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set> 
#include <unordered_map>
#include <queue>
#include <stack>
#include <stdexcept>
#include <list>
#include <algorithm>
#include <set>
#include "tDia.h"
using namespace std;

bool resuelveCaso() {
    int numPeliculas; 
    cin >> numPeliculas; 
    if(numPeliculas == 0) return false; 

    unordered_map<string, int> pelicula_num_emisiones;
    unordered_map<string, int> actor_num_apariciones;
    unordered_map<string, unordered_map<string, int>> pelicula_actor_apariciones;
    set<string> peliculas, actores;

    // Leemos los datos 
    for(int i = 0; i < numPeliculas; i++){
        string pelicula;
        int numActores;
        cin >> pelicula >> numActores; 
        peliculas.insert(pelicula);
        for(int i = 0; i < numActores; i++){
            string nombreActor;
            int tiempoActuacion;
            cin >> nombreActor >> tiempoActuacion;
            pelicula_actor_apariciones[pelicula][nombreActor] = tiempoActuacion;
            actores.insert(nombreActor);
        }
        pelicula_num_emisiones[pelicula] = 0;
    }
    int numEmisiones = 0; 
    cin >> numEmisiones;
    for(int i = 0; i < numEmisiones; i++){
        string pelicula;
        cin >> pelicula; 
        pelicula_num_emisiones[pelicula] = pelicula_num_emisiones[pelicula]+1;
    }

    // Calculamos/Actualizamos las veces que han aparecido los actores
    int max_tiempo = 0;
    for(const string& pelicula : peliculas){
        int veces = pelicula_num_emisiones[pelicula];
        for(const auto& kv : pelicula_actor_apariciones[pelicula]){
            actor_num_apariciones[kv.first] += kv.second * veces;
            max_tiempo = max(max_tiempo, actor_num_apariciones[kv.first] );
        }
    }
    
    // Calculamos los actores preferidos
    set<string> ya_añadidos;
    for (const auto& actor : actores) {
        if (actor_num_apariciones[actor] == max_tiempo && !ya_añadidos.count(actor)) {
            ya_añadidos.insert(actor);
        }
    }

    // Calculemos el maximo de los actores
    int max_emisiones = 0;
    string peli_preferida;
    for(const string& peli : peliculas) {
        if(pelicula_num_emisiones[peli] > max_emisiones || (pelicula_num_emisiones[peli] == max_emisiones && peli_preferida.empty())) {
            max_emisiones = pelicula_num_emisiones[peli];
            peli_preferida = peli;
        }
    }

    cout << max_emisiones  << ' ' << peli_preferida << '\n';

    cout << max_tiempo << " ";
    for (const auto& actor : ya_añadidos) {
        cout << actor << " ";
    }
    cout << '\n';

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