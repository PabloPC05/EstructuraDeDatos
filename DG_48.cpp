#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;


class AutoEscuela{
    private:
        struct tAlumno{
            string nombre;
            int puntos; 
        };
        unordered_map<string, string> alumnos_profesor; 
        vector<tAlumno> alumnos;

        int posicion(const string& nombre_alumno) const{ // Devuelve la posicion o la que deberia ser la posicion del alumno en la lista de alumnos
            int ini = 0, fin = alumnos.size() - 1;
            while(ini <= fin){
                int mitad = (ini + fin) / 2;
                if(alumnos[mitad].nombre == nombre_alumno){ // Si el alumno ya existe, se devuelve la posicion
                    return mitad;
                }
                else if(alumnos[mitad].nombre < nombre_alumno){ // Si el alumno es mayor, se busca en la parte derecha
                    ini = mitad + 1;
                }
                else{ // Si el alumno es menor, se busca en la parte izquierda
                    fin = mitad - 1;
                }
            }
            return ini; // Si no se encuentra, se devuelve la posicion donde deberia estar

        }
    public:
        AutoEscuela() : alumnos_profesor(), alumnos(){} // Constructor por defecto
        void alta(const string& nombre_alumno, const string& nombre_profesor){
            if(alumnos_profesor.count(nombre_alumno)){// Si el alumno ya existe, se cambia de profesor
                alumnos_profesor[nombre_alumno] = nombre_profesor;
            }
            else{ // Si el alumno no existe, se añade a la lista de alumnso con el profesor dado, y 0 puntos
                alumnos_profesor[nombre_alumno] = nombre_profesor; // Se añade el alumno al profesor
                int pos = posicion(nombre_alumno); // Se busca la posicion del alumno en la lista de alumnos
                alumnos.insert(alumnos.begin() + pos, {nombre_alumno, 0}); // Se inserta el alumno en la lista de alumnos
            }
        }

        bool es_alumno(const string& nombre_alumno, const string& nombre_profesor) const{
            auto it = alumnos_profesor.find(nombre_alumno); // Se busca el alumno en el mapa
            if(it == alumnos_profesor.end()){ // Si no existe, se devuelve false
                return false;
            }
            return it->second == nombre_profesor; // Se devuelve true si el profesor coincide
        }

        int puntuacion(const string& nombre_alumno) const{
            int pos = posicion(nombre_alumno); // Se busca la posicion del alumno en la lista de alumnos
            if(pos < alumnos.size() && alumnos[pos].nombre == nombre_alumno){ // Si el alumno existe, se devuelve la puntuacion
                return alumnos[pos].puntos;
            } else{ // Si el alumno no existe, se lanza la excepcion
                throw domain_error("El alumno " + nombre_alumno + " no está matriculado");
            }	
        }

        void actualizar(const string& nombre_alumno, const int& puntos){
            int pos = posicion(nombre_alumno);
            if(pos < alumnos.size() && alumnos[pos].nombre == nombre_alumno){ // Si el alumno existe, se actualiza la puntuacion
                alumnos[pos].puntos += puntos; // Se actualiza la puntuacion del alumno
            } else{ // Si el alumno no existe, se lanza la excepcion
                throw domain_error("El alumno " + nombre_alumno + " no está matriculado");
            }
        }

        vector<string> examen(const string& nombre_profesor, const int& puntos_minimos) const{
            vector<string> alumnos_examen; // Se crea un vector para los alumnos que pasan el examen
            for(const auto& alumno : alumnos){ // Se recorre la lista de alumnos
                if(alumno.puntos >= puntos_minimos && alumnos_profesor.at(alumno.nombre) == nombre_profesor){ // Si el alumno pasa el examen y es del profesor dado, se añade al vector
                    alumnos_examen.push_back(alumno.nombre);
                }
            }
            sort(alumnos_examen.begin(), alumnos_examen.end()); // Ordenar los que pasan el examen
            return alumnos_examen; // Se devuelve el vector de alumnos que pasan el examen
        }

        void aprobar(const string& nombre_alumno){
            int pos = posicion(nombre_alumno); // Se busca la posicion del alumno en la lista de alumnos
            if(!(pos < alumnos.size() && alumnos[pos].nombre == nombre_alumno)) // Si el alumno no existe, se lanza la excepcion
                throw domain_error("El alumno " + nombre_alumno + " no está matriculado");
            else{ // Si el alumno es aprobado, entonces se le elimina de la autoescula junto con toda la informacion que de el existiera
                alumnos_profesor.erase(nombre_alumno); // Se elimina el alumno del mapa de alumnos
                alumnos.erase(alumnos.begin() + pos); // Se elimina el alumno de la lista de alumnos
            }
        }
};

bool resuelveCaso(){
    string orden; 
    cin >> orden; 
    if(!std::cin) return false; // Fin de la entrada
    AutoEscuela autoescuela; // Se crea la autoescuela
    while(orden != "FIN"){
        try {
            if(orden == "alta"){
                string nombre_alumno, nombre_profesor;
                cin >> nombre_alumno >> nombre_profesor;
                autoescuela.alta(nombre_alumno, nombre_profesor);
            }
            else if(orden == "es_alumno"){
                string nombre_alumno, nombre_profesor;
                cin >> nombre_alumno >> nombre_profesor;
                bool es = autoescuela.es_alumno(nombre_alumno, nombre_profesor);
                if(es){
                    cout << nombre_alumno << " es alumno de " << nombre_profesor << endl;
                } else{
                    cout << nombre_alumno << " no es alumno de " << nombre_profesor << endl;
                }
            }
            else if(orden == "puntuacion"){
                string nombre_alumno;
                cin >> nombre_alumno;
                int puntuacion = autoescuela.puntuacion(nombre_alumno);
                cout << "Puntuacion de " << nombre_alumno << ": " << puntuacion << endl;
            }
            else if(orden == "actualizar"){
                string nombre_alumno;
                int puntos;
                cin >> nombre_alumno >> puntos;
                autoescuela.actualizar(nombre_alumno, puntos);
            }
            else if(orden == "examen"){
                string nombre_profesor;
                int puntos_minimos; 
                cin >> nombre_profesor >> puntos_minimos;
                vector<string> alumnos_examen = autoescuela.examen(nombre_profesor, puntos_minimos);
                cout << "Alumnos de " << nombre_profesor << " a examen: " << endl;
                for(const auto& alumno : alumnos_examen){
                    cout << alumno << endl;
                }
            }
            else if(orden == "aprobar"){
                string nombre_alumno;
                cin >> nombre_alumno;
                autoescuela.aprobar(nombre_alumno);
            }
        }catch(const domain_error& e){
            cout << "ERROR\n";
        }
        cin >> orden; // Leer la próxima orden
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