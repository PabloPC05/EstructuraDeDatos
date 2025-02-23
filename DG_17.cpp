#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "dequeue.h"
using namespace std;
using deque = Dequeue<char>;

bool esVocal(char c){
    c = std::tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool resuelveCaso(){
    string str, result;
    getline(cin, str);
    if(!cin) return false;
    deque d;
    // Resolveremos la primera encriptacion a la vez que creamos la deque
    // Invertimos la cadena y vamos metiendo los caracteres en la deque
    reverse(str.begin(), str.end());
    int N = str.size();
    bool alternada = (N % 2 == 0); // Empieza en push_back si el tamaño es par, push_front si es impar
    for (char c : str) {
        if (alternada) {
            d.push_back(c);
        } else {
            d.push_front(c);
        }
        alternada = !alternada;
    }
    // Ahora vamos a hacer la segunda encriptacion
    // Mientras la cola no esté vacía
    /*while(!d.empty()){
        // Sacamos el primer caracter
        char c = d.front();
        d.pop_front();
        string aux = "";
        result += c; 
        if(esVocal(c)){
            while(!d.empty() && !esVocal(d.front())){
                aux += d.front();
                d.pop_front();
            }
            reverse(aux.begin(), aux.end());
            result += aux;
        }
    }*/
    string aux;
    while(!d.empty()){
        char c = d.front();
        if(esVocal(c)){
            reverse(aux.begin(), aux.end());
            result += aux;
            result += c;
            aux.clear();
        }
        else{
            aux += c;
        }
        d.pop_front();
    }
    reverse(aux.begin(), aux.end());
    result += aux;
    cout << result << '\n';
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
    