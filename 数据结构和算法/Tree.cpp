/*#include <iostream>
using namespace std;
template<typename T>
struct ListNode {
    T data;//数据域
    ListNode *next;//指向下一个结点的指针。
    ListNode(T d):data(d),next(NULL){}
};//孩子列表用链表存储。
//实现树结点
template<typename T>
struct TreeNode{
    T data;//数据域
    ListNode<TreeNode<T> *> *childrenHead;//指向子结点的链表头结点。
    TreeNode(){
        childrenHead=NULL;
    }
    ////TreeNode<T>* 代替了ListNode构造函数中的T？？？？？？？？？
    void AddChild(TreeNode<T>* node){//添加子结点。
        ListNode<TreeNode<T>* > *childNode=new ListNode< TreeNode<T>* >(node) ;
        if(childrenHead==NULL){
            childrenHead=childNode;
        }else{
            childNode->next=childrenHead;
            childrenHead=childNode;
        }
    }
};
template<typename T>
class Tree{
private:
    TreeNode<T> *nodes;
    TreeNode<T> *root;//根结点指针。
public:
    Tree();
    Tree(int maxNodes);
    ~Tree();
    TreeNode<T>* GetTreeNode(int id);//通过Id获取结点
    void SetRoot(int rootId);//设置根节点
    void AddChild(int patentId,int sonId);//
    void AssignData(int nodeId,T data);
    void Print(TreeNode<T> *node=NULL);//利用深度遍历打印
};
template<typename T>
Tree<T>::Tree(){
    nodes=new TreeNode<T>[100];
}
template<typename T>
Tree<T>::Tree(int maxNodes){
    nodes=new TreeNode<T>[maxNodes];
}
template<typename T>
Tree<T>::~Tree(){
    delete[] nodes;
}
template<typename T>
TreeNode<T>* Tree<T>::GetTreeNode(int id){
    return &nodes[id];//nodes[id]是一个对象，所以需要取地址。
}
template<typename T>
void Tree<T>::SetRoot(int rootId){
    root=GetTreeNode(rootId);
}
template<typename T>
void Tree<T>::AddChild(int patentId,int sonId){
    TreeNode<T> *patentNode=GetTreeNode(patentId);
    TreeNode<T> *sonNode=GetTreeNode(sonId);
    patentNode->AddChild(sonNode);
}
template<typename T>
void Tree<T>::AssignData(int id,T data){
    GetTreeNode(id)->data=data;
}
template<typename T>
void Tree<T>::Print(TreeNode<T> *node){
    if(node==NULL){
        node=root;
    }
    cout<<node->data;
    ListNode<TreeNode<T>* > *tmp=node->childrenHead;
    while(tmp){
    Print(tmp->data);
    tmp=tmp->next;
    }
}
int main(){
    Tree<char> T(9);
    T.SetRoot(0);
    T.AssignData(0,'a');
    T.AssignData(1,'b');
    T.AssignData(2,'c');
    T.AssignData(3,'d');
    T.AssignData(4,'e');
    T.AssignData(5,'f');
    T.AssignData(6,'g');
    T.AssignData(7,'h');
    T.AssignData(8,'i');
    T.AddChild(0,1);
    T.AddChild(0,2);
    T.AddChild(1,3);
    T.AddChild(2,4);
    T.AddChild(2,5);
    T.AddChild(3,6);
    T.AddChild(3,7);
    T.AddChild(3,8);
    T.Print();
    return 0;
}*/
#include <iostream>
using namespace std;

// 链表节点模板类（用于存储树的子节点指针集合）
template<typename T>
struct ListNode {
    T data;         // 数据域：存储树节点指针（实际类型是TreeNode<T>*）  为什么不是T型????????????
    ListNode *next; // 指针域：指向下一个链表节点

    // 构造函数：初始化数据域，next指针置空
    ListNode(T d) : data(d), next(NULL) {}
}; // 分号结束结构体定义

// 树节点模板类（构成树结构的基本单元）
template<typename T>
struct TreeNode {
    T data;  // 节点存储的数据（可以是任意数据类型）
    ListNode<TreeNode<T>*> *childrenHead; // 子节点链表头指针

    // 构造函数：初始化子节点链表为空
    TreeNode() : childrenHead(NULL) {}

    // 添加子节点方法（核心逻辑）
    void AddChild(TreeNode<T>* node) {
        /* 创建新的链表节点，存储目标树节点指针
         * 注意模板参数的特殊性：
         * ListNode< TreeNode<T>* > 表示链表存储的是指向树节点的指针
         * 相当于用链表存储一组"子节点入口地址"
         */
        ListNode<TreeNode<T>*> *childNode = new ListNode<TreeNode<T>*>(node);

        /* 头插法建立链表（新节点始终插入在链表头部）
         * 特点：插入速度快O(1)，但最终子节点顺序与添加顺序相反
         * 示例：按序添加1,2,3，链表存储顺序为3->2->1
         */
        if (childrenHead == NULL) {  // 空链表直接作为头节点
            childrenHead = childNode;
        } else {                     // 非空链表执行头插
            childNode->next = childrenHead;
            childrenHead = childNode;
        }
    }
};

// 树容器类（管理整棵树的结构）
template<typename T>
class Tree {
private:
    TreeNode<T> *nodes;  // 节点数组（静态预分配内存）
    TreeNode<T> *root;   // 根节点指针（树的入口）

public:
    // 构造函数与析构函数
    Tree();               // 默认构造（预分配100节点）
    Tree(int maxNodes);   // 自定义容量构造
    ~Tree();              // 析构函数（需要改进内存泄漏）

    // 功能方法
    TreeNode<T>* GetTreeNode(int id);  // 通过索引获取节点
    void SetRoot(int rootId);          // 设置根节点位置
    void AddChild(int parentId, int childId); // 建立父子关系
    void AssignData(int nodeId, T data);     // 节点数据赋值
    void Print(TreeNode<T> *node = NULL);    // 深度优先遍历打印
};

//───────────────────────────
// 类方法实现
//───────────────────────────

// 默认构造函数：预分配100个树节点
template<typename T>
Tree<T>::Tree() {
    nodes = new TreeNode<T>[100]; // 静态分配内存（需预先估计最大节点数）
}

// 带容量参数的构造函数
template<typename T>
Tree<T>::Tree(int maxNodes) {
    nodes = new TreeNode<T>[maxNodes]; // 按需分配节点空间
}

// 析构函数：释放节点数组（⚠️存在内存泄漏）
template<typename T>
Tree<T>::~Tree() {
    delete[] nodes;
    /* 问题说明：
     * 此处仅释放了TreeNode数组，但每个TreeNode中的childrenHead链表
     * 包含动态分配的ListNode节点未被释放！
     * 改进建议：在TreeNode中添加析构函数，递归释放链表内存
     */
}

// 通过索引获取树节点（直接访问数组元素）
template<typename T>
TreeNode<T>* Tree<T>::GetTreeNode(int id) {
    // 注意：nodes是数组，返回的是对应索引位置的树节点引用
    return &nodes[id];
}

// 设置根节点（通过索引指定）
template<typename T>
void Tree<T>::SetRoot(int rootId) {
    root = GetTreeNode(rootId); // 将指定节点设为树的入口
}

// 建立父子关系（通过索引操作）
template<typename T>
void Tree<T>::AddChild(int parentId, int childId) {
    // 获取父子节点对象
    TreeNode<T>* parent = GetTreeNode(parentId);
    TreeNode<T>* child = GetTreeNode(childId);

    // 调用树节点的添加子节点方法
    parent->AddChild(child);
    /* 等效于：
     * parent->childrenHead链表添加指向child的节点
     */
}

// 给指定节点赋值数据
template<typename T>
void Tree<T>::AssignData(int nodeId, T data) {
    GetTreeNode(nodeId)->data = data; // 直接修改目标节点的数据域
}

// 深度优先遍历打印（递归实现）
template<typename T>
void Tree<T>::Print(TreeNode<T> *node) {
    if (node == NULL) { // 默认从根节点开始遍历
        node = root;
    }

    // 先序遍历：先输出当前节点数据
    cout << node->data << " ";

    // 递归遍历所有子节点（通过链表遍历）
    ListNode<TreeNode<T>*> *current = node->childrenHead;
    while (current != NULL) {
        Print(current->data);  // current->data是TreeNode<T>*类型
        current = current->next;
    }
}

//───────────────────────────
// 测试用例
//───────────────────────────
int main() {
    // 创建最多包含9个节点的字符树
    Tree<char> T(9);

    // 设置根节点（ID=0对应数组第0个元素）
    T.SetRoot(0);

    // 给所有节点赋值（a-i的字母）
    for (int i = 0; i < 9; ++i) {
        T.AssignData(i, 'a' + i); // 利用ASCII码顺序赋值
    }

    /* 构建树结构：
     *        a(0)
     *       /   \
     *     b(1)  c(2)
     *     /    /   \
     *   d(3) e(4)  f(5)
     *   / | \
     * g(6) h(7) i(8)
     */
    T.AddChild(0, 1);  // a->b
    T.AddChild(0, 2);  // a->c
    T.AddChild(1, 3);  // b->d
    T.AddChild(2, 4);  // c->e
    T.AddChild(2, 5);  // c->f
    T.AddChild(3, 6);  // d->g
    T.AddChild(3, 7);  // d->h
    T.AddChild(3, 8);  // d->i

    // 打印结果（深度优先遍历）
    // 预期输出：a b d g h i c e f
    T.Print();  // 输出末尾带空格

    return 0;
}