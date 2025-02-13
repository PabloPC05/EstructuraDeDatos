/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

/*
 * Implementación del TAD Lista mediante listas enlazadas dobles.
 *
 * Esta versión incluye la sobrecarga de operadores <<, [] y asignación.
 */

#ifndef __LIST_LINKED_DOUBLE_H
#define __LIST_LINKED_DOUBLE_H

#include <cassert>
#include <iostream>
#include <string>

class ListLinkedDouble {
private:
  struct Node {
    int value;
    Node *next;
    Node *prev;
  };

public:
  ListLinkedDouble() : num_elems(0) {
    head = new Node;
    head->next = head;
    head->prev = head;
  }

  ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
    copy_nodes_from(other);
    num_elems = other.num_elems;
  }

  ~ListLinkedDouble() { delete_nodes(); }

  void push_front(const int &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }

  void push_back(const int &elem) {
    Node *new_node = new Node{elem, head, head->prev};
    head->prev->next = new_node;
    head->prev = new_node;
    num_elems++;
  }

  void pop_front() {
    assert(num_elems > 0);
    Node *target = head->next;
    head->next = target->next;
    target->next->prev = head;
    delete target;
    num_elems--;
  }

  void pop_back() {
    assert(num_elems > 0);
    Node *target = head->prev;
    target->prev->next = head;
    head->prev = target->prev;
    delete target;
    num_elems--;
  }

  int size() const { return num_elems; }

  bool empty() const { return num_elems == 0; };

  const int &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  int &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const int &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  int &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const int &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  int &operator[](int index) {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  ListLinkedDouble &operator=(const ListLinkedDouble &other) {
    if (this != &other) {
      delete_nodes();
      head = new Node;
      head->next = head->prev = head;
      copy_nodes_from(other);
      num_elems = other.num_elems;
    }
    return *this;
  }

  void display(std::ostream &out) const;

  void display() const { display(std::cout); }

  void detach(Node* node);
  void attach(Node* n1, Node* n2);
  void partition(const int& num);
  void appaned(ListLinkedDouble &ld);
  ListLinkedDouble split(int num);
  void display_reverse();
  void zip(ListLinkedDouble other);

private:
  Node *head;
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

void ListLinkedDouble::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
  Node *current_other = other.head->next;
  Node *last = head;

  while (current_other != other.head) {
    Node *new_node = new Node{current_other->value, head, last};
    last->next = new_node;
    last = new_node;
    current_other = current_other->next;
  }
  head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
  out << "[";
  if (head->next != head) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != head) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
  l.display(out);
  return out;
}

// El coste asintotico es cosntante O(1)
void ListLinkedDouble::detach(Node* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

// Inserta el nodo node en la posición pos
// El coste asintotico es constante O(1)
void ListLinkedDouble::attach(Node* node, Node* pos){
    node->prev = pos->prev;
    node->next = pos;
    pos->prev->next = node;
    pos->prev = node;
}

void ListLinkedDouble::appaned(ListLinkedDouble &l2){
  head->prev->next = l2.head->next;
  l2.head->next->prev = head->prev; 
  l2.head->prev->next = head;
  head->prev = l2.head->prev;
  l2.head->prev = l2.head->next = l2.head;

  num_elems += l2.num_elems;
}

/*ListLinkedDouble ListLinkedDouble::split(int i){
  Node* primer = nth_node(i);
  ListLinkedDouble res;
  res.head->next = primer; 
  res.head->prev = head->prev;
  primer->prev->next = head;
  head->prev = primer->prev;
  primer->prev = res.head;
  head->prev = primer->prev = res.head;
  res.num_elems = num_elems - i;
  num_elems = i;
  return res;
}*/

// Coste asintótico es O(n) siendo n el numero de elementos de la lista
void ListLinkedDouble::partition(const int& num){
  // Cogemos el primer elemento de la lista dado que se trata de una clase con nodo fantasma
  Node* current = head->next; 
  // Recorremos la lista en busca de la particion
  Node* last_low = head; 

  for(int i = 0; i < num_elems; i++){
    // Si el valor del nodo actual es menor que el numero dado
    // Entonces tendremos que mover el nodo al siguiente lugar del ultimo nodo que ha sido menor que el numero
    Node* next = current->next;
    if(current->value <= num){
      // Guardamos el nodo actual
      Node* aux = current;
      // Movemos el nodo al siguiente lugar del ultimo nodo que ha sido menor que el numero
      detach(aux);
      attach(aux, last_low->next);
      // Actualizamos el ultimo nodo que ha sido menor que el numero
      last_low = aux;
    }
    // Si el valor del nodo actual es mayor que el numero dado no se hace nada ya que solo movemos aquellos que son menores
    current = next; 
  }
}


void ListLinkedDouble::display_reverse(){
  std::cout << "[";
  if(head->prev != head){
    std::cout << head->prev->value;
    Node* current = head->prev->prev;
    while(current != head){
      std::cout << ", " << current->value;
      current = current->prev;
    }
  }
  std::cout << "]";
}

// El coste asintótico de la funcion es O(n+m)
// Siendo n y m el numero de elementos de la lista1 y lista2 respectivamente
void ListLinkedDouble::zip(ListLinkedDouble other){
  Node* current1 = head->next;
  Node* current2 = other.head->next;
  Node* next1;
  Node* next2;
  // Mientras no se haya recorrido toda la lista1 y la lista2
  while(current1 != head && current2 != other.head){
    next1 = current1->next; // Guardamos el siguiente nodo de la lista1
    next2 = current2->next; // Guardamos el siguiente nodo de la lista2
    other.detach(current2); // Desconectamos el nodo de la lista2
    attach(current2, current1->next); // Conectamos el nodo de la lista2 en la lista1
    current1 = next1; // Actualizamos el nodo de la lista1
    current2 = next2; // Actualizamos el nodo de la lista2
  }
  // Si aun quedan elementos de la lista 2 que no sean recorrido
  while(current2 != other.head){
    next2 = current2->next;
    other.detach(current2);
    attach(current2, head);
    current2 = next2;
  }
  // Vaciamos la lista2
  other.head->next = other.head;
  other.head->prev = other.head;
  other.num_elems = 0;
  num_elems += other.num_elems;
}

#endif
