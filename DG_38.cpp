#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <climits>
#include <vector>
#include <string>
#include "set_tree.h"
using namespace std;

bool resuelveCaso() {
    char car; 
    cin >> car;
    if (!cin) return false;
    int num;
    cin >> num;
    if (car == 'N') {
        SetTree<int> set;
        int elem;
        cin >> elem;
        while (elem != -1) {
            if (!set.contains(elem)) {
                set.insert(elem);
                if (set.size() > num) {
                    set.erase_min();
                }
            }
            cin >> elem;
        }
        set.display(cout);
        cout << '\n';       
    } 
    else if (car == 'P') {
        SetTree<string> set;
        string elem;
        cin >> elem;
        while (elem != "FIN") {
            if (!set.contains(elem)) {
                set.insert(elem);
                if (set.size() > num) {
                    set.erase_min();
                }
            }
            cin >> elem;
        }
        set.display(cout);
        cout << '\n';
    }

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
    