#include <string>
#include <vector>

const int MAX_RESERVAS = 50000;

class Teatro {
    public: 
        Teatro() : num_reservas(0) {}

        bool nueva_reserva(int inicio, int fin, std::string nombre) {
            bool returnValue = false;
            // Si se ha alcanzado el maximo
            if(num_reservas == MAX_RESERVAS) returnValue = false;
            // Si no hay ninguna reserva realizada
            if(num_reservas == 0){
                reservas.push_back(Reserva(inicio, fin, nombre));
                num_reservas++;
                returnValue = true;
            }
            else{
                int i = 0, f = num_reservas; 
                int mitad = i + (f - i) / 2;
                // A través de la búsqueda binaria buscamos la posición donde insertar la reserva
                while(i < f) {
                    mitad = i + (f - i) / 2;
                    if(reservas[mitad].inicio < inicio) {
                        i = mitad + 1;
                    }
                    else {
                        f = mitad;
                    }
                }  
                if((i == 0 || reservas[i - 1].fin < inicio) && (i == num_reservas || reservas[i].inicio > fin)){
                    reservas.resize(num_reservas + 1);
                    for(int j = num_reservas; j >i; j--){
                        reservas[j] = reservas[j - 1];
                    }
                    reservas[i] = { inicio, fin, nombre };
                    num_reservas++;
                    returnValue = true;
                }
            }

            return returnValue;
        }

        std::string nombre_reserva(int num_butaca) {
            // Busqueda binaria para encontrar la reserva
            int i = 0, f = num_reservas;
            int mitad = i + (f - i) / 2;
            while(i < f) {
                mitad = i + (f - i) / 2;
                if(reservas[mitad].inicio < num_butaca) {
                    i = mitad + 1;
                }
                else {
                    f = mitad;
                }
            }
            if(i < num_reservas && reservas[i].inicio <= num_butaca && reservas[i].fin >= num_butaca) {
                return reservas[i].nombre;
            }
            return "LIBRE";
        }

        private:
            struct Reserva {
                int inicio;
                int fin;
                std::string nombre;
                Reserva(int i, int f, std::string s) : inicio(i), fin(f), nombre(s) {}
                Reserva() : inicio(0), fin(0), nombre("") {}
            };
        
            std::vector<Reserva> reservas;
            int num_reservas;
    };