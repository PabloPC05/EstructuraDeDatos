#include <iostream>
#include <vector>
#include <iomanip>
#ifndef TDIA_H
#define TDIA_H
class tDia{
    int dia, mes, anyo;
    public:
    tDia(int d = 0, int m = 0, int a = 0): dia(d), mes(m), anyo(a){}
    int getDia() const{return dia;}
    int getMes() const{return mes;}
    int getAnyo() const{return anyo;}
    void setDia(int d){dia = d;}
    void setMes(int m){mes = m;}
    void setAnyo(int a){anyo = a;}
    tDia operator+(tDia const& dia1) const{
        tDia res;
        res.setDia((dia1.getDia() + dia) % 30);
        res.setMes((dia1.getMes() + mes + (dia1.getDia() + dia) / 30) % 12);
        res.setAnyo(dia1.getAnyo() + anyo + (dia1.getMes() + mes + (dia1.getDia() + dia) / 30) / 12);
        return res;
    }
    bool operator<(tDia const& dia1) const{
        if(dia1.getAnyo() < anyo) return true;
        else if(dia1.getAnyo() > anyo) return false;
        else if(dia1.getMes() < mes) return true;
        else if(dia1.getMes() > mes) return false;
        else if(dia1.getDia() < dia) return true;
        else return false;
    }
    bool operator==(tDia const& dia1) const{
        return dia1.getAnyo() == anyo && dia1.getMes() == mes && dia1.getDia() == dia;
    }
    void read(std::istream & entrada = std::cin){
        char aux;
        entrada >> dia >> aux >> mes >> aux >> anyo;
    }
    void write(std::ostream & salida = std::cout) const{
        salida << std::setfill('0') << std::setw(2) << dia << '/' << std::setfill('0') << std::setw(2) << mes << '/' << std::setfill('0') << std::setw(4) << anyo;
    }
};
    std::istream &operator>>(std::istream & entrada, tDia &dia){
        dia.read(entrada);
        return entrada;
    }
    std::ostream &operator<<(std::ostream & salida, tDia const& dia){
        dia.write(salida);
        return salida;
    }
#endif
// #endif
