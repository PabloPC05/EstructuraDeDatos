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

class FantasiaFinal {
    private:
    
    struct tVillano{ 
        int vida;
        int danyo; 
        tVillano () : vida(0), danyo(0) {}
        tVillano(int v, int d) : vida(v), danyo(d) {}
    };

    struct tHeroe{
        int vida;
        unordered_map<string, int> poderes;
        tHeroe() : vida(0) {}
        tHeroe(int v) : vida(v) {}
    };

    unordered_map<string, tVillano> villanos;
    unordered_map<string, tHeroe> heroes;

    list<pair<string, int>> personajes;
    unordered_map<string, list<pair<string, int>>::iterator> iteradores;

    public:     

        void aparece_villano(const string& villano, const int& vida, const int& a){
            if(villanos.count(villano)){
                 throw invalid_argument("Personaje ya existente");
            }
            villanos[villano] = tVillano(vida,a);
            personajes.push_back({villano, vida});
            iteradores[villano] = --personajes.end();
        }

        void aparece_heroe(const string& hero, const int& puntos){
            if(heroes.count(hero)) throw invalid_argument("Personaje ya existente");
            heroes[hero] = tHeroe(puntos);
            personajes.push_back({hero, puntos});
            iteradores[hero] = --personajes.end();
        }

        void aprende_ataque(const string&hero, const string& ataque,const int& danyo){
            if(!heroes.count(hero)) throw invalid_argument("Heroe inexistente");
            if(heroes[hero].poderes.count(ataque)) throw invalid_argument("Ataque repetido");
            heroes[hero].poderes[ataque] = danyo;
        }

        list<pair<string, int>> mostrar_ataques(const string& hero){
            if(!heroes.count(hero)) throw invalid_argument("Heroe inexistente");
            list<pair<string,int>> result;
            for(auto [poder, damage] : (heroes[hero].poderes)){
                result.push_back({poder, damage});
            }
            return result; 
        }

        list<pair<string, int>> mostrar_turnos(){
            return personajes;
        }

        bool villano_ataca(const string& villano, const string& hero){
            if(!villanos.count(villano)) throw invalid_argument("Villano inexistente");
            if(!heroes.count(hero)) throw invalid_argument("Heroe inexistente");
            if(personajes.front().first != villano){ 
                throw invalid_argument("No es su turno");
            }
            heroes[hero].vida -= villanos[villano].danyo;
            auto it = iteradores[hero];
            it->second -= villanos[villano].danyo;
            personajes.pop_front();
            bool derrotado = false;
            if(heroes[hero].vida <= 0){ // Eliminamos al heroe
                personajes.erase(iteradores[hero]);
                iteradores.erase(hero);
                heroes.erase(hero);
                derrotado = true;
            }
            personajes.push_back({villano, villanos[villano].vida});
            iteradores[villano] = --personajes.end();
            return derrotado;
        }

        bool heroe_ataca(const string& hero, const string& ataque, const string& villano){
            if(!villanos.count(villano)) throw invalid_argument("Villano inexistente");
            if(!heroes.count(hero)) throw invalid_argument("Heroe inexistente");
            if(personajes.front().first != hero) throw invalid_argument("No es su turno");
            if(!heroes[hero].poderes.count(ataque)) throw invalid_argument("Ataque no aprendido");
            bool derrotado = false;
            villanos[villano].vida -= heroes[hero].poderes[ataque];
            auto it = iteradores[villano];
            it->second -=  heroes[hero].poderes[ataque];
            personajes.pop_front();
            if(villanos[villano].vida <= 0){ // Eliminamos al heroe
                personajes.erase(iteradores[villano]);
                iteradores.erase(hero);
                villanos.erase(villano);
                derrotado = true;
            }
            personajes.push_back({hero, heroes[hero].vida});
            iteradores[hero] = --personajes.end();
            return derrotado;
        }

        

};

bool resuelveCaso() {
  string operacion;
  cin >> operacion;

  if (cin.eof()) return false;

  FantasiaFinal ff;

  while (operacion != "FIN") {
    try {
        if(operacion == "aparece_villano"){
            string nombre;
            int vida, damage;
            cin >> nombre >> vida >> damage;
            ff.aparece_villano(nombre, vida, damage);
        } else if(operacion == "aparece_heroe"){
            string nombre; int vida;
            cin >> nombre >> vida;
            ff.aparece_heroe(nombre, vida);
        } else if(operacion == "aprende_ataque"){
            string hero, nombre;int damage;
            cin >> hero >> nombre >> damage;
            ff.aprende_ataque(hero, nombre, damage);
        } else if(operacion == "mostrar_ataques"){
            string hero;
            cin >> hero;
            auto lista = ff.mostrar_ataques(hero);
            cout << "Ataques de " << hero << '\n';
            for(const auto& ataque : lista){
                cout << ataque.first << ' ' << ataque.second << '\n';
            }
        } else if(operacion == "mostrar_turnos"){
            auto list = ff.mostrar_turnos();
            cout << "Turno:\n";
            for(const auto& ataque : list){
                cout << ataque.first << ' ' << ataque.second << '\n';
            }
        } else if(operacion == "villano_ataca"){
            string villano, hero;
            cin >> villano >> hero;
            bool derrotado = ff.villano_ataca(villano, hero);
            cout << villano << " ataca a " << hero << '\n';
            if(derrotado) cout << hero << " derrotado\n";
        } else if(operacion == "heroe_ataca"){
            string villano, hero, ataque;
            cin >> hero >> ataque >> villano;
            bool derrotado = ff.heroe_ataca(hero, ataque, villano);
            cout << hero << " ataca a " << villano << '\n';
            if(derrotado) cout << villano << " derrotado\n";
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