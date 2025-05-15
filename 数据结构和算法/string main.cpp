#include<iostream>
#include<cstring>
using namespace std;
class String{
private:
    char *str;//动态分配的字符串内存空间
    size_t length;//字符串长度
public:
    String();//构造函数，初始化字符串为空
    String(const char *s);//构造函数，初始化字符串为s
    String(const String &s);//拷贝构造函数
    ~String();//析构函数，释放动态分配的字符串的内存空间
    size_t getLength() const;//获取字符串长度
    char operator[] (size_t index) const;//访问重载
    String & operator=(const String &s);//赋值重载
    bool operator==(const String &s) const;//等于重载
    bool operator!=(const String &s) const;//不等于重载
    String copy() const;//字符串的拷贝
    String operator+(const String &s) const;//拼接重载
    friend ostream& operator<<(ostream &out,const String &s);//输出重载
};
String::String(){
    length=0;
    str=new char[1];
    str[0]='\0';
}
String::String(const char *s){
    length=strlen(s);
    str=new char[length+1];
    strcpy(str,s);
}
String::String(const String &s){
    length=s.length;
    str=new char[length+1];
    strcpy(str,s.str);
}
String::~String(){
    delete []str;
}
size_t String::getLength() const{//const意义：在这个类中，不会修改其成员变量
    return length;
}
char String::operator[](size_t index) const{
    if(index>=length)
        return '\0';
    return str[index];
}
String & String::operator=(const String &s){
    if(this!=&s){
        delete [] this->str;//？？？？？？？？？？？？？？？
        this->length=s.length;
        this->str=new char[length+1];
        strcpy(this->str,s.str);
    }
    return *this;
}
bool String::operator==(const String &s) const{
    if(length!=s.length)
        return false;
    for(size_t i=0;i<length;i++)
        if(this->str[i]!=s.str[i])
            return false;
    return true;
    //或return strcmp(this->str,s.str)==0;
}
bool String::operator!=(const String &s) const{
    return strcmp(this->str,s.str)!=0;
}
String String::copy() const {
    String s=*this;
    return s;
}
String String::operator+(const String &s) const{
    String temp;
    temp.length=this->length+s.length;
    temp.str=new char[temp.length+1];
    strcpy(temp.str,this->str);
    strcat(temp.str,s.str);
    return temp;
}
ostream& operator<<(ostream &out,const String &s){//作用域？？？？
    out<<s.str;
    return out;
}//？？？？？？？？？？？？？？？？？？？？？？？
int main(){
    String s("hello");
    cout<<s<<endl;
    cout<<s+" world"<<endl;
    cout<<(s=="hello")<<endl;
    s=s+" world";
    cout<<s<<endl;
    cout<<s[6]<<endl;
    String x=s.copy();
    cout<<x<<endl;
}
