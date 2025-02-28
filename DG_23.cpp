/*@ <authors>
 *
Diego Rodríguez Cubero DG30
Pablo Pardo Cotos DG26
 *
 *@ </authors> */

 #include <iostream>
 #include <fstream>
 #include <cassert>
 #include <string>
 
 /*
   Implementación de listas doblemente enlazadas circulares
 
   https://github.com/manuelmontenegro/ED/blob/main/lineales/list_linked_double_v4/list_linked_double.h
 
 */
 
 class ListLinkedDouble
 {
 private:
     struct Node
     {
         int value;
         Node *next;
         Node *prev;
     };
 
 public:
     ListLinkedDouble() : num_elems(0)
     {
         head = new Node;
         head->next = head;
         head->prev = head;
     }
 
     ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble()
     {
         copy_nodes_from(other);
         num_elems = other.num_elems;
     }
 
     ~ListLinkedDouble() { delete_nodes(); }
 
     void push_front(const int &elem)
     {
         Node *new_node = new Node{elem, head->next, head};
         head->next->prev = new_node;
         head->next = new_node;
         num_elems++;
     }
 
     void push_back(const int &elem)
     {
         Node *new_node = new Node{elem, head, head->prev};
         head->prev->next = new_node;
         head->prev = new_node;
         num_elems++;
     }
 
     void pop_front()
     {
         assert(num_elems > 0);
         Node *target = head->next;
         head->next = target->next;
         target->next->prev = head;
         delete target;
         num_elems--;
     }
 
     void pop_back()
     {
         assert(num_elems > 0);
         Node *target = head->prev;
         target->prev->next = head;
         head->prev = target->prev;
         delete target;
         num_elems--;
     }
 
     int size() const { return num_elems; }
 
     bool empty() const { return num_elems == 0; };
 
     const int &front() const
     {
         assert(num_elems > 0);
         return head->next->value;
     }
 
     int &front()
     {
         assert(num_elems > 0);
         return head->next->value;
     }
 
     const int &back() const
     {
         assert(num_elems > 0);
         return head->prev->value;
     }
 
     int &back()
     {
         assert(num_elems > 0);
         return head->prev->value;
     }
 
     const int &operator[](int index) const
     {
         assert(0 <= index && index < num_elems);
         Node *result_node = nth_node(index);
         return result_node->value;
     }
 
     int &operator[](int index)
     {
         assert(0 <= index && index < num_elems);
         Node *result_node = nth_node(index);
         return result_node->value;
     }
 
     ListLinkedDouble &operator=(const ListLinkedDouble &other)
     {
         if (this != &other)
         {
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
 
     // Implementa este método más abajo
     void sort_and_dedup();
 
 private:
     Node *head;
     int num_elems;
 
     Node *nth_node(int n) const;
     void delete_nodes();
     void copy_nodes_from(const ListLinkedDouble &other);
 
     // Métodos privados. Impleméntalos más abajo
     Node *minimum(Node *begin, Node *end) const;
     void detach(Node *n);
     void attach(Node *n, Node *position);
 };
 
 ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const
 {
     int current_index = 0;
     Node *current = head->next;
 
     while (current_index < n && current != head)
     {
         current_index++;
         current = current->next;
     }
 
     return current;
 }
 
 void ListLinkedDouble::delete_nodes()
 {
     Node *current = head->next;
     while (current != head)
     {
         Node *target = current;
         current = current->next;
         delete target;
     }
 
     delete head;
 }
 
 void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other)
 {
     Node *current_other = other.head->next;
     Node *last = head;
 
     while (current_other != other.head)
     {
         Node *new_node = new Node{current_other->value, head, last};
         last->next = new_node;
         last = new_node;
         current_other = current_other->next;
     }
     head->prev = last;
 }
 
 void ListLinkedDouble::display(std::ostream &out) const
 {
     out << "[";
     if (head->next != head)
     {
         out << head->next->value;
         Node *current = head->next->next;
         while (current != head)
         {
             out << ", " << current->value;
             current = current->next;
         }
     }
     out << "]";
 }
 
 std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l)
 {
     l.display(out);
     return out;
 }
 
 //---------------------------------------------------------------
 // Modificar a partir de aquí
 // --------------------------------------------------------------
 //@ <answer>
 
 /*
 Explicacion del algoritmo:
 Primero ordenamos el vector, para ello hacemos lo siguiente:
     - Buscamos el minimo de los elementos no ordenados todavia (vamos recorriendo el vector, ordenando 1 elemento en cada vuelta) con la funcion minimun
     - Lo quitamos de su posicion con la funcion dettach
     - Lo añadimos justo despues del ultimo elemento ordenado
 Despues recorremos los elementos de nuevo borrando los repetidos, para ello:
     - Comprobamos si el nodo actual y el siguiente comparten valor (al estar ordenados, si hay un valor repetido debera estar justo despues de su primera aparicion (si hay mas de 2 veces un valor, estaran todos seguidos))
     - Si coinciden, eliminamos el primero (decision de los desarrolladores) para que asi no se repita (si hay varios en secuencia iguales se borraran en las siguientes iteraciones del bucle)
     - Si no coinciden, solo pasamos al siguiente nodo
 Asi el vector estara ordenado y sin elementos repetidos
 */
 
 // NOTA: n representa siempre la cantidad de nodos de la lista (num_elems)
 
 // Coste: O(n)
 // Ya que recorremos la lista (n nodos) una sola vez, haciendo en el caso peor 2 comprobaciones y 2 asignaciones
 // Todo ello de coste constante, asi el coste total de la funcion es O(n) lineal
 ListLinkedDouble::Node *ListLinkedDouble::minimum(Node *begin, Node *end) const
 {
     // Variables auxiliares
     Node *min_node = begin;
     Node *current = begin->next;
     // Recorremos la lista
     while (current != end)
     {
         // Si hay un nuevo minimo
         if (current->value < min_node->value)
         {
             // Lo guardamos
             min_node = current;
         }
         // Pasamos al siguiente
         current = current->next;
     }
     // Devolvemos el resultado
     return min_node;
 }
 
 // O(1)
 // Solo hacemos 2 asignaciones de coste constante
 void ListLinkedDouble::detach(Node *n)
 {
     // Enlazamos los dos nodos de al rededor para que se apunten entre si
     n->prev->next = n->next;
     n->next->prev = n->prev;
 }
 
 // O(1)
 // Solo hacemos 4 asignaciones de coste constante
 void ListLinkedDouble::attach(Node *n, Node *position)
 {
     // Insertamos el nodo n
     n->prev = position;
     n->next = position->next;
     // Actualizamos los nodods de alrededor para que lo apunten
     position->next->prev = n;
     position->next = n;
 }
 
 // O(n^2)
 // Nota: el acceder a los valores de los nodos, sus siguientes, anteriores y demas siempre es O(1), si tienes el puntero al propio nodo
 // Primero recorremos el vector (n elementos) haciendo siempre una llamada a la funcion minimun O(n), otra a detach O(1) y otra a attach O(1), y despues una asignacion de coste O(1) constante
 // Asi, este primer bucle recorre n vueltas de coste O(n), y por tanto tiene coste O(n^2)
 // El siguiente bucle realiza operaciones (a saber, 2 comprobaciones, 2 asignaciones, 1 borrado y 1 llamada a la funcion detach O(1)) de coste O(1) constante, recorriendo los n elementos
 // Asi, este segundo bucle tiene coste O(n) lineal
 // Finalmente, el coste total es O(n^2 + n) = O(n^2)
 void ListLinkedDouble::sort_and_dedup()
 {               
     // Guardamos el nodo anterior
     Node *previo = head;
 
     // Seguimos hasta que el siguiente sea head, ya que asumimos que previo es el ultimo elemento ordenado
     while (previo->next != head)
     {
         // Buscamos el minimo
         Node *mini = minimum(previo->next, head);
         // Lo quitamos
         detach(mini);
         // Lo añadimos despues del previo (ya ordenado)
         attach(mini, previo);
         // Pasamos al siguiente
         previo = previo->next;
     }
 
     // Guardamos el primer nodo
     Node *current = head->next;
 
     // Revisamos todos los nodos
     while (current != head)
     {
         // Si el valor de este nodo coincide con el siguiente
         if (current->value == current->next->value){
             Node *borrar = current;
             // Pasamos ya al siguiente
             current = current->next;
             // Quitamos el repetido
             detach(borrar);
             // Lo borramos
             delete borrar;
         }
         // Si no son iguales, pasamos al siguiente
         else {
             current = current->next;
         }
     }
 
 }
 
 //@ </answer>
 //---------------------------------------------------------------
 // No modificar por debajo de esta línea
 // --------------------------------------------------------------
 
 using namespace std;
 
 void resuelve_caso()
 {
     int x;
 
     ListLinkedDouble l;
     cin >> x;
     while (x != -1)
     {
         l.push_back(x);
         cin >> x;
     }
 
     l.sort_and_dedup();
     cout << l << '\n';
 }
 
 int main()
 {
 
     // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
     // redirigiran cualquier lectura de cin al fichero 'casos.txt'. Esto es
     // útil para no tener que teclear los casos de prueba por teclado cada vez
     // que ejecutas el programa.
     //
     // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
     // comenta las líneas comprendidas entre los #ifndef y #endif
 #ifndef DOMJUDGE
     std::ifstream in("casos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf());
 #endif
 
     // La entrada comienza con el número de casos de prueba.
     int num_casos;
     cin >> num_casos;
 
     // Llamamos tantas veces a `tratar_caso` como nos diga el número.
     for (int i = 0; i < num_casos; i++)
     {
         resuelve_caso();
     }
 
     // Comenta esto también si has comentado lo anterior.
 #ifndef DOMJUDGE
     std::cin.rdbuf(cinbuf);
 #endif
     return 0;
 }