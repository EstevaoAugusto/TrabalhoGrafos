#include <iostream>
#include <fstream>
#include <graphics.h>
#include <vector>
#include <list>
#include <array>

using namespace std;

class Grafo{
    private:
        vector <int> vertices;
        vector <array <int, 2>> arestas;
        bool eh_direcionado;
        int retorna_posicao(int x){
            for(int i{0}; i < vertices.size(); i++){
                if(x == vertices[i])
                    return i;
            }
        }
    public:
        Grafo(vector <int> pVertices, vector <array <int,2>> pArestas, bool pEh_direcionado){
            vertices = pVertices;
            arestas = pArestas;
            eh_direcionado = pEh_direcionado;
        }
        ~Grafo(){}
        void matriz_adjacencia();
        void lista();
        void grafico();
};

void Grafo::matriz_adjacencia(){
    vector<vector<int>> matriz(vertices.size(), vector<int>(vertices.size()));
    int x;
    int y;
    int posicao_x;
    int posicao_y;
    if(eh_direcionado){
        for(int i{0}; i < arestas.size(); i++){
           x = arestas[i][0];
           y = arestas[i][1];
           posicao_x = retorna_posicao(x);
           posicao_y = retorna_posicao(y);
           matriz[posicao_x][posicao_y] = 1;
        }
    }
    else{
        for(int i{0}; i < arestas.size(); i++){
            x = arestas[i][0];
            y = arestas[i][1];
            posicao_x = retorna_posicao(x);
            posicao_y = retorna_posicao(y);
            matriz[posicao_x][posicao_y] = 1;
            matriz[posicao_y][posicao_x] = 1;
        }
    }
    for(int i{0}; i < vertices.size(); i++){
        cout << "   " << vertices[i];
    }
    cout << endl;
    for(int i{0}; i < vertices.size(); i++){
        cout << vertices[i] << " ";
        for(int j{0}; j < vertices.size(); j++){
            cout << '[' << matriz[i][j] << ']' << " ";
        }
        cout << endl;
    }
}

void Grafo::lista(){
    vector<list <int>> listas;
    for(int i{0}; i < vertices.size(); i++){
        list <int> lista;
        lista.push_back(vertices[i]);
        listas.push_back(lista);
    }
    if(eh_direcionado){
        for(int i{0}; i < listas.size(); i++){
            for(int j{0}; j < arestas.size(); j++){
                if(arestas[j][0] == listas[i].front())
                    listas[i].push_back(arestas[j][1]);
            }
        }
    }
    else{
        for(int i{0}; i < listas.size(); i++){
            for(int j{0}; j < arestas.size(); j++){
                if(arestas[j][0] == listas[i].front())
                    listas[i].push_back(arestas[j][1]);
                if(arestas[j][1] == listas[i].front())
                    listas[i].push_back(arestas[j][0]);
            }
        }
    }
    for(int i{0}; i < listas.size(); i++){
        cout << '[' << listas[i].front() << ']';
        bool frente = true;
        for(auto v : listas[i]){
            if(!frente)
                cout << " -> " << v;
            frente = false;
        }
        cout << endl;
    }
}


void existe(vector <int> vertices, int vertice){
    bool achou = false;
    for(int i{0}; i < vertices.size(); i++){
        if(vertices.at(i) == vertice)
            achou = true;
    }
    if(achou == false)
        throw string("Erro! Aresta de vertice inexistente!");
}

void nao_existe(vector <int> vertices, int vertice){
    bool achou = false;
    for(int i{0}; i < vertices.size(); i++){
        if(vertices.at(i) == vertice)
            achou = true;
    }
    if(achou == true)
        throw string("Erro! Vertice repetido!");
}

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
        grafo.matriz_adjacencia();
        grafo.lista();
    }
    catch(string& mensagem){
        cerr << mensagem;
    }
}