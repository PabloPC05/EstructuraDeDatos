#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <list>
#include <algorithm>
#include <deque>

using namespace std;

class TiendaCamisetas {
    private:
        deque<string> camisetas;
        unordered_map<string, list<int>> camisetas_posiciones;
        int limite_derecho, limite_izquierdo;
        set<int> unicas;

    public:     
    TiendaCamisetas() : limite_derecho(-1), limite_izquierdo(0) {}
    void inserta_izquierda(const string& color){
        limite_izquierdo--;
        camisetas.push_front(color);
        if(!camisetas_posiciones.count(color)) unicas.insert(limite_izquierdo);
        else if(camisetas_posiciones[color].size() == 1){
            unicas.erase(camisetas_posiciones[color].front());
        }
        camisetas_posiciones[color].push_back(limite_izquierdo);
    }

    void inserta_derecha(const string& color){
        limite_derecho++;
        camisetas.push_back(color);
        if(!camisetas_posiciones.count(color)) unicas.insert(limite_derecho);
        else if(camisetas_posiciones[color].size() == 1){
            unicas.erase(camisetas_posiciones[color].back());
        }
        camisetas_posiciones[color].push_back(limite_derecho);
    }

    void compra_izquierda(){
        if(camisetas.empty()) throw domain_error("Tienda sin camisetas");
        string camiseta = camisetas.front();
        camisetas.pop_front();
        camisetas_posiciones[camiseta].pop_front();
        if (camisetas_posiciones[camiseta].empty()) {              // O(1)
            camisetas_posiciones.erase(camiseta);                    // O(1)
            unicas.erase(limite_izquierdo);                             // O(log U)
            // Si solamente queda una posiciÃ³n de ese color, la camiseta pasa a ser Ãºnica
        } else if (camisetas_posiciones[camiseta].size() == 1) {   // O(1)
            unicas.insert(camisetas_posiciones[camiseta].front());   // O(log U)
        }
        limite_izquierdo++;
    }

    void compra_derecha(){
        if(camisetas.empty()) throw domain_error("Tienda sin camisetas");
        string camiseta = camisetas.front();
        camisetas.pop_back();
        camisetas_posiciones[camiseta].pop_front();
        if (camisetas_posiciones[camiseta].empty()) {              // O(1)
            camisetas_posiciones.erase(camiseta);                    // O(1)
            unicas.erase(limite_derecho);                             // O(log U)
            // Si solamente queda una posiciÃ³n de ese color, la camiseta pasa a ser Ãºnica
        } else if (camisetas_posiciones[camiseta].size() == 1) {   // O(1)
            unicas.insert(camisetas_posiciones[camiseta].front());   // O(log U)
        }
        limite_derecho--;

    }

    pair<int, string> pregunta(){
        if(camisetas.empty()) throw domain_error("NADA INTERESANTE");
        if(unicas.empty()) throw domain_error("NADA INTERESANTE");
        int compra_izq = *unicas.begin() - limite_izquierdo + 1;
        auto last_it = unicas.end();
        --last_it;
        int compra_der = limite_derecho - *last_it + 1;
        if (compra_izq < compra_der) {
            return {compra_izq, "IZQUIERDA"};
        } else if (compra_izq > compra_der) {
            return {compra_der, "DERECHA"};
        } else {
            return {compra_izq, "CUALQUIERA"};
        }
    }
};

bool resuelveCaso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  TiendaCamisetas tienda;

  while (operacion != "FIN") {
    try {
        if(operacion == "inserta_derecha"){
            string color;
            cin >> color;
            tienda.inserta_derecha(color);
        } else if(operacion == "inserta_izquierda"){
            string color;
            cin >> color;
            tienda.inserta_izquierda(color);
        } else if(operacion == "compra_izquierda"){
            tienda.compra_izquierda();
        } else if(operacion == "compra_derecha"){
            tienda.compra_derecha();
        } else if(operacion == "pregunta"){
            auto result = tienda.pregunta();
            if(result.first == -1) cout << "NADA INTERESANTE\n";
            else{
                cout << result.first << ' ' << result.second << '\n'; 
            }

        }
    } catch (exception &e) {
      cout << "ERROR: " << e.what() << "\n";
    }
    cin >> operacion;
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