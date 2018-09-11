#include<iostream>
#include<vector>
using namespace std;
void  ReorderArry(vector<int>& array)
{
	int nBegin=0;
	int nEnd=array.size()-1;
        while(nBegin<nEnd)
        {
            //如果是奇数，则一直向后移动
            while(  nBegin<nEnd && ((array[nBegin]&0x1)!=0) )
            {
                nBegin++;
            }
            //如果是偶数，则向前移动  
             while( ((array[nEnd]&0x1)==0) && nBegin<nEnd )
            {
                nEnd--;
            }
            if(nBegin<nEnd)
            {
               array[nEnd]= array[nEnd]^array[nBegin];
               array[nBegin]= array[nEnd]^array[nBegin];
               array[nEnd]= array[nEnd]^array[nBegin];
            }
        }
}
int main()
{

	int arr[]={1,2,3,4,5};
	vector<int >array={1,2,3,4,5};
	ReorderArry(array);
	for(auto itr = array.begin();itr!=array.end();itr++)
	{
		cout<<*itr<<endl;
	}

return 0;
}
