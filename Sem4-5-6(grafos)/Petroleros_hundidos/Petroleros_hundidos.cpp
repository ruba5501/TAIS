
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int n, m;
	cin >> n >> m;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	vector<string> mapa(n);
	for (int i = 0; i < n; i++) {
		cin >> mapa[i];
	}
	int maxi = 0;
	vector<int> tamanosMareas;
	ConjuntosDisjuntos cd(n * m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mapa[i][j] == '#') {
				maxi = max(maxi,1);
				int df[] = {-1, 1, 0, 0, -1, -1, 1, 1};
				int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};

				for (int x = 0; x < 8; x++){
					int auxi = df[x] + i;
					int auxj = dc[x] + j;
					if (auxi >= 0 && auxi < n && auxj >= 0 && auxj < m && mapa[auxi][auxj] == '#') {
						int cur = cd.buscar(i * m + j);
						int vec = cd.buscar(auxi * m + auxj);

						if (cur != vec) {
							cd.unir(cur, vec);
							maxi = max(maxi, cd.cardinal(cur));
						}
					}
				}
			}
		}
	}
	tamanosMareas.push_back(maxi);
	// escribir la solución
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int r, c;
		cin >> r >> c;
		r--;
		c--;

		if (mapa[r][c] == '#') {
			tamanosMareas.push_back(maxi);
		}
		else {
			mapa[r][c] = '#';

			int curr = r * m + c;
			maxi = max(maxi, 1);

			int df[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
			int dc[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

			for (int k = 0; k < 8; k++) {
				int ni = r + df[k];
				int nj = c + dc[k];

				if (ni >= 0 && ni < n && nj >= 0 && nj < m && mapa[ni][nj] == '#') {
					int neighbor = cd.buscar(ni * m + nj);
					cd.unir(curr, neighbor);
					maxi = max(maxi, cd.cardinal(curr));
				}
			}
			tamanosMareas.push_back(maxi);
		}
	}

	for (int i = 0; i < tamanosMareas.size(); i++) {
		if (i > 0) cout << " ";
		cout << tamanosMareas[i];
	}
	cout << endl;

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
