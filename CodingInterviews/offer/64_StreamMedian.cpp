
//大家好，我来了！欢迎点赞！
class Solution {
private:
        vector<int> min;
        vector<int> max;
public:
        void Insert(int num)
        {
           if(((min.size()+max.size())&1)==0)//偶数时 ，放入最小堆
           {
              if(max.size()>0 && num<max[0])
              {
                // push_heap (_First, _Last),要先在容器中加入数据，再调用push_heap ()
                 max.push_back(num);//先将元素压入容器
                 push_heap(max.begin(),max.end(),less<int>());//调整最大堆
                 num=max[0];//取出最大堆的最大值
                 //pop_heap(_First, _Last)，要先调用pop_heap()再在容器中删除数据
                 pop_heap(max.begin(),max.end(),less<int>());//删除最大堆的最大值
                 max.pop_back(); //在容器中删除
              }
              min.push_back(num);//压入最小堆
              push_heap(min.begin(),min.end(),greater<int>());//调整最小堆
           }
           else//奇数时候，放入最大堆
           {
              if(min.size()>0 && num>min[0])
              {
                // push_heap (_First, _Last),要先在容器中加入数据，再调用push_heap ()
                 min.push_back(num);//先将元素压入容器
                 push_heap(min.begin(),min.end(),greater<int>());//调整最小堆
                 num=min[0];//得到最小堆的最小值（堆顶）
                 //pop_heap(_First, _Last)，要先调用pop_heap()再在容器中删除数据
                 pop_heap(min.begin(),min.end(),greater<int>());//删除最小堆的最大值
                 min.pop_back(); //在容器中删除
              }
              max.push_back(num);//压入数字
              push_heap(max.begin(),max.end(),less<int>());//调整最大堆
           }   
        }


        /*获取中位数*/      
        double GetMedian()
        {
            int min.size()+max.size();
            if(size<=0) //没有元素，抛出异常
                return 0;//throw exception("No numbers are available");
            if((size&1)==0)//偶数时，去平均
                return (  (double)(max[0]+min[0])/2);
            else//奇数，去最小堆，因为最小堆数据保持和最大堆一样多，或者比最大堆多1个
                return min[0];
        }
};



//******************实现二****************************//
class Solution 
{
    priority_queue<int, vector<int>, less<int>  > p;//大根堆，头元素最大  
    priority_queue<int, vector<int>, greater<int>  > q; //小根堆，头元素最小
     
public:
    void Insert(int num)
	{
        if( p.empty() || num <= p.top())
		{
			p.push(num);	
		}	
        else
		{
			q.push(num);
		} 
        if( p.size() == q.size() + 2) //偶数时 ，放入最小堆
		{
			q.push(p.top());
			p.pop();
		}
        if( p.size() + 1 == q.size())//奇数时候，放入最大堆
		{
			p.push(q.top());
			q.pop();
		} 
    }

    double GetMedian()
	{ 
      return p.size() == q.size() ? (p.top() + q.top()) / 2.0 : p.top();
    }
};
