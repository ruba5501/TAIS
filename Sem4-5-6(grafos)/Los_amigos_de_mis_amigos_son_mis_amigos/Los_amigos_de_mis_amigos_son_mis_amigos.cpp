/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	int cont;
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				cont++;
				ant[w] = v;
				dfs(G, w);
			}
		}
	}
public:
	CaminosDFS(Grafo const& g) : visit(g.V(), false),
		ant(g.V()), cont(1) {
		for (int i = 1; i < g.V(); i++) {
			if (!visit[i]) {
				dfs(g, i);
				if (cont > contMax) contMax = cont;
				cont = 1;
			}
		}
	}
	int contMax = 0;
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}

	int grupoMasGrande() {
		return contMax;
	}
	/*using Camino = std::deque<int>; // para representar caminos
	// devuelve un camino desde el origen a v (debe existir)
	Camino camino(int v) const {
		if (!hayCamino(v))
			throw std::domain_error("No existe camino");
		Camino cam;
		// recuperamos el camino retrocediendo
		for (int x = v; x != s; x = ant[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}*/
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {
	// leer los datos de la entrada
	int n, m;
	cin >> n >> m;
	Grafo g(n+1);
	int a1, a2;
	for (int i = 0; i < m; i++) {
		cin >> a1 >> a2;
		g.ponArista(a1, a2);
	}
	// resolver el caso posiblemente llamando a otras funciones
	CaminosDFS dfs(g);
	// escribir la solución
	cout << dfs.grupoMasGrande() << "\n";
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

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio y parar antes de salir
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif

	return 0;
}
