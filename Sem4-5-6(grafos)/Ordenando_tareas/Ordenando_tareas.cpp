
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

class OrdenTopologico {
public:
	// g es DAG
	OrdenTopologico(Digrafo const& g) : visit(g.V(), false), hecho(g.V(), false), sepuede(true) {
		for (int v = 1; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
	}
	// devuelve la ordenación topológica
	std::deque<int> const& orden() const {
		return _orden;
	}
	bool haysolucion() {
		return sepuede;
	}
private:
	std::vector<bool> visit;
	std::deque<int> _orden; // ordenación topológica
	vector<bool> hecho;
	bool sepuede;
	void dfs(Digrafo const& g, int v) {
		visit[v] = true;
		for (int w : g.ady(v))
			if (!visit[w])
				dfs(g, w);
			else if(!hecho[w]) sepuede = false;
		hecho[v] = true;
		_orden.push_front(v);
	}
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int n, m;
	cin >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Digrafo dg(n + 1);
	cin >> m;
	int a1, a2;
	for (int i = 0; i < m; i++) {
		cin >> a1 >> a2;
		dg.ponArista(a1, a2);
	}
	OrdenTopologico ot(dg);
	
	// escribir la solución
	if (ot.haysolucion()) {
		for (auto it : ot.orden()) {
			cout << it << " ";
		}
	}
	else cout << "Imposible";
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
