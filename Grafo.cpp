#include "Grafo.h"
Grafo::Grafo() {

}
bool Grafo::escreverGrafoInfo(string file) {
	ofstream myfile(file);
	if (!myfile.is_open())
	{
		return false;
	}
	float* infos = this->grau_info();

	myfile << "Numero de v�rtices: " << num_vertices << endl;
	myfile << "Numero de arestas: " << num_arestas << endl;
	myfile << "Grau m�nimo: " << infos[0] << endl;
	myfile << "Grau m�ximo: " << infos[1] << endl;
	myfile << "Grau m�dio: " << infos[2] << endl;
	myfile << "Grau mediano: " << infos[3] << endl;
	vector<vector<int>> cc_info = bfs_conexa();
	int* ccs = new int[cc_info.size()];

	for (int i = 0; i < cc_info.size(); i++) {
		ccs[i] = cc_info[i].size();

	}
	sort(ccs, ccs + cc_info.size());

	for (int i = 0; i < cc_info.size(); i++) {
		myfile << "Componente : " << i + 1 << " Tamanho: " << ccs[i] << endl;
	}

	myfile.close();
	return true;
}
bool Grafo::escreveDisco_bfs(int inicial, string file) {
	int** bfs_info = bfs_busca(inicial);
	ofstream myfile(file);
	if (!myfile.is_open())
	{
		return false;
	}
	myfile << "V�rtice: 1 Pai: RAIZ N�vel: 0\n";
	for (int i = 1; i < num_vertices; i++) {
		myfile << "V�rtice: " << i << " Pai: " << bfs_info[0][i] << " N�vel: " << bfs_info[1][i] << "\n";
	}
	myfile.close();
	delete[] bfs_info[0];
	delete[] bfs_info[1];
	return true;
}
bool Grafo::escreveDisco_dfs(int inicial, string file) {
	int** dfs_info = dfs_busca(inicial);
	ofstream myfile(file);
	if (!myfile.is_open())
	{
		return false;
	}
	myfile << "V�rtice: 1 Pai: RAIZ N�vel: 0\n";
	for (int i = 1; i < num_vertices; i++) {
		myfile << "V�rtice: " << i << " Pai: " << dfs_info[0][i] << " N�vel: " << dfs_info[1][i] << "\n";
	}
	myfile.close();
	delete[] dfs_info[0];
	delete[] dfs_info[1];
	return true;
}
int Grafo::distanciaBFS(int u, int v) {
	int** bfs = bfs_busca(u);
	return bfs[1][v];
}
float Grafo::excentricidade(int u) {
	if (peso) {
		float** djk = dijkstra(u);
		float ex = *max_element(djk[1], djk[1] + num_vertices);
		delete[] djk[0];
		delete[] djk[1];
		return ex;
	}
	else {
		int** bfs = bfs_busca(u);
		float ex = *max_element(bfs[1], bfs[1] + num_vertices);
		delete[] bfs[0];
		delete[] bfs[1];
		return ex;

	}
}
float* Grafo::grau_info() {
	float* resultados = new float[4]{ 0 };
	float soma = 0.0;
	sort(graus, graus + num_vertices);
	resultados[0] = graus[1];
	resultados[1] = graus[num_vertices - 1];
	for (int i = 1; i < num_vertices; i++) {
		soma += graus[i];
	}
	resultados[2] = soma / (num_vertices - 1);

	if ((num_vertices - 1) % 2 != 0) {
		int meio = (int)((num_vertices - 1) / 2);
		resultados[3] = (graus[meio] + graus[meio + 1]) / 2;
	}
	else {
		resultados[3] = graus[(num_vertices - 1) / 2];

	}
	return resultados;
}
//ultimo elemento � a distancia
list<float> Grafo::min_caminho(int v1, int v2) {
	list<float> caminho;
	if (peso) {
		float** djk = dijkstra(v1);
		caminho.push_back(v2);
		int i = v2;
		while (djk[0][i] != 0) {
			caminho.push_front(djk[0][i]);
			i = caminho.front();
		}
		caminho.push_back(djk[1][v2]);
		delete[] djk[0];
		delete[] djk[1];
	}
	else {
		int** bfs = bfs_busca(v1);
		caminho.push_back(v2);
		int i = v2;
		while (bfs[0][i] != 0) {
			caminho.push_front(bfs[0][i]);
			i = caminho.front();
		}
		caminho.push_back(bfs[1][v2]);
		delete[] bfs[0];
		delete[] bfs[1];
	}
	return caminho;
}
bool Grafo::escreveDisco_mst(string file) {
	ofstream myfile(file);
	if (!myfile.is_open())
	{
		return false;
	}
	float** primresult = prim(1);
	float pesomst = 0;
	myfile << num_vertices - 1 << endl;
	for (int i = 1; i < num_vertices; i++) {
		if (primresult[i] != 0) {
			int pai = primresult[i][0];
			float peso = primresult[i][1];
				myfile << i << " Pai: " << pai << " Peso: " << std::setprecision(20) << peso << endl;
				pesomst += peso;
		}
	}

	myfile << "Peso da MST: " << std::setprecision(20) << pesomst;
	return true;
}

