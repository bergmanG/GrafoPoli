#pragma once
#include "Grafo.h"
class GrafoAdjacencia: public Grafo
{
public:
	GrafoAdjacencia(string, bool peso);
	vector<pair<int, float>>* adjaListPeso;

	int** bfs_busca(int);
	int** dfs_busca(int);
	vector<vector<int>> bfs_conexa();
	int diametro();
	float** dijkstra(int);
	float** prim(int);
};

