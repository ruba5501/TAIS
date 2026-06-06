
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>º

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

class CicloDirigido {
public:
	CicloDirigido(Digrafo const& g) : visit(g.V(), false),
		apilado(g.V(), false), hayciclo(false) {
		dfs(g, 1);
	}
	bool hayCiclo() const { return hayciclo; }
	string sol(Digrafo const& g) const {
		if (visit[g.V()-1] && !hayCiclo()) return "SIEMPRE";
		else if (visit[g.V() - 1] && hayCiclo()) return "A VECES";
		else if (!visit[g.V() - 1] && hayCiclo()) return "NUNCA";
	}
private:
	std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
	std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	bool hayciclo;
	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (!visit[w]) { // encontrado un nuevo vértice, seguimos
				dfs(g, w);
			}
			else if (apilado[w]) { // hemos detectado un ciclo
				// se recupera retrocediendo
				hayciclo = true;
			}
		}
		apilado[v] = false;
	}
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	Digrafo dg(n + 2);
	string letra;
	int a;
	for (int i = 1; i <= n; i++) {
		cin >> letra;
		if (letra == "A") {
			dg.ponArista(i, i + 1);
		}
		else if (letra == "J") {
			cin >> a;
			dg.ponArista(i, a);
		}
		else if (letra == "C") {
			cin >> a;
			dg.ponArista(i, a);
			dg.ponArista(i, i + 1);
		}
	}
	CicloDirigido cd(dg);
	// escribir la solución
	cout << cd.sol(dg) << "\n";
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
