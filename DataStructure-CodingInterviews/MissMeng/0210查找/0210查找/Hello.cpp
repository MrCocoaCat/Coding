#include <iostream>
#include <thread> //��
#include <mutex>
#include <algorithm>
void hello() //��
{
	std::cout<<std::this_thread::get_id()<<std::endl;;
	std::cout << "Hello Concurrent World\n";
}
int main()
{
	 []()->int{return 7;};
	int i=std::thread::hardware_concurrency();
	std::cout<<i<<std::endl;
	
	std::thread t(hello); //��
	if(!t.joinable())
	{
		throw std::logic_error("Erro thread");
	}

	std::cout<<t.get_id()<<std::endl;
	//t.join();  //�̵߳ȴ�
	t.detach();//�̷߳���

}