#include "GrafoMatriz.h"
GrafoMatriz::GrafoMatriz(string file, bool peso) {
	ifstream myfile(file);
	myfile >> num_vertices;
	num_vertices++;
	graus = new int[num_vertices];
	fill(graus, graus + num_vertices, 0);
	this->peso = peso;

	int v1, v2;
	float v3;
	matriz = new bool* [num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		matriz[i] = new bool[num_vertices] {false};
	}

	if (peso) {
		matrizpeso = new float* [num_vertices];
		for (int i = 0; i < num_vertices; i++) {
			matrizpeso[i] = new float[num_vertices] {0};
		}
	}

	if (peso) {
		while (myfile >> v1 >> v2 >> v3) {
			matriz[v1][v2] = true;
			matriz[v2][v1] = true;
			matrizpeso[v1][v2] = v3;
			matrizpeso[v2][v1] = v3;
			graus[v1]++;
			graus[v2]++;
			num_arestas++;
		}
	}
	else {
		while (myfile >> v1 >> v2) {
			matriz[v1][v2] = true;
			matriz[v2][v1] = true;
			graus[v1]++;
			graus[v2]++;
			num_arestas++;
		}
	}


	myfile.close();
	//checa_bipartido(0);
}
int** GrafoMatriz::bfs_busca(int inicial) {
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
		for (int i = 1; i < num_vertices; i++) {
			if (matriz[v][i]) {
				if (nivel[i] == -1)
				{
					fila.push_back(i);
					pai[i] = v;
					nivel[i] = nivel[pai[i]] + 1;
				}
			}
		}

	}
	return new int* [2]{ pai, nivel };
}
int** GrafoMatriz::dfs_busca(int inicial) {
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
			for (int i = num_vertices - 1; i > 0; i--) {
				if (matriz[u][i]) {
					if (!marcados[i]) {
						pilha.push_back(i);
						pai[i] = u;
						nivel[i] = nivel[u] + 1;
					}
				}
			}

		}
	}
	delete[] marcados;
	return new int* [2]{ pai,nivel };
}
vector<vector<int>> GrafoMatriz::bfs_conexa() {
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
			for (int i = 1; i < num_vertices; i++) {
				if (matriz[v][i]) {
					if (!marcados[i])
					{
						marcados[i] = true;
						retorno[i_componente].push_back(i);
						vertices.erase(ponteiros[i]);

						fila.push_back(i);
					}
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
int GrafoMatriz::diametro() {
	int diametro = 0;
	list<int> fila;
	for (int i = 1; i < num_vertices; i++) {
		fila.push_back(i);
		int* nivel = new int[num_vertices];

		fill(nivel, nivel + num_vertices, -1);

		nivel[i] = 0;
		int v;
		while (fila.size() != 0) {
			v = fila.front();
			fila.pop_front();
			for (int i = 1; i < num_vertices; i++) {
				if (matriz[v][i]) {
					if (nivel[i] == -1)
					{
						fila.push_back(i);
						nivel[i] = nivel[v] + 1;
						if (nivel[i] > diametro) {
							diametro = nivel[i];
						}
					}
				}
			}

		}

		delete[] nivel;
	}
	return diametro;
}
float** GrafoMatriz::dijkstra(int inicial) {
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
		explorados[TBD] = true;

		for (int i = 1; i < num_vertices; i++) {
			if (matriz[TBD][i]) {
				float aresta = matrizpeso[TBD][i];
				if (aresta < 0) {
					cout << "Grafo com aresta negativa";
					exit(1);
				}
				if (dist[i] > dist[TBD] + aresta || dist[i] == -1) {
					if (dist[i] != -1) {
						setHeap.erase(setHeap.find(make_pair(dist[i], i)));
					}
					pai[i] = TBD;
					dist[i] = dist[TBD] + aresta;
					setHeap.insert(make_pair(dist[i], i));
				}
			}
		}
	}


	delete[] explorados;
	return new float* [2]{ pai, dist };
}
float** GrafoMatriz::prim(int inicial) {

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
		for (int i = 1; i < num_vertices; i++) {
			if (matriz[u][i]) {
				if (!explorados[i]) {
					float peso = matrizpeso[u][i];
					if (custo[i] > peso) {
						if (custo[i] != FLT_MAX) {
							setHeap.erase(setHeap.find(make_pair(custo[i], i)));
						}
						pai[i] = new float[2]{ (float)u,peso };
						custo[i] = peso;
						setHeap.insert(make_pair(custo[i], i));
					}
				}
			}
		}
	}

	delete[] explorados;
	delete[] custo;
	return pai;
}