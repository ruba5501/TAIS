
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

#define lli long long int
bool resuelveCaso() {
	// leer los datos de la entrada
	int n, num;
	cin >> n;
	if (n == 0)
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<lli, vector<lli>, greater<lli>> pq;
	for (int i = 0; i < n; i++){
		cin >> num;
		pq.push(num);
	}
	// escribir la solución
	lli a, b, cont = 0;
	while (pq.size() > 1) {
		a = pq.top();
		pq.pop();
		b = pq.top();
		pq.pop();

		cont += (a + b);
		pq.push(a + b);
	}

	cout << cont << endl;

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
