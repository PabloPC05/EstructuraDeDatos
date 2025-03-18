#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;

bool esPrimo(const int& n){
    if(n == 1) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i*i <= n; i+=2){
        if(n % i == 0) return false;
    }
    return true;
}
    

// Devolvemos el nodo múltiplo de 7 que se encuentra a menor profundidad y que en su camino a la raiz no tiene ningun numero primo
void busqueda(const BinTree<int>& arbol, bool& encontrado, int &nodo, int nivel, int& nivelEncontrado){
    // Caso base
    if(arbol.empty()) return;
    // Si la raiz es primo, dejamos de buscar
    else if(esPrimo(arbol.root())) return;
    // Si la raiz es multiplo de 7
    else if(arbol.root() % 7 == 0){
        // Si no lo habiamos encontrado
        if(!encontrado || nivel < nivelEncontrado){
            encontrado = true;  //Ponemos que ya lo hemos encontrado
            nodo = arbol.root();    // Ponemos que el nuevo nodo es la raiz
            nivelEncontrado = nivel;
        }
    }    
    busqueda(arbol.left(), encontrado, nodo, nivel+1, nivelEncontrado);
    busqueda(arbol.right(), encontrado, nodo, nivel+1, nivelEncontrado);
}


void resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    if (arbol.empty()) {
        cout << "NO HAY" << endl;
        return;
    }
    bool encontrado = false;
    int nodo = 0;
    int nivel = 0;
    int raiz = arbol.root();
    int nivelEncontrado = 0;
    busqueda(arbol, encontrado, nodo, nivel, nivelEncontrado);
    if(encontrado){
        cout << nodo << ' ' << nivelEncontrado+1 << endl;
    } else {
        cout << "NO HAY" << endl;
    }
}


int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos;
    cin >> numCasos;
    while(numCasos--){ resuelveCaso();}
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}
    