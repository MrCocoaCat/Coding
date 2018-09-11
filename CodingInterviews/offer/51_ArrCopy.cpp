//
class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //  数组长度：      length:      the length of array numbers
    //  位置：      duplication: (Output) the duplicated number in the array number
    // 			Return value: true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication)
    {
        if( length <= 0 || numbers == NULL)
		{
			return false;
		}
		for(int i=0 ; i < length ; i++)
		{
			if(numbers[i] == i)
			{
				continue;
			}
			else
			{
				if( numbers[i] == numbers[numbers[i]] )
				{
					*duplication =  numbers[i] ;
					return true;
				}
				int temp = numbers[i];
				
				numbers[i] = numbers[temp];
				numbers[temp]=temp;
			}
		}
		return false;
        
    }
};