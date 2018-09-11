
//引用马客（Mark）的解题思路，马客没加注释，我用自己的理解加下注释，希望对你们有用，
//如有错误，见谅，我会及时修改。
//deque s中存储的是num的下标
class Solution
 {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> res;
        deque<int> s; //用这个来模仿窗口
        for(unsigned int i=0;i < num.size();++i) //i 表示位置
		{
            while(s.size() && num[s.back()] <= num[i])
            {
				//从后面依次弹出队列中比当前num值小的元素，
				//同时也能保证队列首元素为当前窗口最大值下标
				s.pop_back();
			}   
            while(s.size() && i - s.front() +1 > size) //s.front() 是当前队列的第一个元素的下标
            {
				//当 当前窗口移出队首元素所在的位置，即队首元素坐标对应的num不在窗口中，需要弹出
				//只有不在窗口位置了，才会对queue的开头操作
				s.pop_front();
			} 
			
			//把每次滑动的num下标加入队列，queue管理的是一个队列    
            s.push_back(i);     
  			//每次滑动一位，就会移动一下窗口，就有一个最大值出现，
			//但是必须从第一个窗口出现开始
			if(size && i + 1 >= size) 
			{
				//当滑动窗口首地址i大于等于size时才开始写入窗口最大值
				res.push_back( num[s.front()] ); //将最大值结果，放入数组中
			}    
        }
        return res;
    }
};