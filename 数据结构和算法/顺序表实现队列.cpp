#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
class Queue{
private:
    T *data;
    int front;//指向队首
    int rear;//队尾元素后一个位置
    int capacity;
    void resize();
public:
    Queue():data(new T[capacity]),front(0),rear(0),capacity(10){}
    ~Queue();
    void enqueue(T element);
    T dequeue();
    T getFront() const;
    int getSize() const;
};
template<typename T>
void Queue<T>::resize(){
    int newCapacity=capacity*1.5;
    T *newData=new T[newCapacity];
    for(int i=0;i<capacity;i++)
        newData[i]=data[i];
    delete [] data;
    data=newData;
    capacity=newCapacity;
}
template<typename T>
Queue<T>::~Queue(){
    delete [] data;
}
template<typename T>
void Queue<T>::enqueue(T element){
    if(rear==capacity){
        resize();
    }
    data[rear++]=element;//队尾插入元素
}
template<typename T>
T Queue<T>::dequeue(){//队首删除元素
    if(front==rear)
        throw std::underflow_error("Queue is empty");
    return data[front++];
}
template<typename T>
T Queue<T>::getFront() const{//获得队首元素
    if(front==rear)
        throw std::underflow_error("Queue is empty");
    return data[front];
}
template<typename T>
int Queue<T>::getSize() const{//获得队列长度
    if(front==rear)
        throw std::underflow_error("Queue is empty");
    return rear-front;
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