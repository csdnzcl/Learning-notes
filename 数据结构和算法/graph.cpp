#include <iostream>
using namespace std;
//邻接矩阵代码篇
#define inf 0
class Graph{
private:
    int vertices;
    int **edges;//？？？？？？？？？
public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int v1,int v2,int weight);
    void printGraph();
};
Graph::Graph(int vertices) {
    this->vertices=vertices;
    edges=new int *[vertices];//？？？？？？
    for(int i=0;i<vertices;i++){
        edges[i]=new int[vertices];//？？？？
        for(int j=0;j<vertices;j++){
            edges[i][j]=inf;
        }
    }
}
Graph::~Graph() {
    for(int i=0;i<vertices;i++){
        delete []edges[i];
    }
    delete []edges;//？？？？？？？？？
}
void Graph::addEdge(int u, int v, int weight){
    edges[u][v]=weight;
}
void Graph::printGraph(){
    for(int i=0;i<vertices;i++){
        for(int j=0;j<vertices;j++){
            cout<<edges[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main(){
    Graph graph(5);
    graph.addEdge(0,1,1);
    graph.addEdge(0,2,3);
    graph.addEdge(1,2,2);
    graph.addEdge(2,3,7);
    graph.addEdge(3,4,9);
    graph.addEdge(4,0,4);
    graph.addEdge(4,2,5);
    graph.printGraph();
}