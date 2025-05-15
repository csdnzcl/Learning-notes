#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class Queue {
private:
    struct Node{
        T data;
        Node *next;
        Node(T element):data(element),next(nullptr){}
    };
    Node *front;
    Node *rear;
    int size;
public:
    Queue() : front(NULL), rear(NULL),size(0) {}
    ~Queue();
    void enqueue(T element);
    T dequeue();
    T getFront();
    int getSize();
};
template<typename T>
Queue<T>::~Queue(){
    while(front){
        Node *temp=front;
        front=front->next;
        delete temp;
    }
}
template<typename T>
void Queue<T>:: enqueue(T element){
    Node *newNode=new Node(element);
    if(rear==NULL){
        rear=newNode;
        front=rear;
    }else{
        rear->next=newNode;
        rear=newNode;
    }
    size++;
}
template<typename T>
T Queue<T>:: dequeue(){
    if(front==NULL)
        throw runtime_error("Queue is empty");
    T element=front->data;
    Node *temp=front;
    front=front->next;//会不会出现front==NULL??????????
    delete temp;
    if(--size){rear=NULL;}
    return element;
}
template<typename T>
T Queue<T>:: getFront(){
    if(front==NULL)
        throw runtime_error("Queue is empty");
    return front->data;
}
template<typename T>
int Queue<T>:: getSize(){
    return size;
}
    int main(){
        int N;
        cin>>N;
        while(N--){
            int n;
            cin>>n;
            Queue<int> q1,q2;
            for(int i=1;i<=n;++i){
                q1.enqueue(i);
            }
            while(q1.getSize()>3){
                int cnt=0;
                while(q1.getSize()){
                    int v=q1.dequeue();
                    cnt++;
                    if(cnt%2==1){
                        q2.enqueue(v);
                    }
                }
                if(q2.getSize()<=3){
                    while(q2.getSize()){
                        q1.enqueue(q2.dequeue());
                    }
                    break;
                }
                cnt=0;
                while(q2.getSize()){
                    int v=q2.dequeue();
                    cnt++;
                    if(cnt%3==1||cnt%3==2){
                        q1.enqueue(v);
                    }
                }
            }
            int flag=0;
            while(q1.getSize()){
                if(flag){
                    cout<<" ";
                }
                cout<<q1.getFront();
                q1.dequeue();
                flag++;
            }
        }
    }