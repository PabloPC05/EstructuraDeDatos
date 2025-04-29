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

class iPud {
    private: 
        unordered_map<string, int> cancion_duracion; 
        unordered_map<string, string> cancion_artista;
        unordered_map<string, list<string>::iterator> cancion_info;
        list<string> played_history;
        list<string> playlist;
        int total_duracion_playlist;
    public: 
        iPud() : cancion_duracion(), cancion_artista(), cancion_info(), played_history(), playlist(), total_duracion_playlist(0) {}

        void addSong(const string& cancion, const string& artista, const int& duracion){
            if(cancion_duracion.count(cancion)) throw domain_error("");
            cancion_duracion[cancion] = duracion; 
            cancion_artista[cancion] = artista;
        }

        void addToPlaylist(const string& cancion){
            if(cancion_info.count(cancion)) return; 
            auto it = cancion_duracion.find(cancion);
            if(it == cancion_duracion.end()) throw domain_error("ERROR addToPlaylist");
            playlist.push_back(cancion);
            cancion_info[cancion] = --playlist.end();
            total_duracion_playlist += it->second;
        }

        string current() const{
            if(playlist.empty()) throw domain_error("current");
            return playlist.front();
        }

        string play(){
            if (playlist.empty()) return ""; 
            string cancion = playlist.front();
            total_duracion_playlist -= cancion_duracion[cancion];
            playlist.pop_front();
            cancion_info.erase(cancion);
            played_history.push_back(cancion);
            return cancion;          
        }

        int totalTime(){
            return total_duracion_playlist;
        }

        list<string> recent(const int& N) const {
            list<string> recently_played;
            unordered_set<string> already_added;
            int count = 0;
            for (auto it = played_history.rbegin(); it != played_history.rend() && count < N; ++it) {
                if (!already_added.count(*it)) {
                    recently_played.push_back(*it);
                    already_added.insert(*it);
                    ++count;
                }
            }
            return recently_played;
        }
        
        void deleteSong(const string& cancion){
            auto it = cancion_duracion.find(cancion);
            if (it != cancion_duracion.end()) {
                if (cancion_info.count(cancion)) {
                    total_duracion_playlist -= it->second;
                    playlist.erase(cancion_info[cancion]);
                    cancion_info.erase(cancion);
                }
                cancion_duracion.erase(it);
                cancion_artista.erase(cancion);
                played_history.remove(cancion);
            }
        }
        
};

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if(!cin) return false;
    iPud ipud;
    while(orden != "FIN"){
        if(orden == "addSong"){
            try {
                string cancion, artista;
                int duracion; 
                cin >> cancion >> artista >> duracion; 
                ipud.addSong(cancion, artista, duracion);
            }catch(const domain_error& e){
                cout << "ERROR addSong\n";
            }
        } else if(orden == "addToPlaylist"){
            try {
                string cancion; 
                cin >> cancion;
                ipud.addToPlaylist(cancion);    
            } catch(const domain_error& e){
                cout << "ERROR addToPlaylist\n";
            }
        } else if(orden == "play"){
            string cancion = ipud.play();
            if (cancion == "") cout << "No hay canciones en la lista\n";
            else cout << "Sonando " << cancion << '\n';
        } else if(orden == "totalTime"){
            cout << "Tiempo total " << ipud.totalTime() << '\n';
        } else if(orden == "recent"){
            int N;
            cin >> N;
            list<string> mas_recientes = ipud.recent(N);
            if(mas_recientes.empty()) cout << "No hay canciones recientes\n";
            else{
                cout << "Las " << mas_recientes.size() << " mas recientes\n"; 
                for(const auto& cancion : mas_recientes){
                    cout << "    " << cancion << '\n';
                }
            }
        } else if(orden == "deleteSong"){
            string cancion; 
            cin >> cancion; 
            ipud.deleteSong(cancion);
        } else if(orden == "current"){
            try{
                string cancion = ipud.current();
            }catch(const domain_error& e){
                cout << "ERROR current\n";
            }
        }
        cin >> orden;
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