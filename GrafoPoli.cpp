// GrafoPoli.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Grafo.h"
#include "GrafoMatriz.h"
#include "GrafoAdjacencia.h"

int main()
{
	GrafoAdjacencia* g = new GrafoAdjacencia("grafo_teste_3.txt",false,false);
	/*float** M = g->distancia();
	for (int i = 1; i < g->num_vertices; i++) {
		for (int j = 1; j < g->num_vertices; j++) {
			cout << "Distancia de " << j << " para " << i << ": " << M[i][j] << endl;
		}
	}*/
//	g->bellmanford(1);
	g->escrever_emparelhamento("estudo3emp.txt");
}
