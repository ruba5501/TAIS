
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

class CaminoMasCorto {
public:
	// Eliminamos el parámetro 'int s' del constructor porque ahora buscaremos todos los orígenes
	CaminoMasCorto(Grafo const& g) : visit(g.V(), false),
		ant(g.V()), dist(g.V()), esNaranja(g.V(), false), esBipartito(true), color(true) {

		// Bucle para asegurarnos de que cubrimos TODAS las componentes conexas
		for (int i = 0; i < g.V(); ++i) {
			if (!visit[i] && esBipartito) {
				bfs(g, i); // Lanzamos el BFS desde cada isla no visitada
			}
		}
	}

	bool hayCamino(int v) const { return visit[v]; }
	int distancia(int v) const { return dist[v]; }
	bool bipartito() { return esBipartito; }

private:
	std::vector<bool> visit;
	std::vector<int> ant;
	std::vector<int> dist;
	std::vector<bool> esNaranja;
	bool esBipartito;
	bool color;

	void bfs(Grafo const& g, int origen) {
		std::queue<int> q;
		dist[origen] = 0;
		visit[origen] = true;
		esNaranja[origen] = true; // Pintamos el origen de la isla de color true (naranja)
		q.push(origen);

		while (!q.empty() && esBipartito) {
			int v = q.front(); q.pop();
			color = !esNaranja[v];
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					esNaranja[w] = color; 
					q.push(w);
				}
				else {
					if (esNaranja[w] != color) {
						esBipartito = false;
					}
				}
			}
		}
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
	CaminoMasCorto bfs(g);
	bool sol = bfs.bipartito();
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
