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

class CasaDeSubastas {
    private:
        // Un objeto en la casa de subasta puede tener: puja minima, pujadores y sus pujas
        struct infoObjeto{
            int puja_minima;
            map<int, list<string>> puja_participantes; // Mapa de enteros ordenador de menor a mayor, por lo que el ultimo es la mayor puja que se ha hecho
            bool comprado;
        };

        struct infoParticipante{
            int saldo;
            unordered_set<string> objetos_comprados;
            unordered_map<string, pair<int, list<string>::iterator>> objeto_puja_iterador;
        };

        unordered_map<string, infoObjeto> objetos;
        unordered_map<string, infoParticipante> participantes;


    public:     
        void nuevo_participante(const string& part,const int& inicial){
            if(inicial <= 0) throw  domain_error("Saldo inicial no valido");
            if(participantes.count(part)) throw  domain_error("Participante ya existente");
            participantes[part].saldo = inicial; 
        }

        void nueva_subasta(const string& obj, const int& puja_min){
            if(puja_min <= 0) throw  domain_error("Puja inicial no valida");
            if(objetos.count(obj)) throw  domain_error("Objeto no valido");
            objetos[obj].comprado = false; 
            objetos[obj].puja_minima = puja_min;
            objetos[obj].puja_participantes = map<int, list<string>>();
        }

        void nueva_puja(const string& part, const string& obj, const int& cantidad){
            if(!participantes.count(part)) throw  domain_error("Participante no existente");
            if(!objetos.count(obj)) throw  domain_error("Objeto no valido");
            if(participantes[part].objeto_puja_iterador.count(obj)) throw  domain_error("Participante repetido");
            if(participantes[part].saldo < cantidad || cantidad < objetos[obj].puja_minima) throw domain_error("Cantidad no valida");
            objetos[obj].puja_participantes[cantidad].push_back(part);
            participantes[part].objeto_puja_iterador[obj] = {cantidad, --objetos[obj].puja_participantes[cantidad].end()};
            participantes[part].saldo -= cantidad;
        }

        list<string> subastas_ganadas(const string& part) const{
            if(!participantes.count(part)) throw domain_error("Participante no existente");
            const infoParticipante info  = participantes.at(part);
            list<string> list(info.objetos_comprados.begin(), info.objetos_comprados.end());
            return list;
        }

        void abandonar_casa(const string& part){
            if(!participantes.count(part)) throw domain_error("Participante no existente");
            const infoParticipante& info = participantes.at(part);
            for(auto& it: info.objeto_puja_iterador){
                objetos[it.first].puja_participantes[it.second.first].erase(it.second.second);
            }
            participantes.erase(part);
        }

        string cerrar_subasta(const string& obj){
            if(!objetos.count(obj)) throw domain_error("Objeto no valido");
            if(objetos[obj].puja_participantes.empty()) throw domain_error("Objeto no vendido");
            string ganador = objetos[obj].puja_participantes.crbegin()->second.front();
            objetos[obj].comprado = true;
            infoObjeto& info = objetos.at(obj);
            for(auto& it : info.puja_participantes){
                for(string participante : it.second){// Por cada uno de los participantes
                    participantes[participante].saldo += it.first;
                }
            }
            return ganador;
        }


};

bool resuelveCaso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  CasaDeSubastas cs;

  while (operacion != "FIN") {
    try {
      if (operacion == "nuevo_participante") {
        string part; int saldo;
        cin >> part >> saldo;
        cs.nuevo_participante(part, saldo);
        cout << "OK\n";
      } else if (operacion == "nueva_subasta") {
        string obj; int puja_min;
        cin >> obj >> puja_min;
        cs.nueva_subasta(obj, puja_min);
        cout << "OK\n";
      } else if (operacion == "nueva_puja") {
        string part, obj; int cantidad;
        cin >> part >> obj >> cantidad;
        cs.nueva_puja(part, obj, cantidad);
        cout << "OK\n";
      } else if (operacion == "subastas_ganadas") {
        string part;
        cin >> part;
        list<string> result = cs.subastas_ganadas(part);
        cout << part << " ha ganado:";
        for (const string &part : result) {
          cout << " " << part;
        }
        cout << "\n";
      } else if (operacion == "abandonar_casa") {
        string part;
        cin >> part;
        cs.abandonar_casa(part);
        cout << "OK\n";
      } else if (operacion == "cerrar_subasta") {
        string obj;
        cin >> obj;
        string ganador = cs.cerrar_subasta(obj);
        cout << obj << " ha sido ganado por: " << ganador << "\n";        
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