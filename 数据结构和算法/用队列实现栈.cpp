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
public:///////////下面？？？？？?????？？？？？？？？？？？？？？？？？？？？？？？？
    Queue():data(new T[10]),front(0),rear(0),capacity(10){}
    ~Queue();
    void enqueue(T element) ;
    T dequeue();
    T getFront() const;
    int getSize() const;
    bool empty() const;
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
template<typename T>
bool Queue<T>::empty() const{//判断队列是否为空
    return front==rear;
}
#define typename int
class MyStack{
private:
      Queue<typename> q1;
      Queue<typename> q2;
public:
      MyStack(){}
      void push(typename element){
          q1.enqueue(element);
}
      typename pop(){
          while(q1.getSize()>1){
              q2.enqueue(q1.dequeue());
          }
          typename result=q1.dequeue();
          while(!q2.empty()){
              q1.enqueue(q2.dequeue());
          }
          return result;
}
      typename top(){
          while(q1.getSize()>1){
              q2.enqueue(q1.dequeue());
          }
          typename result=q1.dequeue();
          q2.enqueue(result);
          while(!q2.empty()){
              q1.enqueue(q2.dequeue());
          }
          return result;
}
      bool empty(){
          return q1.empty();
}
};
int main(){
    MyStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout<<s.top()<<endl;//栈---后进先出--输出3
    cout<<s.pop()<<endl;//栈---后进先出--输出3并且弹出3
    cout<<s.top()<<endl;//栈---后进先出--输出2
    return 0;
}