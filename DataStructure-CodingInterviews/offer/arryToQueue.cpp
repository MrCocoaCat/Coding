* 
* File name  : Aqueue.cpp 
* Function   : 数组实现循环队列  C++实现 
               数组a[0] 一端为head 
               1. 当 head==tail时为空 
               2. tail总指向 队尾元素的下一位置 
               3. tail MAX==head-1,也就是说,保留一个元素空间 
               4. 队列最多有 MAX-1 个元素 
               5. 当 (tail+1)% MAX ==head 时,队列满. 
               6. 队列长度 若 head < tail,为 tail - head 
                           若 head > tail,为 tail - head +MAX 
                  综上 队列长度= ( tail - head +MAX )% MAX 
* Created on : 2016年4月26日 
* Author     : beijiwei@qq.com 
* Copyright  : 欢迎大家和我一起交流学习，转载请保持源文件的完整性。 
任何单位和个人不经本人允许不得用于商业用途 
*/  
#define MAX 10  
#include <cstdio>  
#include <iostream>  
using namespace std;  
typedef int Elem_t;  
  
typedef struct Aqueue 
{  
    Elem_t data[MAX];  
    int head;  
    int tail;  
}Aqueue;  
  

void queue_init(Aqueue & Q)  
{  
    Q.head = 0;  
    Q.tail = 0;  
}  
void queue_clear(Aqueue & Q)  
{  
    Q.head = 0;  
    Q.tail = 0;  
}  
bool queue_get_head(Aqueue & Q, Elem_t &elem)  
{  
    if (Q.head == Q.tail) 
	{  
        cout << "queue is empty can not get" << endl;  
        return false;  
    }  
    elem = Q.data[Q.head];  
    return true;  
}  
  
bool queue_is_empty(Aqueue & Q)  
{  
    return (Q.head == Q.tail) ? true : false;  
}  
  
bool queue_is_full(Aqueue &Q)
{  
    if ((Q.tail + 1) % MAX == Q.head)  
	{
		 return true;  
	} 
    else  
	{
		 return false;  
	}
       
}  

bool queue_in(Aqueue & Q, Elem_t elem)  
{  
    if ( queue_is_full(Q) )
	{  
        cout << "can not in, queue is full" << endl;  
        return false;  
    }  
    if (Q.tail == MAX)
	{  
        Q.tail = 0;  
    }  
    Q.data[Q.tail++] = elem;  
      
    return true;  
} 

bool queue_out(Aqueue & Q, Elem_t &elem)  
{  
    if (Q.head == Q.tail) 
	{  
        cout << "queue is empty can not out" << endl;  
        return false;  
    }  
    elem = Q.data[Q.head++];  
	if (Q.head == MAX)  
	{
		 Q.head = 0;  
	}   
    return true;  
}  

int queue_get_length(Aqueue & Q)  
{  
    return  (Q.tail -Q.head + MAX)%MAX;  
} 

int main(int argc, char** argv)  
{  
    Aqueue aq;  
    Elem_t elem;  
    queue_init(aq);  
	cout << "queue is empty ? " << queue_is_empty(aq) << endl;  
    for (int i = 0; i < 11; i++) 
	{  
        queue_in(aq, i + 10);  
    }  
    cout << "The length of queue is  " << queue_get_length(aq) << endl;  
    queue_get_head(aq, elem);  
    cout << "The head of queue is  " << elem<< endl;  
    for (int i = 0; i <=5; i++)
	{  
        queue_out(aq, elem);  
        if (i == 3) 
		{  
            cout << "queue is empty ? " << queue_is_empty(aq) << endl;  
            cout << "The length of queue is  " << queue_get_length(aq) << endl;  
            queue_get_head(aq, elem);  
            cout << "The head of queue is  " << elem << endl;  
        }  
    }  
  
    for (int i = 0; i <=6; i++) 
	{  
        queue_in(aq, i + 20);  
    }  
	
    cout << "The length of queue is  " << queue_get_length(aq) << endl;  
    queue_get_head(aq, elem);
    cout << "The head of queue is  " << elem << endl;  
	system("pause");
    return 0;  
}  
  