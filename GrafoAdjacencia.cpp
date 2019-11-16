#include "GrafoAdjacencia.h"
GrafoAdjacencia::GrafoAdjacencia(string file, bool peso) {
	ifstream myfile(file);
	myfile >> num_vertices;
	num_vertices++;
	graus = new int[num_vertices];
	fill(graus, graus + num_vertices, 0);
	this->peso = peso;

	int v1, v2;
	float v3;
		adjaListPeso = new vector<pair<int, float>>[num_vertices];

		if (peso) {
			while (myfile >> v1 >> v2 >>v3) {
				adjaListPeso[v1].push_back(make_pair(v2, v3));
				adjaListPeso[v2].push_back(make_pair(v1, v3));
				graus[v1]++;
				graus[v2]++;
				num_arestas++;
			}
		}
		else {
			while (myfile >> v1 >> v2) {
				adjaListPeso[v1].push_back(make_pair(v2, 0));
				adjaListPeso[v2].push_back(make_pair(v1, 0));
				graus[v1]++;
				graus[v2]++;
				num_arestas++;
			}
		}
	myfile.close();
	//checa_bipartido(0);
}
int** GrafoAdjacencia::bfs_busca(int inicial) {
	list<int> fila;
	fila.push_back(inicial);
	int* nivel = new int[num_vertices];

	fill(nivel, nivel + num_vertices, -1);

	int* pai = new int[num_vertices] {0};
	pai[inicial] = 0;
	nivel[inicial] = 0;

	int v;
	while (fila.size() != 0) {
		v = fila.front();
		fila.pop_front();
		for (int i = 0; i < adjaListPeso[v].size(); i++) {
			int r = adjaListPeso[v][i].first;
			if (nivel[r] == -1) {
				fila.push_back(r);
				pai[r] = v;
				nivel[r] = nivel[v] + 1;
			}
		}
	}

	return new int* [2]{ pai, nivel };
}
int** GrafoAdjacencia::dfs_busca(int inicial) {
	int* nivel = new int[num_vertices];
	fill(nivel, nivel + num_vertices, -1);
	int* pai = new int[num_vertices] {0};
	int* marcados = new int[num_vertices] {0};
	pai[inicial] = 0;
	nivel[inicial] = 0;
	list<int> pilha;
	pilha.push_back(inicial);
	int u;
	while (!pilha.empty()) {
		u = pilha.back();
		pilha.pop_back();
		if (!marcados[u]) {
			marcados[u] = true;
			for (int i = adjaListPeso[u].size() - 1; i >= 0; i--) {
				int r = adjaListPeso[u][i].first;
				if (!marcados[r]) {
					pilha.push_back(r);
					pai[r] = u;
					nivel[r] = nivel[u] + 1;
				}
			}

		}
	}
	delete[] marcados;
	return new int* [2]{ pai,nivel };
}
vector<vector<int>> GrafoAdjacencia::bfs_conexa() {
	vector<vector<int>> retorno;
	list<int> vertices;
	list<int>::iterator* ponteiros = new list<int>::iterator[num_vertices];
	for (int i = 1; i < num_vertices; i++) {
		vertices.push_back(i);
		ponteiros[i] = --(vertices.end());
	}

	int i_componente = 0;
	bool* marcados = new bool[num_vertices] {false};
	list<int> fila;
	while (vertices.size() > 0) {
		retorno.push_back(vector<int>());
		int s = vertices.back();
		marcados[s] = true;
		vertices.erase(ponteiros[s]);

		//
		fila.push_back(s);
		retorno[i_componente].push_back(s);
		int v;
		while (fila.size() != 0) {
			v = fila.front();
			fila.pop_front();
			for (int i = 0; i < adjaListPeso[v].size(); i++)
			{
				int r = adjaListPeso[v][i].first;
				if (!marcados[r]) {
					marcados[r] = true;
					retorno[i_componente].push_back(r);
					vertices.erase(ponteiros[r]);
					fila.push_back(r);
				}
			}
		}

		//	
		i_componente++;
	}
	delete[] marcados;
	delete[] ponteiros;
	return retorno;
}
int GrafoAdjacencia::diametro() {
	int diametro = 0;
	list<int> fila;
	for (int i = 1; i < num_vertices; i++) {
		fila.push_back(i);
		int* nivel = new int[num_vertices];

		fill(nivel, nivel + num_vertices, -1);

		nivel[i] = 0;
		int v;
		while (!fila.empty()) {
			v = fila.front();
			fila.pop_front();
			for (int i = 0; i < adjaListPeso[v].size(); i++) {
				int r = adjaListPeso[v][i].first;
				if (nivel[r] == -1) {
					fila.push_back(r);
					nivel[r] = nivel[v] + 1;
					if (nivel[r] > diametro) {
						diametro = nivel[r];
					}
				}
			}
		}

		delete[] nivel;
	}
	return diametro;
}
float** GrafoAdjacencia::dijkstra(int inicial) {
	set< pair<float, float> > setHeap;
	setHeap.insert(make_pair(0, inicial));
	float* pai = new float[num_vertices] {0};
	float* dist = new float[num_vertices];
	fill(dist, dist + num_vertices, -1);
	dist[inicial] = 0;
	bool* explorados = new bool[num_vertices] {0};
	while (!setHeap.empty()) {
		pair<float, float> p = *(setHeap.begin());
		int TBD = (int)p.second;
		setHeap.erase(setHeap.begin());

		for (int i = 0; i < adjaListPeso[TBD].size(); i++) {
			int r = adjaListPeso[TBD][i].first;
			float aresta = adjaListPeso[TBD][i].second;
			if (aresta < 0) {
				cout << "Grafo com aresta negativa";
				exit(1);
			}
			if (dist[r] > dist[TBD] + aresta || dist[r] == -1) {
				if (dist[r] != -1) {
					setHeap.erase(setHeap.find(make_pair(dist[r], r)));
				}
				pai[r] = TBD;
				dist[r] = dist[TBD] + aresta;
				setHeap.insert(make_pair(dist[r], r));
			}
		}
	}

	delete[] explorados;
	return new float* [2]{ pai, dist };
}
float** GrafoAdjacencia::prim(int inicial) {
	set< pair<float, float> > setHeap;
	setHeap.insert(make_pair(0, inicial));
	float** pai = new float* [num_vertices] {0};
	pai[inicial] = new float[2]{ 0, 0 };
	bool* explorados = new bool[num_vertices] {0};
	float* custo = new float[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		custo[i] = FLT_MAX;
	}
	custo[inicial] = 0;
	while (!setHeap.empty()) {
		pair<float, float> p = *(setHeap.begin());
		int u = (int)p.second;
		setHeap.erase(setHeap.begin());
		explorados[u] = true;
		for (int i = 0; i < adjaListPeso[u].size(); i++) {
			int vertice = adjaListPeso[u][i].first;
			if (!explorados[vertice]) {
				float peso = adjaListPeso[u][i].second;
				if (custo[vertice] > peso) {
					if (custo[vertice] != FLT_MAX) {
						setHeap.erase(setHeap.find(make_pair(custo[vertice], vertice)));
					}
					pai[vertice] = new float[2]{ (float)u,peso };
					custo[vertice] = peso;
					setHeap.insert(make_pair(custo[vertice], vertice));
				}
			}
		}
	}

	delete[] explorados;
	delete[] custo;
	return pai;
}

float* GrafoAdjacencia::bellmanford(int t) {
	float* M = new float[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		M[i] = FLT_MAX;
	}
	M[t] = 0;

	for (int v = 0; v < num_vertices; v++) {
		for (int w = 0; w < adjaListPeso[v].size(); w++) {
			float c = adjaListPeso[v][w].second;
			w = adjaListPeso[v][w].first;
			M[v] = min(M[v], M[w] + c);
		}
	}
	return M;
}