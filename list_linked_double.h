#ifndef __LIST_LINKED_DOUBLE_H
#define __LIST_LINKED_DOUBLE_H

#include <cassert>
#include <iostream>

template <typename T>
class ListLinkedDouble {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const T& elem) {
        Node* new_node = new Node{elem, head->next, head};
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const T& elem) {
        Node* new_node = new Node{elem, head, head->prev};
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const T& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    T& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const T& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    T& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const T& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    T& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }
    int eliminarSaltando(const int& Q);
    T elem(Node* n);
    Node* advance(Node* n);
    class reverse_iterator{
        private:
            Node* current;
            Node* head;
            reverse_iterator(Node* h, Node* n) : head(h), current(n) {}
        public:
        friend class ListLinkedDouble;
        T elem()const {return current->value;}

        void advance(){
            current = current->prev;
        }

        T elem(Node* n){
            return n->value;
        }

        bool operator!=(const reverse_iterator& other) const {return current != other.current;}
    };

    reverse_iterator rbegin(){
        return reverse_iterator(head, head->prev);
    }
    
    reverse_iterator rend(){
        return reverse_iterator(head, head);
    }



    void reverse();

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};

template <typename T>
typename ListLinkedDouble<T>::Node* ListLinkedDouble<T>::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename T>
void ListLinkedDouble<T>::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{current_other->value, head, last};
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

template <typename T>
void ListLinkedDouble<T>::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<T>& l) {
    l.display(out);
    return out;
}

template <typename T> 
int ListLinkedDouble<T>::eliminarSaltando(const int& Q){
    // Tomamos un nodo auxiliar que almacenará el nodo a elimianr
    Node* to_delete = head->next;
    Node* indice = to_delete;
    while(num_elems != 1){
        // Realizamos los sucesivos saltos hasta llegar al nodo a eliminar
        for(int i = 0; i < Q; i++){
            // Tomamos el siguiente
            indice = indice->next;
            // Si hemos llegado al fin de la lista, volvemos a empezar
            if(indice == head) indice = indice->next;
        }
        to_delete = indice;
        indice = indice->next;
        if(indice == head) indice = indice->next;
        // Una vez ya tenemos el nodo que queremos eliminar, lo tenemos que sacar de la lista
        to_delete->prev->next = to_delete->next;
        to_delete->next->prev = to_delete->prev;
        // Eliminamos el nodo
        delete to_delete;
        // Actualizamos el número de elementos
        num_elems--;
    }
    return indice->value;
}

template <typename T>
void ListLinkedDouble<T>::reverse(){
    Node* current = head->next;
    Node* aux;
    while(current != head){
        aux = current->next;
        current->next = current->prev;
        current->prev = aux;
        current = aux;
    }
    aux = head->next;
    head->next = head->prev;
    head->prev = aux;
}

#endif
