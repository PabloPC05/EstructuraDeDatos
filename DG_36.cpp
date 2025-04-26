#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <climits>
#include "set_tree.h"
using namespace std;

bool resuelveCaso(){
    int N, M;
    cin >> N >> M;
    if(!cin) return false;
    SetTree<int> set;
    int min = INT_MAX, max = INT_MIN;
    for(int i = 0; i < N; ++i){
        int elem;
        cin >> elem;
        if(elem < min) min = elem;
        if(elem > max) max = elem;
        set.insert(elem);
    }
    for(int i = 0; i < M; ++i){
        int a, b;
        cin >> a >> b;
        if(min == a && max == b){
            cout << set.size() << '\n';
        }
        else{
            cout << set.count_interval(a, b) << '\n';
        }
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
    