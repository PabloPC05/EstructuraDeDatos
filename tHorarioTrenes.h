#include <vector>
#include "tHora.h"
const int MAX_TRENES = 100;
struct tHorarioTrenes {
    tHora horario[MAX_TRENES];
    int num_trenes;
};

void inicia(tHorarioTrenes &trenes){
    for(int i = 0; i < MAX_TRENES; i++) trenes.horario[i] = {0, 0, 0};
    trenes.num_trenes = 0;
}

void inserta(tHorarioTrenes &trenes, tHora const& h){
    trenes.horario[trenes.num_trenes] = h;
    trenes.num_trenes++;
}


bool busca(tHorarioTrenes const& trenes, tHora const& h, tHora &sig){
    int i = 0; 
    while(i < trenes.num_trenes && trenes.horario[i] < h) i++;
    if(i < trenes.num_trenes){
        sig = trenes.horario[i];
        return true;
    }
    else return false;
}