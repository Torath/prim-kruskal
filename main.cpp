#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h>

using namespace std::chrono;
using namespace std;




void trybA();
void trybB();
//globalne zmienne
#define edge pair<int,int>

class Graph{

private:
    //graf
    vector <pair<int,edge>> graf;
    //lista sasiedztwa dla algorytmu prima
    list<edge> *listaSasiedztwa;
    vector <pair<int,edge>> drzewo;
    int *parent;
    int liczbaWierzcholkow;

public:
    Graph(int liczbaWierzcholkow);
    void addEdge(int v1,int v2, int w);
    int findSet(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
    void prim();
    void clearMST();
};
class queueComparator{
    public:
        //customowe porównywanie krawedzi dla kolejki
        int operator() (const pair<int,edge> edge1,const pair<int,edge> edge2){
            return edge1.first>edge2.first;
        }
};
//klasa graf
Graph::Graph(int v){
    //inicjalizacja zmiennych
    liczbaWierzcholkow=v;
    parent=new int[liczbaWierzcholkow];
    listaSasiedztwa=new list<edge>[liczbaWierzcholkow];

    for(int i=0;i<liczbaWierzcholkow;i++){
        parent[i]=i;
    }
    graf.clear();
    drzewo.clear();
}
void Graph::clearMST(){
    drzewo.clear();
}
void Graph::addEdge(int v1,int v2,int w){
    Graph::graf.push_back(make_pair(w,edge(v1,v2)));
    listaSasiedztwa[v1].push_back(edge(v2,w));
    listaSasiedztwa[v2].push_back(edge(v1,w));

}
int Graph::findSet(int i){
    if(i==Graph::parent[i])
        return i;
    else
        return findSet(Graph::parent[i]);
}
void Graph::union_set(int u, int v){
    parent[u]=parent[v];
}
void Graph::kruskal(){
    int i,uRep,vRep;


    sort(graf.begin(),graf.end());
    for(int i=0;i< graf.size();i++){
        uRep=findSet(graf[i].second.first);
        vRep=findSet(graf[i].second.second);
        if(uRep != vRep){
            drzewo.push_back(graf[i]);
            union_set(uRep,vRep);
        }
    }
}
void Graph::print(){
    cout<<endl;
    int koszt=0;
    for(int i=0;i<drzewo.size();i++){
        cout<<"V"<<drzewo[i].second.first<<"->V"<<drzewo[i].second.second<<"("<<drzewo[i].first<<"); ";
        koszt+=drzewo[i].first;
    }
    cout<<"Calkowity koszt: "<<koszt;

    drzewo.clear();
}
void Graph::prim(){

        //tablica poprzednika
        //kolejka priorytetowa
        //visited
    //inicjalizacja kolejki priorytetowej
    priority_queue<pair<int,edge>,vector<pair<int,edge>>,queueComparator> Q;

    bool* visited=new bool[liczbaWierzcholkow];
    for(int i=0;i<liczbaWierzcholkow;i++){
        visited[i]=false;
    }
    int v=0;
    visited[0]=true;


    for(int i=0;i<liczbaWierzcholkow-1;i++){
        //dla każdego nieodwiedzonego sąsiada u wierzcholka v
        //dodaj krawedzie do kolejki
        for(auto const& j: listaSasiedztwa[v] ){
            if(visited[j.first]==false){
                int weight=j.second;
                int v2=j.first;
                    Q.push(make_pair(weight,edge(v,v2)));

            }
        }

        pair<int,edge> temp;
        do{//pobieranie krawedzi odrzucając krawedzie do odwiedzonych sasiadow
            temp=Q.top();
            Q.pop();
        }while(visited[temp.second.second]);

        drzewo.push_back(temp);
        visited[temp.second.second]=true;
        v=temp.second.second;



    }

}

Graph tworzGrafA();
Graph tworzGrafB(int w, int p);
int main()
{

    cout << "Wybierz tryb wykonania programu:"<<endl;
    cout << "1. Tryb A - wykonanie algorytmow dla grafu z pliku PrimKruksal_dane.txt"<<endl;
    cout << "2. Tryb B - strumieniowe wykonanie algorytmow dla grafow o zmiennej wielkosci"<<endl;
    int tryb;
    cin >> tryb;
    //tryb A:
    //pojedyncze wykonanie obu algorytmów w oparciu o dane z pliku
    if(tryb==1)trybA();
    //tryb B:
    //wykonanie dla losowych grafów o zmiennej wielkości z zakresu
    if(tryb==2)trybB();

}

int** kruskal(int** graf,int w){
    return 0;
}

void trybA(){

    Graph g=tworzGrafA();

    //wykonanie algorytmu i pomiar czasu
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    g.prim();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    g.print();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);


    std::cout <<endl<<endl<< "Czas wykonania algorytmu Prima :" << time_span.count() << " sekund."<<endl<<endl;

     t1 = high_resolution_clock::now();
    g.kruskal();
     t2 = high_resolution_clock::now();
    g.print();
     time_span = duration_cast<duration<double>>(t2 - t1);


    std::cout <<endl<< "Czas wykonania algorytmu Kruskala :" << time_span.count() << " sekund.";

}

void trybB(){
    cout <<endl<< "Podaj zakres wierzcholkow od:"<<endl;
    int zakresOd,zakresDo,procentWypelnienia,liczbaWykonan;
    cin >> zakresOd;
    cout << "Podaj zakres wierzcholkow do:"<<endl;
    cin >> zakresDo;
    cout << "Podaj procent wypelnienia grafow(minimum 50):"<<endl;
    do{
    cin >> procentWypelnienia;
    }while(procentWypelnienia < 50 || procentWypelnienia > 100 );

    cout << "Podaj liczbe wykonan algorytmu dla kazdej liczby wierzcholkow:"<<endl;
    cin >> liczbaWykonan;
    int i=5;
    for(int i=zakresOd;i<=zakresDo;i++){
        cout<<"Czas dla "<<i<<" wierzcholkow: ";
        double* czasyWykonania=new double[liczbaWykonan];
        double sredniaP=0,sredniaK=0;
        for(int j=0;j<liczbaWykonan;j++){
            Graph graf=tworzGrafB(i,procentWypelnienia);
            auto start = std::chrono::system_clock::now();
            graf.prim();
            auto stop = std::chrono::system_clock::now();
            sredniaP+=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

            graf.clearMST();
            start = std::chrono::system_clock::now();
            graf.kruskal();
            stop = std::chrono::system_clock::now();
            sredniaK+=std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

        }
        cout<<"Algorytm Prima: "<<sredniaP/liczbaWykonan<<" ms,\t";
        cout<<"Algorytm Kruskala :"<<sredniaK/liczbaWykonan<<" ms"<<endl;


    }
}

//wczytanie grafu z pliku
Graph tworzGrafA(){



    ifstream infile("PrimKruskal_dane.txt");
    string line;

    //inicjalizacja zmiennych
    getline(infile, line);
    int V=atoi(line.c_str());
    Graph g(V);


    while (std::getline(infile, line)){
        int v1=-100,v2=-100,weight=-100;
        char temp;
        istringstream ss(line);
        ss>>v1>>temp>>v2>>temp>>weight;
        g.addEdge(v1,v2,weight);
    }

    return g;

}

Graph tworzGrafB(int w, int p){
    int krawedzie=((w*(w-1))/2)*p/100;
    //inicjalizacja zmiennych
    int** macierzSasiedztwa=0;
    macierzSasiedztwa=new int*[w];
    bool* odwiedzoneWierzcholki= new bool[w];
    Graph g(w);

    //wypelnienie tablic zerami/false
    for(int i=0;i<w;i++){
        odwiedzoneWierzcholki[i]=false;
        macierzSasiedztwa[i]=new int[w];

        for(int j=0;j<w;j++){
            macierzSasiedztwa[i][j]=0;
        }
    }

    //losowanie par wierzcholkow dla krawedzi
    srand ( time(NULL) );
    for(int i=0;i<krawedzie;i++){

        //jeśli istnieją wierzcholki bez krawedzi - wybierz ten wierzcholek
        int randIndex=-1;
        for(int i=0;i<w;i++){
            if(odwiedzoneWierzcholki[i]==false){
                randIndex=i;
            }
        }

        //jeśli nie ma nieodwiedzonego wierzchołka - losuj dowolny
        if(randIndex == -1){
           randIndex = rand() % w;
        }
        odwiedzoneWierzcholki[randIndex]=true;

        //losuj drugą parę różną od pierwszego wybranego wierzchołka
        int randIndey;
        do {
        randIndey = rand() % w;
        }while(randIndey==randIndex);
        odwiedzoneWierzcholki[randIndey]=true;

        //losuj wagi dla wybranej krawedzi
        if(macierzSasiedztwa[randIndex][randIndey]==0){
            int weight= rand()% (( 100 + 1 ) - 1);
            macierzSasiedztwa[randIndex][randIndey]=weight;
            macierzSasiedztwa[randIndey][randIndex]=weight;
            g.addEdge(randIndex,randIndey,weight);
        }else{
            i--;
        }

    }
    return g;
}
