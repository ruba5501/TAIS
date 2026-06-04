
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
	int s; // vértice origen

	bool isAciclico;
	bool isConexo;
	bool arbolConexo(Grafo const& G) {
		for (int i = 1; i < G.V(); i++){
			if (!hayCamino(i)) isConexo = false;
		}
		return isConexo;
	}

	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				ant[w] = v;
				dfs(G, w);
			}
			else if (ant[v] != w) {
				isAciclico = false;
			}
		}
	}
public:
	CaminosDFS(Grafo const& g, int s) : visit(g.V(), false),
		ant(g.V()), s(s), isAciclico(true), isConexo(true){
		dfs(g, s);
		arbolConexo(g);
	}
	bool esArbolLibre() const {
		return isAciclico && isConexo;
	}
	// ¿hay camino del origen a v?
	bool hayCamino(int v) const {
		return visit[v];
	}
	using Camino = std::deque<int>; // para representar caminos
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
	}
};


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int v, a;
	cin >> v >> a;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Grafo g(v);
	int a1, a2;
	for (int i = 0; i < a; i++) {
		cin >> a1 >> a2;
		g.ponArista(a1, a2);
	}
	// escribir la solución
	CaminosDFS dfs(g, 0);
	bool sol = dfs.esArbolLibre();
	if (sol) cout << "SI";
	else cout << "NO";
	cout << "\n";

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
