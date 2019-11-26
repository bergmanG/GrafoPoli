#pragma once
#include "Grafo.h"
class GrafoMatriz : public Grafo
{
public:
	GrafoMatriz(string, bool peso,bool direcao);
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
	bool checa_bipartido(int);
	int* hopcroft();//retorna vetor com pares. indice 0 é o emparelhamento maximo
	bool dfsHopcroft(int u, int* pairA, int* pairB, int* dist);
	bool bfsHopcroft(int* pairA, int* pairB, int* dist);
};

