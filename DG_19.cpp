#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>
#include <queue>
using namespace std;

bool resuelveCaso(){
    int N, K; 
    cin >> N >> K; 
    if(!cin) return false;
    deque<pair<int, int>> maximos;
    int elem; 
    cin >> elem;
    maximos.push_back({elem, 0});
    for(int i = 1; i < K; i++){
        cin >> elem;
        // Si el nuevo elemento leido es mayor que el maximo actual,
        // se borran todos los elementos que se habian añadido hasta el momento 
        // y se añade el nuevo
        if(maximos.front().first < elem ){
            maximos.clear();
            maximos.push_back({elem, i});
        // Si el nuevo elemento leido es menor que el maximo actual
        // Se eliminan todos los elementos que sean menores que el nuevo
        // y se añade el nuevo
        } else {
            while(!maximos.empty() && maximos.back().first < elem){
                maximos.pop_back();
            }
            maximos.push_back({elem, i});
        }
    }
    cout << maximos.front().first << " ";
    for(int i = K; i < N; i++){
        cin >> elem;
        if(maximos.front().first < elem ){
            maximos.clear();
            maximos.push_back({elem, i});
        } else {
            while(!maximos.empty() && maximos.back().first < elem){
                maximos.pop_back();
            }
            maximos.push_back({elem, i});
        }
        if(maximos.front().second <= i - K){
            maximos.pop_front();
        }
        cout << maximos.front().first << " ";
    }
    cout << endl;
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
    // Descomentar si se necesita
    // system("PAUSE");
    #endif
    
    return 0;
}
    