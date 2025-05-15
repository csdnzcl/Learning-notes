#include <iostream>
using namespace std;
template<typename T>
struct TreeNode{
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(T x):val(x),left(nullptr),right(nullptr){}
};
template<typename T>
class BinarySearchTree{
private:
        TreeNode<T> *root;
        TreeNode<T> *insertNode(TreeNode<T> *node,T val);
        TreeNode<T> *removeNode(TreeNode<T> *node,T val);
        bool searchNode(TreeNode<T> *node,T val);
        void inOrder(TreeNode<T> *node);
public:
        BinarySearchTree():root(nullptr){}
        ~BinarySearchTree();
        void insert(T val){
            root=insertNode(root,val);
        }
        void remove(T val){
            root=removeNode(root,val);
        }
        bool search(T val){
            return searchNode(root,val);
        }
        void inOrder(){
            inOrder(root);
        }
};
template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    while(root){
        remove(root->val);
    }
}
template<typename T>
TreeNode<T> *BinarySearchTree<T>::insertNode(TreeNode<T> *node, T val) {
    if(node==nullptr){
        return new TreeNode<T>(val);
    }
    if(val<node->val){
        node->left=insertNode(node->left,val);
    }
    else if(val>node->val){
        node->right=insertNode(node->right,val);
    }
    return node;
}
template<typename T>//删除节点比较难
TreeNode<T> *BinarySearchTree<T>::removeNode(TreeNode<T> *node, T val) {
    if(node==nullptr){
        return nullptr;
    }
    if(val<node->val){
        node->left=removeNode(node->left,val);
    }
    else if(val>node->val){
        node->right=removeNode(node->right,val);
    }
    else{
        if(node->left==nullptr&&node->right==nullptr){
           delete node;
           return nullptr;
        }else if(node->left==nullptr){
            TreeNode<T> *temp=node->right;
            delete node;//???????
            return temp;
        }else if(node->right==nullptr){
            TreeNode<T> *temp=node->left;
            delete node;
            return temp;
        }else{
            TreeNode<T> *replacement=node->right;
            while(replacement->left){
                replacement=replacement->left;
            }
            node->val=replacement->val;
            node->right=removeNode(node->right,replacement->val);
        }
    }
}
template<typename T>
bool BinarySearchTree<T>::searchNode(TreeNode<T> *node, T val) {
    if(node== nullptr){
        return false;
    }
    if(val<node->val){
        return  searNode(node->left,val);
    }
    else if(val>node->val){
        return searNode(node->right,val);
    }
    return true;
}
template<typename T>
void BinarySearchTree<T>::inOrder(TreeNode<T> *node) {
    if(node==nullptr){
        return;
    }
    inOrder(node->left);
    cout<<node->val<<" ";
    inOrder(node->right);
}
int main() {
    BinarySearchTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    //bst.insert(7);
    bst.insert(2);
    bst.insert(4);
   // bst.insert(6);
    //bst.insert(8);
    bst.inOrder();
    return 0;
}
