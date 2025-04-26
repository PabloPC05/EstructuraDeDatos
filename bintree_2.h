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
* Esta implementación utiliza smart pointers para prevenir
* fugas de memoria y problemas con la destrucción.
*/

#ifndef __BINTREE_H
#define __BINTREE_H

#include <cassert>
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <limits>
#include <string>

template <class T> class BinTree {
public:
BinTree() : root_node(nullptr) {}

BinTree(const T &elem)
    : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

BinTree(const BinTree &left, const T &elem, const BinTree &right)
    : root_node(std::make_shared<TreeNode>(left.root_node, elem,
                                            right.root_node)) {}

bool empty() const { return root_node == nullptr; }

const T &root() const {
  assert(root_node != nullptr);
  return root_node->elem;
}

BinTree left() const {
  assert(root_node != nullptr);
  BinTree result;
  result.root_node = root_node->left;
  return result;
}

BinTree right() const {
  assert(root_node != nullptr);
  BinTree result;
  result.root_node = root_node->right;
  return result;
}

void display(std::ostream &out) const { display_node(root_node, out); }

T minimo() const {
  assert(!empty());
  T min = root();
  if (!left().empty()) {
    min = std::min(min, left().minimo());
  }
  if (!right().empty()) {
    min = std::min(min, right().minimo());
  }
  return min;
}

bool esCompleto() const {
  if (empty()) return true;

  bool leftComplete = left().esCompleto();
  bool rightComplete = right().esCompleto();

  if (!leftComplete || !rightComplete) return false;

  int leftHeight = left().altura();
  int rightHeight = right().altura();

  return (leftHeight == rightHeight);
}

int altura() const {
  if (empty()) return 0;
  return 1 + std::max(left().altura(), right().altura());
}


std::pair<int, int> diameterAux() const{
  if(empty()) return {0, 0};  
  auto leftDiameter = left().diameterAux();
  auto rightDiameter = right().diameterAux();
  int height = std::max(leftDiameter.first, rightDiameter.first) + 1;
  int diameter = std::max({leftDiameter.second, rightDiameter.second, leftDiameter.first + rightDiameter.first + 1});
  return {height, diameter};
}


int diameter() const {
  return diameterAux().second;
}


bool es_equilibrado() const{
  if(empty()) return true;
  if(left().empty() && right().empty()) return true;
  if(left().empty() && !right().empty()) return right().altura() <= 1;
  if(!left().empty() && right().empty()) return left().altura() <= 1;
  return left().es_equilibrado() && right().es_equilibrado() && std::abs(left().altura() - right().altura()) <= 1;
}

bool es_estable() const {
  return es_estable_aux(root_node);
}

int numNodos() const {
  if(empty()) return 0;
  return 1 + left().numNodos() + right().numNodos();
}

int min_num_nodos_infectados() const {
  return min_num_nodos_infectados(root_node);
}


static BinTree<T> reconstruir(std::vector<int> const& preorden, std::vector<int> const& inorden){
  if(preorden.size() == 0) return BinTree<T>(); // Si el vector es vacío devolvemos un árbol vacío
  int raiz = preorden[0]; // Por el orden en el que se recorren los nodos en el preorden sabemos que el primer elemento es la raíz
  int pos_raiz = 0; // Buscamos la posición de la raíz en el inorden
  while(inorden[pos_raiz] != raiz) pos_raiz++;  // Buscamos la posición de la raíz en el inorden
  // Tomamos los elementos de la izquierda y de la derecha de la raíz en ambos recorridos
  std::vector<int> preorden_izq(preorden.begin() + 1, preorden.begin() + pos_raiz + 1);
  std::vector<int> preorden_der(preorden.begin() + pos_raiz + 1, preorden.end());
  std::vector<int> inorden_izq(inorden.begin(), inorden.begin() + pos_raiz);
  std::vector<int> inorden_der(inorden.begin() + pos_raiz + 1, inorden.end());
  return BinTree<T>(reconstruir(preorden_izq, inorden_izq), raiz, reconstruir(preorden_der, inorden_der));
}

// Queremos priorizar la rama izquierda
/*std::vector<int> perfil(int nivel = 1) {
  std::vector<int> returnValue;
  if(empty()) return returnValue;
  returnValue.push_back(root());
  std::vector<int> leftProfile = left().perfil(nivel + 1);
  if(nivel >)
}*/

std::vector<T> perfil() {
  std::vector<T> returnValue;
  perfil(returnValue, 0);
  return returnValue;
}


void perfil(std::vector<T>& perfil, int nivel){
  if(empty()) return;
  if(nivel == perfil.size()) perfil.push_back(root());
  left().perfil(perfil, nivel + 1);
  right().perfil(perfil, nivel + 1);
}

std::string maxString(size_t length) {
  return std::string(length, '\xFF'); // Crea un string con 'length' caracteres '\xFF'
}



bool es_de_busqueda(T minVal, T maxVal) const {
  return es_de_busqueda_aux(root_node, minVal, maxVal);
}




private:
  // Las definiciones de TreeNode y NodePointer dependen recursivamente
  // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
  // para que el compilador sepa, cuando analice la definición de NodePointer,
  // que TreeNode va a ser definida más adelante.

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static bool es_de_busqueda_aux(const NodePointer& node, T minVal, T maxVal)  {
    // Si el arbol es vacío o es una hoja devolvemos verdadero
    if (node == nullptr) return true;
    // Si el nodo actual es mayor que el valor máximo o menor que el valor mínimo devolvemos falso
    if (node->elem <= minVal || node->elem >= maxVal) return false;
    return es_de_busqueda_aux(node->left, minVal, node->elem) && es_de_busqueda_aux(node->right, node->elem, maxVal);
  }
  
  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }

  int min_num_nodos_infectados(NodePointer root) const {
    int num_infectados_izq = 0;
    int num_infectados_der = 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    if (root->left != nullptr) num_infectados_izq += min_num_nodos_infectados(root->left);
    if (root->right != nullptr) num_infectados_der += min_num_nodos_infectados(root->right);
    return 1 + std::min(num_infectados_izq, num_infectados_der);
  }

  bool es_estable_aux(NodePointer root) const {
    // Si el árbol es vacío devolvemos true
    if (root == nullptr) return true;
    // Si el árbol es una hoja devolvemos true
    if (root->left == nullptr && root->right == nullptr) return true;
    // Si el árbol tiene un hijo a la izquierda y no tiene hijo a la derecha
    if (root->left != nullptr) {
        NodePointer aux = root->left;
        root->left = nullptr;
        bool equilibrado = es_equilibrado();
        root->left = aux;
        if (!equilibrado) return false;
    }
    // Si el árbol tiene un hijo a la derecha y no tiene hijo a la izquierda
    if (root->right != nullptr) {
        NodePointer aux = root->right;
        root->right = nullptr;
        bool equilibrado = es_equilibrado();
        root->right = aux;
        if (!equilibrado) return false;
    }
    return es_estable_aux(root->left) && es_estable_aux(root->right);
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

#endif