#include <iostream>
#include <thread> //①
#include <mutex>
#include <algorithm>
void hello() //②
{
	std::cout<<std::this_thread::get_id()<<std::endl;;
	std::cout << "Hello Concurrent World\n";
}
int main()
{
	 []()->int{return 7;};
	int i=std::thread::hardware_concurrency();
	std::cout<<i<<std::endl;
	
	std::thread t(hello); //③
	if(!t.joinable())
	{
		throw std::logic_error("Erro thread");
	}

	std::cout<<t.get_id()<<std::endl;
	//t.join();  //线程等待
	t.detach();//线程分离

}