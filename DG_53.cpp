#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_set> 
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <list>
#include <algorithm>

using namespace std;

class Libreria {
    private:
        unordered_map<string, int> libro_cantidad; 
        unordered_map<string, int> libro_ventas;
        map<int, list<string>> ventas_libro;
        unordered_map<string, list<string>::iterator> libro_iterador;
        int cantidadLibrosVendidos;
    public: 
        Libreria() : libro_cantidad(), libro_ventas(), libro_iterador(), cantidadLibrosVendidos(0) {}
        void nuevoLibro(const string& libro, const int& cantidad){
            libro_cantidad[libro] += cantidad;
        }

        void comprar(const string& libro){
            if(!libro_cantidad.count(libro)) throw invalid_argument("Libro no existente\n");
            if(libro_cantidad[libro] == 0) throw out_of_range("No hay ejemplares\n");
            libro_cantidad[libro]--; // Restamos un ejemplar del almacen
            if(!libro_ventas.count(libro)) cantidadLibrosVendidos++; // Si el libro aparece que no se ha vendido lo añadimos a la cantidad de libros vendidos
            int& cant = libro_ventas[libro];    // Tomamos la cantidad de ventas que tiene el libro
            if(cant != 0){
                ventas_libro[cant].erase(libro_iterador[libro]); // Borramos el libro de su lista de cantidad de ventas
            }
            cant++; // Actualizamos la cantidad de ventas que tiene el libro
            ventas_libro[cant].push_front(libro); // Metemos al libro en su nueva lista de cantidades vendidas
            libro_iterador[libro] = ventas_libro[cant].begin(); // Actualizamos el iterador del libro
        }

        bool estaLibro(const string& libro) const{
            return libro_cantidad.count(libro);
        }

        void elimLibro(const string& libro){ // Eliminamos del sistema el libro
            if(!libro_cantidad.count(libro)) return; // Si el libro nunca ha sido añadido
            libro_cantidad.erase(libro); // Lo eliminamos del almacen 

            if(!libro_ventas.count(libro)) return; // Si tampoco lo hemos vendido nunca hemos terminado de operar con el
            int cantidad = libro_ventas[libro]; // Tomamos la cantidad de ventas
            ventas_libro[cantidad].erase(libro_iterador[libro]); // Lo eliminamos de su lita de vendidos
            if(ventas_libro[cantidad].empty()) ventas_libro.erase(cantidad); // Si ademas su puesto en el mapa se ha quedado vacío entonces eliminamos tambien la key 
            libro_iterador.erase(libro); // Eliminamos el libro del mapa de iteradores
            libro_ventas.erase(libro); // Eliminamos el libro del registro de sus ventas
            cantidadLibrosVendidos--; // Como eliminamos todo rastro del libro, tambien lo eliminamos como libro vendido
        }

        int numEjemplares(const string& libro) const{
            if(!estaLibro(libro)) throw invalid_argument("Libro no existente\n"); 
            return libro_cantidad.at(libro);
        }

        list<string> top10() const{
            list<string> result;
            int limit = 10;
            for (auto it = ventas_libro.rbegin(); it != ventas_libro.rend() && limit > 0; ++it) {
                for (const string& libro : it->second) {
                    if (limit == 0) break;
                    result.push_back(libro);
                    --limit;
                }
            }
            return result;
            /*list<string> returnValue;
            int i = 0; // Cantidad de libros que ya he vendido
            int N = min(cantidadLibrosVendidos, 10); // Cuantos libros podremos poner en el top10
            int j = 1; 
            while(i < N){
                auto it = ventas_libro.end(); // Tomamos el elemento del final, que en un mapa ordenado es el ultimo, estamos tomando la lista de libros que tienen x numero de ventas
                it = std::prev(it, j);
                list<string> lista = it->second;
                int size = min(int(lista.size()), N - i); // Tomamos el minimo entre la cantidad de libros vendida y los libros que aun necesitemos para llegar al top10
                returnValue.insert(returnValue.end(), lista.begin(), std::next(lista.begin(), size)); // Insertamos los elementos mas vendidos en la lista que se devolverá
                i += size; // Actualizamos cuantos elementos quedan para llegar al final 
                j++;
            }
            return returnValue;*/
        }
};

bool resuelveCaso() {
    int num_ordenes; 
    cin >> num_ordenes;
    if(!cin) return false; 
    Libreria libreria;
    string orden; 
    cin.ignore();
    while(num_ordenes--){
        string linea;
        getline(cin, linea); 
        istringstream ss(linea);
        ss >> orden;
        if(orden == "nuevoLibro"){
            int cantidad; 
            string libro; 
            ss >> cantidad;
            getline(ss, libro);
            if(!libro.empty() && libro[0] == ' ') libro.erase(0,1);
            libreria.nuevoLibro(libro, cantidad);
        } else if(orden == "comprar"){
            try{
                string libro; 
                getline(ss, libro);
                if(!libro.empty() && libro[0] == ' ') libro.erase(0,1);
                libreria.comprar(libro);
            } catch(const invalid_argument& a){ 
                cout << a.what();
            } catch(const out_of_range& e){
                cout << e.what();
            }
        } else if(orden == "numEjemplares"){
            string libro; 
            getline(ss, libro);
            if(!libro.empty() && libro[0] == ' ') libro.erase(0,1);
            try{
                int num = libreria.numEjemplares(libro);
                cout << "Existen " << num << " ejemplares del libro " << libro << '\n';
            } catch(const invalid_argument& a){ 
                cout << "No existe el libro " << libro << " en el sistema\n";
            }
        } else if(orden == "estaLibro"){
            string libro; 
            getline(ss, libro);
            if(!libro.empty() && libro[0] == ' ') libro.erase(0,1);
            if(libreria.estaLibro(libro)) cout << "El libro " << libro << " esta en el sistema\n";
            else cout << "No existe el libro " << libro << " en el sistema\n";
        } else if(orden == "top10"){
            cout << "TOP10\n"; 
            list<string> top10 = libreria.top10();
            for(const auto& libro : top10){
                cout << "    " << libro << '\n';
            }
        } else if(orden == "elimLibro"){
            string libro; 
            getline(ss, libro);
            if(!libro.empty() && libro[0] == ' ') libro.erase(0,1);
            libreria.elimLibro(libro);
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