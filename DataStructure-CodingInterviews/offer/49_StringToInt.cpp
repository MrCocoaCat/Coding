class Solution {
public:
    int StrToInt(string str)
    {
		int symbol=0;
		int i=0;
		int sum =0;
        if(str.length() == 0)
		{
			return false;
		}
		if(str[i] == '-')
		{
			symbol=-1;
			i++;
		}
		else if(str[i] == '+')
		{
			symbol=1;
			i++;
		}
		for(i;i < str.size();i++)
		{
			if(str[i] <'0' || strr[i] > '9' )
			{
				break;
			}
			sum = sum * 10 + str[i] - '0';
		}
		return symbol * sum;
    }
};