#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <iostream>
using namespace std;

enum class Categoria {Primero = 1, Segundo = 2, Postre = 3};

struct Plato {
    Categoria categoria;
    string nombre;
};

Categoria categoria(const char& c) {
    switch(c) {
        case '1': return Categoria::Primero;
        case '2': return Categoria::Segundo;
        default: return Categoria::Postre;
    }
}

char categoria(const Categoria& c){
    switch(c){
        case Categoria::Primero: return '1';
        case Categoria::Segundo: return '2';
        default: return 'P';
    }
}

void ordenar_menu(list<Plato>& platos) {
    auto it = platos.begin();
    auto insertar_primero = platos.begin();
    bool primero = true;
    auto limit = platos.end();
    while(it != limit){
        if(it->categoria == Categoria::Primero){
            if(it == insertar_primero) {
                ++insertar_primero;
                ++it;
            } else {
                insertar_primero = platos.insert(insertar_primero, *it);
                ++insertar_primero;
                it = platos.erase(it);
            }
        } else if(it->categoria == Categoria::Postre){
            if(it == insertar_primero) insertar_primero = next(it);
            if(primero){ limit = platos.insert(platos.end(), *it); primero = false;}
            else platos.insert(platos.end(), *it);
            it = platos.erase(it);
        } else ++it;
    }
}


bool resolverCaso() {
    int N;
    cin >> N;
    if(N == 0) return false;
    list<Plato> platos;
    cin.ignore();
    for(int i = 0; i < N; i++){
        string line;
        getline(cin, line);
        char c = line[0];
        line.erase(line.begin());
        line.erase(line.begin());
        platos.push_back({categoria(c), line});
    }
    ordenar_menu(platos);
    for(const Plato& p : platos){
        cout << categoria(p.categoria) << " " << p.nombre << '\n';
    }
    cout << "---\n";
    return true;
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while(resolverCaso()) ;
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
    #endif
    return 0;
}
