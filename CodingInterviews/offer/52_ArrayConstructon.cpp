链接：https://www.nowcoder.com/questionTerminal/94a4d381a68b47b7a8bed86f2975db46
/*******************************************************
<分析>：
解释下代码，设有数组大小为5。
对于第一个for循环
第一步：b[0] = 1;
第二步：b[1] = b[0] * a[0] = a[0]
第三步：b[2] = b[1] * a[1] = a[0] * a[1];
第四步：b[3] = b[2] * a[2] = a[0] * a[1] * a[2];
第五步：b[4] = b[3] * a[3] = a[0] * a[1] * a[2] * a[3];
然后对于第二个for循环
第一步
temp *= a[4] = a[4]; 
b[3] = b[3] * temp = a[0] * a[1] * a[2] * a[4];
第二步
temp *= a[3] = a[4] * a[3];
b[2] = b[2] * temp = a[0] * a[1] * a[4] * a[3];
第三步
temp *= a[2] = a[4] * a[3] * a[2]; 
b[1] = b[1] * temp = a[0] * a[4] * a[3] * a[2];
第四步
temp *= a[1] = a[4] * a[3] * a[2] * a[1]; 
b[0] = b[0] * temp = a[4] * a[3] * a[2] * a[1];
由此可以看出从b[4]到b[0]均已经得到正确计算。
***********************************************************/

class Solution 
{
public:
    vector<int> multiply(const vector<int>& A)
    {
        vector<int> b(A.size());
		b[0] = 1;
		for(int i=1; i<A.size() ;i++)
		{
			b[i]=b[i-1]*A[i-1];
		}
		int temp =1; //数组的后半段
		for(int j= A.size() -2; j >=0  ;j--)
		{
			temp = temp * A[j+1];
			b[j] = temp * b[j];
		}
		return b;
    }
};