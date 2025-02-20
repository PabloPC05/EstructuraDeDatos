#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "stack_linkedlist.h"
using namespace std;

bool estaEquilibrada(string str){
    if(str.empty()) return true;
    StackLinkedList<char> stack;
    int n = str.size(), i = 0; 
    bool equilibrada = false; 
    for(char c : str){
        // Si el caracter es de abertura
        if(c == '(' || c == '[' || c == '{'){
            stack.push(c); // Lo metemos en la pila
        }
        // Si el caracter es de cierre
        else if((c == ']' || c == '}' || c == ')')){
            // si la pila esta vacia pero hay uno de salida, no esta equilibrada
            if(stack.empty()) return false;
            char tope = stack.top();
            // Si el tope de la pila es el caracter de abertura correspondiente
            if ((c == ')' && tope == '(') || (c == ']' && tope == '[') || (c == '}' && tope == '{')) {
                stack.pop();
            }
            else return false;
        }
    }
    // Si la pila está vacía al final, está equilibrada
    return stack.empty();
}

bool resuelveCaso(){
    string line; 
    getline(cin, line);
    if(!cin) return false; 
    if(estaEquilibrada(line)) cout << "SI" << endl;
    else cout << "NO" << endl;
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
    