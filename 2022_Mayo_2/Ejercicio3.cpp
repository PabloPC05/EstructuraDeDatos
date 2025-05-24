//******************************************************
// IMPORTANTE
// NOMBRE Y APELLIDOS DEL ALUMNO:
// USUARIO DEL JUEZ DE ESTE EXAMEN:
// LABORATORIO Y PUESTO:
//******************************************************

// Explicación de la representación empleada. 




// Indicar el coste de cada método en un comentario al principio del método.





#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector> 
#include <unordered_map>
#include <map>
#include <set>
#include <list>

using namespace std;

// añade las librerías de la STL que necesites



using artista = std::string;
using obra = std::string;

// Elige el tipo representante adecuado para el TAD GaleriaArte e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de las operaciones.

class galeriaArte {
    private:
        list<obra> obras_antiguas;
        struct infoObra{
            artista artista;
            int precio;
        };
        unordered_map<obra, infoObra> obras;
        map<artista, int> artista_ventas;
        set<string> artistas_mas_vendidos;
        int max_ventas = 0;
    
    
public:
    galeriaArte() {}
    
    void nueva_obra(obra const& c, artista const& a, int p) {
        if(obras.count(c)) throw invalid_argument("Obra ya en la galeria");
        obras[c] = {a, p};
        obras_antiguas.push_back(c);
    }
    
    void venta_obra (obra const& c) {
        if(!obras.count(c)) throw invalid_argument("Obra no existente");
        string& artista = obras[c].artista;
        int& ventas = artista_ventas[artista];
        ventas += obras[c].precio;
        if(ventas == max_ventas){
            artistas_mas_vendidos.insert(artista);
        } else if(artistas_mas_vendidos.empty() || ventas > max_ventas){
            artistas_mas_vendidos.clear();
            artistas_mas_vendidos.insert(artista);
            max_ventas = ventas;
        }
        obras.erase(c);
        obras_antiguas.remove(c);
    }
    
    std::vector<artista> mas_vendidos() const {
        vector<artista> result;
        for(auto artista: artistas_mas_vendidos){
            result.push_back(artista);
        }
        return result;
    }
    
    std::vector<obra> obras_por_antiguedad(int k) const {
        vector<obra> result;
        auto it = obras_antiguas.begin();
        int i = 0;
        while(i < k && it != obras_antiguas.end()){
            result.push_back(*it);
            i++;
            it++;
        }
        return result;
    }
};

// No modificar el código a partir de aqui.
// Entrada y salida de datos
bool resuelveCaso() {
    std::string op;
    std::cin >> op;
    if (!std::cin) return false;
    
    galeriaArte galeria;
    while (op != "FIN") {
        try {
            if (op == "nueva_obra") {
                obra c; artista a; int p;
                std::cin >> c >> a >> p;
                galeria.nueva_obra(c,a,p);
            }
            else if (op == "venta_obra") {
                obra c; 
                std::cin >> c;
                galeria.venta_obra(c);
            }
            else if (op == "mas_vendidos") {
                std::vector<artista> sol = galeria.mas_vendidos();
                std::cout << "Los artistas que mas han vendido son:\n";
                for (auto n : sol) std::cout << n << '\n';
            }
            else if (op == "obras_por_antiguedad") {
                int k; 
                std::cin >> k;
                std::vector<obra> v = galeria.obras_por_antiguedad(k);
                std::cout << "Obras mas antiguas en la galeria:\n";
                for (obra o : v) std::cout  << o << '\n';
            }
        }
        catch(std::invalid_argument& e) {
            std::cout << "ERROR: " << e.what() << "\n";
        }
        std::cin >> op;
    } 
    std::cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif 
    
    while (resuelveCaso()) ;
    
#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
  
    return 0;
}

