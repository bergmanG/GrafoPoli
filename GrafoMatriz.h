#pragma once
#include "Grafo.h"
class GrafoMatriz : public Grafo
{
public:
	GrafoMatriz(string, bool peso);
	float** matrizpeso;
	bool** matriz;

	int** bfs_busca(int);
	int** dfs_busca(int);
	vector<vector<int>> bfs_conexa();
	int diametro();
	float** dijkstra(int);
	float** prim(int);
	float* bellmanford(int t);
	float** distancia();
};

