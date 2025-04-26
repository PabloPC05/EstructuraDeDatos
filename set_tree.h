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
 * Implementación del TAD Conjunto mediante árboles binarios de búsqueda.
 *  
 * Esta versión añade iteradores.
 */

 #ifndef __SET_TREE_H
 #define __SET_TREE_H
 
 #include <cassert>
 #include <iostream>
 #include <stack>
 
 template <typename T, typename ComparatorFunction = std::less<T>>
 class SetTree {
 
 private:
   struct Node;
 
 public:
   SetTree(ComparatorFunction less_than)
       : root_node(nullptr), num_elems(0), less_than(less_than) {}
   SetTree() : root_node(nullptr), num_elems(0) {}
   SetTree(const SetTree &other)
       : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
   ~SetTree() { delete_nodes(root_node); }
 
   void insert(const T &elem) {
     bool inserted = insert(root_node, elem);
     if (inserted) {
       num_elems++;
     }
   }
 
   bool contains(const T &elem) const { return search(root_node, elem); }
 
   void erase(const T &elem) {
     bool removed = erase(root_node, elem);
     if (removed) {
       num_elems--;
     }
   }
 
   int size() const { return num_elems; }
   bool empty() const { return num_elems == 0; }
 
   SetTree &operator=(const SetTree &other) {
     if (this != &other) {
       num_elems = other.num_elems;
       delete_nodes(root_node);
       root_node = copy_nodes(other.root_node);
     }
     return *this;
   }
 
   void display(std::ostream &out) const {
     out << "{";
     display(root_node, out);
     out << "}";
   }
 
   class iterator {
   public:
     const T &operator*() const {
       assert(!st.empty());
       return st.top()->elem;
     }
 
     const T *operator->() const { return &operator*(); }
 
     iterator &operator++() {
       assert(!st.empty());
       Node *top = st.top();
       st.pop();
       descend_and_push(top->right, st);
       return *this;
     }
 
     iterator operator++(int) {
       iterator previous = *this;
       ++(*this);
       return previous;
     }
 
     bool operator==(const iterator &other) { return st == other.st; }
 
     bool operator!=(const iterator &other) { return !this->operator==(other); }



 
   private:
     friend class SetTree;
 
     iterator() {}
 
     iterator(Node *root) { descend_and_push(root, st); }
 
     std::stack<Node *> st;
     static void descend_and_push(Node *node, std::stack<Node *> &st) {
       Node *current = node;
       while (current != nullptr) {
         st.push(current);
         current = current->left;
       }
     }
   };

   T min() const {
    assert(root_node != nullptr); // Debe haber al menos un elemento en el árbol
    return find_min(root_node)->elem; // Devuelve el elemento del nodo mínimo
  }

  void erase_min() {
    assert(root_node != nullptr);
    erase_min(root_node);
}

  std::pair<bool, int> lower_bound(const T& elem) const{
    return lower_bound(root_node, elem);
  }
 
   iterator begin() const { return iterator(root_node); }
 
   iterator end() const { return iterator(); }

   int count_interval(const T& lower, const T& upper) const {
    auto lower_it = lower_bound(root_node, lower); // Encuentra el primer elemento >= lower
    auto upper_it = lower_bound(root_node, upper + 1); // Encuentra el primer elemento > upper

    int count = 0;

    // Iteramos entre los dos límites
    while (lower_it.first && lower_it.second < upper_it.second) {
        count++;
        lower_it = lower_bound(root_node, lower_it.second + 1); // Avanza al siguiente elemento
    }

    return count;
  }
 
 private:
   struct Node {
     T elem;
     Node *left, *right;
 
     Node(Node *left, const T &elem, Node *right)
         : left(left), elem(elem), right(right) {}
   };
 
   Node *root_node;
   int num_elems;
 
   ComparatorFunction less_than;
 
   static Node *copy_nodes(const Node *node) {
     if (node == nullptr) {
       return nullptr;
     } else {
       return new Node(copy_nodes(node->left), node->elem,
                       copy_nodes(node->right));
     }
   }
 
   static void delete_nodes(const Node *node) {
     if (node != nullptr) {
       delete_nodes(node->left);
       delete_nodes(node->right);
       delete node;
     }
   }
 
   bool insert(Node *&root, const T &elem) {
     if (root == nullptr) {
       root = new Node(nullptr, elem, nullptr);
       return true;
     } else if (less_than(elem, root->elem)) {
       return insert(root->left, elem);
     } else if (less_than(root->elem, elem)) {
       return insert(root->right, elem);
     } else {
       return false;
     }
   }
 
   bool search(const Node *root, const T &elem) const {
     if (root == nullptr) {
       return false;
     } else if (less_than(elem, root->elem)) {
       return search(root->left, elem);
     } else if (less_than(root->elem, elem)) {
       return search(root->right, elem);
     } else {
       return true;
     }
   }
 
   bool erase(Node *&root, const T &elem) {
     if (root == nullptr) {
       return false;
     } else if (less_than(elem, root->elem)) {
       return erase(root->left, elem);
     } else if (less_than(root->elem, elem)) {
       return erase(root->right, elem);
     } else {
       remove_root(root);
       return true;
     }
   }
 
   static void remove_root(Node *&root) {
     Node *left_child = root->left, *right_child = root->right;
     delete root;
     if (left_child == nullptr && right_child == nullptr) { // Caso sin hijos
       root = nullptr;
     } else if (left_child == nullptr) { // Caso solo hijo derecho
       root = right_child;
     } else if (right_child == nullptr) { // Caso solo hijo izquierdo
       root = left_child;
     } else { // Caso con dos hijos
       Node *lowest = remove_lowest(right_child); 
       lowest->left = left_child;
       lowest->right = right_child;
       root = lowest;
     }
   }
 
   static Node *remove_lowest(Node *&root) {
     assert(root != nullptr);
     if (root->left == nullptr) {
       Node *result = root;
       root = root->right;
       return result;
     } else {
       return remove_lowest(root->left);
     }
   }
 
   static void display(Node *root, std::ostream &out) {
     if (root != nullptr) {
       if (root->left != nullptr) {
         display(root->left, out);
         out << ", ";
       }
       out << root->elem;
       if (root->right != nullptr) {
         out << ", ";
         display(root->right, out);
       }
     }
   }

   int count_interval(Node *root, const T &a, const T &b) const {
     if (root == nullptr) {
       return 0;
     } else if (less_than(root->elem, a)) {
       return count_interval(root->right, a, b);
     } else if (less_than(b, root->elem)) {
       return count_interval(root->left, a, b);
     } else {
       return 1 + count_interval(root->left, a, b) + count_interval(root->right, a, b);
     }
   }

   // Método que devuelve el mayor elemento que es menor o igual que elem
  std::pair<bool, T> lower_bound(Node* root, const T& elem) const {
      if (root == nullptr) {
          return {false, T()}; // Usar el constructor por defecto de T
      } else if (less_than(root->elem, elem)) {
          return lower_bound(root->right, elem);
      } else if (less_than(elem, root->elem)) {
          auto res = std::make_pair(true, root->elem);
          auto posible_res = lower_bound(root->left, elem);
          if (posible_res.first) return posible_res;
          else return res;
      } else {
          return {true, root->elem};
      }
  }
  
  void erase_min(Node*& root) {
    if (root == nullptr) return; // Si root es nullptr, no hacemos nada.
    if (root->left == nullptr) { 
        // Si no hay hijo izquierdo, root es el nodo mínimo.
        Node* temp = root;
        root = root->right; // Puede ser nullptr si no hay hijo derecho.
        delete temp;
    } else {
        // Continuamos buscando por el subárbol izquierdo.
        erase_min(root->left);
    }
}
};
 
  template <typename T>
  std::ostream &operator<<(std::ostream &out, const SetTree<T> &set) {
    set.display(out);
    return out;
  }
  #endif