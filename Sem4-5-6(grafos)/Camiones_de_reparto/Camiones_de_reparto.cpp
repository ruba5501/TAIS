
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

class CaminosDFS {
private:
	std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
	std::vector<int> ant; // ant[v] = último vértice antes de llegar a v
	int s; // vértice origen
	int dest;
	void dfs(GrafoValorado<int> const& G, int ini, int fin, int camion) {
		visit[ini] = true;
		for (Arista<int> w : G.ady(ini)) {
			if (w.valor() >= camion) {
				if (!visit[w.otro(ini)]) {
					dfs(G, w.otro(ini), fin, camion);
				}
			}
		}
	}
public:
	CaminosDFS(GrafoValorado<int> const& g, int ini, int fin, int camion) : visit(g.V(), false),
		ant(g.V()), s(s), dest(fin) {
		dfs(g, ini, fin, camion);
	}

	bool pasa() {
		return visit[dest];
	}
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, E;
	cin >> V;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	GrafoValorado<int> gv(V+1);
	cin >> E;
	int a1, a2, valor;
	for (int i = 0; i < E; i++) {
		cin >> a1 >> a2 >> valor;
		Arista<int> a(a1, a2, valor);
		gv.ponArista(a);
	}
	// escribir la solución
	int n, ini, fin, camion;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> ini >> fin >> camion;
		CaminosDFS dfs(gv, ini, fin, camion);
		if (dfs.pasa()) cout << "SI";
		else cout << "NO";
		cout << "\n";
	}
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
