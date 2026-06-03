
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 * Ruben Gomez-escalonilla f21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ===============================================================
struct orquesta {
	int musicos, partituras, carga;
	bool operator<(orquesta const& orq2) const {
		return carga < orq2.carga;
	}
};
void sol(priority_queue<orquesta>& pq, int n, int p) {
	int sobrantes = p - n;
	while (sobrantes > 0) {
		orquesta topOrq = pq.top();
		pq.pop();
		topOrq.partituras++;
		topOrq.carga = (topOrq.musicos + topOrq.partituras - 1) / topOrq.partituras;
		pq.push({ topOrq });
		sobrantes--;
	}
}
//@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int p, n;
	cin >> p >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	orquesta orq;
	priority_queue<orquesta> pq;

	for (int i = 0; i < n; i++) {
		cin >> orq.carga;
		orq.musicos = orq.carga;
		orq.partituras = 1;
		pq.push({ orq });
	}
	// resolver el caso posiblemente llamando a otras funcione
	sol(pq, n, p);
	// escribir la solución
	orq = pq.top();
	cout << orq.carga << "\n";

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
