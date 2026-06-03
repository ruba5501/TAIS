
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (FXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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

void equilibrar(PriorityQueue<int, greater<int>>& max, PriorityQueue<int>& min) {
	int d = min.size() - max.size();
	if (d < 1) {//si max es mayor
		int aux = max.top(); max.pop();//log(N)
		min.push(aux);//log(N)
	}
	else if (d > 1) {//si min es mayor
		int aux = min.top(); min.pop();
		max.push(aux);//log(N)
	}
}

bool resuelveCaso() {
	int e, p;
	cin >> e >> p;
	if (e == 0 && p == 0) return false;
	PriorityQueue<int, greater<int>> max;//cola de maximos
	PriorityQueue<int> min;
	min.push(e);//inserta en la cola de minimos el primer pajaro
	for (int i = 0; i < p; i++) {//Numero de parejas,  O(P(LogN + 2LogN))
		for (int j = 0; j < 2; j++) {//lee cada par  //coste O(2log(N))
			cin >> e;
			if (e > min.top())//se va construyendo los 2 monticulos
				min.push(e);//cola minimos
			else
				max.push(e);//cola maximos
		}
		equilibrar(max, min);//O(logN)
		cout << min.top() << " ";
	}
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
