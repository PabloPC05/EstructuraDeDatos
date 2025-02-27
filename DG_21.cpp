#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
using namespace std;


bool resuelveCaso() {
    string line; 
    // leemos la linea
    getline(cin, line);
    if (!cin) return false;
    deque<char> inputDeque(line.begin(), line.end());
    deque<char> coutLine;
    auto j = coutLine.end();
    while (!inputDeque.empty()) {
        char current = inputDeque.front();
        inputDeque.pop_front();

        if (current == '+') {
            j = coutLine.end();
        }
        else if (current == '-') {
            j = coutLine.begin();
        }
        else if (current == '3') {
            if (j != coutLine.end()) {
                j = coutLine.erase(j);
            }
        }
        else if (current == '*') {
            if (j != coutLine.end()) {
                ++j;
            }
        }
        else {
            j = coutLine.insert(j, current);
            ++j;
        }
    }
    for(const char& c : coutLine) {
        cout << c;
    }
    cout << '\n';
    return true;
}


//Correccion
/*
    bool resuelveCaso(){
    string line; 
    getline(line, cin);
    if(!cin) return false;
    list<char> l;
    auto it = l.end();
    for(char c : line){
    switch(c){
        case '+':
            it = l.end();
            break;
        case '-':
            it = l.begin();
            break;
        case '*':
            if(it != l.end()) ++it;
            break;
        case '3':
            if(it != l.end()) it = l.erase(it);
            break;
        default:
            it = l.insert(it, c);
            ++it;
    }
    return true; 
    }
*/

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
    