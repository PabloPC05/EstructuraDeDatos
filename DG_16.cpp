#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "queue_linkedlist.h"
using namespace std;
using cola = QueueLinkedList<int>;

cola merge(cola derech, cola izq){
    cola returnCola;
    // Mientras las colas no estén vacías iremos añadiendo valores a la cola de retorno
    while(!derech.empty() || !izq.empty()){
        // Si la cola derecha está vacía, añadimos el valor de la izquierda
        if(derech.empty()){
            returnCola.push(izq.front());
            izq.pop();
        }
        // Si la cola izquierda está vacía, añadimos el valor de la derecha
        else if(izq.empty()){
            returnCola.push(derech.front());
            derech.pop();
        }
        // Si el valor de la derecha es menor que el de la izquierda, añadimos el de la derecha
        else if(derech.front() < izq.front()){
            returnCola.push(derech.front());
            derech.pop();
        }
        // Si el valor de la izquierda es menor que el de la derecha, añadimos el de la izquierda
        else{
            returnCola.push(izq.front());
            izq.pop();
        }
    }
    return returnCola;
}

cola mergeSort(cola q, int size){
    // Si la cola tiene un tamaño menor o igual a 1, la devolvemos
    if(size <= 1) return q;
    cola izq;
    int mitad = size/2;
    // Dividimos la cola en dos mitades
    // Copiamos la primera mitad en la cola izquierda
    for(int i = 0; i < mitad; i++){
        izq.push(q.front());
        q.pop();
    }
    // Al quedar solo los valores de la segunda mitad en la cola, no hace falta crear una nueva cola
    izq = mergeSort(izq, mitad);
    q = mergeSort(q, size - mitad);
    return merge(q, izq)    ;
}

bool resuelveCaso(){
    int size;
    cin >> size;
    if(size == 0) return false; 
    QueueLinkedList<int> cola; 
    for(int i = 0; i < size; i++){
        int elem; 
        cin >> elem; 
        cola.push(elem);
    }
    cola = mergeSort(cola, size);
    while(!cola.empty()){
        cout << cola.front() << " ";
        cola.pop();
    }
    cout << endl;
    return true;
}

int main() {
    #ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    while (resuelveCaso());
    
    #ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
    #endif
    
    return 0;
}
    