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

using namespace std;

class Camping {
    private:
        struct infoParcela{
            string titular;
            list<string> lista_espera;
            bool reservado;
        };

        map<pair<int, int>, infoParcela> parcelas; // Parcela_dia
        unordered_map<string, pair<int, int>> personas_con_reserva;
        unordered_map<string, pair<int, int>> personas_en_espera;
        map<int, set<int>> dia_parcelas_reservadas;
    public:     
        void nueva_reserva(const string& persona, const int& parcela, const int& dia){
            if(personas_con_reserva.count(persona) || personas_en_espera.count(persona)) throw domain_error("Persona ya ha reservado");
            infoParcela& info = parcelas[make_pair(parcela, dia)];
            if(info.reservado){ info.lista_espera.push_back(persona); personas_en_espera[persona] = make_pair(parcela, dia);}
            else {
                info.reservado = true; 
                info.titular = persona;
                personas_con_reserva[persona] = make_pair(parcela, dia);
                dia_parcelas_reservadas[dia].insert(parcela);
            }
        }

        void cancelar_reserva(const string& persona){
            if(!personas_con_reserva.count(persona)) throw domain_error("No es titular de ninguna reserva");
            auto parcela_dia = personas_con_reserva[persona];
            infoParcela& info = parcelas[parcela_dia];
            if(info.lista_espera.empty()){
                dia_parcelas_reservadas[parcela_dia.second].erase(parcela_dia.first);
                return;
            }
            string nuevo_titular = info.lista_espera.front();
            info.lista_espera.pop_front();
            info.titular = nuevo_titular;
            personas_con_reserva.erase(persona);
            personas_en_espera.erase(nuevo_titular);
            personas_con_reserva[nuevo_titular] = parcela_dia;

        }   

        string quien_reserva(const int& parcela, const int& dia) const{
            const infoParcela& info = parcelas.at(make_pair(parcela, dia));
            if(!info.reservado) throw domain_error("Parcela no reservada");
            return info.titular;
        }

        bool puede_extender_reserva(const string& persona, const int& n) const{
            bool returnValue = true; 
            if(!personas_con_reserva.count(persona)) throw domain_error("No es titular de ninguna reserva");
            auto parcela_dia = personas_con_reserva.at(persona);
            for(int i = 1; i <= n && returnValue; i++){
                if(!parcelas.count(make_pair(parcela_dia.first, parcela_dia.second + i))) returnValue = true;
                else returnValue = !parcelas.at(make_pair(parcela_dia.first, parcela_dia.second + i)).reservado; 
            }
            return returnValue;
        }

        int menor_distancia_vecinos(const string& persona) const{
            if(!personas_con_reserva.count(persona)) throw domain_error("No es titular de ninguna reserva");
            auto parcela_dia = personas_con_reserva.at(persona);
            const set<int>& parcelas_reservadas = dia_parcelas_reservadas.at(parcela_dia.second); // Cogemos el set de las parcelas reservadas para un detemrinado dia
            auto it = parcelas_reservadas.find(parcela_dia.first); // Tomamos el iterador que apunta a la parcela reservada 
            // Como es un set, está ordenado, así que sólo habria que comparar los valores de los dos elementos a sus lados
            int dist_izq = -1, dist_derech = -1;
            if(it != parcelas_reservadas.begin()){ // Si no es la primera, quiere decir que tiene otra antes
                auto it_izq = it;
                it_izq--;
                dist_izq = *it - *it_izq -1;
            }

            auto it_derech = it;
            it_derech++;
            if(it_derech!= parcelas_reservadas.end()){ // Si no es la ultima
                dist_derech = *it_derech - *it -1;
            }
            if(dist_derech != -1 && dist_izq != -1) return min(dist_derech, dist_izq);
            else if(dist_derech == -1) return dist_izq;
            else if(dist_izq == -1) return dist_derech;
            else return -1;
        }

};

bool resuelveCaso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  Camping camp;

  while (operacion != "FIN") {
    try {
        if(operacion == "nueva_reserva"){
            string nombre;
            int parcela, dia; 
            cin >> nombre >> parcela >> dia; 
            camp.nueva_reserva(nombre, parcela, dia);
            cout << "OK\n";
        } else if(operacion == "cancelar_reserva"){
            string nombre;
            cin >> nombre;
            camp.cancelar_reserva(nombre);
            cout << "OK\n";
        } else if(operacion == "quien_reserva"){
            int parcela, dia;
            cin >> parcela >> dia;
            string nombre = camp.quien_reserva(parcela,dia);
            cout << '(' << parcela << ',' << dia << ") reservada por " << nombre << '\n';
        } else if(operacion == "puede_extender_reserva"){
            int n;
            string nombre;
            cin >> nombre >> n;
            bool b = camp.puede_extender_reserva(nombre, n);
            if(b) cout << nombre << " puede extender la reserva " << n <<" dias\n";
            else  cout << nombre << " no puede extender la reserva " << n <<" dias\n";
        } else if(operacion == "menor_distancia_vecinos"){
            string nombre;
            cin >> nombre;
            int dist = camp.menor_distancia_vecinos(nombre);
            if(dist == -1) cout << "INFINITO\n";
            else cout << dist << '\n';
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