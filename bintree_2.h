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


bool es_estable() const{
  if(empty()) return true;
  if(left().empty() && right().empty()) return true;
  if(left().empty() && !right().empty()) return right().altura() <= 1;
  if(!left().empty() && right().empty()) return left().altura() <= 1;
  return left().es_estable() && right().es_estable() && std::abs(left().altura() - right().altura()) <= 1;
}

bool es_equilibrado const{
  
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