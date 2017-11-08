//============================================================================
// Name        : coloring.cpp
// Author      : Adam Lamoglia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Grafo{
	int numVertices, numCoresMaxima;



public:

	struct vertice{
			int grau;
			int index;
			vector<int> coresPossiveis;
	};

	vector<vertice> vertices;
	vector<int> corDoVertice;
	vector<vector<int> > listaDeAdjacencia;

	Grafo(int numVertices);


	int getSize();
	int getVerticeDeMaiorGrau();


	void addEdge(int u, int v);
	void ordenarGrafoPorVerticeDeMaiorGrau();
	void restringirCor(int u, int cor);
	void definirCor(int u,int cor);
	void colorirGrafo();
	int verificarCorPossivel(int u);
	void imprime();
};

Grafo::Grafo(int numVertices){
	this->numVertices = numVertices;
	this->numCoresMaxima = 0;

	vector<int> aux;

	this->vertices.resize(this->getSize());

	for(int i = 0; i < this->getSize(); i++){
		this->vertices[i].index = i;
		this->vertices[i].grau = 0;
		this->vertices[i].coresPossiveis.resize(this->getSize());

		//no inicio, todos os vertices podem ter cores de 0..tamanho-1
		for(int j = 0; j < this->getSize(); j++){
			this->vertices[i].coresPossiveis[j] = j;
		}
	}

	this->corDoVertice.resize(this->getSize(),-1);
	this->listaDeAdjacencia.resize(this->getSize());


}



int Grafo::getSize(){
	return this->numVertices;
}


void Grafo::addEdge(int u,int v){

	this->listaDeAdjacencia[u].push_back(v);
	this->listaDeAdjacencia[v].push_back(u);

	this->vertices[u].grau = this->listaDeAdjacencia[u].size();
	this->vertices[v].grau = this->listaDeAdjacencia[v].size();
}

bool maiorGrau(Grafo::vertice u,Grafo::vertice v){
	return u.grau > v.grau;
}

void Grafo::ordenarGrafoPorVerticeDeMaiorGrau(){

	sort(this->vertices.begin(),this->vertices.end(),maiorGrau);

}



//CP
void Grafo::restringirCor(int u,int cor){

	for(int i = 0; i < this->listaDeAdjacencia[u].size(); i++)
		this->vertices[this->listaDeAdjacencia[u][i]].coresPossiveis[cor] = -1;



}

void Grafo::definirCor(int u,int cor){

	this->corDoVertice[u] = cor;

	if(cor > this->numCoresMaxima)
		this->numCoresMaxima = cor;

}

int Grafo::verificarCorPossivel(int u){

	for(int i = 0; i < this->getSize(); i++)
		if(this->vertices[u].coresPossiveis[i] != -1)
			return this->vertices[u].coresPossiveis[i];


	return -1;
}

void Grafo::colorirGrafo(){
	int corAtual;

	this->ordenarGrafoPorVerticeDeMaiorGrau();


	for(int i = 0; i < this->getSize(); i++){


		if(i == 0){
			this->definirCor(this->vertices[i].index,0);
			this->restringirCor(this->vertices[i].index,0);
			continue;
		}

		corAtual = this->verificarCorPossivel(this->vertices[i].index);

		this->definirCor(this->vertices[i].index,corAtual);
		this->restringirCor(this->vertices[i].index,corAtual);

	}

	this->imprime();
}

void Grafo::imprime(){

	cout << this->numCoresMaxima +1 << " " << 0 << endl;

	for(int i = 0; i < this->getSize(); i++){
		cout << this->corDoVertice[i] << " ";
	}
}


int main() {
	int n,e,u,v;

	cin >> n >> e;

	Grafo g(n);

	for(int i = 0; i < e; i++){
		cin >> u >> v;

		g.addEdge(u,v);
	}

	g.colorirGrafo();

}
