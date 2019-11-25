#pragma once
#include "Grafo.h"
class GrafoAdjacencia: public Grafo
{
public:
	GrafoAdjacencia(string, bool peso,bool direcao);
	vector<pair<int, float>>* adjaListPeso;

	int** bfs_busca(int);
	int** dfs_busca(int);
	vector<vector<int>> bfs_conexa();
	int diametro();
	float** dijkstra(int);
	float** prim(int);
	float* bellmanford(int t);
	float** distancia();
	vector<pair<int, bool>>* hopcraft();
	bool checa_bipartido(int);
	list<int>* encontra_caminho(vector<pair<int, bool>>* grafo_residual, bool* expostos);
};

