/*#include <iostream>
using namespace std;
template<typename T>
struct TreeNode{
    T val;
    TreeNode *left;//指向左子结点的指针
    TreeNode *right;//指向右子结点的指针
    TreeNode() : val(0), left(NULL), right(NULL) {}
    TreeNode(T x) : val(x), left(NULL), right(NULL) {}
};///二叉树节点
template<typename T>
class Tree{
private:
    TreeNode<T> *root;//根结点
    TreeNode<T> *nodes;//结点池
    size_t nodeSize;//结点池大小
    TreeNode<T>* Creat(T a[],int size,int nodeId,T nullNode);//创建二叉树
    void visit(TreeNode<T> *node);//访问结点
    void preOrder(TreeNode<T> *node);//先序遍历
    void inOrder(TreeNode<T> *node);//中序遍历
    void postOrder(TreeNode<T> *node);//后序遍历
public:
    Tree();//构造函数
    Tree(int maxNodes);//构造函数
    ~Tree();//析构函数
    TreeNode<T>* GetTreeNode(int nodeId);//通过id获取结点
    void CreateTree(T a[],int size,T nullNode);//通过传入顺序表存储的数生成二叉树
    void preOrderTraversal();//先序遍历
    void inOrderTraversal();//中序遍历
    void postOrderTraversal();//后序遍历
};
template<typename T>
Tree<T>::Tree(){
    nodeSize=10000;
    nodes=new TreeNode<T>[nodeSize];
}
template<typename T>
Tree<T>::Tree(int maxNodes){
    nodeSize=maxNodes;
    nodes=new TreeNode<T>[nodeSize];
}
template<typename T>
Tree<T>::~Tree(){
    delete[] nodes;
}
template<typename T>
TreeNode<T>* Tree<T>::Creat(T a[],int size,int nodeId,T nullNode){
    if(nodeId>=size||a[nodeId]==nullNode)
        return NULL;
    TreeNode<T> *newNode=GetTreeNode(nodeId);
    newNode->val=a[nodeId];
    newNode->left=Creat(a,size,nodeId*2,nullNode);//递归调用
    newNode->right=Creat(a,size,nodeId*2+1,nullNode);//递归调用
    return newNode;
}//创建二叉树（通过顺序表创建）
template<typename T>
TreeNode<T>* Tree<T>::GetTreeNode(int nodeId){
    if(nodeId>=nodeSize)
        return NULL;
    return &nodes[nodeId];//记得需要取地址---nodes[nodeId]是一个对象，而不是一个地址？？？？？？？？？？？？？？？？？？？？？？？
}//nodes[nodeId]存储的是T类型的数据---与nodes->val相同?????????
template<typename T>
void Tree<T>::CreateTree(T a[],int size,T nullNode){
    root=Creat(a,size,1,nullNode);
}
template<typename T>
void Tree<T>::visit(TreeNode<T> *node) {
    cout<<node->val<<" ";
}
template<typename T>
void Tree<T>::preOrder(TreeNode<T> *node){
    if(node){
    visit(node);
    preOrder(node->left);//递归调用左子树
    preOrder(node->right);//递归调用右子树
    }
}
template<typename T>
void Tree<T>::inOrder(TreeNode<T> *node){
    if(node){
    inOrder(node->left);
    visit(node);
    inOrder(node->right);
    }
}
template<typename T>
void Tree<T>::postOrder(TreeNode<T> *node){
    if(node){
    postOrder(node->left);
    postOrder(node->right);
    visit(node);
    }
}
template<typename T>
void Tree<T>::preOrderTraversal() {
    preOrder(root);
}
template<typename T>
void Tree<T>::inOrderTraversal() {
    inOrder(root);
}
template<typename T>
void Tree<T>::postOrderTraversal() {
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
    T.CreateTree(a,15,nullNode);
    T.preOrderTraversal();
    cout<<endl;
    T.inOrderTraversal();
    cout<<endl;
    T.postOrderTraversal();
    cout<<endl;
    return 0;
}
*/
#include <iostream>
using namespace std;
// 二叉树结点模板类
template<typename T>
struct TreeNode {
    T val;
    TreeNode *left;   // 左子节点指针
    TreeNode *right;  // 右子节点指针

    // 默认构造函数（值初始化为0）
    TreeNode() : val(0), left(NULL), right(NULL) {}
    // 带值参数的构造函数
    TreeNode(T x) : val(x), left(NULL), right(NULL) {}
};

// 二叉树模板类
template<typename T>
class Tree {
private:
    TreeNode<T> *root;     // 根节点指针
    TreeNode<T> *nodes;    // 预分配的节点池（数组实现）
    size_t nodeSize;       // 节点池最大容量

    // 核心创建函数（递归实现）
    // 参数说明：
    // - a[]: 输入数组（按完全二叉树层序存储）
    // - size: 数组长度
    // - nodeId: 当前节点在数组中的逻辑位置（注意从1开始计数）
    // - nullNode: 表示空节点的特殊值
    TreeNode<T>* Creat(T a[], int size, int nodeId, T nullNode);// 递归创建树
    void visit(TreeNode<T> *node);       // 节点访问操作
    void preOrder(TreeNode<T> *node);    // 递归先序遍历
    void inOrder(TreeNode<T> *node);     // 递归中序遍历
    void postOrder(TreeNode<T> *node);   // 递归后序遍历

public:
    Tree();                   // 默认构造函数（预分配10000节点）
    Tree(int maxNodes);       // 自定义节点池大小的构造函数
    ~Tree();                  // 析构函数

    // 通过逻辑位置获取物理节点（注意潜在越界风险）
    TreeNode<T>* GetTreeNode(int nodeId);

    // 根据层序数组创建树（需包含nullNode标记空位）
    void CreateTree(T a[], int size, T nullNode);

    // 遍历接口（注意递归深度限制）
    void preOrderTraversal();
    void inOrderTraversal();
    void postOrderTraversal();
};

/* 类方法实现 */

// 默认构造函数（预分配10000个节点）
template<typename T>
Tree<T>::Tree() {
    nodeSize = 10000;
    nodes = new TreeNode<T>[nodeSize];  // 可能抛出bad_alloc异常
}

// 自定义容量构造函数
template<typename T>
Tree<T>::Tree(int maxNodes) {
    nodeSize = maxNodes;
    nodes = new TreeNode<T>[nodeSize];
}

// 析构函数（释放节点池内存）
template<typename T>
Tree<T>::~Tree() {
    delete[] nodes;  // 注意：节点间连接关系不影晌数组内存释放
}

// 通过逻辑位置获取节点（注意：nodeId从0开始计数）
template<typename T>
TreeNode<T>* Tree<T>::GetTreeNode(int nodeId) {
    if (nodeId >= nodeSize)  // 越界保护
        return NULL;
    return &nodes[nodeId];   // 返回节点池中的物理地址
}

// 节点访问操作（可修改为其他操作）
template<typename T>
void Tree<T>::visit(TreeNode<T> *node) {
    cout << node->val << " ";
}

// 递归先序遍历实现
template<typename T>
void Tree<T>::preOrder(TreeNode<T> *node) {
    if (node) {
        visit(node);
        preOrder(node->left);   // 递归左子树
        preOrder(node->right);  // 递归右子树
    }
}

// 递归中序遍历实现
template<typename T>
void Tree<T>::inOrder(TreeNode<T> *node) {
    if (node) {
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
}

// 递归后序遍历实现
template<typename T>
void Tree<T>::postOrder(TreeNode<T> *node) {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        visit(node);
    }
}

/* 核心树构建方法 */
template<typename T>
TreeNode<T>* Tree<T>::Creat(T a[], int size, int nodeId, T nullNode) {
    // 退出条件：
    // 1. 逻辑位置超出数组物理大小
    // 2. 当前元素是空节点标记
    if (nodeId >= size || a[nodeId] == nullNode)
        return NULL;

    // 从节点池获取物理节点
    TreeNode<T> *newNode = GetTreeNode(nodeId);
    newNode->val = a[nodeId];  // 设置节点值

    // 计算子节点逻辑位置（完全二叉树特性）：
    // 左子节点位置 = 2 * nodeId
    // 右子节点位置 = 2 * nodeId + 1
    // 注意：这种计算方式要求数组从索引1开始存储根节点。。。。。。。。。。。。。。。。。。。
    newNode->left = Creat(a, size, nodeId * 2, nullNode);
    newNode->right = Creat(a, size, nodeId * 2 + 1, nullNode);

    return newNode;
}

// 创建树入口方法
template<typename T>
void Tree<T>::CreateTree(T a[], int size, T nullNode) {
    root = Creat(a, size, 1, nullNode);  // 从逻辑位置1开始构建（对应a[1]）
}

// 遍历接口封装
template<typename T>
void Tree<T>::preOrderTraversal() {
    preOrder(root);
}

template<typename T>
void Tree<T>::inOrderTraversal() {
    inOrder(root);
}

template<typename T>
void Tree<T>::postOrderTraversal() {
    postOrder(root);
}

/* 测试用例 */
int main() {
    const char nullNode = '-';
    // 测试数组说明：
    // - 索引0未使用（占位）
    // - 按完全二叉树层序存储（索引1为根）
    char a[15] = {
            nullNode,  // [0] 占位
            'a',       // [1] 根节点
            'b',       // [2] 根的左孩子
            'c',       // [3] 根的右孩子
            'd',       // [4] b的左孩子
            nullNode,  // [5] b的右孩子
            'e',       // [6] c的左孩子
            'f',       // [7] c的右孩子
            'g','h',   // [8][9] d的左右孩子
            nullNode,nullNode,nullNode,nullNode,  // [10]-[13] 占位
            'i'        // [14] f的右孩子
    };

    Tree<char> T(15);
    T.CreateTree(a, 15, nullNode);

    cout << "先序遍历: ";
    T.preOrderTraversal();
    cout << endl;

    cout << "中序遍历: ";
    T.inOrderTraversal();
    cout << endl;

    cout << "后序遍历: ";
    T.postOrderTraversal();
    cout << endl;

    return 0;
}























