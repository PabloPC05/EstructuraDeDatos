#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 


template <typename Elem> class ListLinkedDouble {
private:
  struct Node {
    Elem value;
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

  void push_front(const Elem &elem) {
    Node *new_node = new Node{elem, head->next, head};
    head->next->prev = new_node;
    head->next = new_node;
    num_elems++;
  }

  void push_back(const Elem &elem) {
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

  const Elem &front() const {
    assert(num_elems > 0);
    return head->next->value;
  }

  Elem &front() {
    assert(num_elems > 0);
    return head->next->value;
  }

  const Elem &back() const {
    assert(num_elems > 0);
    return head->prev->value;
  }

  Elem &back() {
    assert(num_elems > 0);
    return head->prev->value;
  }

  const Elem &operator[](int index) const {
    assert(0 <= index && index < num_elems);
    Node *result_node = nth_node(index);
    return result_node->value;
  }

  Elem &operator[](int index) {
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


  void desparizar(ListLinkedDouble &aux){
    Node* current = head->next;
    while(current != head){
      Node* next = current->next;
      if(current->value % 2 == 0){
        detach(current);
        attach(current, aux.head->prev);
      }
      current = next;
    }
  }


  void unzip(ListLinkedDouble& aux){
    int i = 1;
    Node* current = head->next;
    while(current != head){
      Node* next = current->next;
      if(i % 2 == 0){
        detach(current);
        attach(current, aux.head);
      }
      current = next;
      i++;
    }
  }

private:
  // Cabeza de la lista
  Node *head;
  // Número de elementos de la lista
  int num_elems;

  Node *nth_node(int n) const;
  void delete_nodes();
  void copy_nodes_from(const ListLinkedDouble &other);

  // Operaciones auxiliares. Se implementan más abajo

  // Desengancha un nodo de la lista enlazada
  // Coste lineal O(1) ya que son operaciones de asignación simples
    void detach(Node *n){
      n->prev->next = n->next;
      n->next->prev = n->prev;
    }
  // Engancha un nodo a una lista enlazada, justo antes de position
    void attach(Node *n, Node *position){
      position->prev->next = n;
      n->prev = position->prev;
      position->prev = n;
      n->next = position;
    }
};

template <typename Elem>
typename ListLinkedDouble<Elem>::Node *
ListLinkedDouble<Elem>::nth_node(int n) const {
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != head) {
    current_index++;
    current = current->next;
  }

  return current;
}

template <typename Elem> void ListLinkedDouble<Elem>::delete_nodes() {
  Node *current = head->next;
  while (current != head) {
    Node *target = current;
    current = current->next;
    delete target;
  }

  delete head;
}

template <typename Elem>
void ListLinkedDouble<Elem>::copy_nodes_from(const ListLinkedDouble &other) {
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

template <typename Elem>
void ListLinkedDouble<Elem>::display(std::ostream &out) const {
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

template <typename Elem>
std::ostream &operator<<(std::ostream &out, const ListLinkedDouble<Elem> &l) {
  l.display(out);
  return out;
}

