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
#include <list>
using namespace std;

void reconstruir(list<int>& lista){
    stack<int> numeros_positivos;
    auto it = lista.begin();
    while (it != lista.end()) {
        if (*it > 0) {
            numeros_positivos.push(*it);
            ++it;
        } else if (*it == 0) {
            *it = -numeros_positivos.top();
            numeros_positivos.pop();
            ++it;
        } else { // Si es un número negativo
            if (!numeros_positivos.empty()) {
                if (*it != -numeros_positivos.top()) {
                    *it = -numeros_positivos.top();
                    ++it;
                    numeros_positivos.pop();
                } else {
                    numeros_positivos.pop();
                    ++it;
                }
            } else {
                it = lista.erase(it); // erase devuelve el siguiente iterador válido
            }
        }
    }
    while (!numeros_positivos.empty()) {
        lista.push_back(-numeros_positivos.top());
        numeros_positivos.pop();
    }
}

bool resuelveCaso() {
    int numElem;
    cin >> numElem;
    if(!cin) return false;
    list<int> lista;
    while(numElem--){
        int n;
        cin >> n;
        lista.push_back(n);
    }
    reconstruir(lista);
    for(const int& elem : lista){
        cout << elem << ' ';
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