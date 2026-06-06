
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */
const int MAX =	10000;

/*void bfs(Grafo const& g) {
	std::queue<int> q;
	dist[s] = 0; visit[s] = true;
	q.push(s);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
				q.push(w);
			}
		}
	}
}*/
int adyacentes(int v, int i) {
	switch (i) {
	case 0:return (v + 1) % MAX;
	case 1:return (v * 2) % MAX;
	case 2:return (v / 3);
	}
}
int bfs(int ini, int fin) {
	if (ini == fin) return 0;
	queue<int> q;
	vector<bool>visit(MAX, false);
	vector<int>dist(MAX);
	dist[ini] = 0; visit[ini] = true;
	q.push(ini);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int i = 0; i < 3; i++) {
			int w = adyacentes(v, i);
			if (!visit[w]) {
				dist[w] = dist[v] + 1; visit[w] = true;
				if (w == fin) return dist[w];
				else q.push(w);
			}
		}
	}
}

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int ini, fin;
	cin >> ini >> fin;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	// escribir la solución
	cout << bfs(ini, fin) << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
