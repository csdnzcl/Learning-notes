#include <iostream>
using namespace std;
class Graph{
private:
    // 边结点结构体
    struct EdgeNode{
        int vertex;// 顶点编号
        int weight;// 权重
        EdgeNode* next;// 指向下一个边结点的指针
    };
    // 顶点结点结构体
    struct VertexNode{
        int vertex;// 顶点编号
        EdgeNode* firstEdge;// 指向第一个边结点指针
    };
    int vertices;// 顶点个数
    VertexNode* nodes;// 顶点数组
public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int u,int v, int w);// 添加边
    void printGraph();
};
Graph::Graph(int vertices){
    this->vertices=vertices;
    this->nodes=new VertexNode[vertices];
    for(int i=0;i<vertices;++i){
        nodes[i].vertex=i;
        nodes[i].firstEdge=NULL;
    }
}
Graph::~Graph(){
    //先释放所有边结点
    for(int i=0;i<vertices;++i){
        EdgeNode* curr=nodes[i].firstEdge;
        while(curr){
            EdgeNode *temp=curr;
            curr=curr->next;
            delete temp;
        }
    }
    // 再释放顶点结点
    delete [] nodes;
}
void Graph::addEdge(int u,int v, int w) {
    EdgeNode *newNode = new EdgeNode;
    newNode->vertex = v;
    newNode->weight = w;//不讨论firstEdge是否为空？？？？？？？？
    newNode->next = nodes[u].firstEdge;//头插法
    nodes[u].firstEdge = newNode;
}
void Graph::printGraph(){
    for(int i=0;i<vertices;++i){
        EdgeNode *curr=nodes[i].firstEdge;
        cout<<"Vertex"<<i<<": ";
        while(curr) {
            cout << curr->vertex << "(" << curr->weight << ")";
            curr = curr->next;
        }
        cout<<endl;
    }
}
int main(){
    Graph graph(5);
    graph.addEdge(0,1,4);
    graph.addEdge(0,2,2);
    graph.addEdge(1,2,3);
    graph.addEdge(2,3,4);
    graph.addEdge(3,4,2);
    graph.printGraph();
    return 0;
}