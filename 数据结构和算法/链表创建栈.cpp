#include <iostream>
#include <stdexcept>//用于处理异常的类
using namespace std;
template <typename T>
class Stack{
private:
    struct Node{
        T data;
        Node* next;
        Node(T d):data(d),next(NULL){}
    };
    Node* head;
    int size;
public:
    Stack():head(NULL),size(0){}
    ~Stack();
    void push(T element);
    T pop();
    T top() const;
    int getSize() const;
};
template <typename T>
Stack<T>::~Stack(){
    while(head!=NULL){
        Node* temp=head;
        head=head->next;
        delete temp;
    }
}
template <typename T>
void Stack<T>::push(T element){
    Node* newNode=new Node(element);//new动态申请内存
    newNode->next=head;
    head=newNode;
    ++size;
}
template <typename T>
T Stack<T>::pop(){
    if(head==NULL)
        throw runtime_error("Stack is empty");
    T element=head->data;
    Node* temp=head;
    head=head->next;
    delete temp;
    --size;
    return element;
}
template <typename T>
T Stack<T>::top() const{
    if(head==NULL)
        throw runtime_error("Stack is empty");
    return head->data;
}
template <typename T>
int Stack<T>::getSize() const{
    return size;
}
int main(){
    Stack<int> s;
    for(int i=0;i<10;++i)
        s.push(i);
    cout<<s.top()<<endl;
    s.push(17);
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.top()<<endl;
    cout<<s.getSize()<<endl;
    return 0;
}