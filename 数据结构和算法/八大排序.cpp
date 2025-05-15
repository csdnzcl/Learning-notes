#include <iostream>
#include <vector>
using namespace std;
//1. 选择排序---升序排列
void selectionSort(vector<int> &a){
    int n=a.size();
    for(int i=0;i<n;++i){
        int min=i;
        for(int j=i+1;j<n;++j){
            if(a[min]>a[j]){
                min=j;
            }
        }
        int tmp=a[min];
        a[min]=a[i];
        a[i]=tmp;
    }
}
//2. 冒泡排序---升序排列
void bubbleSort(vector<int> &a){
    int n=a.size();
    for(int i=n-1;i>=0;--i){
        for(int j=0;j<i;++j){
            if(a[j]>a[j+1]){
                int tmp=a[j+1];
                a[j+1]=a[j];
                a[j]=tmp;
            }
        }

    }
}
//3. 插入排序---升序排列
void insertionSort(vector<int> &a){
    int n=a.size();
    for(int i=1;i<n;++i){
        for(int j=i-1;j>=0;--j){
            if(a[j+1]<a[j]){
                int tmp=a[j+1];
                a[j+1]=a[j];
                a[j]=tmp;
            }else{
                break;
            }
        }
    }
}
//3. 插入排序---升序排列
void insertionSort2(vector<int> &a){
    for(int i=1;i<a.size();++i){
        int x=a[i];
        int j;
        for(j=i-1;j>=0;--j){
            if(x<a[j]){
                a[j+1]=a[j];
            }else{
                break;
            }
        }
        a[j+1]=x;
    }
}
//计数排序--升序
void countingSort(vector<int> &a, int m){
    //数据范围：[0,1,2,3,……,m]
    int n=a.size();
    int *count=new int[m+1];//使用new动态申请内存
    memset(count,0,sizeof(int)*(m+1));//memset初始化语法
    for(int i=0;i<n;++i){
        count[ a[i] ]++;
    }
    int idx=0;
    for(int v=0;v<=m;++v){
        while(count[v]>0){
            a[idx++]=v;
            count[v]--;
        }
    }
    delete [] count;
}
//5. 归并排序---数组实现
void merge(vector<int> &a,int l,int m,int r){
    int n1=m-l+1;
    int n2=r-m;
    int temp[n1+n2];
    for(int i=0;i<n1;++i){
        temp[i]=a[l+i];
    }
    for(int j=0;j<n2;++j){
        temp[n1+j]=a[m+1+j];
    }
    int i=0,j=n1,k=l;
    while(i<n1&&j<n1+n2){
        if(temp[i]<=temp[j]){
            a[k++]=temp[i++];
        }else{
            a[k++]=temp[j++];
        }
    }
    while(i<n1){
        a[k++]=temp[i++];
    }
    while(j<n1+n2){
        a[k++]=temp[j++];
    }
}
void mergeSort(vector<int> &a,int l,int r){
    if(l>=r){
        return ;
    }
    int m=(l+r)/2;
    mergeSort(a,l,m);
    mergeSort(a,m+1,r);
    merge(a,l,m,r);
}
//5.归并排序---链表实现
//合并两个有序链表
ListNode *mergeSort(ListNode *a,ListNode *b){
    a=sortList(a);//将a链表升序排序----递归调用，不断“均分”a，再将均分的a进行排序（运用了mergeSort函数）
    b=sortList(b);//将b链表升序排序
    ListNode *head=new ListNode();//虚拟头结点
    ListNode *tail=head;//定义一个游标节点,后续作为尾结点
    while(a||b){
        if(a==NULL){
            tail->next=b;
            break;
        }
        if(b==NULL){
            tail->next=a;
            break;
        }
        if(a->val<b->val){
            tail->next=a;
            a=a->next;
        }else{
            tail->next=b;
            b=b->next;
        }
        tail=tail->next;
        tail->next=NULL;
    }
    return head->next;
}
//将一个链表变成两个链表
ListNode* sortList(ListNode* head) {
    if(head==NULL){
        return NULL;
    }else if(head->next==NULL){
        return head;
    }
    ListNode *fast=head;
    ListNode *slow=head;
    ListNode *prev=NULL;
    while(fast){//快慢指针实现链表“均分”
        prev=slow;
        slow=slow->next;
        fast=fast->next;
        if(fast){
            fast=fast->next;
        }
    }
    //head->…………->prev->slow->……->……->fast
    prev->next=NULL;
    return mergeSort(head,slow);
}
int main(){
        vector<int> a;
        for (int i=0;i<10;++i){
            a.push_back(100-i);
        }
        for (int i=0;i<10;++i){
            cout << a[i] << " ";
        }
        cout<<endl;
        a[1]=91;
        a[2]=2;
        a[3]=55;
        insertionSort(a);
    for (int i=0;i<10;++i){
        cout << a[i] << " ";
    }
        return 0;
};