#include<iostream>
#include<stdlib.h>
using namespace std;
class Solution
{
	public:
		double Power(double base, int n) 
		{
			double res = 1.0;
			double curr = base;
			int exponent;			
			if(n>0)
			{
				exponent = n;
			}
			else if(n<0)
			{
				if(base==0)
				{
					// throw new RuntimeException("分母不能为0");  
				}
				exponent = -n;
			}
			else
			{// n==0
				return 1;// 0的0次方
			}
			while(exponent!=0)
			{
				if((exponent&1)==1)
					res*=curr;
				curr*=curr;// 翻倍
				exponent>>=1;// 右移一位
			}return n>=0?res:(1/res);
		}
};
int main(int argc,char *argv[])
{
	double a=atof(argv[1]);
	int b=atoi(argv[2]);
	Solution so;
	cout<<so.Power(a,b)<<endl;;
}
