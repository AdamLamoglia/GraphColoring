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
	int numVertices,verticeDeMaiorGrau = 0,corAtual = -1,numCoresMaxima;


public:
	vector<int> corDoVertice;
	vector<int> numCoresPossiveisDoVertice;
	vector<vector<int> > listaDeAdjacencia;

	Grafo(int numVertices);


	void setCorAtual(int cor);
	void setVerticeDeMaiorGrau(int u);
	void setNumCoresMaxima(int num);

	int getCorAtual();
	int getSize();
	int getVerticeDeMaiorGrau();
	int getNumCoresMaxima();

	void addEdge(int u,int v);
	void definirVerticeDeMaiorGrau();
	void restringirCor(int u);
	void definirCor();
	void colorirGrafo();
	void imprime();
};

Grafo::Grafo(int numVertices){
	this->numVertices = numVertices;
	this->numCoresMaxima = numVertices;

	vector<int> aux;

	this->corDoVertice.resize(this->getSize(),-1);
	this->listaDeAdjacencia.resize(this->getSize());
	this->numCoresPossiveisDoVertice.resize(this->getSize(),this->getSize());

}

void Grafo::setCorAtual(int cor){
	this->corAtual = cor;
}

void Grafo::setVerticeDeMaiorGrau(int u){
	this->verticeDeMaiorGrau = u;
}

void Grafo::setNumCoresMaxima(int num){
	this->numCoresMaxima = num;
}

int Grafo::getCorAtual(){
	return this->corAtual;
}

int Grafo::getVerticeDeMaiorGrau(){
	return this->verticeDeMaiorGrau;
}

int Grafo::getSize(){
	return this->numVertices;
}

int Grafo::getNumCoresMaxima(){
	return this->numCoresMaxima;
}


void Grafo::addEdge(int u,int v){
	this->listaDeAdjacencia[u].push_back(v);

	this->listaDeAdjacencia[v].push_back(u);
}

void Grafo::definirVerticeDeMaiorGrau(){

	//se o vertice ainda nao foi colorido, sera analisado
	//caso tenha mais vizinhos, ele sera o vertice de maior grau
	//tal escolha sera feita pois aumentara as restricoes para os outros vertices
	for(int i = 0; i < this->getSize(); i++)
		if(this->listaDeAdjacencia[i].size() > this->getVerticeDeMaiorGrau() && this->corDoVertice[i] == -1)
			this->setVerticeDeMaiorGrau(i);

}

void Grafo::restringirCor(int u){

	//se o vertice ainda nao foi colorido, o numero de cores possiveis para ele diminuira
	for(int i = 0; i < this->listaDeAdjacencia[u].size(); i++)
		if(this->corDoVertice[listaDeAdjacencia[u][i]] == -1)
			this->numCoresPossiveisDoVertice[listaDeAdjacencia[u][i]]--;

}

void Grafo::definirCor(){

	this->corDoVertice[this->getVerticeDeMaiorGrau()] = this->getCorAtual();

	this->restringirCor(this->getVerticeDeMaiorGrau());

}

void Grafo::colorirGrafo(){

	for(int i = 0; i < this->getSize(); i++){

		cout << "Cores dos vertices: " << endl;

		for(int j = 0; j < this->getSize(); j++)
			cout << this->corDoVertice[j] << " ";
		cout << endl;

		this->definirVerticeDeMaiorGrau();

		cout << "Vertice de maior grau atual: " << this->getVerticeDeMaiorGrau() << endl;
		cout << "Numero de cores possiveis do vertice " << this->getVerticeDeMaiorGrau() << ": "  << this->numCoresPossiveisDoVertice[this->getVerticeDeMaiorGrau()] << endl;

		if(this->numCoresPossiveisDoVertice[this->getVerticeDeMaiorGrau()] == this->getNumCoresMaxima()){
			cout << "entrou" << endl;

			this->setCorAtual(this->getCorAtual() + 1);

			this->definirCor();

			this->setVerticeDeMaiorGrau(0);
		}
		else if(this->numCoresPossiveisDoVertice[this->getVerticeDeMaiorGrau()] < this->getNumCoresMaxima()){

			cout << "entrou2" << endl;

			this->definirCor();

			this->setVerticeDeMaiorGrau(0);
		}

	}

	this->imprime();
}

void Grafo::imprime(){

	cout << this->getCorAtual() << " " << 0 << endl;

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

	for(int i = 0; i < g.listaDeAdjacencia.size(); i++){
		cout << "Adjacentes de " << i << ": ";
		for(int j = 0; j < g.listaDeAdjacencia[i].size(); j++){
			cout << g.listaDeAdjacencia[i][j] << " ";
		}
		cout << endl;
	}

	g.colorirGrafo();

}
