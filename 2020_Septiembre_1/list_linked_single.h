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
 * Implementación del TAD Lista mediante listas enlazadas simples.
 *
 * Esta versión introduce genericidad mediante plantillas.
 */

#ifndef __LIST_LINKED_SINGLE_H
#define __LIST_LINKED_SINGLE_H

#include <cassert>
#include <iostream>
#include <string>

template <typename Elem> class ListLinkedSingle {
private:
  struct Node {
    Elem value;
    Node *next;
  };

public:
  ListLinkedSingle() {
    head = new Node;
    head->next = nullptr;
  }

  ~ListLinkedSingle() { delete_list(head); }

  ListLinkedSingle(const ListLinkedSingle &other)
      : head(copy_nodes(other.head)) {}

  void push_front(const Elem &elem) {
    Node *new_node = new Node{elem, head->next};
    head->next = new_node;
  }

  void push_back(const Elem &elem);

  void pop_front() {
    assert(head->next != nullptr);
    Node *old_head = head->next;
    head->next = head->next->next;
    delete old_head;
  }

  void pop_back();

  int size() const;

  bool empty() const { return head->next == nullptr; };

  const Elem &front() const {
    assert(head->next != nullptr);
    return head->next->value;
  }

  Elem &front() {
    assert(head->next != nullptr);
    return head->next->value;
  }

  const Elem &back() const { return last_node()->value; }

  Elem &back() { return last_node()->value; }

  const Elem &operator[](int index) const {
    Node *result_node = nth_node(index);
    assert(result_node != nullptr);
    return result_node->value;
  }

  Elem &operator[](int index) {
    Node *result_node = nth_node(index);
    assert(result_node != nullptr);
    return result_node->value;
  }

  ListLinkedSingle &operator=(const ListLinkedSingle &other) {
    if (this != &other) {
      delete_list(head);
      head = copy_nodes(other.head);
    }
    return *this;
  }

  void display(std::ostream &out) const;

  void display() const { display(std::cout); }

  Node* buble_sort_aux(Node* limit){
    Node* prev = head;
    Node *current = head->next;
    while(current->next != limit){
        if(current->value > current->next->value){   // Intercambiamos los dos elementos
            prev->next = current->next;
            Node* temp = current->next;
            current->next = temp->next;
            temp->next = current;
            prev = temp;
        } else{
            prev = current;
            current = current->next;
        }
    }
    return current;
  }

void buble_sort() {
    Node* limit = nullptr; // Al principio, nada está ordenado
    while (head->next != limit) {
        limit = buble_sort_aux(limit);
    }
}


void partition(const int& pivote){
  Node* current = head->next;
  Node* prev = head;
  bool si = false;
  Node* last = head;
  while(current != last){
    Node* next = current->next;
    if(current->value > pivote){ // Si el siguiente al actual es mayor que el pivote
      prev->next = current->next;
      last_node()->next = current;
      current->next = nullptr;
      if(!si){
        si = true;
        last = current;
      }
      current = next;
    } else{
      prev = current;
      current = next;
    }
  }
}

private:
  Node *head;

  void delete_list(Node *start_node);
  Node *last_node() const;
  Node *nth_node(int n) const;
  Node *copy_nodes(Node *start_node) const;
};

template <typename Elem>
typename ListLinkedSingle<Elem>::Node *
ListLinkedSingle<Elem>::copy_nodes(Node *start_node) const {
  if (start_node != nullptr) {
    Node *result = new Node{start_node->value, copy_nodes(start_node->next)};
    return result;
  } else {
    return nullptr;
  }
}

template <typename Elem>
void ListLinkedSingle<Elem>::delete_list(Node *start_node) {
  if (start_node != nullptr) {
    delete_list(start_node->next);
    delete start_node;
  }
}

template <typename Elem>
void ListLinkedSingle<Elem>::push_back(const Elem &elem) {
  Node *new_node = new Node{elem, nullptr};
  last_node()->next = new_node;
}

template <typename Elem> void ListLinkedSingle<Elem>::pop_back() {
  assert(head->next != nullptr);
  Node *previous = head;
  Node *current = head->next;

  while (current->next != nullptr) {
    previous = current;
    current = current->next;
  }

  delete current;
  previous->next = nullptr;
}

template <typename Elem> int ListLinkedSingle<Elem>::size() const {
  int num_nodes = 0;

  Node *current = head->next;
  while (current != nullptr) {
    num_nodes++;
    current = current->next;
  }

  return num_nodes;
}

template <typename Elem>
typename ListLinkedSingle<Elem>::Node *
ListLinkedSingle<Elem>::last_node() const {
  Node *current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  return current;
}

template <typename Elem>
typename ListLinkedSingle<Elem>::Node *
ListLinkedSingle<Elem>::nth_node(int n) const {
  assert(0 <= n);
  int current_index = 0;
  Node *current = head->next;

  while (current_index < n && current != nullptr) {
    current_index++;
    current = current->next;
  }

  return current;
}

template <typename Elem>
void ListLinkedSingle<Elem>::display(std::ostream &out) const {
  out << "[";
  if (head->next != nullptr) {
    out << head->next->value;
    Node *current = head->next->next;
    while (current != nullptr) {
      out << ", " << current->value;
      current = current->next;
    }
  }
  out << "]";
}

template <typename Elem>
std::ostream &operator<<(std::ostream &out, const ListLinkedSingle<Elem> &l) {
  l.display(out);
  return out;
}

#endif