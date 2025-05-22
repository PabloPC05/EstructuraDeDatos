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

int comprobar_whitesmiths(list<pair<int,char>> programa){
    int returnValue = 0;
    stack<int> pila; 
    if(programa.front().first != 0) return 1;
    pila.push(0);
    int i = 1;
    for(const auto& p : programa){
        if(p.second == '{'){
            if(p.first <= pila.top()) return i; 
            pila.push(p.first);
        } else if(p.second == '}'){
            if(p.first != pila.top()) return i;
            pila.pop();
        } else if(p.first != pila.top()) return i;
        i++;
    }
    return -1;
}

bool resuelveCaso() {
    int numLineas; 
    cin >> numLineas;
    if(numLineas == 0) return false;
    cin.ignore();
    list<pair<int, char>> list;
    for(int i = 0; i < numLineas; i++){
        string linea; 
        getline(cin, linea);
        int indentacion = 0; 
        char c;
        for(const char cx : linea){
            if(cx != ' '){c = cx; break;}
            indentacion++;
        }
        list.push_back(make_pair(indentacion, c));
    }
    cout << comprobar_whitesmiths(list) << '\n';
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