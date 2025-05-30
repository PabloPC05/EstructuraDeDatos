#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set> 
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <stack>
using namespace std;


bool resuelveCaso() {
    int N;
    cin >> N;
    if(!cin) return false;
    unordered_map<string, vector<int>> juegos;
    for(int i = 0; i < N; i++){
        string juego;
        cin >> juego;
        juegos[juego].push_back(i);
    }
    int M; 
    cin >> M;
    for(int i = 0; i < M; i++){
        int k; 
        cin >> k;
        string juego;
        cin >> juego;
        if(juegos.count(juego) && juegos[juego].size() >= k){
            cout << juegos[juego][k-1]+1 << '\n';
        } else cout << "NO JUEGA\n";
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