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

class ListLinkedSingle {
private:
   struct Node {
      int value;
      Node *next;
   };
   
public:
   ListLinkedSingle(): head(nullptr) { }
   ~ListLinkedSingle() {
      delete_list(head);
   }
   
   ListLinkedSingle(const ListLinkedSingle &other)
   : head(copy_nodes(other.head)) { }
   
   void push_front(const int &elem) {
      Node *new_node = new Node { elem, head };
      head = new_node;
   }
   
   void push_back(const int &elem);
   
   void pop_front() {
      assert (head != nullptr);
      Node *old_head = head;
      head = head->next;
      delete old_head;
   }
   
   void pop_back();
   
   int size() const;
   
   bool empty() const {
      return head == nullptr;
   };
   
   const int & front() const {
      assert (head != nullptr);
      return head->value;
   }
   
   int & front() {
      assert (head != nullptr);
      return head->value;
   }
   
   const int & back() const {
      return last_node()->value;
   }
   
   int & back() {
      return last_node()->value;
   }
   
   const int & at(int index) const {
      Node *result_node = nth_node(index);
      assert(result_node != nullptr);
      return result_node->value;
   }
   
   int & at(int index) {
      Node *result_node = nth_node(index);
      assert(result_node != nullptr);
      return result_node->value;
   }
   
   void display(std::ostream &out) const;
   void display() const {
      display(std::cout);
   }
   
   // Nuevo método. Debe implementarse abajo
   void reverse_segment(int index, int length);
   
private:
   Node *head;
   
   void delete_list(Node *start_node);
   Node *last_node() const;
   Node *nth_node(int n) const;
   Node *copy_nodes(Node *start_node) const;
   
};

ListLinkedSingle::Node * ListLinkedSingle::copy_nodes(Node *start_node) const {
   if (start_node != nullptr) {
      Node *result = new Node { start_node->value, copy_nodes(start_node->next) };
      return result;
   } else {
      return nullptr;
   }
}

void ListLinkedSingle::delete_list(Node *start_node) {
   if (start_node != nullptr) {
      delete_list(start_node->next);
      delete start_node;
   }
}

void ListLinkedSingle::push_back(const int &elem) {
   Node *new_node = new Node { elem, nullptr };
   if (head == nullptr) {
      head = new_node;
   } else {
      last_node()->next = new_node;
   }
}

void ListLinkedSingle::pop_back() {
   assert (head != nullptr);
   if (head->next == nullptr) {
      delete head;
      head = nullptr;
   } else {
      Node *previous = head;
      Node *current = head->next;
      
      while (current->next != nullptr) {
         previous = current;
         current = current->next;
      }
      
      delete current;
      previous->next = nullptr;
   }
}

int ListLinkedSingle::size() const {
   int num_nodes = 0;
   
   Node *current = head;
   while (current != nullptr) {
      num_nodes++;
      current = current->next;
   }
   
   return num_nodes;
}


ListLinkedSingle::Node * ListLinkedSingle::last_node() const {
   assert (head != nullptr);
   Node *current = head;
   while (current->next != nullptr) {
      current = current->next;
   }
   return current;
}

ListLinkedSingle::Node * ListLinkedSingle::nth_node(int n) const {
   assert (0 <= n);
   int current_index = 0;
   Node *current = head;
   
   while (current_index < n && current != nullptr) {
      current_index++;
      current = current->next;
   }
   
   return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
   out << "[";
   if (head != nullptr) {
      out << head->value;
      Node *current = head->next;
      while (current != nullptr) {
         out << ", " << current->value;
         current = current->next;
      }
   }
   out << "]";
}


// ----------------------------------------------------------------
// ¡No modificar nada por encima de esta línea!

// Implementa a continuación el método pedido.
//@ <answer>

// Funcion que invierte los valores de una lista a partir de un indice y hasta una longitud
void ListLinkedSingle::reverse_segment(int index, int length) {
   for(int i = 0; i < length/2; i++){
      Node *current = nth_node(i + index);
      Node *destino = nth_node(length + index - i - 1);
      int aux = current->value;
      current->value = destino->value;
      destino->value = aux;
   }  
}
// El coste asintótico de la funcion reverse_segment es lineal O(n) siendo n el tamaño de la lista
// Ya que en el peor de los casos recorrerá la lista entera, pues está inviertiendo el orden de todo el vector
// En el mejor de los casos, si la longitud es 0 ó 1, no hará nada, por lo que el coste será constante O(1)

using namespace std;

bool resuelveCaso() {
   int N, P, L;
   cin >> N >> P >> L;
   if (!cin)
      return false;
   
   ListLinkedSingle lista;
   int elem;
   while (N--) {
      cin >> elem;
      lista.push_back(elem);
   }
   lista.reverse_segment(P, L);
   
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

