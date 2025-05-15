#include<iostream>
using namespace std;
template<typename T>
struct TreeNode{
    T data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): data(0),left(NULL),right(NULL){}
    TreeNode(T d):data(d),left(NULL),right(NULL){}
};
template<typename T>
class Tree{
private:
    TreeNode<T> *root;
    TreeNode<T> *nodes;
    size_t nodeSize;
    TreeNode<T>* create(T a[],int size,int nodeId,T nullNode);
    void visit(TreeNode<T> *node);
    void preOrder(TreeNode<T>* node);
    void inOrder(TreeNode<T>* node);
    void postOrder(TreeNode<T>* node);
public:
    Tree();
    Tree(int maxSize);
    ~Tree();
    void createTree(T a[],int size,T nullNode);
    TreeNode<T>* getNode(int nodeId);
    void preOrderTraversal();
    void inOrderTraversal();
    void postOrderTraversal();
};
template<typename T>
Tree<T>::Tree(){
    nodeSize=10000;
    nodes=new TreeNode<T>[nodeSize];
}
template<typename T>
Tree<T>::Tree(int maxSize){
    nodeSize=maxSize;
    nodes=new TreeNode<T>[nodeSize];
}
template<typename T>
Tree<T>::~Tree(){
    delete [] nodes;
}
template<typename T>
TreeNode<T>* Tree<T>::getNode(int nodeId){
    if(nodeId>=nodeSize)
        return NULL;
    return &nodes[nodeId];
}
template<typename T>
TreeNode<T>* Tree<T>::create(T a[], int size, int nodeId, T nullNode) {
    if(nodeId>=size||a[nodeId]==nullNode)
        return NULL;
    TreeNode<T>* newNode=getNode(nodeId);
    newNode->data=a[nodeId];
    newNode->left=create(a,size,2*nodeId,nullNode);
    newNode->right=create(a,size,2*nodeId+1,nullNode);
    return newNode;
}
template<typename T>
void Tree<T>::createTree(T a[],int size,T nullNode){//?????????
    root=create(a,size,1,nullNode);
}
template<typename T>
void Tree<T>::visit(TreeNode<T> *node){
    cout<<node->data<<" ";
}
template<typename T>
void Tree<T>::preOrder(TreeNode<T>* node){
    if(node)
        visit(node);
    preOrder(node->left);
    preOrder(node->right);
}
template<typename T>
void Tree<T>::inOrder(TreeNode<T>* node){
    if(node){
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}
template<typename T>
void Tree<T>::postOrder(TreeNode<T> *node) {
    if(node){
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
}
template<typename T>
void Tree<T>::preOrderTraversal(){
    preOrder(root);
}
template<typename T>
void Tree<T>::inOrderTraversal(){
    inOrder(root);
}
template<typename T>
void Tree<T>::postOrderTraversal(){
    postOrder(root);
}
int main(){
    const char nullNode='-';
    char a[15]={
            nullNode,'a','b','c','d',
            nullNode,'e','f','g','h',
            nullNode,nullNode,nullNode,nullNode,'i'
    };
    Tree<char> T(15);
    T.createTree(a,15,nullNode);
    T.preOrderTraversal();
    cout<<endl;
    T.inOrderTraversal();
    cout<<endl;
    T.postOrderTraversal();
    cout<<endl;
    return 0;
}