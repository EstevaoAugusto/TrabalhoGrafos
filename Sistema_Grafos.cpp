/* Ciência da Computação - 10A - 3o período
 * Estevao Augusto da Fonseca Santos
 * Felipe 
 * Eduardo
 * */

#include <iostream>
#include <fstream>
#include <graphics.h>
#include <vector>
#include <list>
#include <array>

using namespace std;

bool existe(const vector <int> &vertices, const int &vertice); //checa se um vertice existe dentro de um vetor de vertices

class Grafo{
    private:
        vector <int> vertices; //vetor de tamanho dinamico
        vector <array <int, 2>> arestas; // vetor de tamanho dinamico contendo uma vetor de tamanho 2 como valor
        bool eh_direcionado;
        int retorna_posicao(int x){
            for(unsigned int i{0}; i < vertices.size(); i++){
                if(x == vertices[i])
                    return i; // retorna a posicao de um vertice presente no vector vertices
            }
            return -1; // retorna valor invalido caso nao seja encontrado
        }
    public:
        Grafo(vector <int> pVertices, vector <array <int,2>> pArestas, bool pEh_direcionado){
            vertices = pVertices;
            arestas = pArestas;
            eh_direcionado = pEh_direcionado;
        }
        ~Grafo(){
			
			}
			
		vector <int> getVertice() { return vertices;};
        void matriz_adjacencia();
        void lista_adjacencia(); 
        void grafico();
        void imprimir_conjunto();
        void reescrever_arquivo();
        void inserir_vertice(int v);
        void inserir_aresta(const array <int, 2> &a);
        void remover_vertice(int v);
        void remover_aresta(const array <int, 2> &a);
};

void Grafo::reescrever_arquivo(){
	ofstream alterar("grafos.txt");
	
	alterar << "V = {";
	for(unsigned int i = 0; i < vertices.size(); i++){
		alterar << vertices.at(i);
		if(i != vertices.size() - 1){ 
			alterar << ", ";
		}
	}
	alterar << "}; A = {(";
	for(unsigned int i = 0; i < arestas.size(); i++){
		alterar << arestas[i].at(0);
		alterar << ",";
		alterar << arestas[i].at(1) << ")";
		if(i != arestas.size() - 1){ 
			alterar << ",(";
		}
	}
	alterar << "};";
	
	alterar.close();
};

void Grafo::inserir_aresta(const array <int, 2> &a){
	if(existe(vertices, a[0]) and existe(vertices, a[1])){ //checa se os vertices do array a existem 
		arestas.push_back(a);
		imprimir_conjunto();
	} else {
		cout << "ERRO: Um dos vertices nao existe." << endl;
	}
}

void Grafo::inserir_vertice(int v){	
	if(!existe(vertices, v)){
		vertices.push_back(v);
		imprimir_conjunto();
	} else {
		cout << "ERRO: O vertice já existe!" << endl;
	}
};

void Grafo::imprimir_conjunto(){
	cout << endl << endl;
	
	cout << "V = {"; // Vertices
	for(unsigned int i{0}; i < vertices.size(); i++){
		if(i != vertices.size()-1){
			cout << vertices.at(i) << ", ";
		} else {
			cout << vertices.at(i) << "} " << endl;
		}
	}
	
	cout << "A = {"; // Arestas
	for(unsigned int i{0}; i < arestas.size(); i++){
		cout << "(";
		if(i != arestas.size()-1){
			cout << arestas[i][0] << ", " << arestas[i][1] << "),";
		} else {
			cout << arestas[i][0] << ", " << arestas[i][1] << ")}";
		}
	}
	cout << endl << endl;
	
}

void Grafo::matriz_adjacencia(){
	
    vector<vector<int>> matriz(vertices.size(), vector<int>(vertices.size()));
    
    int x;
    int y;
    int posicao_x;
    int posicao_y;
    if(eh_direcionado){
        for(unsigned int i{0}; i < arestas.size(); i++){
           x = arestas[i][0];
           y = arestas[i][1];
           posicao_x = retorna_posicao(x);
           posicao_y = retorna_posicao(y);
           matriz[posicao_x][posicao_y] = 1;
        }
    } else{
        for(unsigned int i{0}; i < arestas.size(); i++){
            x = arestas[i][0];
            y = arestas[i][1];
            posicao_x = retorna_posicao(x);
            posicao_y = retorna_posicao(y);
            matriz[posicao_x][posicao_y] = 1;
            matriz[posicao_y][posicao_x] = 1;
        }
    }
    for(unsigned int i{0}; i < vertices.size(); i++){
        cout << "   " << vertices[i];
    }
    cout << endl;
    for(unsigned int i{0}; i < vertices.size(); i++){
        cout << vertices[i] << " ";
        for(unsigned int j{0}; j < vertices.size(); j++){
            cout << '[' << matriz[i][j] << ']' << " ";
        }
        cout << endl;
    }
    cout << "linha: entrada do vertice" << endl;
	cout << "coluna: saida do vertice" << endl << endl;
    system("pause");
    
}

void Grafo::lista_adjacencia(){
    vector<list <int>> listas;
    for(unsigned int i{0}; i < vertices.size(); i++){
        list <int> lista;
        lista.push_back(vertices[i]);
        listas.push_back(lista);
    }
    if(eh_direcionado){
        for(unsigned int i{0}; i < listas.size(); i++){
            for(unsigned int j{0}; j < arestas.size(); j++){
                if(arestas[j][0] == listas[i].front())
                    listas[i].push_back(arestas[j][1]);
            }
        }
    } else{
        for(unsigned int i{0}; i < listas.size(); i++){
            for(unsigned int j{0}; j < arestas.size(); j++){
                if(arestas[j][0] == listas[i].front())
                    listas[i].push_back(arestas[j][1]);
                if(arestas[j][1] == listas[i].front())
                    listas[i].push_back(arestas[j][0]);
            }
        }
    }
    for(unsigned int i{0}; i < listas.size(); i++){
        cout << '[' << listas[i].front() << ']';
        bool frente = true;
        for(auto v : listas[i]){
            if(!frente)
                cout << " -> " << v;
            frente = false;
        }
        cout << endl;
    }
    cout << endl << endl;
    
    system("pause");
}


bool existe(const vector <int> &vertices, const int &vertice){
    for(unsigned int i{0}; i < vertices.size(); i++){
        if(vertices.at(i) == vertice)
            return true; // vertice existe dentro do conjunto de vertices
    }
    return false; // vertice nao existe dentro do conjunto de vertices
}

int main(){
	ifstream arquivo("grafos.txt");
	
	char lixo;
	vector <int> vertices; // vetor de vertice temporario
	vector <array <int, 2>> arestas; // vetor dinamico de aresta temporaria
	int vertice; // valor do vertice
	array <int, 2> aresta; // vetor fixo de arestas
	bool mEh_direcionado;
	cout << "O seu grafo eh direcionado?";
	cin >> mEh_direcionado;
	try{
		arquivo >> lixo;
		if(lixo != 'V') {
			throw string("Erro sintatico!");
		}
		arquivo >> lixo;
		if(lixo != '=') {
			throw string("Erro sintatico!");
		}
		arquivo >> lixo;
		if(lixo != '{'){
			throw string("Erro sintatico!");
		}
		while(lixo != '}'){ // lera todos os valores de vertice
			if(arquivo >> vertice){
				if(existe(vertices, vertice)){
					throw string("Erro! Vertice repetido!");
				}
			}else{
				throw string("Erro sintatico!");
			}
			vertices.push_back(vertice);
			arquivo >> lixo;
			if(lixo != ',' and lixo != '}')
				throw string("Erro sintatico!");
        }
        arquivo >> lixo;
        if(lixo!= ';')
                throw string("Erro sintatico!");
        arquivo >> lixo;
        if(lixo!= 'A')
                throw string("Erro sintatico!");
        arquivo >> lixo;
        if(lixo != '=')
            throw string("Erro sintatico!");
        arquivo >> lixo;
        if(lixo != '{')
            throw string("Erro sintaico!");
        while(lixo != '}'){ // lera todos os valores da aresta
            arquivo >> lixo;
            if(lixo != '(')
                throw string("Erro sintatico!");
            if(arquivo >> aresta[0]) {
                if(!existe(vertices, aresta[0])){
					throw string("Erro! Aresta de vertice inexistente!");
				}
            } else {
                throw string("Erro sintatico!");
			}
            arquivo >> lixo;

            if(lixo != ',') {
                throw string("Erro sintatico!");
			}
            if(arquivo >> aresta[1]){
                if(!existe(vertices, aresta[1])){
					throw string("Erro! Aresta de vertice inexistente!");
				}
            } else {
                throw string("Erro sintatico!");
			}
            arestas.push_back(aresta);
            arquivo >> lixo;
            if(lixo != ')')
                throw string("Erro sintatico!");
            arquivo >> lixo;
            if(lixo != ',' and lixo != '}')
                throw string("Erro sintatico!");
        }
        arquivo >> lixo;
        if(lixo!= ';')
			throw string("Erro sintatico!");
        
        arquivo.close();
        Grafo grafo(vertices, arestas, mEh_direcionado);
        char opcao;
        
        
		do{
			cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
			cout << "       Algoritmos em Grafos" << endl;
			cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl << endl;
		
			cout << "O que deseja fazer com o grafo?" << endl<<endl;
					
			cout << "1) Inserir" << endl;
			cout << "2) Remover" << endl;
			cout << "3) Verificar" << endl;
			cout << "4) Buscar" << endl;
			cout << "5) Visualizar" << endl;
			cout << "0) Sair" << endl << endl;
        
			cout << "Sua resposta: ";
			cin >> opcao;
        
			switch(opcao){
				case '1': { //Insercao
					cout << endl << endl;
					cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
					cout << "    O que deseja inserir?" << endl;
					cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl << endl;
					
					cout << "1) Vertice" << endl;
					cout << "2) Aresta" << endl;
					cout << "Qualquer numero) Voltar" << endl << endl;
					
					cout << "Sua resposta: ";
					cin >> opcao;
					if(opcao == '1'){
						grafo.imprimir_conjunto();
						
						cout << "Qual vertice deseja inserir? ";
						cin >> vertice;
						
						grafo.inserir_vertice(vertice);
					} else if(opcao == '2'){
						grafo.imprimir_conjunto();
						array<int,2> a;
						cout << "Qual aresta deseja criar? ";
						
						cin >> a[0] >> a[1];
						grafo.inserir_aresta(a);
						
					}
					opcao = '1';
					
					break;
				}
				case '2': { //Remocao
					cout << endl << endl;
					cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
					cout << "    O que deseja Remover?" << endl;
					cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl << endl;
					
					cout << "1) Vertice" << endl;
					cout << "2) Aresta" << endl;
					cout << "Qualquer numero) Voltar" << endl << endl;
					
					cout << "Sua resposta: ";
					cin >> opcao;
					
					if(opcao == '1'){
						// codar aqui
					} else if (opcao == '2'){
						// codar aqui
					}
					
					opcao = '2';
					break;
				}
				case '3': { //Verificar grafo
					break;
				}
				case '4': { //Buscar grafo
					break;
				}
				case '5': { //Visualizar grafo
					cout << endl << endl;
					cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
					cout << "    Como deseja visualizar o grafo" << endl;
					cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl << endl;
				
					cout << "1) Matriz de adjacencia" << endl;
					cout << "2) Lista de adjacencia" << endl;
					cout << "3) Conjunto" << endl;
					cout << "Qualquer numero) Voltar" << endl << endl;
				
					cout << "Sua resposta: ";
					cin >> opcao;
					if(opcao == '1'){
						grafo.matriz_adjacencia();
					} else if(opcao == '2'){
						grafo.lista_adjacencia();
					} else if(opcao == '3'){
						grafo.imprimir_conjunto();
					}
					opcao = '5';
					break;
				}
				case '0': {
					break;
				}
				default: {
					break;
				}
			}
		}while(opcao != '0');
		
		cout << "Salvando o grafo" << endl;
		grafo.reescrever_arquivo();
		cout << "O Grafo foi salvo" << endl;
	} catch(string& mensagem){
		cerr << mensagem;
	}
    
	return 0;
}
