#include <iostream>
#include <iomanip>

#ifndef THORA_H
#define THORA_H

struct tHora {
    int hh; 
    int mm; 
    int ss;
};

bool operator<(tHora const& a, tHora const& b) {
    if (a.hh < b.hh) return true;
    else if (a.hh > b.hh) return false;
    else if (a.mm < b.mm) return true;
    else if (a.mm > b.mm) return false;
    else return a.ss < b.ss;
}

std::istream &operator>>(std::istream &entrada, tHora &hora) {
    char aux; 
    entrada >> hora.hh >> aux >> hora.mm >> aux >> hora.ss; 
    return entrada; 
}

std::ostream &operator<<(std::ostream &salida, tHora const &hora) {
    salida << std::setfill('0') << std::setw(2) << hora.hh << ':'
           << std::setfill('0') << std::setw(2) << hora.mm << ':'
           << std::setfill('0') << std::setw(2) << hora.ss;    
    return salida; 
}

#endif // THORA_H