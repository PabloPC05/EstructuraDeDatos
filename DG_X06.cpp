#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <deque>

using namespace std;


void insertar_ordenado(deque<pair<int, long long int>>& hongos, pair<int, long long int> tCantidad) {
	auto it = hongos.begin();
	while (it != hongos.end() && it->first < tCantidad.first) ++it;
	if (it == hongos.end()) hongos.push_back(tCantidad);
	else if (it->first == tCantidad.first) it->second += tCantidad.second;
	else hongos.insert(it, tCantidad);
}


void simular(deque<pair<int, long long int>>& hongos, int N, int M, int T) {
	int t = 1;
	long long int cont = 0;
	while (t <= T) {
		while (!hongos.empty() && hongos.front().first == t) {
			cont += hongos.front().second;
			hongos.pop_front();
		}

		if (cont > 0) {
			hongos.push_back({ t + M, cont });
			insertar_ordenado(hongos, { t + N, cont });
		}
		cont = 0;
		t++;
	}
	
}
//El coste es O(T)



// Indica el coste en función de los parámetros del problema (N, M, T)
bool tratar_caso() {
	int N, M, T; cin >> N >> M >> T;
	if (!cin)
		return false;
	deque<pair<int, long long int>> hongos;

	hongos.push_back({ N, 1 });
	simular(hongos, N, M, T);
	long long int total = 0;
	while (!hongos.empty()) {
		auto [t, cantidad] = hongos.front();
		total += cantidad;
		hongos.pop_front();
	}
	cout << total << '\n';
	return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("casos.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
  
  while (tratar_caso()) {  }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  // system("PAUSE");
#endif
  return 0;
}

