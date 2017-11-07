//============================================================================
// Name        : coloring.cpp
// Author      : Adam Lamoglia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;


class Grafo{
	int numVertices,verticeDeMaiorGrau = 0;


public:
	vector<int> corDoVertice;
	vector<int> numCoresPossiveisDoVertice;
	vector<vector<int> > listaDeAdjacencia;

	Grafo(int numVertices);

	void addEdge(int u,int v);
	void setVerticeDeMaiorGrau(int u);
	int getSize();
	int getVerticeDeMaiorGrau();
	void definirVerticeDeMaiorGrau();
	void restringirCor(int u);
	void definirCor();
};

Grafo::Grafo(int numVertices){
	this->numVertices = numVertices;

	vector<int> aux;

	this->corDoVertice.resize(this->getSize());
	this->listaDeAdjacencia.resize(this->getSize());
	this->numCoresPossiveisDoVertice.resize(this->getSize(),this->getSize());

}

void Grafo::addEdge(int u,int v){
	this->listaDeAdjacencia[u].push_back(v);

	this->listaDeAdjacencia[v].push_back(u);
}

void Grafo::setVerticeDeMaiorGrau(int u){
	this->verticeDeMaiorGrau = u;
}

int Grafo::getVerticeDeMaiorGrau(){
	return this->verticeDeMaiorGrau;
}

int Grafo::getSize(){
	return this->numVertices;
}

void Grafo::definirVerticeDeMaiorGrau(){

	for(int i = 0; i < this->getSize(); i++)
		if(this->listaDeAdjacencia[i].size() > this->getVerticeDeMaiorGrau() && this->corDoVertice[i] != -1)
			this->setVerticeDeMaiorGrau(i);

}

void Grafo::restringirCor(int u){

	for(int i = 0; i < this->listaDeAdjacencia[u].size(); i++)
		if(this->corDoVertice[listaDeAdjacencia[u][i]] == -1)
			this->numCoresPossiveisDoVertice--;

}

int main() {
	int n,e,u,v;

	cin >> n >> e;

	Grafo g(n);

	for(int i = 0; i < e; i++){
		cin >> u >> v;

		g.addEdge(u,v);
	}

	for(int i = 0; i < g.listaDeAdjacencia.size(); i++){
		cout << "Adjacentes de " << i << ": ";
		for(int j = 0; j < g.listaDeAdjacencia[i].size(); j++){
			cout << g.listaDeAdjacencia[i][j] << " ";
		}
		cout << endl;
	}

}
