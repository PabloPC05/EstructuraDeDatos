#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

bool resuelveCaso() {
    int N;
    cin >> N; 
    cin.ignore();
    if(N == 0) return false;
    unordered_map<int, vector<string>> numero_jugadores; 
    unordered_map<string, int> jugadores_nums_carton; // Mapa para contar el numero de numeros del carton de cada jugador
    // Leemos los jugadores y sus numeros asociando a cada numero el conjunto de jugadores que lo tienen
    for(int i = 0; i < N; i++){
        string nombre;
        cin >> nombre;
        int numero;
        int total = 0;
        while(cin >> numero && numero != 0){
            numero_jugadores[numero].push_back(nombre);
            total++;
        }
        jugadores_nums_carton[nombre] = total; // Guardamos el total de numeros de cada jugador
    }


    int num_bingo;
    vector<string> jugadores; 
    bool exit = false; 


    while(!exit && cin >> num_bingo){ // Leemos los numeros del bingo
        for(const auto& jugador : numero_jugadores[num_bingo]){ // Para cada jugador que tiene ese numero
            int nums = jugadores_nums_carton[jugador] -1 ; // Obtenemos el total de numeros del jugador
            if(nums == 0){ // Si el jugador ha acertado todos los numeros
                jugadores.push_back(jugador); // Añadimos el jugador a la lista de ganadores
                exit = true;   // Una vez ha ganado un o unos jugdores, el juego termina
            }
            jugadores_nums_carton[jugador] = nums; // Actualizamos el mapa de jugadores
        }
        if(exit){
            string discard; 
            getline(cin, discard); // Limpiamos el buffer de entrada
        }
    }

    sort(jugadores.begin(), jugadores.end()); // Ordenamos los jugadores alfabéticamente
    for (size_t i = 0; i < jugadores.size(); ++i) {
        if (i > 0) cout << " ";
        cout << jugadores[i];
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