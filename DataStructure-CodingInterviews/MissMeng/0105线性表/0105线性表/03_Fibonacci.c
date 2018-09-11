//#include<stdio.h>
//
//int Fibonacci(int n)
//{
//	if(n <=0)return -1;
//	if(n <=2)return 1;
//	return Fibonacci(n-1) + Fibonacci(n-2);
//}
//
//int Fibonacci2(int n)
//{
//	int fn1;
//	int fn2;
//	int fn;
//	int i;
//	if(n <=0)return -1;
//	if(n<=2)return 1;
//	fn1 = 1;
//	fn2 = 1;
//	
//	for(i = 3;i<=n;i++)
//	{
//		fn = fn1+fn2;
//		fn2 = fn1;
//		fn1 = fn;
//	}
//	return fn;
//}
//
//int main()
//{
//	int n = Fibonacci2(8);
//	printf("%d\n",n);
//	return 0;
//}