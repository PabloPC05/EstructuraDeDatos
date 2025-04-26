#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <climits>
#include <vector>
#include "set_tree.h"
using namespace std;

bool resuelveCaso(){
    int N; 
    cin >> N;
    if(N == 0) return false;
    SetTree<int> set;
    for(int i = 0; i < N; ++i){
        int elem;
        cin >> elem;
        set.insert(elem);
    }
    int M;
    cin >> M;
    for(int i = 0; i < M; ++i){
        int a; 
        cin >> a; 
        auto resultado = set.lower_bound(a);
        if(resultado.first){
            cout << resultado.second << '\n';
        }
        else cout << "NO HAY\n";
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
    