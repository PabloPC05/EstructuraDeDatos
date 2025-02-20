#include <iostream>
#include <vector>
#include <iomanip>
#ifndef THORA_H
#define THORA_H

class tHora{
    public: 
    
    tHora(int hh = 0, int mm = 0, int ss = 0): hh(hh), mm(mm), ss(ss){}

    //Metodos de acceso
    int getHora() const{return hh;}
    int getMinuto() const{return mm;}
    int getSegundo() const{return ss;}

    //Metodos de modificacion
    void setHora(int hora){hh = hora;}
    void setMinuto(int minuto){mm = minuto;}
    void setSegundo(int segundo){ss = segundo;}

    //Metodos artimetico-logicos
    tHora operator+(tHora const& hora1) const{
        tHora res;
        res.setSegundo((hora1.getSegundo() + ss) % 60);
        res.setMinuto((hora1.getMinuto() + mm + (hora1.getSegundo() + ss) / 60) % 60);
        res.setHora((hora1.getHora() + hh + (hora1.getMinuto() + mm + (hora1.getSegundo() + ss) / 60) / 60) % 24);
        return res;
    }
    bool operator<(tHora const& hora1) const{
        if(hora1.getHora() < hh) return true;
        else if(hora1.getHora() > hh) return false;
        else if(hora1.getMinuto() < mm) return true;
        else if(hora1.getMinuto() > mm) return false;
        else if(hora1.getSegundo() < ss) return true;
        else return false;
    }
    bool operator==(tHora const& hora1) const{
        return hora1.getHora() == hh && hora1.getMinuto() == mm && hora1.getSegundo() == ss;
    }

    //Metodos de lectura y escritura
    void read(std::istream & entrada = std::cin){
        char aux;
        entrada >> hh >> aux >> mm >> aux >> ss;
    }
    void write(std::ostream & salida = std::cout) const{
        salida << std::setfill('0') << std::setw(2) << hh << ':' << std::setfill('0') << std::setw(2) << mm << ':' << std::setfill('0') << std::setw(2) << ss;
    }

    private:
    int hh, mm, ss;
};

    std::istream &operator>>(std::istream & entrada, tHora &hora){
        hora.read(entrada);
        return entrada;
    }
    std::ostream &operator<<(std::ostream & salida, tHora const& hora){
        hora.write(salida);
        return salida;
    }


#endif