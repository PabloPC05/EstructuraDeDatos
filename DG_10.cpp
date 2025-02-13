/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
 *  Estudiante 1: Pablo Pardo Cotos
 *@ </answer> */

/*
 * Implementa las operaciones pedidas en el ejercicio al final de
 * este fichero, entre las etiquetas.
 */

#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

class ListLinkedDouble {
private:
   struct Node {
        int value;
        Node *next;
        Node *prev;
    };
    Node *head;
    int num_elems; 
public:
    ListLinkedDouble() : head(nullptr), num_elems(0) {}

    void push_back(int elem) {
        Node* new_node = new Node{elem, nullptr, nullptr};
        if (head == nullptr) {  // If the list is empty
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr) {  // Find the last node
                current = current->next;
            }
            current->next = new_node;
            new_node->prev = current;
        }
        num_elems++;  // Update the element count
    }

    void display() const {
        display(std::cout);
    }

    void display(std::ostream &out) const {
        out << "[";
        Node* current = head;
        while (current != nullptr) {
            out << current->value;
            if (current->next != nullptr) {
                out << ", ";
            }
            current = current->next;
        }
        out << "]";
    }

     void swap2by2() {
        if (head == nullptr || head->next == nullptr) return; // Si la lista está vacía o tiene un solo nodo, no hay nada que intercambiar
        Node* prev = nullptr;
        Node* current = head;
        head = current->next; //El nuevo head será el segundo nodo
        while (current != nullptr && current->next != nullptr) {
            Node* nextPair = current->next->next;
            Node* second = current->next;

            // Intercambiar los punteros
            second->next = current;
            current->next = nextPair;
            if (prev != nullptr) {
                prev->next = second;
            }

            // Mover los punteros hacia adelante
            prev = current;
            current = nextPair;
        }


        // Correccion
        Node* curent = head -> next; 
        while(current != head && current->next != head){
            Node* sale = current-> next;
            //detach(sale); ::
            sale->prev->next = sale->next;
	        sale->next-> prev = sale->prev;
            //attach(sale, current) ::
            sale->prev = current->prev;
	        sale->next = current;
	        current->prev->next = sale;
	        current->prev = sale;
            current = current -> next;
        }
    }
};

bool resuelveCaso() {
   int N;
   cin >> N;
   if (N == 0) return false;   
   ListLinkedDouble lista;
   int elem;
   while (N--) {
    cin >> elem;
    lista.push_back(elem);
   }
   lista.swap2by2();
   lista.display();
   cout << '\n';
   return true;
}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

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

