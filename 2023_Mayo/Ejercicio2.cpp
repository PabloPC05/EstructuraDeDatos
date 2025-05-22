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
#include "BinTree.h"
using namespace std;
//     BPP,     minP, maxP      minIP, maxIP
tuple<bool, pair<int, int>, pair<int,int>> busqueda_por_paridad_aux(const BinTree<int>& tree){
    if(tree.empty()){ // Si es una hoja
        return make_tuple(true, make_pair(INT_MAX, INT_MIN), make_pair(INT_MAX, INT_MIN)); 
    } else{
        bool es_abbp;
        auto [es_izq, par_izq, impar_izq] = busqueda_por_paridad_aux(tree.left());
        auto [es_der, par_der, impar_der] = busqueda_por_paridad_aux(tree.right());
        // Calculemos el nuevo intervalo de los numeros
        auto intervalo_par = make_pair(min(par_der.first, par_izq.first), max(par_izq.second, par_der.second));
        auto intervalo_impar = make_pair(min(impar_der.first, impar_izq.first), max(impar_izq.second, impar_der.second));
        if(tree.root() % 2 == 0 ){ // Si la raiz es par
            es_abbp = es_izq && es_der && par_izq.first > tree.root() && par_der.second < tree.root();
            intervalo_par.first = min(intervalo_par.first, tree.root());
            intervalo_par.second = max(intervalo_par.second, tree.root());
        } else{
            es_abbp = es_izq && es_der && impar_izq.second < tree.root() && tree.root() < impar_der.first;
            intervalo_impar.first = min(intervalo_impar.first, tree.root());
            intervalo_impar.second = max(intervalo_impar.second, tree.root());
        }
        return {es_abbp, intervalo_par, intervalo_impar};
    }
}

bool busqueda_por_paridad(const BinTree<int>& tree){
    return get<0>(busqueda_por_paridad_aux(tree));
}

bool resuelveCaso() {
    BinTree<int> arbol = read_tree<int>(cin);
    if(arbol.empty()) return false;
    if(busqueda_por_paridad(arbol)) cout << "SI\n";
    else cout << "NO\n";
    return true;
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    int numCasos; 
    cin >> numCasos;
    while(numCasos--) resuelveCaso();
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}