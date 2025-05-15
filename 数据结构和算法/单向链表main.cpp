#include <iostream>
#include <stdexcept>
using namespace std;
#define eleType int
struct ListNode {
    eleType data;//数据域,存储该节点的数据
    ListNode *next;//指针域，存储下一节点指针（地址）即指向下一个节点ListNode*。
    ListNode(eleType x):data(x),next(NULL){}
    //构造函数初始化列表---创建节点
};//构造节点
class LinkedList {//实现链表的类。
private:
    ListNode* head;//存储头节点。
    int size;//链表元素
public:
    LinkedList():head(NULL),size(0){}
    //链表的构造函数初始化
    ~LinkedList();//析构函数
    void insert(int i,eleType value);//增
    void remove(int i);//删
    ListNode* find(eleType value);//查找节点（值），返回值类型为ListNode*（节点）。。
    ListNode* get(int i);//查找节点（索引），返回值类型为ListNode*（节点）
    void update(int i,eleType value);//更新节点data---利用get(i)函数。
    void print();
};//实现链表的类(链表的增删改查）。
LinkedList::~LinkedList() {//析构函数，析构每个节点的内存空间
    ListNode* curr = head;
    while(curr != NULL){
        ListNode* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
}//析构函数
void LinkedList::insert(int i, eleType value) {
    if(i<0||i>size){
        throw std:: out_of_range("Invalid position");
    }
    ListNode* newNode = new ListNode(value);//创建节点
    if(i==0){
        newNode->next = head;
        head = newNode;
    }
    else{
        ListNode* curr = head;
        for(int j=0;j<i-1;j++){//注意遍历范围，<i-1。
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    size++;
}//插入节点。
void LinkedList::remove(int i){
    if(i<0||i>=size){
        throw std:: out_of_range("Invalid position");
    }
    if(i==0){
        ListNode* temp=head;
        head = head->next;
        delete temp;
    }else{
        ListNode* curr = head;
        for(int j=0;j<i-1;j++){
            curr = curr->next;
        }
        ListNode* temp = curr->next;
        curr->next = curr->next->next;//Or  curr->next = temp->next;
        delete temp;
    }
    size--;
}//删除节点
ListNode* LinkedList::find(eleType value) {
    ListNode* curr = head;
    while(curr!=NULL&&curr->data!=value){
        curr = curr->next;
    }
    return curr;
}//查找节点（根据值）。。
ListNode* LinkedList::get(int i) {
    if(i<0||i>=size){
        throw std:: out_of_range("Invalid position");
    }
    ListNode* curr = head;
    for(int j=0;j<i;j++){
        curr = curr->next;
    }
    return curr;
}//查找节点(根据索引)。
void LinkedList::update(int i, eleType value) {
   get(i)->data=value;
}//更新节点。
void LinkedList::print() {
    ListNode* curr = head;
    while(curr){
        cout<<curr->data<<" ";
        curr = curr->next;
    }
    cout<<endl;
}
int main() {
    LinkedList list;
    list.insert(0,10);
    list.insert(1,20);
    list.insert(2,30);
    list.insert(3,40);
    list.insert(4,50);
    list.print();
    list.remove(1);
    list.print();
    list.update(2,60);
    list.print();
    ListNode* tmp=list.find(30);

    cout<<tmp->data<<endl;
    cout<<list.get(3)->data<<endl;
    return 0;
}
