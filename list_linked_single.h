#ifndef __LIST_LINKED_SINGLE_H
#define __LIST_LINKED_SINGLE_H

#include <cassert>
#include <iostream>
#include <string>

class ListLinkedSingle {
private:
struct Node {
    int value;
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

void push_front(const int &elem) {
    Node *new_node = new Node{elem, head->next};
    head->next = new_node;
}

void push_back(const int &elem);

void pop_front() {
    assert(head->next != nullptr);
    Node *old_head = head->next;
    head->next = head->next->next;
    delete old_head;
}

void pop_back();

int size() const;

bool empty() const { return head->next == nullptr; };

const int &front() const {
    assert(head->next != nullptr);
    return head->next->value;
}

int &front() {
    assert(head->next != nullptr);
    return head->next->value;
}

const int &back() const { return last_node()->value; }

int &back() { return last_node()->value; }

const int &operator[](int index) const {
    Node *result_node = nth_node(index);
    assert(result_node != nullptr);
    return result_node->value;
}

int &operator[](int index) {
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
    void intersect(const ListLinkedSingle &other);
    // Metodo que devuelve true si la lista contiene el elemento elem
    // Se ha desarrollado teniendo en cuenta que la lista esta ordenada
    // Por lo que se ha hecho uso de la busqueda binaria
    bool contains(int value) const {
        Node* left = head->next;
        Node* right = nullptr;
        
        // Encontrar el último nodo para usarlo como `right`
        Node* temp = head->next;
        while (temp != nullptr) {
            right = temp;
            temp = temp->next;
        }
    
        while (left != right) {
            // Buscar el nodo en la mitad de la lista
            Node* middle = left;
            Node* fast = left;
            
            while (fast != right && fast->next != right) {
                middle = middle->next;
                fast = fast->next->next;
            }
    
            if (middle->value == value) return true;
            if (middle->value < value) left = middle->next;
            else right = middle;
        }
    
        return (left != nullptr && left->value == value);
    }
    
    

    private:
    Node *head;

    void delete_list(Node *start_node);
    Node *last_node() const;
    Node *nth_node(int n) const;
    Node *copy_nodes(Node *start_node) const;
};

ListLinkedSingle::Node *ListLinkedSingle::copy_nodes(Node *start_node) const {
    if (start_node != nullptr) {
        Node *result = new Node{start_node->value, copy_nodes(start_node->next)};
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
    Node *new_node = new Node{elem, nullptr};
    last_node()->next = new_node;
}

void ListLinkedSingle::pop_back() {
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

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node *current = head->next;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}

ListLinkedSingle::Node *ListLinkedSingle::last_node() const {
    Node *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node *ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node *current = head->next;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
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

std::ostream &operator<<(std::ostream &out, const ListLinkedSingle &l) {
    l.display(out);
    return out;
}



// El coste asintótico de esta funcion es de O(n + m) donde n es el tamaño de la lista this y m el tamaño de la lista other
void ListLinkedSingle::intersect(const ListLinkedSingle &other) {
    // Si alguna de las dos listas es vacia
    if(head-> next == nullptr || other.head->next == nullptr) {
        head->next = nullptr;
        return;
    }
    Node *current = head->next;
    Node *prev = nullptr;
    Node *otherCurrent = other.head->next;

    while (current != nullptr && otherCurrent != nullptr) {
        // Si el nodo de `this` es menor, eliminarlo
        if (current->value < otherCurrent->value) {
            Node *temp = current; // Guardar el nodo actual
            current = current->next;    // Avanzar en `this`
            if (prev == nullptr) {  
                head->next = current;  // Si eliminamos el primer nodo real
            } else {
                prev->next = current;
            }
            delete temp;    // Liberamos la memoria del nodo
        } else if (current->value > otherCurrent->value) {
            otherCurrent = otherCurrent->next; // Avanzar en other para encontrar coincidencia
        } else {
            // Mantener el nodo porque está en la intersección
            prev = current;
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        if (prev == nullptr) {
            head->next = current;
        } else {
            prev->next = current;
        }
        delete temp;
    }
}

#endif 