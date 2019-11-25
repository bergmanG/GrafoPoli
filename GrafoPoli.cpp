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

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
