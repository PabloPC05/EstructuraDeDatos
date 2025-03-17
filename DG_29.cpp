#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bintree_2.h"
using namespace std;

template <typename T>
bool es_estable(const BinTree<T>& arbol){
    return arbol.es_estable();
}

template <typename T>
bool es_estable(const typename BinTree<T>::NodePointer& node) {
    if (node == nullptr) return true;
    bool left_stable = es_estable(node->left);
    bool right_stable = es_estable(node->right);
    return left_stable && right_stable && (node->left == nullptr || node->elem <= node->left->elem) && (node->right == nullptr || node->elem <= node->right->elem);
}


void resuelveCaso(){
    BinTree<int> arbol = read_tree<int>(cin);
    if(es_estable(arbol)){
        cout << "SI" << endl;
    }else{
        cout << "NO" << endl;
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
    