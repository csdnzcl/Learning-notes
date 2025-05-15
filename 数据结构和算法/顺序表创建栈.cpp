//顺序表创建栈
#include <iostream>
#include<vector>
#include <stdexcept>//用于处理异常的类
using namespace std;
template<typename T>
class Stack{
private:
    T* data;//数据
    int size;//元素个数
    int capacity;//容量
    void resize();//扩容
public:
    Stack():data (new T[capacity]),size(0),capacity(10){}
    ~Stack();
    void push(T element);//入栈
    T pop();//出栈
    T top() const;//栈顶元素
    int getSize() const;//获取元素个数
};
template<typename T>
void Stack<T>::resize(){
    int newCapacity=capacity*2;
    T* newData=new T[newCapacity];
    for(int i=0;i<size;i++){
        newData[i]=data[i];
    }
    delete[] data;
    data=newData;
    capacity=newCapacity;
}
template<typename T>
Stack<T>::~Stack(){
    delete[] data;
}
template<typename T>
void Stack<T>::push(T element){
    if(size==capacity){
        resize();
    }
    data[size++]=element;//插入元素，栈顶元素加1
}
template<typename T>
T Stack<T>::pop(){
    if(size==0){
        throw runtime_error("Stack is empty");
    }
    return data[--size];//返回栈顶元素，并栈顶元素减1
}
template<typename T>
T Stack<T>::top() const{
    if(size==0){
        throw runtime_error("Stack is empty");
    }
    return data[size-1];//返回栈顶元素
}
template<typename T>
int Stack<T>::getSize() const{
    return size;
}

int main() {

}