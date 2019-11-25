#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
#include <set>
#include <iomanip>
using namespace std;
class Grafo
{
protected:
	Grafo();
public:
	bool peso = false;
	bool bipartido = false;
	int num_vertices;
	int num_arestas;
	bool ciclo_negativo = false;
	int* graus;
	vector<int> conjuntos[2];
	
	virtual int** bfs_busca(int) = 0;
	virtual int** dfs_busca(int) = 0;
	virtual vector<vector<int>> bfs_conexa() = 0;
	virtual int diametro() = 0;
	virtual float** dijkstra(int) = 0;
	virtual float** prim(int) = 0;
	virtual bool checa_bipartido(int) = 0;
	virtual float* bellmanford(int t) = 0;
	virtual vector<pair<int, bool>>* hopcraft()=0;
	virtual float** distancia() = 0;
	
	list<float>min_caminho(int, int);
	bool escreverGrafoInfo(string file);
	bool escreveDisco_bfs(int, string);
	bool escreveDisco_dfs(int, string);
	bool escrever_emparelhamento(string file);
	bool escrever_bellmanford(string file);
	int distanciaBFS(int, int);
	float excentricidade(int u);
	float* grau_info();
	bool escreveDisco_mst(string);
	float max(float, float);
	float min(float, float);
};

