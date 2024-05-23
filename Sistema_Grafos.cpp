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
        void inserir_aresta(array <int, 2> a);
};

void Grafo::inserir_aresta(array <int, 2> a){
	bool repete = false;
	
	for(unsigned int i{0}; i < a.size(); i++){
		
	}
	
	if(!repete){
		
		
		imprimir_conjunto();
	} else {
		cout << "A aresta já existe, ou possui um vertice inexistente." << endl;
	}
}

void Grafo::inserir_vertice(int v){
	bool repete = false;
	for(unsigned int i{0}; i < vertices.size(); i++){
        if(vertices.at(i) == v)
            repete = true;
    }
    
	if(!repete){
		vertices.push_back(v);
		
		imprimir_conjunto();
	} else {
		cout << "O vertice já existe!" << endl;
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


void existe(vector <int> vertices, int vertice){
    bool achou = false;
    for(unsigned int i{0}; i < vertices.size(); i++){
        if(vertices.at(i) == vertice)
            achou = true;
    }
    if(achou == false)
        throw string("Erro! Aresta de vertice inexistente!");
}

void nao_existe(vector <int> vertices, int vertice){
    bool achou = false;
    for(unsigned int i{0}; i < vertices.size(); i++){
        if(vertices.at(i) == vertice)
            achou = true;
    }
    if(achou == true)
        throw string("Erro! Vertice repetido!");
}
/*
Grafo iniciar(){
	ifstream arquivo("grafos.txt");
    char lixo;
    vector <int> vertices;
    vector <array <int, 2>> arestas;
    int vertice;
    array <int, 2> aresta;
    bool mEh_direcionado;
    cout << "O seu grafo eh direcionado?";
    cin >> mEh_direcionado;
    try{
        arquivo >> lixo;
        if(lixo != 'V')
            throw string("Erro sintatico!");
        arquivo >> lixo;
        if(lixo != '=')
            throw string("Erro sintatico!");
        arquivo >> lixo;
        if(lixo != '{')
            throw string("Erro sintatico!");
        while(lixo != '}'){
            if(arquivo >> vertice)
                nao_existe(vertices, vertice);
            else
                throw string("Erro sintatico!");
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
        while(lixo != '}'){
            arquivo >> lixo;
            if(lixo != '(')
                throw string("Erro sintatico!");
            if(arquivo >> aresta[0])
                existe(vertices, aresta[0]);
            else
                throw string("Erro sintatico!");
            arquivo >> lixo;

            if(lixo != ',')
                throw string("Erro sintatico!");
            if(arquivo >> aresta[1])
                existe(vertices, aresta[1]);
            else
                throw string("Erro sintatico!");
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

        Grafo grafo(vertices, arestas, mEh_direcionado);
        
    } catch(string& mensagem){
        cerr << mensagem;
    }
}*/

int main(){
	ifstream arquivo("grafos.txt");
	char lixo;
	vector <int> vertices;
	vector <array <int, 2>> arestas;
	int vertice;
	array <int, 2> aresta;
	bool mEh_direcionado;
	cout << "O seu grafo eh direcionado?";
	cin >> mEh_direcionado;
	try{
		arquivo >> lixo;
		if(lixo != 'V')
			throw string("Erro sintatico!");
		arquivo >> lixo;
		if(lixo != '=')
			throw string("Erro sintatico!");
		arquivo >> lixo;
		if(lixo != '{')
			throw string("Erro sintatico!");
		while(lixo != '}'){ // lera todos os valores de vertice
			if(arquivo >> vertice){
				nao_existe(vertices, vertice);
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
        while(lixo != '}'){
            arquivo >> lixo;
            if(lixo != '(')
                throw string("Erro sintatico!");
            if(arquivo >> aresta[0])
                existe(vertices, aresta[0]);
            else
                throw string("Erro sintatico!");
            arquivo >> lixo;

            if(lixo != ',')
                throw string("Erro sintatico!");
            if(arquivo >> aresta[1])
                existe(vertices, aresta[1]);
            else
                throw string("Erro sintatico!");
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
				case '1': {
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
						
						unsigned int v;
						cout << "Qual vertice deseja inserir? ";
						cin >> v;
						
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
				case '2': {
					break;
				}
				case '3': {
					break;
				}
				case '4': {
					break;
				}
				case '5': {
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
	} catch(string& mensagem){
		cerr << mensagem;
	}
    
	return 0;
}
