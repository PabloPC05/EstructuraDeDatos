#include <iostream>
#include <vector>
using namespace std;

const int MAX_ELEMS = 2000;

class Multiconjunto {
    public:
        Multiconjunto() : num_elems(0) {}
    
        int buscar(int elem) {
            int izq = 0, der = num_elems - 1;
            while (izq <= der) {
                int mid = (izq + der) / 2;
                if (elems[mid].valor == elem) return mid;
                else if (elems[mid].valor < elem) izq = mid + 1;
                else der = mid - 1;
            }
            return -1;
        }
    
        void anyadir(int elem) {
            int pos = buscar(elem);
            if (pos != -1) {
                elems[pos].multiplicidad++;
                return;
            }
            int i;
            for (i = num_elems - 1; i >= 0 && elems[i].valor > elem; i--) {
                elems[i + 1] = elems[i];
            }
            elems[i + 1] = {elem, 1};
            num_elems++;
        }
    
        bool eliminar(int elem) {
            int pos = buscar(elem);
            if (pos == -1 || elems[pos].multiplicidad == 0) return false;
            elems[pos].multiplicidad--;
            return true;
        }
    
        bool pertenece(int elem) {
            int pos = buscar(elem);
            return (pos != -1 && elems[pos].multiplicidad > 0);
        }
    
    private:
        struct Elem {
            int valor, multiplicidad;
        };
        Elem elems[MAX_ELEMS];
        int num_elems;
    };