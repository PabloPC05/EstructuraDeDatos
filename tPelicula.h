#include "tHora.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

class tPelicula{
    public: 
    //Constructor de la clase
    tPelicula(std::string nombre = "", tHora horaInicio = tHora(), tHora duracion = tHora()): nombre(nombre), horaInicio(horaInicio), duracion(duracion){}

    //Metodos de comparacion
    bool operator<(tPelicula const& peli) const{
        if(peli.getHoraFin() < horaFin) return true;
        else if(peli.getHoraFin() == horaFin){
            if(peli.getName().compare(nombre) > 0) return true;
            else return false;
        }
        else return false;
    }

    bool operator==(tPelicula const& peli) const{
        return getName() == peli.getName();
    }

    //Metodos de acceso
    std::string getName() const{return nombre;}
    tHora getHoraInicio () const{return horaInicio;}
    tHora getDuracion () const{return duracion;}
    tHora getHoraFin () const{return horaFin;}
    void read(std::istream & entrada = std::cin){
        entrada >> horaInicio >> duracion;
        std::cin.ignore(256,' ');
        getline(entrada, nombre);
    }

    //Metodos de modificacion
    void setName(std::string name){nombre = name;}
    void setHoraInicio(tHora hora){horaInicio = hora;}
    void setDuracion(tHora dur){duracion = dur;}
    void setHoraFin(tHora hora){horaFin = hora;}
    void write(std::ostream& salida = std::cout) const{
        salida << horaFin << " " << nombre;
    }

    void calcularHoraFin(tPelicula& peli){
        setHoraFin(getHoraInicio() + getDuracion());
    }
    

    private:
    //Atributos de la clase
    std::string nombre;
    tHora horaInicio;
    tHora duracion;
    tHora horaFin;
};

std::istream &operator>>(std::istream &entrada, tPelicula &peli) {
    peli.read(entrada);
    return entrada;
}

std::ostream &operator<<(std::ostream &salida, tPelicula const& peli) {
    peli.write(salida);
    return salida;
}
