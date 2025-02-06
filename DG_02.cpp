#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


class Complejo {
    private:
        double parteReal, parteImaginaria;

    public:
        Complejo() : parteReal(0), parteImaginaria(0) {}
        Complejo(double pR, double pI) : parteReal(pR), parteImaginaria(pI) {}
        ~Complejo() {}
        Complejo(const Complejo &other) : parteReal(other.parteReal), parteImaginaria(other.parteImaginaria) {}
        Complejo operator+(const Complejo &other) const {
            return Complejo(parteReal + other.parteReal, parteImaginaria + other.parteImaginaria);
        }
        Complejo operator*(const Complejo &other) const {
            return Complejo(parteReal * other.parteReal - parteImaginaria * other.parteImaginaria,
                            parteReal * other.parteImaginaria + parteImaginaria * other.parteReal);
        }
        double modulo() const {
            return sqrt(abs(parteReal * parteReal + parteImaginaria * parteImaginaria));
        }
        bool esDeMandelbrot(int numIteraciones) const {
            Complejo z(0, 0); // z0 = 0
            for (int i = 0; i < numIteraciones; i++) {
                z = z * z + *this; // zn = zn-1^2 + c, donde c es *this
                if (z.modulo() > 2) return false; // Si el módulo es mayor que 4, la serie es divergente
            }
            return true; // Si se alcanza la n-ésima iteración sin divergencia, el número pertenece al conjunto de Mandelbrot
        }

};


void resuelveCaso(){
    double parteReal, parteImaginaria, numIteraciones; 
    cin >> parteReal >> parteImaginaria >> numIteraciones;
    Complejo c(parteReal, parteImaginaria);
    c.modulo();
    if(c.esDeMandelbrot(numIteraciones)) cout << "SI\n";
    else cout << "NO\n";
}

int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   int numCasos; 
   cin >> numCasos; 
   while (numCasos--) resuelveCaso();
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se necesita
  // system("PAUSE");
#endif

   return 0;
}

